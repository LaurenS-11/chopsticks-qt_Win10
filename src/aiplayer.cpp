#include "aiplayer.h"
#include <QDebug>
#include <algorithm>

AIPlayer::AIPlayer(QObject *parent)
    : QObject(parent)
    , m_difficulty(Medium)
    , m_moveTimer(new QTimer(this))
    , m_moveDelay(1500) // 1.5 second delay for natural feel
{
    m_moveTimer->setSingleShot(true);
    connect(m_moveTimer, &QTimer::timeout, this, &AIPlayer::executePlannedMove);
}

void AIPlayer::makeMove(const Player &aiPlayer, const Player &humanPlayer)
{
    // Find the best move based on difficulty
    m_plannedMove = findBestMove(aiPlayer, humanPlayer);
    
    // Add some delay to make it feel more natural
    m_moveTimer->start(m_moveDelay);
    
    // Clear debug output for AI moves
    QString difficultyName;
    QString difficultyEmoji;
    switch (m_difficulty) {
        case Easy: 
            difficultyName = "Easy"; 
            difficultyEmoji = "😊"; 
            break;
        case Medium: 
            difficultyName = "Medium"; 
            difficultyEmoji = "😐"; 
            break;
        case Hard: 
            difficultyName = "Hard"; 
            difficultyEmoji = "😈"; 
            break;
    }
    
    if (m_plannedMove.type == Move::Tap) {
        QString fromHand = (m_plannedMove.fromHand == 0) ? "Left" : "Right";
        QString toHand = (m_plannedMove.toHand == 0) ? "Left" : "Right";
        qDebug() << QString("🤖 [AI %1 %2] Planning attack: AI's %3 hand → Your %4 hand")
                    .arg(difficultyName, difficultyEmoji, fromHand, toHand);
    } else {
        qDebug() << QString("🤖 [AI %1 %2] Planning strategic split to redistribute fingers")
                    .arg(difficultyName, difficultyEmoji);
    }
}

void AIPlayer::executePlannedMove()
{
    if (m_plannedMove.type == Move::Tap) {
        emit moveDecided(m_plannedMove.fromHand, m_plannedMove.toHand);
    } else {
        emit splitDecided();
    }
}

AIPlayer::Move AIPlayer::findBestMove(const Player &aiPlayer, const Player &humanPlayer)
{
    switch (m_difficulty) {
    case Easy:
        return findEasyMove(aiPlayer, humanPlayer);
    case Medium:
        return findMediumMove(aiPlayer, humanPlayer);
    case Hard:
        return findHardMove(aiPlayer, humanPlayer);
    }
    return findMediumMove(aiPlayer, humanPlayer);
}

AIPlayer::Move AIPlayer::findEasyMove(const Player &aiPlayer, const Player &humanPlayer)
{
    // Easy AI: Mostly random moves with very basic strategy
    QList<Move> allMoves = generateAllMoves(aiPlayer, humanPlayer);
    
    if (allMoves.isEmpty()) {
        return Move{Move::Tap, 0, 0, 0}; // Fallback
    }
    
    // 30% chance to make a good move, 70% random
    if (QRandomGenerator::global()->bounded(100) < 30) {
        // Try to find a winning move
        for (const Move &move : allMoves) {
            if (move.score > 100) { // Winning move
                return move;
            }
        }
    }
    
    // Otherwise, pick randomly
    int randomIndex = QRandomGenerator::global()->bounded(allMoves.size());
    return allMoves[randomIndex];
}

AIPlayer::Move AIPlayer::findMediumMove(const Player &aiPlayer, const Player &humanPlayer)
{
    // Medium AI: Good strategy with occasional suboptimal moves
    QList<Move> allMoves = generateAllMoves(aiPlayer, humanPlayer);
    
    if (allMoves.isEmpty()) {
        return Move{Move::Tap, 0, 0, 0}; // Fallback
    }
    
    // Evaluate all moves
    for (Move &move : allMoves) {
        move.score = evaluateTapMove(move.fromHand, move.toHand, aiPlayer, humanPlayer);
    }
    
    // Sort by score (best first)
    std::sort(allMoves.begin(), allMoves.end(), [](const Move &a, const Move &b) {
        return a.score > b.score;
    });
    
    // 80% chance to pick the best move, 20% to pick from top 3
    if (QRandomGenerator::global()->bounded(100) < 80) {
        return allMoves.first();
    } else {
        int topChoices = qMin(3, allMoves.size());
        int randomIndex = QRandomGenerator::global()->bounded(topChoices);
        return allMoves[randomIndex];
    }
}

