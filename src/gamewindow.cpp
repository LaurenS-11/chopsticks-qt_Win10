#include "gamewindow.h"
#include "player.h"
#include "aiplayer.h"
#include "networkmanager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QResizeEvent>
#include <QFont>
#include <QEvent>
#include <QWindowStateChangeEvent>
#include <QTimer>

GameWindow::GameWindow(QWidget *parent, NetworkManager* networkManager)
    : QMainWindow(parent), player1(new Player()), player2(new Player()), currentPlayer(player1), selectedMyHand(-1),
      m_gameType(NetworkDialog::LocalTwoPlayer), m_aiDifficulty(1), m_aiPlayer(nullptr), m_networkManager(networkManager)
{
    setWindowTitle("Chopsticks Game");
    // setFixedSize(400, 350); // Remove or comment out this line
    setMinimumSize(600, 500); // Increased minimum size for better spacing
    resize(700, 600); // Set default window size - larger and more comfortable

    QVBoxLayout *mainLayout = new QVBoxLayout;

    instructionsLabel = new QLabel("Select your hand, then tap an opponent's hand or your own dead hand to split.");
    mainLayout->addWidget(instructionsLabel);

    // Player 1 hand buttons
    QHBoxLayout *p1HandLayout = new QHBoxLayout;
    p1LeftButton = new QPushButton("P1 Left");
    p1RightButton = new QPushButton("P1 Right");
    p1LeftButton->setStyleSheet("background: #ffe0b2;");
    p1RightButton->setStyleSheet("background: #ffe0b2;");
    connect(p1LeftButton, &QPushButton::clicked, this, [this]() {
        if (currentPlayer == player1 && selectedMyHand == -1)
            selectMyHand(0);
        else if (selectedMyHand != -1)
            selectOpponentHand(0, true);
    });
    connect(p1RightButton, &QPushButton::clicked, this, [this]() {
        if (currentPlayer == player1 && selectedMyHand == -1)
            selectMyHand(1);
        else if (selectedMyHand != -1)
            selectOpponentHand(1, true);
    });
    p1HandLayout->addWidget(p1LeftButton);
    p1HandLayout->addWidget(p1RightButton);

    player1Label = new QLabel;
    mainLayout->addWidget(player1Label);
    mainLayout->addLayout(p1HandLayout);

    // Player 2 hand buttons
    QHBoxLayout *p2HandLayout = new QHBoxLayout;
    p2LeftButton = new QPushButton("P2 Left");
    p2RightButton = new QPushButton("P2 Right");
    p2LeftButton->setStyleSheet("background: #b3e5fc;");
    p2RightButton->setStyleSheet("background: #b3e5fc;");
    connect(p2LeftButton, &QPushButton::clicked, this, [this]() {
        if (currentPlayer == player2 && selectedMyHand == -1)
            selectMyHand(0);
        else if (selectedMyHand != -1)
            selectOpponentHand(0, false);
    });
    connect(p2RightButton, &QPushButton::clicked, this, [this]() {
        if (currentPlayer == player2 && selectedMyHand == -1)
            selectMyHand(1);
        else if (selectedMyHand != -1)
            selectOpponentHand(1, false);
    });
    p2HandLayout->addWidget(p2LeftButton);
    p2HandLayout->addWidget(p2RightButton);

    player2Label = new QLabel;
    mainLayout->addWidget(player2Label);
    mainLayout->addLayout(p2HandLayout);

    turnLabel = new QLabel;
    mainLayout->addWidget(turnLabel);

    // Game mode display
    gameModeLabel = new QLabel("Game Mode: Local Two Player");
    gameModeLabel->setStyleSheet("color: #666; font-style: italic;");
    mainLayout->addWidget(gameModeLabel);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    p1LeftButton->setMinimumSize(120, 100); // Increased button size for better visibility
    p1RightButton->setMinimumSize(120, 100);
    p2LeftButton->setMinimumSize(120, 100);
    p2RightButton->setMinimumSize(120, 100);

    // Set size policy for buttons
    p1LeftButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p1RightButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p2LeftButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    p2RightButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Set default font
    QFont defaultFont;
    defaultFont.setPointSize(10); // Small default font
    p1LeftButton->setFont(defaultFont);
    p1RightButton->setFont(defaultFont);
    p2LeftButton->setFont(defaultFont);
    p2RightButton->setFont(defaultFont);

    startGame();
}

