#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player();
    void reset();
    int getLeftHand() const;
    int getRightHand() const;
    int getHand(int handIndex) const;
    void setHand(int handIndex, int value);
    bool isHandAlive(int handIndex) const;
    bool isOut() const;
    // Tap logic: tap from this player's hand to another player's hand
    void tap(Player& opponent, int myHandIndex, int opponentHandIndex);
    // ...split logic as before...
private:
    int leftHand;
    int rightHand;
};

#endif // PLAYER_H