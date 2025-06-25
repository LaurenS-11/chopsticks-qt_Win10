// Example integration into your main chopsticks-qt.cpp
#include <QApplication>
#include <QMessageBox>
#include "gamewindow.h"
#include "networkdialog.h"
#include "aiplayer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Show game setup dialog first
    NetworkDialog setupDialog;
    if (setupDialog.exec() == QDialog::Accepted) {
        
        NetworkDialog::GameType gameType = setupDialog.getSelectedGameType();
        
        // Create game window
        GameWindow gameWindow;
        
        switch (gameType) {
        case NetworkDialog::LocalTwoPlayer:
            QMessageBox::information(&gameWindow, "Local Game", 
                "🎮 Starting local two-player game!\nPlayer 1 vs Player 2");
            gameWindow.setGameMode(GameWindow::LocalTwoPlayer);
            break;
            
        case NetworkDialog::SinglePlayerVsAI:
        {
            int difficulty = setupDialog.getAIDifficulty();
            QString difficultyText[] = {"Easy", "Medium", "Hard"};
            QMessageBox::information(&gameWindow, "AI Challenge", 
                QString("🤖 Challenge accepted!\nDifficulty: %1\n\nGood luck!")
                .arg(difficultyText[difficulty]));
            gameWindow.setGameMode(GameWindow::SinglePlayerVsAI);
            gameWindow.setAIDifficulty(static_cast<AIPlayer::Difficulty>(difficulty));
            break;
        }
        
        case NetworkDialog::NetworkServer:
        {
            QString address = setupDialog.getServerAddress();
            quint16 port = setupDialog.getServerPort();
            QMessageBox::information(&gameWindow, "Network Server", 
                QString("🏠 Network game server started!\nWaiting for players to connect..."));
            gameWindow.setGameMode(GameWindow::NetworkServer);
            gameWindow.configureNetwork(NetworkManager::ServerMode, address, port);
            break;
        }
        
        case NetworkDialog::NetworkClient:
        {
            QString address = setupDialog.getServerAddress();
            quint16 port = setupDialog.getServerPort();
            QMessageBox::information(&gameWindow, "Network Client", 
                QString("🔗 Connected to network game!\nServer: %1:%2")
                .arg(address).arg(port));
            gameWindow.setGameMode(GameWindow::NetworkClient);
            gameWindow.configureNetwork(NetworkManager::ClientMode, address, port);
            break;
        }
        }
        
        gameWindow.show();
        return app.exec();
    }
    
    return 0;
}
