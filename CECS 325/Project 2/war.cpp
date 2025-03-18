// Name: Andre Badrous
// Class CECS 325-02
// Project Name: Prog 2 – More War (vector)
// Due Date: 10/1/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

class Card
{
private:
    char rank;
    char suit;

public:
    Card(char Rank, char Suit)
    {
        rank = Rank;
        suit = Suit;
    }
    void print()
    {
        if (rank == 'T')
        {
            cout << "10" << suit;
        }
        else
        {
            cout << rank << suit;
        }
    }
    int compare(Card next)
    {
        int temp;
        int temp2;

        if (rank == 'A')
            temp = 1;
        else if (rank == '2')
            temp = 2;
        else if (rank == '3')
            temp = 3;
        else if (rank == '4')
            temp = 4;
        else if (rank == '5')
            temp = 5;
        else if (rank == '6')
            temp = 6;
        else if (rank == '7')
            temp = 7;
        else if (rank == '8')
            temp = 8;
        else if (rank == '9')
            temp = 9;
        else if (rank == 'T')
            temp = 10;
        else if (rank == 'J')
            temp = 11;
        else if (rank == 'Q')
            temp = 12;
        else if (rank == 'K')
            temp = 13;

        if (next.rank == 'A')
            temp2 = 1;
        else if (next.rank == '2')
            temp2 = 2;
        else if (next.rank == '3')
            temp2 = 3;
        else if (next.rank == '4')
            temp2 = 4;
        else if (next.rank == '5')
            temp2 = 5;
        else if (next.rank == '6')
            temp2 = 6;
        else if (next.rank == '7')
            temp2 = 7;
        else if (next.rank == '8')
            temp2 = 8;
        else if (next.rank == '9')
            temp2 = 9;
        else if (next.rank == 'T')
            temp2 = 10;
        else if (next.rank == 'J')
            temp2 = 11;
        else if (next.rank == 'Q')
            temp2 = 12;
        else if (next.rank == 'K')
            temp2 = 13;

        if (temp > temp2)
            return 1;
        else if (temp < temp2)
            return -1;
        else
            return 0;
    }
};

class Deck
{
private:
    vector<Card> deck;

public:
    Deck()
    {
        vector<char> ranks = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
        vector<char> suits = {'C', 'S', 'D', 'H'};
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                deck.push_back(Card(ranks[j], suits[i]));
            }
        }
    }
    Card deal()
    {
        if (isEmpty() == false)
        {
            Card temp = deck.front();
            deck.erase(deck.begin());
            return temp;
        }
        else
        {
            throw 5;
        }
    }
    void print()
    {
        for (int i = 0; i < 52; i++)
        {
            deck[i].print();
            if (i % 13 == 12)
            {
                cout << '\n';
            }
            else
            {
                cout << ',';
            }
        }
    }
    void shuffle()
    {
        srand(time(0));
        int amount = rand();
        amount = amount % 10000;
        for (int i = 0; i < amount; i++)
        {
            for (int j = 0; j < 52; j++)
            {
                Card temp = deck[j];
                deck[j] = deck[(i + j) % 52];
                deck[(i + j) % 52] = temp;
            }
        }
    }
    bool isEmpty()
    {
        if (deck.size() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    Deck deck = Deck();
    int player1_wins = 0;
    int player2_wins = 0;
    int player1_losses = 0;
    int player2_losses = 0;
    int ties = 0;
    string player1;
    string player2;
    int games;
    cout << "Enter the name of the first player : ";
    cin >> player1;
    cout << "Enter the name of the second player : ";
    cin >> player2;
    cout << "How many games will they play? ";
    cin >> games;
    cout << "" << endl;
    cout << " Original Deck" << endl;
    deck.print();
    deck.shuffle();
    cout << "\n Shuffled Deck";
    cout << endl;
    deck.print();

    try
    {
        for (int i = 0; i < games; i++)
        {
            Card card1 = deck.deal();
            Card card2 = deck.deal();

            cout << "\n\nGame " << i + 1 << "\n--------" << endl;
            cout << "         " << player1 << "=>";

            card1.print();
            cout << "\n         " << player2 << "=>";
            card2.print();

            int result = card1.compare(card2);
            if (result == 1)
            {
                cout << "\n"
                     << player1 << "=> Winner";
                ++player1_wins;
                ++player2_losses;
            }
            else if (result == -1)
            {
                cout << "\n"
                     << player2 << "=> Winner";
                ++player1_losses;
                ++player2_wins;
            }
            else
            {
                cout << "\nTie game";
                ++ties;
            }
        }
    }
    catch (...)
    {
        cout << "\nError - deck is empty";
    }

    cout << "\n\n------Final Stats-------" << endl;
    cout << "       " << player1 << " vs. " << player2 << endl;
    cout << "Wins   " << player1_wins << "        " << player2_wins << endl;
    cout << "Losses " << player1_losses << "        " << player2_losses << endl;
    cout << "Ties   " << ties << "         " << ties << endl;
    return 0;
}
