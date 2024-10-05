// Name: Andre Badrous
// Class CECS 325-02
// Project Name: Prog 1 – One Card War
// Due Date: 12/19/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#ifndef DECK_H
#define DECK_H
#include "card.h"

class Deck
{
private:
    Card pile[52];
    int topcard;

public:
    Deck();
    Card deal();
    void print();
    void shuffle();
};
#endif