#include "networkmanager.h"
#include <QHostAddress>
#include <QNetworkInterface>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDataStream>
#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
    , m_gameMode(LocalMode)
    , m_server(nullptr)
    , m_clientSocket(nullptr)
    , m_serverPort(12345)
{
}

NetworkManager::~NetworkManager()
{
    stopServer();
    disconnectFromServer();
}

bool NetworkManager::startServer(quint16 port)
{
    if (m_server && m_server->isListening()) {
        return true; // Already running
    }

    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, &NetworkManager::onNewConnection);

    if (!m_server->listen(QHostAddress::Any, port)) {
        qDebug() << QString("🚨 [Network Server] ERROR: Failed to start server on port %1")
                    .arg(port);
        qDebug() << QString("   └─ Reason: %1").arg(m_server->errorString());
        qDebug() << QString("   └─ Suggestion: Try a different port or check if another application is using port %1").arg(port);
        delete m_server;
        m_server = nullptr;
        return false;
    }

    m_serverPort = port;
    m_gameMode = ServerMode;
    qDebug() << QString("🏠 [Network Server] SUCCESS: Server started and listening on port %1")
                .arg(port);
    qDebug() << QString("   └─ Status: Ready to accept player connections");
    qDebug() << QString("   └─ Other players can connect to your IP address on port %1").arg(port);
    return true;
}

void NetworkManager::stopServer()
{
    if (m_server) {
        // Disconnect all clients
        for (QTcpSocket *client : m_clients) {
            client->disconnectFromHost();
            client->deleteLater();
        }
        m_clients.clear();

        m_server->close();
        m_server->deleteLater();
        m_server = nullptr;
    }
    m_gameMode = LocalMode;
}

bool NetworkManager::isServerRunning() const
{
    return m_server && m_server->isListening();
}

QString NetworkManager::getServerAddress() const
{
    if (!isServerRunning()) {
        return QString();
    }

    // Get the first non-localhost IP address
    const QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    for (const QHostAddress &address : addresses) {
        if (address != QHostAddress::LocalHost && address.toIPv4Address() != 0) {
            return address.toString();
        }
    }
    return QHostAddress(QHostAddress::LocalHost).toString();
}

bool NetworkManager::connectToServer(const QString &address, quint16 port)
{
    if (m_clientSocket && m_clientSocket->state() == QTcpSocket::ConnectedState) {
        return true; // Already connected
    }

    disconnectFromServer(); // Clean up any existing connection

    m_clientSocket = new QTcpSocket(this);
    connect(m_clientSocket, &QTcpSocket::connected, this, &NetworkManager::onConnectedToServer);
    connect(m_clientSocket, &QTcpSocket::disconnected, this, &NetworkManager::onDisconnectedFromServer);
    connect(m_clientSocket, &QTcpSocket::readyRead, this, &NetworkManager::onDataReceived);
    connect(m_clientSocket, &QTcpSocket::errorOccurred, this, &NetworkManager::onSocketError);

    m_clientSocket->connectToHost(address, port);
    m_gameMode = ClientMode;
    
    qDebug() << QString("🔗 [Network Client] CONNECTING: Attempting to connect to game server");
    qDebug() << QString("   └─ Server Address: %1").arg(address);
    qDebug() << QString("   └─ Server Port: %1").arg(port);
    qDebug() << QString("   └─ Timeout: 5 seconds");
    
    return m_clientSocket->waitForConnected(5000); // 5 second timeout
}

void NetworkManager::disconnectFromServer()
{
    if (m_clientSocket) {
        m_clientSocket->disconnectFromHost();
        m_clientSocket->deleteLater();
        m_clientSocket = nullptr;
    }
    if (m_gameMode == ClientMode) {
        m_gameMode = LocalMode;
    }
}

bool NetworkManager::isConnectedToServer() const
{
    return m_clientSocket && m_clientSocket->state() == QTcpSocket::ConnectedState;
}

void NetworkManager::sendGameMove(int fromHand, int toHand, int playerId)
{
    QJsonObject data;
    data["fromHand"] = fromHand;
    data["toHand"] = toHand;
    data["playerId"] = playerId;
    sendMessage(GameMove, data);
}

void NetworkManager::sendGameState(const QJsonObject &gameState)
{
    sendMessage(GameState, gameState);
}

void NetworkManager::sendMessage(MessageType type, const QJsonObject &data)
{
    QByteArray message = createMessage(type, data);
    
    if (m_gameMode == ServerMode) {
        // Send to all connected clients
        for (QTcpSocket *client : m_clients) {
            if (client->state() == QTcpSocket::ConnectedState) {
                client->write(message);
            }
        }
    } else if (m_gameMode == ClientMode && isConnectedToServer()) {
        // Send to server
        m_clientSocket->write(message);
    }
}

