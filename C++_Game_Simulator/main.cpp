// Add winning. So greater sum than dealer you win. Pushes. Instant Blackjack you win. Dealer blackjack everybody loses.
// Fix if there are two aces
// Make a new deck when it runs out or game nds at end of shoe.

// Need to make a general plan. How to go through multiple runs in one program? (Big while loop player still has money or still wants to play). How to have multiple players play? (2D vector or class? How to use it in different functions if object of class? Maybe fill a vector with the player objects).
// Once all functions and scope are good, move onto to checking who won, if player busts first etc. Then splits, double down, etc. Player should be able to choose how many hands to play.
// Function bet: player makes bet. Function deal: deals basic cards. Function player_play: player makes decisions. Should also include functions for spliting and doubling down. Function dealer_play: dealer makes decisions.

// Things After:
    // need a general check to make sure everything works in terms of random.

// To test:
    //Card mycard (1, "Ace");
    //decks[0] = (mycard);

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include "Card.h"
#include "Player.h"

using namespace std;


void setdeck (vector <Card> &decks, int size, double penetration);

vector <Card> shuffle (vector <Card> decks);

void deal (vector <Card> &dealerhand, vector <Card> &decks, vector <Player> &players);

void play (vector <Card> decks);

void player_play (char hs, int playersum, vector <Card> dealerhand, vector <Card> &decks, vector <Player> &players, int playa, vector <int> &win);

void dealer_play (int &dealersum, vector <Card> dealerhand, vector <Card> &decks);

void win_test (vector <Player> players, int dealersum, vector <int> &win);


int main () {
    srand((int)time(0));
    
    vector <Card> decks;
    int size =1;
    double penetration =1;
    
//    cout << "input size";
//    cin >> size;
//    
//    cout <<"input penetration";
//    cin >> penetration;
    
    setdeck(decks, size, penetration);
    
    play(decks);
    
    
    
    
}

vector <Card> shuffle (vector <Card> decks) {
    vector <Card> random(decks.size());
    for (int i=0; i<decks.size(); i++) {
        int random_number = rand() % decks.size();
        while (random.at(random_number).get_rank() > 0) {
            random_number = rand() % decks.size();
        }
        random[random_number] = decks[i];
        
    }
    return random;
    
}


void setdeck (vector <Card> &decks, int size, double penetration) {
    size*=4;
    for (int j =0; j<size; j++) {
        for (int i =1; i<10; i++) {
            string name;
            if (i == 1)
                name = "Ace";
            else if (i == 2)
                name = "Two";
            else if (i == 3)
                name = "Three";
            else if (i == 4)
                name = "Four";
            else if (i == 5)
                name = "Five";
            else if (i == 6)
                name = "Six";
            else if (i == 7)
                name = "Seven";
            else if (i == 8)
                name = "Eight";
            else
                name = "Nine";
            
            Card mycard(i, name);
            decks.push_back(mycard);
        }
        for (int i = 0; i<4; i++) {
            string name;
            if (i == 0)
                name = "Ten";
            else if (i == 1)
                name = "Jack";
            else if (i == 2)
                name = "Queen";
            else
                name = "King";
            Card mycard (10, name);
            decks.push_back(mycard);

        }

    }
    
    decks = shuffle(decks);
    
    int pen_amount = decks.size()-decks.size()*penetration;
    for (int i =0; i<pen_amount; i++)
        decks.pop_back();

}



void deal (vector <Card> &dealerhand, vector <Card> &decks, vector <Player> &players) {
    vector <Card>::iterator iter = decks.begin();


    dealerhand.push_back(decks[0]);
    decks.erase(iter);
    dealerhand.push_back(decks[0]);
    decks.erase(iter);
    
    for (int i=0; i<players.size(); i++)
    players[i].set_hand(decks[0]);
    decks.erase(iter);
    
}