void GameWindow::startGame()
{
    player1->reset();
    player2->reset();
    currentPlayer = player1;
    selectedMyHand = -1;
    
    // Clear debug logging for new game
    QString modeDescription;
    switch (m_gameType) {
        case NetworkDialog::LocalTwoPlayer:
            modeDescription = "Local Two Player";
            break;
        case NetworkDialog::SinglePlayerVsAI:
            {
                QString difficulty;
                switch (m_aiDifficulty) {
                    case 0: difficulty = "Easy 😊"; break;
                    case 1: difficulty = "Medium 😐"; break;
                    case 2: difficulty = "Hard 😈"; break;
                    default: difficulty = "Unknown"; break;
                }
                modeDescription = QString("Single Player vs AI (%1)").arg(difficulty);
            }
            break;
        case NetworkDialog::NetworkServer:
            modeDescription = "Network Server";
            break;
        case NetworkDialog::NetworkClient:
            modeDescription = "Network Client";
            break;
    }
    
    qDebug() << QString("🎮 [New Game] Starting fresh Chopsticks game");
    qDebug() << QString("   └─ Mode: %1").arg(modeDescription);
    qDebug() << QString("   └─ Both players start with 1 finger on each hand");
    qDebug() << QString("   └─ %1 goes first").arg(m_gameType == NetworkDialog::SinglePlayerVsAI ? "You (Human)" : "Player 1");
    
    updateDisplay();
    checkWin();
}

