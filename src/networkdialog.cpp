#include "networkdialog.h"
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>
#include <QHostAddress>
#include <QDebug>

NetworkDialog::NetworkDialog(QWidget *parent)
    : QDialog(parent)
    , m_networkManager(new NetworkManager(this))
    , m_currentGameType(LocalTwoPlayer)
{
    setWindowTitle("Game Setup - Choose Your Adventure!");
    setModal(true);
    resize(520, 450);
    
    setupUI();
    updateUI();
    
    // Connect network manager signals
    connect(m_networkManager, &NetworkManager::clientConnected, 
            this, &NetworkDialog::onClientConnected);
    connect(m_networkManager, &NetworkManager::connectedToServer, 
            this, &NetworkDialog::onConnectedToServer);
    connect(m_networkManager, &NetworkManager::connectionError, 
            this, &NetworkDialog::onConnectionError);
    
    // Setup update timer for server info
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &NetworkDialog::updateServerInfo);
}

void NetworkDialog::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // Game type selection
    QGroupBox *gameTypeGroup = new QGroupBox("🎮 Game Mode Selection");
    QVBoxLayout *gameTypeLayout = new QVBoxLayout(gameTypeGroup);
    
    m_gameTypeGroup = new QButtonGroup(this);
    m_localTwoPlayerRadio = new QRadioButton("👥 Local Two Player (Same Computer)");
    m_singlePlayerVsAIRadio = new QRadioButton("🤖 Single Player vs Computer");
    m_networkServerRadio = new QRadioButton("🏠 Host Network Game (Create Server)");
    m_networkClientRadio = new QRadioButton("🔗 Join Network Game (Connect to Server)");
    
    m_gameTypeGroup->addButton(m_localTwoPlayerRadio, LocalTwoPlayer);
    m_gameTypeGroup->addButton(m_singlePlayerVsAIRadio, SinglePlayerVsAI);
    m_gameTypeGroup->addButton(m_networkServerRadio, NetworkServer);
    m_gameTypeGroup->addButton(m_networkClientRadio, NetworkClient);
    
    m_localTwoPlayerRadio->setChecked(true);
    
    gameTypeLayout->addWidget(m_localTwoPlayerRadio);
    gameTypeLayout->addWidget(m_singlePlayerVsAIRadio);
    gameTypeLayout->addWidget(m_networkServerRadio);
    gameTypeLayout->addWidget(m_networkClientRadio);
    
    connect(m_gameTypeGroup, QOverload<int>::of(&QButtonGroup::idClicked),
            this, &NetworkDialog::onModeChanged);
    
    // AI settings
    m_aiGroup = new QGroupBox("🤖 Computer Player Settings");
    QHBoxLayout *aiLayout = new QHBoxLayout(m_aiGroup);
    
    aiLayout->addWidget(new QLabel("Difficulty:"));
    m_aiDifficultyCombo = new QComboBox();
    m_aiDifficultyCombo->addItem("😊 Easy - Learning the ropes");
    m_aiDifficultyCombo->addItem("😐 Medium - Balanced challenge");
    m_aiDifficultyCombo->addItem("😈 Hard - Prepare to lose!");
    m_aiDifficultyCombo->setCurrentIndex(1); // Default to Medium
    aiLayout->addWidget(m_aiDifficultyCombo);
    aiLayout->addStretch();
    
    // Server settings
    m_serverGroup = new QGroupBox("Server Settings");
    QGridLayout *serverLayout = new QGridLayout(m_serverGroup);
    
    serverLayout->addWidget(new QLabel("Port:"), 0, 0);
    m_portSpinBox = new QSpinBox();
    m_portSpinBox->setRange(1024, 65535);
    m_portSpinBox->setValue(12345);
    serverLayout->addWidget(m_portSpinBox, 0, 1);
    
    m_startServerButton = new QPushButton("Start Server");
    connect(m_startServerButton, &QPushButton::clicked, this, &NetworkDialog::onStartServer);
    serverLayout->addWidget(m_startServerButton, 0, 2);
    
    m_serverStatusLabel = new QLabel("Server not started");
    serverLayout->addWidget(m_serverStatusLabel, 1, 0, 1, 3);
    
    m_serverInfoText = new QTextEdit();
    m_serverInfoText->setMaximumHeight(100);
    m_serverInfoText->setReadOnly(true);
    serverLayout->addWidget(m_serverInfoText, 2, 0, 1, 3);
    
    // Client settings
    m_clientGroup = new QGroupBox("Client Settings");
    QGridLayout *clientLayout = new QGridLayout(m_clientGroup);
    
    clientLayout->addWidget(new QLabel("Server Address:"), 0, 0);
    m_addressLineEdit = new QLineEdit();
    m_addressLineEdit->setPlaceholderText("192.168.1.100 or localhost");
    clientLayout->addWidget(m_addressLineEdit, 0, 1);
    
    clientLayout->addWidget(new QLabel("Port:"), 1, 0);
    m_clientPortSpinBox = new QSpinBox();
    m_clientPortSpinBox->setRange(1024, 65535);
    m_clientPortSpinBox->setValue(12345);
    clientLayout->addWidget(m_clientPortSpinBox, 1, 1);
    
    m_connectButton = new QPushButton("Connect to Server");
    connect(m_connectButton, &QPushButton::clicked, this, &NetworkDialog::onConnectToServer);
    clientLayout->addWidget(m_connectButton, 1, 2);
    
    m_clientStatusLabel = new QLabel("Not connected");
    clientLayout->addWidget(m_clientStatusLabel, 2, 0, 1, 3);
    
    // Control buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    m_okButton = new QPushButton("Start Game");
    m_cancelButton = new QPushButton("Cancel");
    
    connect(m_okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);
    
    // Add to main layout
    m_mainLayout->addWidget(gameTypeGroup);
    m_mainLayout->addWidget(m_aiGroup);
    m_mainLayout->addWidget(m_serverGroup);
    m_mainLayout->addWidget(m_clientGroup);
    m_mainLayout->addStretch();
    m_mainLayout->addLayout(buttonLayout);
}

