#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include "player.h"

class GameWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    void startGame();
    void updateDisplay();

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
    QPushButton* p1LeftButton;
    QPushButton* p1RightButton;
    QPushButton* p2LeftButton;
    QPushButton* p2RightButton;
    int selectedMyHand;

    void selectMyHand(int handIndex);
    void selectOpponentHand(int handIndex, bool isPlayer1Hand);
    void checkWin();
};

#endif // GAMEWINDOW_H