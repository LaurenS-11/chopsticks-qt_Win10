#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "gamewindow.h"
#include "networkdialog.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Welcome message
    qDebug() << "🎮 ========================================";
    qDebug() << "🎮 Welcome to Chopsticks Game (Qt5 Edition)";
    qDebug() << "🎮 ========================================";
    qDebug() << "📋 Features: Local 2-Player | AI Opponent | Network Multiplayer";
    qDebug() << "🚀 Starting game setup dialog...";

    // Show the game mode selection dialog
    NetworkDialog setupDialog;
    if (setupDialog.exec() != QDialog::Accepted) {
        // User cancelled the setup dialog
        qDebug() << "❌ User cancelled game setup. Exiting application.";
        return 0;
    }

    // Get the selected game configuration
    NetworkDialog::GameType gameType = setupDialog.getSelectedGameType();
    int aiDifficulty = setupDialog.getAIDifficulty();
    
    qDebug() << "✅ Game setup complete. Launching game window...";
    
    // Create and configure the game window
    GameWindow* gameWindow = new GameWindow();
    gameWindow->setGameMode(gameType, aiDifficulty);
    gameWindow->show();
    gameWindow->startGame();

    int result = app.exec();
    
    qDebug() << "👋 Chopsticks Game session ended. Thank you for playing!";
    delete gameWindow;
    return result;
}