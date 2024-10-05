// Name: Andre Badrous
// Class CECS 325-02
// Project Name: Prog 1 – One Card War
// Due Date: 12/19/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#ifndef CARD_H
#define CARD_H

class Card {
private:
    char rank;
    char suit;

public:
    Card(char rank, char suit);
    Card();
    void print();
    int compare(Card);
};
#endif