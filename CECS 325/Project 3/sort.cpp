// Name: Andre Badrous
// Class CECS 325-02
// Project Name: Prog 3 – Sort Contest
// Due Date: 10/15/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <fstream>
#include <iostream>

using namespace std;
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void bubble(int a[], int size)
{
    int stack_size = size;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (stack_size - 1); j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
        stack_size--;
    }
    cout << "Ending bubble sort" << endl;
}

int main(int argc, char *argv[])
{
    ofstream fout;
    ifstream fin;
    int n;
    int count = 0;

    fin.open(argv[1]);
    fout.open(argv[2], ios::out | ios::trunc);
    int array[1000000] = {};
    while (fin >> n)
    {
        array[count] = n;
        count++;
    }

    bubble(array, count);

    for (int i = 0; i < count; i++)
    {
        fout << array[i] << endl;
    }
    fout.close();
    fin.close();
    return 0;
}