void play (vector <Card> decks) {
    vector <Card> dealerhand;
    int numplayers;
    
    cout << "How many players?";
    cin >> numplayers;
    
    vector <Player> players (numplayers);
    
    vector <int> win (numplayers); // 1= loss, 2=win, 3=push
    
    Card mycard (1, "Ace");
    decks[0] = (mycard);
    
    vector <Card>::iterator iter = decks.begin();
    for (int i =1; i<numplayers +1; i++) {
        string name;
        int start_balance;
        cout << "Player " << i << ": " <<endl;
        cout << "input name";
        cin >> name;
        cout << "input starting balance";
        cin >> start_balance;
        players[i-1]= Player(name, start_balance, start_balance, decks[0]);
        decks.erase(iter);
    }
    
    // need to put it here for initial decks
    for (int i =1; i<numplayers.size(); i++) {
        int counter = 0;
        while (playersum < 21 && counter<2) {
            counter = 0;
            for (int j = 0; j<players[i].get_hand().size(); j++){
                if (players[i].get_hand()[j].get_rank() == 1) {
                    players[i].get_hand()[j].change_rank(11);
                    break; }
            }
            counter++;
        }
        
    } // HAICH D
    
    int playersum;
    int dealersum;
    
    char hs;
    
    deal (dealerhand, decks, players);
    
    dealersum=dealerhand[0].get_rank() + dealerhand[1].get_rank();

    for (int j =0; j<players.size(); j++) { // Player wins if he gets blackjack. Pushes if player and dealer gets blackjack.
        playersum =0;
        for (int i =0; i<players[j].get_hand().size(); i++)
            playersum += players[j].get_hand()[i].get_rank();
        if (dealersum ==21 && playersum !=21) {
            win[j]=1; }
        if (playersum == 21 && dealersum !=21) {
            win[j]=4; }
        if (playersum ==21 && dealersum ==21) {
            win[j]=3; }
    }


    cout<< "dealer is showing a " <<dealerhand[0].get_name() <<endl;
    for (int i =0; i<players.size(); i++) {
        cout << players[i].get_name() << " is showing a " << players[i].get_hand()[0].get_name() << " and " <<players[i].get_hand()[1].get_name() <<". " << players[i].get_name() << " Would you like to hit or stay (h/s)";
        
        cin>>hs;
       
        

        if (win[i]==0)
        player_play (hs, playersum, dealerhand, decks, players, i, win);
        


    }
   
    dealer_play(dealersum, dealerhand, decks);
    
    
    win_test(players, dealersum, win);
    
    for (int i=0; i<win.size(); i++) {
        if (win[i]== 1)
            cout << endl << players[i].get_name() << " you lost!" <<endl;
        if (win[i]==2)
            cout << endl << players[i].get_name() << " you won!" << endl;
        if (win[i]==3)
            cout << endl << players[i].get_name() << " you pushed!" << endl;
        if (win[i]==4)
            cout << endl << players[i].get_name() << " blackjack nigga!" << endl;
    }
    
}

void player_play (char hs, int playersum, vector <Card> dealerhand, vector <Card> &decks, vector<Player> &players, int playa, vector <int> &win) {
    vector <Card>::iterator iter = decks.begin();
    while (hs == 'h' && playersum <21) { // Finishes player's hand. playa is which player.
        players[playa].set_hand(decks[0]);
        decks.erase(iter);
        
        playersum = 0;
        
        for (int i =0; i<players[playa].get_hand().size(); i++)
            playersum += players[playa].get_hand()[i].get_rank();
        int counter = 0;
        while (playersum < 21 && counter<2) { // problem, loops.
            counter = 0;
            for (int j = 0; j<players[playa].get_hand().size(); j++){
                if (players[playa].get_hand()[j].get_rank() == 1) {
                    players[playa].get_hand()[j].change_rank(11);
                    break; }
            }
            counter++;
        }
        
        cout<< "dealer is showing a " <<dealerhand[0].get_name() <<" and you are showing a ";
        
        if (playersum>21) {
            
            for (int i =0; i<players[playa].get_hand().size(); i++)
                cout <<players[playa].get_hand()[i].get_name() <<" and ";
            
            cout << "player bust!" <<endl;
            win[playa]=1;}
        
        else if (playersum <21) {
            for (int i =0; i<players[playa].get_hand().size(); i++)
                cout <<players[playa].get_hand()[i].get_name() <<" and ";
            cout << "would you like to hit or stay (h/s)";
            cin >>hs;}
        else {
            for (int i =0; i<players[playa].get_hand().size(); i++)
                cout <<players[playa].get_hand()[i].get_name() <<" and ";
            cout << "21!" <<endl; }
    }
    
    
}

void dealer_play (int &dealersum, vector <Card> dealerhand, vector <Card> &decks) {
    vector <Card>::iterator iter = decks.begin();
    
    while (dealersum<=16) {
        dealerhand.push_back(decks[0]);
        decks.erase(iter);
        dealersum =0;
        for (int i =0; i<dealerhand.size(); i++)
            dealersum+= dealerhand[i].get_rank(); }
    
    cout << "dealer is showing a ";
    for (int i=0; i<dealerhand.size(); i++) {
        if (i != dealerhand.size()-1)
            cout << dealerhand[i].get_name()<< " and ";
        else
            cout <<dealerhand[dealerhand.size()-1].get_name(); }
    
}

void win_test (vector <Player> players, int dealersum, vector <int> &win) {
    for (int j=0; j<players.size(); j++){
        int playersum =0;
        for (int i =0; i<players[j].get_hand().size(); i++)
            playersum +=players[j].get_hand()[i].get_rank();
        
        cout <<endl << "player sum is" << playersum <<endl ;
        cout << endl << "dealer sum is" <<dealersum << endl;
            
            if (dealersum > 21 && win[j] ==0){
                cout << endl << "dealer bust!" <<endl;
                win [j]=2;}

           else if (playersum < dealersum && win[j] ==0) {
                win[j]=1;}
           else if (playersum > dealersum && win[j] ==0) {
                win[j]=2;}
           else if (playersum == dealersum&& win[j] ==0) {
                win[j]=3; }
    }
    
}

