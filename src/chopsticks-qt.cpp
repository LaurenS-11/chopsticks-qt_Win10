#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "gamewindow.h"
#include "networkdialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Simple, working version without debug window
    NetworkDialog setupDialog;
    
    if (setupDialog.exec() != QDialog::Accepted) {
        return 0;
    }

    NetworkDialog::GameType gameType = setupDialog.getSelectedGameType();
    int aiDifficulty = setupDialog.getAIDifficulty();
    
    GameWindow* gameWindow = new GameWindow();
    gameWindow->setGameMode(gameType, aiDifficulty);
    gameWindow->show();
    gameWindow->startGame();

    int result = app.exec();
    delete gameWindow;
    return result;
}