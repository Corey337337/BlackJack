#include <iostream>
#include <string>
#include <vector>
#include "time.h"
#include <conio.h>
#include <windows.h>
#include <fstream>

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

void newDeck(vector<Card>& all_cards) {
	all_cards.clear();
	string suits[4] = { "Пики", "Черви", "Бубны", "Трефы" };
	string ranks[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Валет", "Дама", "Король", "Туз" };
	int pointss[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 13; j++)
		{
			Card c(suits[i], ranks[j], pointss[j]);
			all_cards.push_back(c);
		}
	}
}

int money = 1000;

int getBet(int m) {
	int bet;
	while (true) {
		cout << "Your balance: " << m << endl;
		cout << "Enter your bet: ";
		cin >> bet;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Please enter a number!" << endl;
			continue;
		}

		if (bet <= 0) {
			cout << "The bet must be a positive number!" << endl;
		}
		else if (bet > m) {
			cout << "Not enough money! Maximum: " << m << endl;
		}
		else {
			return bet; 
		}
	}
}

int main(){
    setlocale(LC_ALL, "");
    srand(time(0));


    vector<Card> all_cards;
    newDeck(all_cards);



    string name;
    cout << "Welcome to BlackJack!\nPlease enter your name: ";
    getline(cin, name);
    system("cls");

    vector<Card> player;
    vector<Card> enemy;


    Hand hand_player(player);
    Hand hand_enemy(enemy);


    int choice = 0;

    int win_count = 0;

    int points_player = 0;
    int points_enemy = 0;

    cout << "Hello, " << name << "!" << endl;
    cout << "To start the game you need to make a bet!" << endl;
    cout << endl;
    int bet = getBet(money);

    system("cls");
    cout << "Great! Your bet is: " << bet <<" \nTo start the game please enter - 1" << endl;
}