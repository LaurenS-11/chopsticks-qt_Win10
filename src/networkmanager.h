#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

class NetworkManager : public QObject
{
    Q_OBJECT

public:
    enum GameMode {
        LocalMode,
        ServerMode,
        ClientMode
    };

    enum MessageType {
        GameMove,
        GameState,
        PlayerJoined,
        PlayerLeft,
        GameStart,
        GameEnd
    };

    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    // Server functionality
    bool startServer(quint16 port = 8080);
    void stopServer();
    bool isServerRunning() const;
    QString getServerAddress() const;

    // Client functionality
    bool connectToServer(const QString &address, quint16 port = 8080);
    void disconnectFromServer();
    bool isConnectedToServer() const;

    // Game communication
    void sendGameState(const QJsonObject &gameState);
    void sendMessage(MessageType type, const QJsonObject &data);

    GameMode getCurrentMode() const { return m_gameMode; }
    void setGameMode(GameMode mode) { m_gameMode = mode; }

signals:
    // Server signals
    void clientConnected(const QString &clientInfo);
    void clientDisconnected();
    void requestSendGameState();
    
    // Client signals
    void connectedToServer();
    void disconnectedFromServer();
    void connectionError(const QString &error);
    
    // Game signals
    void gameStateReceived(const QJsonObject &gameState);
    void messageReceived(MessageType type, const QJsonObject &data);

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onDataReceived();
    void onSocketError();
    void onConnectedToServer();
    void onDisconnectedFromServer();

private:
    void processMessage(const QByteArray &data);
    QByteArray createMessage(MessageType type, const QJsonObject &data);
    
    GameMode m_gameMode;
    QTcpServer *m_server;
    QTcpSocket *m_clientSocket;  // For client mode
    QList<QTcpSocket*> m_clients; // For server mode
    quint16 m_serverPort;
    QByteArray m_incomingBuffer; // Buffer for newline-delimited JSON messages
};

#endif // NETWORKMANAGER_H