void NetworkDialog::updateUI()
{
    m_currentGameType = static_cast<GameType>(m_gameTypeGroup->checkedId());
    
    // Show/hide appropriate groups
    m_aiGroup->setVisible(m_currentGameType == SinglePlayerVsAI);
    m_serverGroup->setVisible(m_currentGameType == NetworkServer);
    m_clientGroup->setVisible(m_currentGameType == NetworkClient);
    
    // Update OK button state
    bool canStart = false;
    switch (m_currentGameType) {
    case LocalTwoPlayer:
    case SinglePlayerVsAI:
        canStart = true;
        break;
    case NetworkServer:
        canStart = m_networkManager->isServerRunning();
        break;
    case NetworkClient:
        canStart = m_networkManager->isConnectedToServer();
        break;
    }
    
    m_okButton->setEnabled(canStart);
    
    // Update button text based on game type
    switch (m_currentGameType) {
    case LocalTwoPlayer:
        m_okButton->setText("🎮 Start Local Game");
        break;
    case SinglePlayerVsAI:
        m_okButton->setText("🤖 Challenge Computer");
        break;
    case NetworkServer:
        m_okButton->setText("🏠 Start Network Game");
        break;
    case NetworkClient:
        m_okButton->setText("🔗 Join Network Game");
        break;
    }
}

void NetworkDialog::onModeChanged()
{
    updateUI();
}

void NetworkDialog::onStartServer()
{
    quint16 port = static_cast<quint16>(m_portSpinBox->value());
    
    qDebug() << QString("🏠 [Setup Dialog] User attempting to start server on port %1").arg(port);
    
    if (m_networkManager->startServer(port)) {
        m_serverStatusLabel->setText("✅ Server running on port " + QString::number(port));
        m_startServerButton->setText("Stop Server");
        m_startServerButton->disconnect();
        connect(m_startServerButton, &QPushButton::clicked, this, [this]() {
            qDebug() << QString("🏠 [Setup Dialog] User stopping server");
            m_networkManager->stopServer();
            m_serverStatusLabel->setText("Server stopped");
            m_startServerButton->setText("Start Server");
            m_startServerButton->disconnect();
            connect(m_startServerButton, &QPushButton::clicked, this, &NetworkDialog::onStartServer);
            m_updateTimer->stop();
            m_serverInfoText->clear();
            updateUI();
        });
        
        m_updateTimer->start(1000); // Update every second
        updateServerInfo();
        updateUI();
    } else {
        qDebug() << QString("🚨 [Setup Dialog] Failed to start server on port %1").arg(port);
        QMessageBox::warning(this, "Server Error", 
            QString("Failed to start server on port %1.\n\n"
                   "Possible solutions:\n"
                   "• Try a different port number\n"
                   "• Check if another program is using this port\n"
                   "• Make sure your firewall allows the connection").arg(port));
    }
}

void NetworkDialog::onConnectToServer()
{
    QString address = m_addressLineEdit->text().trimmed();
    if (address.isEmpty()) {
        QMessageBox::warning(this, "Connection Error", 
            "Please enter a server address.\n\n"
            "Examples:\n"
            "• 192.168.1.100 (local network)\n"
            "• localhost (same computer)\n"
            "• yourfriend.example.com (internet)");
        return;
    }
    
    quint16 port = static_cast<quint16>(m_clientPortSpinBox->value());
    
    qDebug() << QString("🔗 [Setup Dialog] User attempting to connect to %1:%2").arg(address).arg(port);
    
    m_clientStatusLabel->setText("🔄 Connecting...");
    m_connectButton->setEnabled(false);
    
    if (m_networkManager->connectToServer(address, port)) {
        // Connection successful, onConnectedToServer will be called
        qDebug() << QString("🔗 [Setup Dialog] Connection initiated successfully");
    } else {
        qDebug() << QString("🚨 [Setup Dialog] Connection failed immediately");
        m_clientStatusLabel->setText("❌ Connection failed");
        m_connectButton->setEnabled(true);
        QMessageBox::warning(this, "Connection Failed", 
            QString("Could not connect to %1:%2\n\n"
                   "Please check:\n"
                   "• Server address is correct\n"
                   "• Server is running and accepting connections\n"
                   "• Port number matches the server\n"
                   "• Network connection is working").arg(address).arg(port));
    }
}

