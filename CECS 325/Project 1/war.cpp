// Name: Andre Badrous
// Class CECS 325-02
// Project Name: Prog 1 – One Card War
// Due Date: 12/19/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include "deck.h"
#include <iostream>
using namespace std;

int main()
{
    // Card card = Card('A', 'C');
    // card.print();
    Deck deck = Deck();
    int player1_wins = 0;
    int player2_wins = 0;
    int player1_losses = 0;
    int player2_losses = 0;
    int ties = 0;
    string player1;
    string player2;
    cout << "Enter the name of the first player : ";
    cin >> player1;
    cout << "Enter the name of the second player : ";
    cin >> player2;
    cout << "" << endl;
    cout << " Original Deck" << endl;
    deck.print();
    deck.shuffle();
    cout << "\n Shuffled Deck";
    cout << endl;
    deck.print();

    for (int i = 0; i < 26; i++)
    {
        cout << "\n\nGame " << i + 1 << "\n--------" << endl;
        cout << "         " << player1 << "=>";
        Card card1 = deck.deal();
        Card card2 = deck.deal();
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

    cout << "\n\n------Final Stats-------" << endl;
    cout << "       " << player1 << " vs. " << player2 << endl;
    cout << "Wins   " << player1_wins << "        " << player2_wins << endl;
    cout << "Losses " << player1_losses << "        " << player2_losses << endl;
    cout << "Ties   " << ties << "         " << ties << endl;
    return 0;
}