void GameWindow::updateDisplay()
{
    // Update player labels based on game mode
    if (m_gameType == NetworkDialog::SinglePlayerVsAI) {
        QString difficulty;
        switch (m_aiDifficulty) {
            case 0: difficulty = "Easy 😊"; break;
            case 1: difficulty = "Medium 😐"; break;
            case 2: difficulty = "Hard 😈"; break;
            default: difficulty = "Unknown"; break;
        }
        player1Label->setText(QString("You (Human): Left %1 | Right %2")
                              .arg(player1->getLeftHand())
                              .arg(player1->getRightHand()));
        player2Label->setText(QString("AI (%1): Left %2 | Right %3")
                              .arg(difficulty)
                              .arg(player2->getLeftHand())
                              .arg(player2->getRightHand()));
    } else {
        player1Label->setText(QString("Player 1: Left %1 | Right %2")
                              .arg(player1->getLeftHand())
                              .arg(player1->getRightHand()));
        player2Label->setText(QString("Player 2: Left %1 | Right %2")
                              .arg(player2->getLeftHand())
                              .arg(player2->getRightHand()));
    }

    // Update button text to show finger counts
    p1LeftButton->setText(QString("P1 Left\n%1").arg(player1->getLeftHand()));
    p1RightButton->setText(QString("P1 Right\n%1").arg(player1->getRightHand()));
    p2LeftButton->setText(QString("P2 Left\n%1").arg(player2->getLeftHand()));
    p2RightButton->setText(QString("P2 Right\n%1").arg(player2->getRightHand()));

    bool isP1Turn = (currentPlayer == player1);

    // By default, disable all
    p1LeftButton->setEnabled(false);
    p1RightButton->setEnabled(false);
    p2LeftButton->setEnabled(false);
    p2RightButton->setEnabled(false);

    if (selectedMyHand == -1) {
        // Enable only the current player's hands (if alive)
        if (isP1Turn) {
            if (player1->getLeftHand() > 0) p1LeftButton->setEnabled(true);
            if (player1->getRightHand() > 0) p1RightButton->setEnabled(true);
        } else {
            if (player2->getLeftHand() > 0) p2LeftButton->setEnabled(true);
            if (player2->getRightHand() > 0) p2RightButton->setEnabled(true);
        }
    } else {
        // Enable opponent's hands (if alive) and own dead hand for split
        if (isP1Turn) {
            if (player2->getLeftHand() > 0) p2LeftButton->setEnabled(true);
            if (player2->getRightHand() > 0) p2RightButton->setEnabled(true);

            // Allow split: tap own dead hand
            if (player1->getLeftHand() == 0) p1LeftButton->setEnabled(true);
            if (player1->getRightHand() == 0) p1RightButton->setEnabled(true);

            // Allow advanced split: (3,1), (1,3), (4,1), (1,4), (2,2), (2,3), (3,2), (2,4), (4,2)
            int h1 = player1->getHand(selectedMyHand);
            int otherHand = (selectedMyHand == 0) ? 1 : 0;
            int h2 = player1->getHand(otherHand);
            if (
                ( (h1 == 3 && h2 == 1) || (h1 == 1 && h2 == 3) ) ||
                ( (h1 == 4 && h2 == 1) || (h1 == 1 && h2 == 4) ) ||
                ( h1 == 2 && h2 == 2 ) ||
                ( (h1 == 2 && h2 == 3) || (h1 == 3 && h2 == 2) ) ||
                ( (h1 == 2 && h2 == 4) || (h1 == 4 && h2 == 2) ) ||
                ( h1 == 3 && h2 == 3 )
            ) {
                if (otherHand == 0) p1LeftButton->setEnabled(true);
                else p1RightButton->setEnabled(true);
            }
        } else {
            if (player1->getLeftHand() > 0) p1LeftButton->setEnabled(true);
            if (player1->getRightHand() > 0) p1RightButton->setEnabled(true);

            // Allow split: tap own dead hand
            if (player2->getLeftHand() == 0) p2LeftButton->setEnabled(true);
            if (player2->getRightHand() == 0) p2RightButton->setEnabled(true);

            // Allow advanced split: (3,1), (1,3), (4,1), (1,4)
            int h1 = player2->getHand(selectedMyHand);
            int otherHand = (selectedMyHand == 0) ? 1 : 0;
            int h2 = player2->getHand(otherHand);
            // Enable the other hand for all valid splits
            if (
                // (3,1), (1,3), (4,1), (1,4), (2,2), (2,3), (3,2), (2,4), (4,2)
                ( (h1 == 3 && h2 == 1) || (h1 == 1 && h2 == 3) ) ||
                ( (h1 == 4 && h2 == 1) || (h1 == 1 && h2 == 4) ) ||
                ( h1 == 2 && h2 == 2 ) ||
                ( (h1 == 2 && h2 == 3) || (h1 == 3 && h2 == 2) ) ||
                ( (h1 == 2 && h2 == 4) || (h1 == 4 && h2 == 2) ) ||
                ( h1 == 3 && h2 == 3 )
            ) {
                if (otherHand == 0) p2LeftButton->setEnabled(true);
                else p2RightButton->setEnabled(true);
            }
        }
    }

    // Highlight selected hand
    p1LeftButton->setStyleSheet(selectedMyHand == 0 && isP1Turn ? "background: #ffe082; border: 2px solid blue;" : "background: #ffe0b2;");
    p1RightButton->setStyleSheet(selectedMyHand == 1 && isP1Turn ? "background: #ffe082; border: 2px solid blue;" : "background: #ffe0b2;");
    p2LeftButton->setStyleSheet(selectedMyHand == 0 && !isP1Turn ? "background: #ffe082; border: 2px solid blue;" : "background: #b3e5fc;");
    p2RightButton->setStyleSheet(selectedMyHand == 1 && !isP1Turn ? "background: #ffe082; border: 2px solid blue;" : "background: #b3e5fc;");
    
    // Update turn label based on game mode
    if (m_gameType == NetworkDialog::SinglePlayerVsAI) {
        turnLabel->setText(currentPlayer == player1 ? "Your turn" : "AI is thinking...");
    } else {
        turnLabel->setText(currentPlayer == player1 ? "Player 1's turn" : "Player 2's turn");
    }
}