void NetworkDialog::onClientConnected(const QString &clientInfo)
{
    qDebug() << QString("👥 [Setup Dialog] New player joined server: %1").arg(clientInfo);
    
    QString info = m_serverInfoText->toPlainText();
    info += QString("✅ Player joined: %1\n").arg(clientInfo);
    m_serverInfoText->setPlainText(info);
    m_serverInfoText->moveCursor(QTextCursor::End);
    updateUI();
}

void NetworkDialog::onConnectedToServer()
{
    qDebug() << QString("🔗 [Setup Dialog] Successfully connected to server");
    
    m_clientStatusLabel->setText("✅ Connected and ready to play!");
    m_connectButton->setText("Disconnect");
    m_connectButton->setEnabled(true);
    m_connectButton->disconnect();
    connect(m_connectButton, &QPushButton::clicked, this, [this]() {
        qDebug() << QString("🔗 [Setup Dialog] User disconnecting from server");
        m_networkManager->disconnectFromServer();
        m_clientStatusLabel->setText("Disconnected");
        m_connectButton->setText("Connect to Server");
        m_connectButton->disconnect();
        connect(m_connectButton, &QPushButton::clicked, this, &NetworkDialog::onConnectToServer);
        updateUI();
    });
    updateUI();
}

void NetworkDialog::onConnectionError(const QString &error)
{
    qDebug() << QString("⚠️  [Setup Dialog] Connection error: %1").arg(error);
    
    m_clientStatusLabel->setText("❌ Connection failed");
    m_connectButton->setEnabled(true);
    
    QString userMessage = "Connection Error: " + error + "\n\n";
    if (error.contains("Connection refused", Qt::CaseInsensitive)) {
        userMessage += "The server may not be running or may be using a different port.";
    } else if (error.contains("Network unreachable", Qt::CaseInsensitive)) {
        userMessage += "Check your network connection and firewall settings.";
    } else if (error.contains("Host not found", Qt::CaseInsensitive)) {
        userMessage += "Please verify the server address is correct.";
    } else {
        userMessage += "Please check your connection settings and try again.";
    }
    
    QMessageBox::warning(this, "Network Error", userMessage);
}

void NetworkDialog::updateServerInfo()
{
    if (!m_networkManager->isServerRunning()) {
        return;
    }
    
    QString serverAddress = m_networkManager->getServerAddress();
    quint16 serverPort = static_cast<quint16>(m_portSpinBox->value());
    
    QString info = "🌐 Server Information\n";
    info += "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
    info += QString("📍 Address: %1\n").arg(serverAddress);
    info += QString("🔌 Port: %1\n").arg(serverPort);
    info += "\n📋 Share this connection info with friends:\n";
    info += QString("🔗 %1:%2\n").arg(serverAddress).arg(serverPort);
    info += "\n💡 Tips for other players:\n";
    info += "• Make sure you're on the same network\n";
    info += "• Check that your firewall allows the connection\n";
    info += "• Use the exact address and port shown above\n";
    
    // Note: We can't easily get the actual client count without more complex tracking
    // This is a placeholder that could be enhanced later
    info += "\n👥 Server Status: Ready for connections\n";
    
    m_serverInfoText->setPlainText(info);
}

NetworkDialog::GameType NetworkDialog::getSelectedGameType() const
{
    return m_currentGameType;
}

NetworkManager::GameMode NetworkDialog::getNetworkMode() const
{
    switch (m_currentGameType) {
    case NetworkServer:
        return NetworkManager::ServerMode;
    case NetworkClient:
        return NetworkManager::ClientMode;
    default:
        return NetworkManager::LocalMode;
    }
}

int NetworkDialog::getAIDifficulty() const
{
    return m_aiDifficultyCombo->currentIndex();
}

QString NetworkDialog::getServerAddress() const
{
    return m_addressLineEdit->text().trimmed();
}

quint16 NetworkDialog::getServerPort() const
{
    return m_currentGameType == NetworkClient ? 
           static_cast<quint16>(m_clientPortSpinBox->value()) : 
           static_cast<quint16>(m_portSpinBox->value());
}

void NetworkDialog::addDebugButton(QPushButton *debugButton)
{
    // Find the button layout and add the debug button before OK/Cancel
    QHBoxLayout *buttonLayout = qobject_cast<QHBoxLayout*>(m_mainLayout->itemAt(m_mainLayout->count() - 1)->layout());
    if (buttonLayout) {
        // Remove the stretch
        QLayoutItem *stretch = buttonLayout->takeAt(0);
        delete stretch;
        
        // Add debug button, then stretch, then OK/Cancel buttons
        buttonLayout->insertWidget(0, debugButton);
        buttonLayout->insertStretch(1);
    }
}
