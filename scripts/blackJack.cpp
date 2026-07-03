#include <iostream>
#include <string>
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

int main(){

}