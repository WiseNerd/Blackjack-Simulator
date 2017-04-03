#ifndef Player_h
#define Player_h

#include <iostream>
#include <string>
#include <vector>
#include "Card.h"

using namespace std;

class Player {
private:
    string name;
    double balance;
    double start_money;
    vector <Card> hand;
public:
    Player ();
    Player (string input_name, double input_balance, double input_start_money, Card input_card);
    void set_hand (Card mycard);
    vector <Card> get_hand ();
    string get_name () const;
    
};

Player::Player() {
    name = "";
    balance = 0;
    start_money = 0;
    hand = {Card()};
}

Player::Player(string input_name, double input_balance, double input_start_money, Card input_card) {
    name = input_name;
    balance = input_balance;
    start_money = input_start_money;
    hand.push_back(input_card);
}
void Player::set_hand(Card mycard) {
    hand.push_back(mycard);
}
vector <Card> Player::get_hand () {
    return hand;
}
string Player::get_name() const {
    return name;
}
#endif
