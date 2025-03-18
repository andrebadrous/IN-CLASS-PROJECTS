// Name: Andre Badrous
// Class CECS 325-02
// Project Name: Prog 4 – Threads
// Due Date: 10/31/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
using namespace std;

long long total_swaps = 0;
mutex mtx;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void bubble(int *a, int size, int name)
{

    long long swaps = 0;
    int stack_size = size;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < (stack_size - 1); j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                swaps++;
            }
        }
        stack_size--;
    }
    cout << "Process " << name << " swap count: " << swaps << endl;
    mtx.lock();
    total_swaps += swaps;
    mtx.unlock();
}

void merge(int a[], int b[])
{
    int *ptr1 = &a[0];
    int *ptr2 = &b[0];
    int distance = ptr2 - ptr1;
    int left = 0;
    int right = 0;
    int *nums = new int[distance + distance];
    int count = 0;

    while (left != distance and right != distance)
    {
        if (a[left] < b[right])
        {
            nums[count] = a[left];
            count++;
            left++;
        }
        else if (a[left] > b[right])
        {
            nums[count] = b[right];
            count++;
            right++;
        }
        else
        {
            nums[count] = a[left];
            count++;
            nums[count] = b[right];
            count++;
            right++;
            left++;
        }
    }
    if (left == distance)
    {
        int left_over = distance - right;
        for (int i = 0; i < left_over; i++)
        {
            nums[count] = b[right];
            count++;
            right++;
            ;
        }
    }
    else
    {
        int left_over = distance - left;
        for (int i = 0; i < left_over; i++)
        {
            nums[count] = a[left];
            count++;
            left++;
            ;
        }
    }
    for (int i = 0; i < (distance + distance); i++)
    {
        a[i] = nums[i];
    }
    delete[] nums;
}

int main(int argc, char *argv[])
{
    int array_size;
    if (argc != 3)
    {
        array_size = 1000000;
    }
    else
    {
        array_size = 10000;
    }
    ofstream fout;
    ifstream fin;
    int n;
    int full_count = 0;

    fin.open(argv[1]);
    fout.open(argv[2], ios::out | ios::trunc);
    int *array = new int[array_size];
    while (fin >> n)
    {
        array[full_count] = n;
        full_count++;
    }
    int count = full_count / 16;

    thread t1(bubble, array + (count * 0), count, 0);
    thread t2(bubble, array + (count * 1), count, 1);
    thread t3(bubble, array + (count * 2), count, 2);
    thread t4(bubble, array + (count * 3), count, 3);
    thread t5(bubble, array + (count * 4), count, 4);
    thread t6(bubble, array + (count * 5), count, 5);
    thread t7(bubble, array + (count * 6), count, 6);
    thread t8(bubble, array + (count * 7), count, 7);
    thread t9(bubble, array + (count * 8), count, 8);
    thread t10(bubble, array + (count * 9), count, 9);
    thread t11(bubble, array + (count * 10), count, 10);
    thread t12(bubble, array + (count * 11), count, 11);
    thread t13(bubble, array + (count * 12), count, 12);
    thread t14(bubble, array + (count * 13), count, 13);
    thread t15(bubble, array + (count * 14), count, 14);
    thread t16(bubble, array + (count * 15), count, 15);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();
    t11.join();
    t12.join();
    t13.join();
    t14.join();
    t15.join();
    t16.join();

    merge(array + (count * 0), array + (count * 1));
    merge(array + (count * 2), array + (count * 3));
    merge(array + (count * 4), array + (count * 5));
    merge(array + (count * 6), array + (count * 7));
    merge(array + (count * 8), array + (count * 9));
    merge(array + (count * 10), array + (count * 11));
    merge(array + (count * 12), array + (count * 13));
    merge(array + (count * 14), array + (count * 15));

    merge(array + (count * 0), array + (count * 2));
    merge(array + (count * 4), array + (count * 6));
    merge(array + (count * 8), array + (count * 10));
    merge(array + (count * 12), array + (count * 14));

    merge(array + (count * 0), array + (count * 4));
    merge(array + (count * 8), array + (count * 12));

    merge(array + (count * 0), array + (count * 8));

    cout << "Total swaps: " << total_swaps << endl;
    for (int i = 0; i < full_count; i++)
    {
        fout << array[i] << endl;
    }
    fout.close();
    fin.close();
    delete[] array;
    return 0;
}
