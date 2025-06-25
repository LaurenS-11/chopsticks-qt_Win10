#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "gamewindow.h"
#include "networkdialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    NetworkDialog setupDialog;
    if (setupDialog.exec() != QDialog::Accepted) {
        return 0;
    }

    NetworkDialog::GameType gameType = setupDialog.getSelectedGameType();
    int aiDifficulty = setupDialog.getAIDifficulty();
    NetworkManager* networkManager = nullptr;
    if (gameType == NetworkDialog::NetworkServer || gameType == NetworkDialog::NetworkClient) {
        networkManager = setupDialog.getNetworkManager();
    }
    GameWindow* gameWindow = nullptr;
    if (networkManager) {
        gameWindow = new GameWindow(nullptr, networkManager);
        gameWindow->setGameMode(gameType, aiDifficulty);
    } else {
        gameWindow = new GameWindow();
        gameWindow->setGameMode(gameType, aiDifficulty);
    }
    gameWindow->show();
    gameWindow->startGame();

    int result = app.exec();
    delete gameWindow;
    return result;
}