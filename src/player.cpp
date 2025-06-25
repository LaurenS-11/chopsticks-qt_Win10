#include "player.h"

Player::Player() {
    leftHand = 1;
    rightHand = 1;
}

void Player::reset() {
    leftHand = 1;
    rightHand = 1;
}

int Player::getLeftHand() const {
    return leftHand;
}

int Player::getRightHand() const {
    return rightHand;
}

int Player::getHand(int handIndex) const {
    return (handIndex == 0) ? leftHand : rightHand;
}

void Player::setHand(int handIndex, int value) {
    if (handIndex == 0) leftHand = value;
    else rightHand = value;
}

bool Player::isHandAlive(int handIndex) const {
    return getHand(handIndex) > 0;
}

bool Player::isOut() const {
    return leftHand == 0 && rightHand == 0;
}

// The main tap logic
void Player::tap(Player& opponent, int myHandIndex, int opponentHandIndex) {
    int tapValue = getHand(myHandIndex);
    if (tapValue == 0 || !opponent.isHandAlive(opponentHandIndex)) return; // Can't tap with or to a dead hand

    int newValue = opponent.getHand(opponentHandIndex) + tapValue;
    if (newValue >= 5) newValue = 0;
    opponent.setHand(opponentHandIndex, newValue);
}