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

    while (true) {
	cin >> choice;
	try
	{
		if (choice != 1 and choice != 2 and choice != 3 and choice != 4) {
			throw invalid_argument("");
		}
	}
	catch (const exception&)
	{
		cout << "This command is not available!" << endl;
		continue;
	}
	if (choice == 1) {
		system("cls");
		cout << "---------------------------------" << endl;
		cout << "Take a card - 1\nPass the turn - 2" << endl;
		cout << "---------------------------------" << endl;
		cout << endl;
		cout << "Your hand:\n" << endl;
		hand_player.takeCard(all_cards);
		hand_player.ShowHand();
		points_player = hand_player.AllPoints();
		cout << "---------------------------------" << endl;
		
		if (points_player > 21) {
			cout << "You have more than 21 points - You lost!" << endl;
			cout << endl;
			money -= bet;
			cout << "Your balance: " << money << endl;
			cout << endl;
			cout << "---------------------------------" << endl;
			cout << "Play again - 3\nExit the game - 4" << endl;
			cout << "---------------------------------" << endl;
		}

	}
	else if (choice == 2) {
		while (points_enemy < 20) {  
			system("cls");
			cout << "---------------------------------" << endl;
			cout << "Cards of " << name << ":\n" << endl;
			hand_player.ShowHand();
			points_player = hand_player.AllPoints();
			cout << "---------------------------------" << endl;
			cout << "---------------------------------" << endl; 
			cout << "Dealer's cards:\n" << endl;
			hand_enemy.takeCard(all_cards);
			hand_enemy.ShowHand();
			points_enemy = hand_enemy.AllPoints();
			cout << "---------------------------------" << endl; 
			Sleep(1550);
			if (points_enemy > points_player) { 
				break;
			}
		}

		if ((points_player <= 21 and points_player > points_enemy) or (points_enemy > 21 and points_player <= 21)) {
			cout << name << " won!\n" << endl;
			money += bet;
			cout << "Your balance: " << money << endl;
			cout << endl;
			win_count++;
			ofstream out("victory.txt");
			out << "Number of your victories: " << win_count;
			out.close();
		}
		else if (points_player == points_enemy) {
			cout << "It's a tie\n" << endl;
		}
		else {
			money -= bet;
			cout << "Dealer won!\n" << endl;
			cout << "Your balance: " << money << endl;
			cout << endl;
		}
		cout << "---------------------------------" << endl;
		cout << "Play again - 3\nExit the game - 4" << endl;
		cout << "---------------------------------" << endl;
	}
	else if (choice == 3) {
		system("cls");
		if (money > 0) {
			newDeck(all_cards);
			cout << "For the game to start, you need to make a bet!" << endl;
			cout << endl;
			bet = getBet(money);
			system("cls");
			cout << "---------------------------------" << endl;
			cout << "Take a card - 1\nPass the turn - 2" << endl;
			cout << "---------------------------------" << endl;
			cout << endl;
			cout << "Your hand is empty, take a card!\n" << endl;
			cout << "---------------------------------" << endl;
			points_player = 0;
			points_enemy = 0;

			hand_player.clear_hand();
			hand_enemy.clear_hand();

			continue;
		}
		else {
			cout << name << ", you don't have any money left! The game is over!" << endl;
			break;
		}

	}
	else if (choice == 4) {
		break;
	}
	


}