void NetworkManager::onNewConnection()
{
    if (!m_server) return;

    QTcpSocket *client = m_server->nextPendingConnection();
    connect(client, &QTcpSocket::disconnected, this, &NetworkManager::onClientDisconnected);
    connect(client, &QTcpSocket::readyRead, this, &NetworkManager::onDataReceived);
    
    m_clients.append(client);
    
    QString clientInfo = QString("%1:%2").arg(client->peerAddress().toString()).arg(client->peerPort());
    emit clientConnected(clientInfo);
    
    qDebug() << QString("👥 [Network Server] NEW PLAYER: Connection established");
    qDebug() << QString("   └─ Player IP: %1").arg(client->peerAddress().toString());
    qDebug() << QString("   └─ Player Port: %2").arg(client->peerPort());
    qDebug() << QString("   └─ Total Connected Players: %1").arg(m_clients.size());
}

void NetworkManager::onClientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (client) {
        QString clientInfo = QString("%1:%2").arg(client->peerAddress().toString()).arg(client->peerPort());
        m_clients.removeAll(client);
        client->deleteLater();
        emit clientDisconnected();
        qDebug() << QString("👋 [Network Server] PLAYER DISCONNECTED");
        qDebug() << QString("   └─ Player: %1").arg(clientInfo);
        qDebug() << QString("   └─ Remaining Connected Players: %1").arg(m_clients.size());
    }
}

void NetworkManager::onDataReceived()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    QByteArray data = socket->readAll();
    processMessage(data);
}

void NetworkManager::onSocketError()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        QString errorMsg = socket->errorString();
        QString roleMsg = (m_gameMode == ServerMode) ? "[Network Server]" : "[Network Client]";
        
        emit connectionError(errorMsg);
        qDebug() << QString("⚠️  %1 CONNECTION ERROR").arg(roleMsg);
        qDebug() << QString("   └─ Error Details: %1").arg(errorMsg);
        
        // Provide helpful suggestions based on common error types
        if (errorMsg.contains("Connection refused", Qt::CaseInsensitive)) {
            qDebug() << QString("   └─ Suggestion: Check if the server is running and the port is correct");
        } else if (errorMsg.contains("Network unreachable", Qt::CaseInsensitive)) {
            qDebug() << QString("   └─ Suggestion: Check your network connection and firewall settings");
        } else if (errorMsg.contains("Host not found", Qt::CaseInsensitive)) {
            qDebug() << QString("   └─ Suggestion: Verify the server IP address is correct");
        }
    }
}

void NetworkManager::processMessage(const QByteArray &data)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    
    if (error.error != QJsonParseError::NoError) {
        qDebug() << QString("📨 [Network Protocol] MESSAGE PARSING ERROR");
        qDebug() << QString("   └─ Error: %1").arg(error.errorString());
        qDebug() << QString("   └─ Raw Data Length: %1 bytes").arg(data.length());
        qDebug() << QString("   └─ This indicates a protocol mismatch or corrupted data");
        return;
    }

    QJsonObject message = doc.object();
    MessageType type = static_cast<MessageType>(message["type"].toInt());
    QJsonObject messageData = message["data"].toObject();

    switch (type) {
    case GameMove:
        emit gameMoveReceived(messageData["fromHand"].toInt(), 
                             messageData["toHand"].toInt(), 
                             messageData["playerId"].toInt());
        break;
    case GameState:
        emit gameStateReceived(messageData);
        break;
    default:
        emit messageReceived(type, messageData);
        break;
    }
}

QByteArray NetworkManager::createMessage(MessageType type, const QJsonObject &data)
{
    QJsonObject message;
    message["type"] = static_cast<int>(type);
    message["data"] = data;
    
    QJsonDocument doc(message);
    return doc.toJson(QJsonDocument::Compact);
}

void NetworkManager::onConnectedToServer()
{
    qDebug() << QString("🔗 [Network Client] CONNECTION SUCCESS: Connected to game server");
    qDebug() << QString("   └─ Server Address: %1").arg(m_clientSocket->peerAddress().toString());
    qDebug() << QString("   └─ Server Port: %1").arg(m_clientSocket->peerPort());
    qDebug() << QString("   └─ Ready to play multiplayer Chopsticks!");
    
    emit connectedToServer();
}

void NetworkManager::onDisconnectedFromServer()
{
    qDebug() << QString("👋 [Network Client] DISCONNECTED: Lost connection to game server");
    if (m_clientSocket) {
        qDebug() << QString("   └─ Last Server: %1:%2")
                    .arg(m_clientSocket->peerAddress().toString())
                    .arg(m_clientSocket->peerPort());
    }
    qDebug() << QString("   └─ You can try reconnecting or switch to local play");
    
    emit disconnectedFromServer();
}
