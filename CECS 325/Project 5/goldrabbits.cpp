// Name: Andre Badrous
// Class CECS 325-02
// Project Name: Prog 5 – goldRabbits part 1
// Due Date: 11/14/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <time.h>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
using namespace std;

int funct_call_count = 0;

int goldRabbits(int n)
{
    funct_call_count++;
    static vector<int> farm;

    static map<int, int>::iterator it;
    if (n == -1)
    { /*
         cout << "Fibo Map\n--------" << endl;
         for (it = farm.begin(); it != farm.end(); ++it)
         {
             cout << it->first << "  :  " << it->second << endl;
         }*/

        return 0;
    }
    if (farm[n])
    {
        return farm[n];
    }
    if (n == 0 or n == 1)
    {
        farm[n] = 1;
        return 1;
    }

    int rabbit_n;
    if (farm[n - 1] and farm[n - 2])
    {
        rabbit_n = farm[n - 1] + farm[n - 2];
    }
    else
    {
        rabbit_n = goldRabbits(n - 1) + goldRabbits(n - 2);
    }

    if (rabbit_n < farm[n - 1])
    {
        string error_num = to_string(n);
        throw(error_num);
    }

    farm[n] = rabbit_n;

    return farm[n];
}

int main()
{
    int const months = 12 * 10;
    int start = time(0);

    try
    {
        for (int i = 0; i < months; i++)
        {
            int current = time(0);
            cout << setw(5) << current - start << ":";
            cout << " GoldRabbits(" << setw(2) << i << ")=";
            cout << setw(11) << goldRabbits(i);
            cout << "  " << "fiboCount:" << setw(4) << funct_call_count << endl;
        }
    }
    catch (string error)
    {

        cout << " Overflow on:" << error << endl;
        goldRabbits(-1);
    }
    return 0;
}
