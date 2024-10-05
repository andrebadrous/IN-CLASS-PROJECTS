// Name: Andre Badrous
// Class CECS 325-02
// Project Name: Prog 1 – One Card War
// Due Date: 12/19/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include "card.h"
#include <string>
using namespace std;

Card::Card()
{
    char rank = 'x';
    char suit = 'x';
}

Card::Card(char RANK, char SUIT)
{
    rank = RANK;
    suit = SUIT;
}

void Card::print()
{
    if (rank == 'T')
    {
        cout << "10" << suit;
    }
    else
        cout << rank << suit;
}

int Card::compare(Card next)
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