void GameWindow::selectMyHand(int handIndex)
{
    if ((currentPlayer == player1 && player1->getHand(handIndex) == 0) ||
        (currentPlayer == player2 && player2->getHand(handIndex) == 0)) {
        instructionsLabel->setText("Cannot use a dead hand. Choose another.");
        return;
    }
    selectedMyHand = handIndex;
    instructionsLabel->setText("Now tap an opponent's hand or your own dead hand to split.");
    updateDisplay();
}

void GameWindow::selectOpponentHand(int handIndex, bool isPlayer1Hand)
{
    Player* myPlayer = currentPlayer;
    Player* opponent = (currentPlayer == player1) ? player2 : player1;
    bool moveMade = false;
    int fromHand = selectedMyHand;
    int toHand = handIndex;
    // If tapping own hand (for split/revive or advanced split)
    if ((isPlayer1Hand && currentPlayer == player1) || (!isPlayer1Hand && currentPlayer == player2)) {
        int h1 = myPlayer->getHand(selectedMyHand);
        int h2 = myPlayer->getHand(handIndex);
        // Standard revive/split: tap dead hand with live hand > 1
        if (h2 == 0 && h1 > 1) {
            int total = h1;
            int give = total / 2;
            int remain = total - give;
            myPlayer->setHand(handIndex, give);
            myPlayer->setHand(selectedMyHand, remain);
            moveMade = true;
            currentPlayer = opponent;
        }
        // (3,1) or (1,3) -> (2,2)
        else if ((h1 == 3 && h2 == 1) || (h1 == 1 && h2 == 3)) {
            myPlayer->setHand(selectedMyHand, 2);
            myPlayer->setHand(handIndex, 2);
            moveMade = true;
            currentPlayer = opponent;
        }
        // (4,1) or (1,4) -> (3,2) or (2,3)
        else if ((h1 == 4 && h2 == 1) || (h1 == 1 && h2 == 4)) {
            myPlayer->setHand(selectedMyHand, 3);
            myPlayer->setHand(handIndex, 2);
            moveMade = true;
            currentPlayer = opponent;
        }
        // (2,2) -> (3,1) or (1,3)
        else if (h1 == 2 && h2 == 2) {
            myPlayer->setHand(selectedMyHand, 3);
            myPlayer->setHand(handIndex, 1);
            moveMade = true;
            currentPlayer = opponent;
        }
        // (2,3) or (3,2) -> (4,1) or (1,4)
        else if ((h1 == 2 && h2 == 3) || (h1 == 3 && h2 == 2)) {
            myPlayer->setHand(selectedMyHand, 4);
            myPlayer->setHand(handIndex, 1);
            moveMade = true;
            currentPlayer = opponent;
        }
        // (2,4) or (4,2) -> (3,3)
        else if ((h1 == 2 && h2 == 4) || (h1 == 4 && h2 == 2)) {
            myPlayer->setHand(selectedMyHand, 3);
            myPlayer->setHand(handIndex, 3);
            moveMade = true;
            currentPlayer = opponent;
        }
        // (3,3) -> (4,2) or (2,4)
        else if (h1 == 3 && h2 == 3) {
            myPlayer->setHand(selectedMyHand, 4);
            myPlayer->setHand(handIndex, 2);
            moveMade = true;
            currentPlayer = opponent;
        }
        else {
            instructionsLabel->setText("Invalid split: must tap your own dead hand with a hand > 1, or use a valid split pair.");
            return;
        }
    } else {
        // Normal tap on opponent
        if (opponent->getHand(handIndex) == 0) {
            instructionsLabel->setText("Cannot tap a dead hand. Choose another.");
            return;
        }
        currentPlayer->tap(*opponent, selectedMyHand, handIndex);
        moveMade = true;
        currentPlayer = opponent;
    }
    selectedMyHand = -1;
    updateDisplay();
    checkWin();
    // --- NETWORK MULTIPLAYER ---
    if (moveMade && (m_gameType == NetworkDialog::NetworkServer || m_gameType == NetworkDialog::NetworkClient) && m_networkManager && m_isMyTurn) {
        m_networkManager->sendGameMove(fromHand, toHand, m_localPlayerId);
        m_isMyTurn = false;
        // Do NOT updateDisplay() or checkWin() here in network mode; wait for onNetworkMoveReceived
        return;
    }
    // --- END NETWORK ---
    if (m_gameType == NetworkDialog::SinglePlayerVsAI) {
        QTimer::singleShot(1500, this, &GameWindow::triggerAIMove);
    }
}

