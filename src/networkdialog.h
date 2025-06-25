#ifndef NETWORKDIALOG_H
#define NETWORKDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSpinBox>
#include <QGroupBox>
#include <QTextEdit>
#include <QTimer>
#include <QComboBox>
#include "networkmanager.h"

class NetworkDialog : public QDialog
{
    Q_OBJECT

public:
    enum GameType {
        LocalTwoPlayer,    // Two humans on same computer
        SinglePlayerVsAI,  // One human vs computer
        NetworkServer,     // Host network game
        NetworkClient      // Join network game
    };

    explicit NetworkDialog(QWidget *parent = nullptr);
    
    GameType getSelectedGameType() const;
    NetworkManager::GameMode getNetworkMode() const;
    int getAIDifficulty() const; // 0=Easy, 1=Medium, 2=Hard
    QString getServerAddress() const;
    quint16 getServerPort() const;
    
signals:
    void gameConfigured(GameType gameType, NetworkManager::GameMode networkMode, 
                       const QString &address, quint16 port, int aiDifficulty);

private slots:
    void onModeChanged();
    void onStartServer();
    void onConnectToServer();
    void onClientConnected(const QString &clientInfo);
    void onConnectedToServer();
    void onConnectionError(const QString &error);
    void updateServerInfo();

private:
    void setupUI();
    void updateUI();
    
    // UI Components
    QVBoxLayout *m_mainLayout;
    QButtonGroup *m_gameTypeGroup;
    QRadioButton *m_localTwoPlayerRadio;
    QRadioButton *m_singlePlayerVsAIRadio;
    QRadioButton *m_networkServerRadio;
    QRadioButton *m_networkClientRadio;
    
    // AI settings
    QGroupBox *m_aiGroup;
    QComboBox *m_aiDifficultyCombo;
    
    // Server settings
    QGroupBox *m_serverGroup;
    QSpinBox *m_portSpinBox;
    QPushButton *m_startServerButton;
    QLabel *m_serverStatusLabel;
    QTextEdit *m_serverInfoText;
    QTimer *m_updateTimer;
    
    // Client settings
    QGroupBox *m_clientGroup;
    QLineEdit *m_addressLineEdit;
    QSpinBox *m_clientPortSpinBox;
    QPushButton *m_connectButton;
    QLabel *m_clientStatusLabel;
    
    // Control buttons
    QPushButton *m_okButton;
    QPushButton *m_cancelButton;
    
    NetworkManager *m_networkManager;
    GameType m_currentGameType;
};

#endif // NETWORKDIALOG_H
