#include "gamewindow.h"
#include "player.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QResizeEvent>
#include <QFont>
#include <QEvent>
#include <QWindowStateChangeEvent>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent), player1(new Player()), player2(new Player()), currentPlayer(player1), selectedMyHand(-1)
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
    updateDisplay();
    checkWin();
}

void GameWindow::updateDisplay()
{
    player1Label->setText(QString("Player 1: Left %1 | Right %2")
                          .arg(player1->getLeftHand())
                          .arg(player1->getRightHand()));
    player2Label->setText(QString("Player 2: Left %1 | Right %2")
                          .arg(player2->getLeftHand())
                          .arg(player2->getRightHand()));

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
    turnLabel->setText(currentPlayer == player1 ? "Player 1's turn" : "Player 2's turn");
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
            instructionsLabel->setText("Split performed!");
            currentPlayer = opponent;
        }
        // (3,1) or (1,3) -> (2,2)
        else if ((h1 == 3 && h2 == 1) || (h1 == 1 && h2 == 3)) {
            myPlayer->setHand(selectedMyHand, 2);
            myPlayer->setHand(handIndex, 2);
            instructionsLabel->setText("Split performed! (2,2)");
            currentPlayer = opponent;
        }
        // (4,1) or (1,4) -> (3,2) or (2,3)
        else if ((h1 == 4 && h2 == 1) || (h1 == 1 && h2 == 4)) {
            myPlayer->setHand(selectedMyHand, 3);
            myPlayer->setHand(handIndex, 2);
            instructionsLabel->setText("Split performed! (3,2) or (2,3)");
            currentPlayer = opponent;
        }
        // (2,2) -> (3,1) or (1,3)
        else if (h1 == 2 && h2 == 2) {
            myPlayer->setHand(selectedMyHand, 3);
            myPlayer->setHand(handIndex, 1);
            instructionsLabel->setText("Split performed! (3,1) or (1,3)");
            currentPlayer = opponent;
        }
        // (2,3) or (3,2) -> (4,1) or (1,4)
        else if ((h1 == 2 && h2 == 3) || (h1 == 3 && h2 == 2)) {
            myPlayer->setHand(selectedMyHand, 4);
            myPlayer->setHand(handIndex, 1);
            instructionsLabel->setText("Split performed! (4,1) or (1,4)");
            currentPlayer = opponent;
        }
        // (2,4) or (4,2) -> (3,3)
        else if ((h1 == 2 && h2 == 4) || (h1 == 4 && h2 == 2)) {
            myPlayer->setHand(selectedMyHand, 3);
            myPlayer->setHand(handIndex, 3);
            instructionsLabel->setText("Split performed! (3,3)");
            currentPlayer = opponent;
        }
        // (3,3) -> (4,2) or (2,4)
        else if (h1 == 3 && h2 == 3) {
            myPlayer->setHand(selectedMyHand, 4);
            myPlayer->setHand(handIndex, 2);
            instructionsLabel->setText("Split performed! (4,2) or (2,4)");
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
        instructionsLabel->setText("Tap performed!");
        currentPlayer = opponent;
    }

    selectedMyHand = -1;
    updateDisplay();
    checkWin();
}

void GameWindow::checkWin()
{
    if (player1->isOut()) {
        QMessageBox::information(this, "Game Over", "Player 2 wins!");
        startGame();
    } else if (player2->isOut()) {
        QMessageBox::information(this, "Game Over", "Player 1 wins!");
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