void GameWindow::checkWin()
{
    if (player1->isOut()) {
        QString message;
        if (m_gameType == NetworkDialog::SinglePlayerVsAI) {
            message = "🤖 AI Wins! 🏆\n\nThe AI defeated you this time.\nTry again or adjust the difficulty level!";
            qDebug() << QString("🏁 [Game Over] AI Victory! Human player eliminated");
        } else {
            message = "🎉 Player 2 Wins! 🏆\n\nPlayer 1 has been eliminated.\nGreat game!";
            qDebug() << QString("🏁 [Game Over] Player 2 Victory! Player 1 eliminated");
        }
        QMessageBox::information(this, "Game Over", message);
        startGame();
    } else if (player2->isOut()) {
        QString message;
        if (m_gameType == NetworkDialog::SinglePlayerVsAI) {
            message = "🎉 You Win! 🏆\n\nCongratulations! You defeated the AI.\nWell played!";
            qDebug() << QString("🏁 [Game Over] Human Victory! AI eliminated");
        } else {
            message = "🎉 Player 1 Wins! 🏆\n\nPlayer 2 has been eliminated.\nGreat game!";
            qDebug() << QString("🏁 [Game Over] Player 1 Victory! Player 2 eliminated");
        }
        QMessageBox::information(this, "Game Over", message);
        startGame();
    }
}

void GameWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    // At 80px height, font will be about 6 (for / 14), scales up when window grows
    int fontSize = std::max(8, p1LeftButton->height() / 14);

    QFont btnFont;
    btnFont.setPointSize(fontSize);

    p1LeftButton->setFont(btnFont);
    p1RightButton->setFont(btnFont);
    p2LeftButton->setFont(btnFont);
    p2RightButton->setFont(btnFont);
}

void GameWindow::changeEvent(QEvent* event)
{
    QMainWindow::changeEvent(event);
    if (event->type() == QEvent::WindowStateChange) {
        updateDisplay(); // Force layout/font update
    }
}

void GameWindow::setGameMode(NetworkDialog::GameType gameType, int aiDifficulty)
{
    m_gameType = gameType;
    m_aiDifficulty = aiDifficulty;
    setupGameMode();
    updateGameModeDisplay();
}

