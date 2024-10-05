// Name: Andre Badrous
// Class CECS 325-02
// Project Name: Prog 1 – One Card War
// Due Date: 12/19/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include "deck.h"
#include <time.h>
#include <iostream>

using namespace std;

Deck::Deck()
{
    char let[4] = {'C', 'S', 'D', 'H'};
    char num[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    int j;
    for (int i = 0; i < 4; i++)
    {
        for (j = 0; j < 13; j++)
        {

            pile[(i) * 13 + j] = Card(num[j], let[i]);
        }
    }
    topcard = 0;
}

Card Deck::deal()
{
    return pile[topcard++];
}

void Deck::print()
{
    for (int i = 0; i < 52; i++)
    {
        pile[i].print();
        if ((i) % 13 == 12)
            cout << endl;
        else
            cout << ",";
    }
}

void Deck::shuffle()
{
    srand(time(0));
    int amount = rand();
    amount = amount % 10000;
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < 52; j++)
        {
            Card temp = pile[j];
            pile[j] = pile[(i + j) % 52];
            pile[(i + j) % 52] = temp;
        }
    }
}