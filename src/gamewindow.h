#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "player.h"
#include "networkdialog.h"

class AIPlayer;
class NetworkManager;

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr, NetworkManager* networkManager = nullptr);
    void setGameMode(NetworkDialog::GameType gameType, int aiDifficulty = 1);
    void startGame();
    void updateDisplay();
    // Allow setting network manager after construction
    void setNetworkManager(NetworkManager* networkManager);

    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void changeEvent(QEvent* event) override;

private:
    Player* player1;
    Player* player2;
    Player* currentPlayer;
    QLabel* instructionsLabel;
    QLabel* player1Label;
    QLabel* player2Label;
    QLabel* turnLabel;
    QLabel* gameModeLabel;  // New: Shows current game mode
    QPushButton* p1LeftButton;
    QPushButton* p1RightButton;
    QPushButton* p2LeftButton;
    QPushButton* p2RightButton;
    int selectedMyHand;
    
    // Game mode configuration
    NetworkDialog::GameType m_gameType;
    int m_aiDifficulty;
    AIPlayer* m_aiPlayer;
    NetworkManager* m_networkManager;

    // Multiplayer turn management
    int m_localPlayerId = 1; // 1 for server, 2 for client
    bool m_isMyTurn = true;

    void selectMyHand(int handIndex);
    void selectOpponentHand(int handIndex, bool isPlayer1Hand);
    void checkWin();
    void setupGameMode();
    void updateGameModeDisplay();
    
    // AI integration
    void triggerAIMove();
    
private slots:
    void onAIMove(int fromHand, int toHand);
    void onAISplit();
    // Network multiplayer: handle move received from network
    void onNetworkMoveReceived(int fromHand, int toHand, int playerId);
    void onNetworkGameStateReceived(const QJsonObject& state);
};

#endif // GAMEWINDOW_H