AIPlayer::Move AIPlayer::findHardMove(const Player &aiPlayer, const Player &humanPlayer)
{
    // Hard AI: Always picks the optimal move
    QList<Move> allMoves = generateAllMoves(aiPlayer, humanPlayer);
    
    if (allMoves.isEmpty()) {
        return Move{Move::Tap, 0, 0, 0}; // Fallback
    }
    
    Move bestMove = allMoves.first();
    int bestScore = evaluateTapMove(bestMove.fromHand, bestMove.toHand, aiPlayer, humanPlayer);
    
    for (const Move &move : allMoves) {
        int score = evaluateTapMove(move.fromHand, move.toHand, aiPlayer, humanPlayer);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    
    bestMove.score = bestScore;
    return bestMove;
}

QList<AIPlayer::Move> AIPlayer::generateAllMoves(const Player &aiPlayer, const Player &humanPlayer)
{
    QList<Move> moves;
    
    // Generate all possible tap moves
    for (int aiHand = 0; aiHand < 2; aiHand++) {
        if (aiPlayer.getHand(aiHand) > 0 && aiPlayer.getHand(aiHand) < 5) { // Valid AI hand
            for (int humanHand = 0; humanHand < 2; humanHand++) {
                if (humanPlayer.getHand(humanHand) > 0 && humanPlayer.getHand(humanHand) < 5) { // Valid target
                    moves.append(Move{Move::Tap, aiHand, humanHand, 0});
                }
            }
        }
    }
    
    // Check if splitting is possible and beneficial
    if (shouldSplit(aiPlayer, humanPlayer)) {
        moves.append(Move{Move::Split, -1, -1, 0});
    }
    
    return moves;
}

int AIPlayer::evaluateTapMove(int aiHand, int humanHand, const Player &aiPlayer, const Player &humanPlayer)
{
    int score = 0;
    
    // Get current values
    int aiFingers = aiPlayer.getHand(aiHand);
    int humanFingers = humanPlayer.getHand(humanHand);
    
    if (aiFingers <= 0 || aiFingers >= 5 || humanFingers <= 0 || humanFingers >= 5) {
        return -1000; // Invalid move
    }
    
    int resultFingers = humanFingers + aiFingers;
    
    // Winning move (eliminates opponent's hand)
    if (resultFingers >= 5) {
        score += 500;
        
        // Extra points if this eliminates opponent's last hand
        int otherHumanHand = 1 - humanHand;
        if (humanPlayer.getHand(otherHumanHand) <= 0 || humanPlayer.getHand(otherHumanHand) >= 5) {
            score += 1000; // Game winning move!
        }
    }
    
    // Prefer moves that set up future wins
    if (resultFingers == 4) {
        score += 100; // One away from elimination
    } else if (resultFingers == 3) {
        score += 50; // Two away from elimination
    }
    
    // Avoid giving opponent easy split opportunities
    if (resultFingers == 2 || resultFingers == 4) {
        score -= 30; // These can be split
    }
    
    // Prefer using larger hands (to keep them from being eliminated)
    if (aiFingers >= 3) {
        score += 20;
    }
    
    // Defensive: avoid creating situations where opponent can win next turn
    for (int oppHand = 0; oppHand < 2; oppHand++) {
        int oppFingers = humanPlayer.getHand(oppHand);
        if (oppFingers > 0 && oppFingers < 5) {
            for (int myHand = 0; myHand < 2; myHand++) {
                int myFingers = aiPlayer.getHand(myHand);
                if (myHand != aiHand && myFingers > 0 && myFingers < 5) {
                    if (myFingers + oppFingers >= 5) {
                        score -= 200; // Opponent could eliminate our hand
                    }
                }
            }
        }
    }
    
    return score;
}

bool AIPlayer::shouldSplit(const Player &aiPlayer, const Player &humanPlayer)
{
    // Check if split is possible (even number on one hand, 0 on the other)
    bool canSplit = false;
    for (int i = 0; i < 2; i++) {
        int fingers = aiPlayer.getHand(i);
        int otherFingers = aiPlayer.getHand(1 - i);
        if (fingers > 0 && fingers % 2 == 0 && fingers < 5 && 
            (otherFingers == 0 || otherFingers >= 5)) {
            canSplit = true;
            break;
        }
    }
    
    if (!canSplit) {
        return false;
    }
    
    // Evaluate if splitting is beneficial
    // Split if it prevents immediate loss or creates better offensive opportunities
    
    // Check if we're about to lose (opponent can eliminate both hands)
    int activeHands = 0;
    for (int i = 0; i < 2; i++) {
        if (aiPlayer.getHand(i) > 0 && aiPlayer.getHand(i) < 5) {
            activeHands++;
        }
    }
    
    if (activeHands == 1) {
        // We only have one hand left, splitting might save us
        return true;
    }
    
    // Split if it gives us more attack options
    return QRandomGenerator::global()->bounded(100) < 30; // 30% chance to split when possible
}

int AIPlayer::evaluatePosition(const Player &aiPlayer, const Player &humanPlayer)
{
    int score = 0;
    
    // Count active hands
    int aiActiveHands = 0;
    int humanActiveHands = 0;
    
    for (int i = 0; i < 2; i++) {
        if (aiPlayer.getHand(i) > 0 && aiPlayer.getHand(i) < 5) {
            aiActiveHands++;
        }
        if (humanPlayer.getHand(i) > 0 && humanPlayer.getHand(i) < 5) {
            humanActiveHands++;
        }
    }
    
    // More active hands is better
    score += aiActiveHands * 100;
    score -= humanActiveHands * 100;
    
    // Prefer having fingers distributed (not all on one hand)
    int aiTotal = 0;
    for (int i = 0; i < 2; i++) {
        int fingers = aiPlayer.getHand(i);
        if (fingers > 0 && fingers < 5) {
            aiTotal += fingers;
        }
    }
    
    // Balanced distribution bonus
    if (aiActiveHands == 2) {
        int diff = abs(aiPlayer.getHand(0) - aiPlayer.getHand(1));
        score -= diff * 10; // Penalty for imbalance
    }
    
    return score;
}