void GameWindow::setupGameMode()
{
    // Clean up any existing game mode objects
    if (m_aiPlayer) {
        delete m_aiPlayer;
        m_aiPlayer = nullptr;
    }
    // Only delete and create a new NetworkManager if not provided
    if (!m_networkManager) {
        if (m_networkManager) {
            delete m_networkManager;
            m_networkManager = nullptr;
        }
    }
    // Setup based on game type
    switch (m_gameType) {
        case NetworkDialog::LocalTwoPlayer:
            m_localPlayerId = 1;
            m_isMyTurn = true;
            break;
        case NetworkDialog::SinglePlayerVsAI:
            m_localPlayerId = 1;
            m_isMyTurn = true;
            m_aiPlayer = new AIPlayer(this);
            m_aiPlayer->setDifficulty(static_cast<AIPlayer::Difficulty>(m_aiDifficulty));
            connect(m_aiPlayer, &AIPlayer::moveDecided, this, &GameWindow::onAIMove);
            connect(m_aiPlayer, &AIPlayer::splitDecided, this, &GameWindow::onAISplit);
            break;
        case NetworkDialog::NetworkServer:
            m_localPlayerId = 1;
            m_isMyTurn = true;
            // Only create if not provided
            if (!m_networkManager) m_networkManager = new NetworkManager(this);
            m_networkManager->setGameMode(NetworkManager::ServerMode);
            connect(m_networkManager, &NetworkManager::gameMoveReceived, this, &GameWindow::onNetworkMoveReceived);
            break;
        case NetworkDialog::NetworkClient:
            m_localPlayerId = 2;
            m_isMyTurn = false;
            // Only create if not provided
            if (!m_networkManager) m_networkManager = new NetworkManager(this);
            m_networkManager->setGameMode(NetworkManager::ClientMode);
            connect(m_networkManager, &NetworkManager::gameMoveReceived, this, &GameWindow::onNetworkMoveReceived);
            break;
    }
}

void GameWindow::updateGameModeDisplay()
{
    QString modeText;
    switch (m_gameType) {
        case NetworkDialog::LocalTwoPlayer:
            modeText = "Game Mode: 👥 Local Two Player";
            break;
        case NetworkDialog::SinglePlayerVsAI:
            {
                QString difficulty;
                switch (m_aiDifficulty) {
                    case 0: difficulty = "Easy 😊"; break;
                    case 1: difficulty = "Medium 😐"; break;
                    case 2: difficulty = "Hard 😈"; break;
                    default: difficulty = "Unknown"; break;
                }
                modeText = QString("Game Mode: 🤖 Single Player vs AI (%1)").arg(difficulty);
            }
            break;
        case NetworkDialog::NetworkServer:
            modeText = "Game Mode: 🏠 Network Server (Hosting)";
            break;
        case NetworkDialog::NetworkClient:
            modeText = "Game Mode: 🔗 Network Client (Connected)";
            break;
    }
    gameModeLabel->setText(modeText);
}

void GameWindow::onAIMove(int fromHand, int toHand)
{
    if (m_gameType != NetworkDialog::SinglePlayerVsAI || !m_aiPlayer) {
        return;
    }
    
    // AI wants to tap - fromHand is AI's hand, toHand is human's hand
    if (currentPlayer == player2) { // AI is player2
        QString fromHandName = (fromHand == 0) ? "Left" : "Right";
        QString toHandName = (toHand == 0) ? "Left" : "Right";
        
        qDebug() << QString("🎯 [Game Action] AI executed attack: AI's %1 hand (%2 fingers) → Your %3 hand (%4 fingers)")
                    .arg(fromHandName)
                    .arg(player2->getHand(fromHand))
                    .arg(toHandName)
                    .arg(player1->getHand(toHand));
        
        currentPlayer->tap(*player1, fromHand, toHand);
        instructionsLabel->setText(QString("AI attacked your %1 hand!").arg(toHandName));
        currentPlayer = player1; // Switch back to human
        selectedMyHand = -1;
        updateDisplay();
        checkWin();
    }
}

