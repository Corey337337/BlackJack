#include <iostream>
#include <string>
#include <vector>
#include "time.h"

using namespace std;

class Card{
private:
    string suit;
    string rank;
    int points;
public:
    Card(string s, string r, int p):suit{s},rank{r},points{p}{}

    int getpoints(){
        return points;
    }

    void print(){
        cout << suit << " " << rank << " - " << points << "points" << endl;
    }
}

class Hand{
private:    
    Vector<Card> my_hand;
public:
    Hand(vector<Card> m):my_hand{m}{}

    void take_card(vector<Card>& all_cards){

        int card = rand() % all_cards.size();
        my_hand.push_back(all_cards[card]);

        vector<Card>::iterator it = all_cards.begin();
        advance(it, card);

        all_cards.erase(it);
    }

    int AllPoints(){
        
        int p = 0;

        for (size_t i = 0; i < my_hand.size(); i++)
        {
	        p += my_hand[i].getpoints();
        }
        cout << endl;

        cout << "All points: " << p << endl;
        return p;
    }

    void ShowHand(){
        for (size_t i = 0; i < my_hand.size(); i++)
        {
            my_hand[i].print();
        }
    }

    void clear_hand(){
        my_hand.clear();
    }
}


int main(){

}