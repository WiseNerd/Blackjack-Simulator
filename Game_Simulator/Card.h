#ifndef Card_h
#define Card_h

// for i 1-13 declare object 1, with rank i and push back vector with object. Maybe if i == 1, string is bla bla, or can do that in class like card.h for 10s: in the for loop: if i==0 ten, if i==1 jack, if i==2 queen, etc. Can choose to add in suites as well.
#include <iostream>
#include <vector>
#include <string>

using namespace std;


class Card {
public:
    Card ();
    Card(int input_rank, string input_name);
    string get_name ();
    int get_rank();
    void change_rank(int input_rank);
private:
    int rank;
    string name;
};

Card::Card() {
    rank = 0;
    name = "error";
}
Card::Card(int input_rank, string input_name) {
    rank = input_rank;
    name = input_name;
}
string Card::get_name() {
    return name;
}
int Card::get_rank() {
    return rank;
}
void Card::change_rank(int input_rank) {
    rank = input_rank;
}
#endif