void GameWindow::onAISplit()
{
    if (m_gameType != NetworkDialog::SinglePlayerVsAI || !m_aiPlayer) {
        return;
    }
    
    // AI wants to split hands
    if (currentPlayer == player2) { // AI is player2
        // Find a valid split move for the AI
        // For simplicity, let's implement the most common split (even hand -> half/half)
        int leftHand = player2->getLeftHand();
        int rightHand = player2->getRightHand();
        
        qDebug() << QString("🔄 [Game Action] AI executing split strategy");
        qDebug() << QString("   └─ Before Split: Left=%1, Right=%2").arg(leftHand).arg(rightHand);
        
        if (leftHand > 1 && leftHand % 2 == 0 && rightHand == 0) {
            // Split left hand in half, give to right hand
            int give = leftHand / 2;
            player2->setHand(0, give); // left hand
            player2->setHand(1, give); // right hand
            instructionsLabel->setText(QString("AI split their left hand (%1 → %2 + %3)!").arg(leftHand).arg(give).arg(give));
            qDebug() << QString("   └─ After Split: Left=%1, Right=%2").arg(give).arg(give);
        } else if (rightHand > 1 && rightHand % 2 == 0 && leftHand == 0) {
            // Split right hand in half, give to left hand
            int give = rightHand / 2;
            player2->setHand(1, give); // right hand
            player2->setHand(0, give); // left hand
            instructionsLabel->setText(QString("AI split their right hand (%1 → %2 + %3)!").arg(rightHand).arg(give).arg(give));
            qDebug() << QString("   └─ After Split: Left=%1, Right=%2").arg(give).arg(give);
        } else {
            instructionsLabel->setText("AI attempted to split but couldn't find a valid split!");
            qDebug() << QString("   └─ Split Failed: No valid split available");
        }
        
        currentPlayer = player1; // Switch back to human
        selectedMyHand = -1;
        updateDisplay();
        checkWin();
    }
}

void GameWindow::triggerAIMove()
{
    if (m_gameType != NetworkDialog::SinglePlayerVsAI || !m_aiPlayer) {
        return;
    }
    
    // Only trigger AI if it's AI's turn (player2) and game hasn't ended
    if (currentPlayer == player2 && !player1->isOut() && !player2->isOut()) {
        // Ask AI to make a move
        m_aiPlayer->makeMove(*player2, *player1);
    }
}

void GameWindow::onNetworkMoveReceived(int fromHand, int toHand, int playerId)
{
    Player* remotePlayer = (playerId == 1) ? player1 : player2;
    Player* remoteOpponent = (playerId == 1) ? player2 : player1;
    currentPlayer = remotePlayer;
    selectedMyHand = fromHand;
    // Simulate the move
    if ((remotePlayer == player1 && fromHand < 2 && toHand < 2 && toHand == fromHand) ||
        (remotePlayer == player2 && fromHand < 2 && toHand < 2 && toHand == fromHand)) {
        // Split or revive
        int h1 = remotePlayer->getHand(fromHand);
        int h2 = remotePlayer->getHand(toHand);
        // Use same split logic as selectOpponentHand
        if (h2 == 0 && h1 > 1) {
            int total = h1;
            int give = total / 2;
            int remain = total - give;
            remotePlayer->setHand(toHand, give);
            remotePlayer->setHand(fromHand, remain);
        } else if ((h1 == 3 && h2 == 1) || (h1 == 1 && h2 == 3)) {
            remotePlayer->setHand(fromHand, 2);
            remotePlayer->setHand(toHand, 2);
        } else if ((h1 == 4 && h2 == 1) || (h1 == 1 && h2 == 4)) {
            remotePlayer->setHand(fromHand, 3);
            remotePlayer->setHand(toHand, 2);
        } else if (h1 == 2 && h2 == 2) {
            remotePlayer->setHand(fromHand, 3);
            remotePlayer->setHand(toHand, 1);
        } else if ((h1 == 2 && h2 == 3) || (h1 == 3 && h2 == 2)) {
            remotePlayer->setHand(fromHand, 4);
            remotePlayer->setHand(toHand, 1);
        } else if ((h1 == 2 && h2 == 4) || (h1 == 4 && h2 == 2)) {
            remotePlayer->setHand(fromHand, 3);
            remotePlayer->setHand(toHand, 3);
        } else if (h1 == 3 && h2 == 3) {
            remotePlayer->setHand(fromHand, 4);
            remotePlayer->setHand(toHand, 2);
        }
    } else {
        // Normal tap
        remotePlayer->tap(*remoteOpponent, fromHand, toHand);
    }
    currentPlayer = remoteOpponent;
    selectedMyHand = -1;
    m_isMyTurn = true;
    updateDisplay();
    checkWin();
}

void GameWindow::setNetworkManager(NetworkManager* networkManager) {
    m_networkManager = networkManager;
}