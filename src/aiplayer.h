#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>
#include "player.h"

class AIPlayer : public QObject
{
    Q_OBJECT

public:
    enum Difficulty {
        Easy,    // Random moves with some basic strategy
        Medium,  // Balanced strategy with occasional mistakes
        Hard     // Advanced strategy with optimal moves
    };

    explicit AIPlayer(QObject *parent = nullptr);
    
    void setDifficulty(Difficulty difficulty) { m_difficulty = difficulty; }
    Difficulty getDifficulty() const { return m_difficulty; }
    
    // Main AI decision making
    void makeMove(const Player &aiPlayer, const Player &humanPlayer);
    
    // Set delay for more natural feel
    void setMoveDelay(int milliseconds) { m_moveDelay = milliseconds; }

signals:
    void moveDecided(int fromHand, int toHand); // fromHand: AI's hand, toHand: opponent's hand
    void splitDecided(); // AI wants to split hands

private slots:
    void executePlannedMove();

private:
    struct Move {
        enum Type { Tap, Split };
        Type type;
        int fromHand; // 0 = left, 1 = right
        int toHand;   // 0 = left, 1 = right (for tapping)
        int score;    // Move evaluation score
    };

    // Strategy methods
    Move findBestMove(const Player &aiPlayer, const Player &humanPlayer);
    Move findEasyMove(const Player &aiPlayer, const Player &humanPlayer);
    Move findMediumMove(const Player &aiPlayer, const Player &humanPlayer);
    Move findHardMove(const Player &aiPlayer, const Player &humanPlayer);
    
    // Evaluation methods
    int evaluatePosition(const Player &aiPlayer, const Player &humanPlayer);
    int evaluateTapMove(int aiHand, int humanHand, const Player &aiPlayer, const Player &humanPlayer);
    bool shouldSplit(const Player &aiPlayer, const Player &humanPlayer);
    
    // Utility methods
    QList<Move> generateAllMoves(const Player &aiPlayer, const Player &humanPlayer);
    bool isValidMove(const Move &move, const Player &aiPlayer, const Player &humanPlayer);
    Player simulateMove(const Move &move, const Player &aiPlayer, const Player &humanPlayer, bool &isAITurn);
    
    Difficulty m_difficulty;
    QTimer *m_moveTimer;
    Move m_plannedMove;
    int m_moveDelay;
};

#endif // AIPLAYER_H
