// Name: Andre Badrous
// Class CECS 325-02
// Project Name: Prog 6 – Big Integers
// Due Date: 12/10/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class BigInt
{
private:
    vector<char> v;

public:
    BigInt(vector<char> k)
    {
        v = k;
    };

    BigInt(string len)
    {
        for (int i = 0; i < len.length(); i++)
        {
            v.push_back(char(len[i] - 48));
        }
    };

    BigInt(int n)
    {
        if (n == 0)
            v.push_back(0);
        else
            while (n > 0)
            {
                char digit = n % 10;
                v.insert(v.begin(), digit);
                n /= 10;
            }
    };

    BigInt() {
    };

    BigInt operator-(BigInt num)
    {
        vector<char> new_v;

        int v1_size = this->v.size();
        int v2_size = num.v.size();
        int difference = v1_size - v2_size;

        for (int i = 0; i < difference; i++)
        {
            new_v.push_back(v[i]);
        }

        for (int i = 0; i < v2_size; i++)
        {
            new_v.push_back(v[i + difference] - num.v[i]);
        }

        for (int i = new_v.size() - 1; i > 0; i--)
        {
            if (new_v[i] < 0)
            {
                new_v[i] = new_v[i] + 10;
                new_v[i - 1]--;
            }
            if (new_v[0] == 0)
            {
                new_v.erase(new_v.begin());
            }
        }

        return BigInt(new_v);
    };

    BigInt operator-(int num)
    {
        return (BigInt(this->v) - BigInt(num));
    };

    BigInt operator+(BigInt num)
    {
        vector<char> new_v;
        int size_v1 = v.size() - 1;
        int size_v2 = num.v.size() - 1;

        while (size_v1 >= 0 or size_v2 >= 0)
        {
            if (size_v1 >= 0 and size_v2 >= 0)
            {
                new_v.insert(new_v.begin(), v[size_v1] + num.v[size_v2]);
                size_v1--;
                size_v2--;
            }
            else if (size_v1 >= 0)
            {
                new_v.insert(new_v.begin(), v[size_v1]);
                size_v1--;
            }
            else
            {
                new_v.insert(new_v.begin(), num.v[size_v2]);
                size_v2--;
            }
        }

        new_v.insert(new_v.begin(), 0);
        for (int i = new_v.size() - 1; i >= 0; i--)
        {
            if (new_v[i] > 9)
            {
                new_v[i] = new_v[i] - 10;
                new_v[i - 1] = new_v[i - 1] + 1;
            }
        }
        if (new_v[0] == 0)
        {
            new_v.erase(new_v.begin());
        }
        return BigInt(new_v);
    };

    friend BigInt operator+(int x, BigInt y)
    {
        return (BigInt(x) + y);
    };

    friend ostream &operator<<(ostream &out, BigInt b)
    {
        if (b.v.size() > 12)
        {
            vector<char>::iterator it = b.v.begin();
            int k = 0;
            while (it != b.v.end() and k < 7)
            {
                out << int(*it++);
                if (k == 0)
                {
                    out << ".";
                }
                k++;
            }
            out << "e" << (b.v.size() - 1);
            return out;
        }
        else
        {
            vector<char>::iterator it = b.v.begin();
            while (it != b.v.end())
                out << int(*it++);
            return out;
        }
    };

    BigInt fibo_helper(BigInt n, BigInt a = 1, BigInt b = 1)
    {
        if (n == 1)
        {
            return a;
        }
        else if (n == 2)
        {
            return b;
        }
        else
        {
            return fibo_helper(n - 1, b, a + b);
        }
    }

    BigInt fibo()
    {

        return fibo_helper(this->v);
    };

    bool operator==(BigInt v2)
    {
        if (this->v == v2.v)
        {
            return true;
        }
        else
        {
            return false;
        }
    };
    bool operator!=(BigInt v2)
    {
        if (this->v != v2.v)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    void print()
    {
        vector<char>::iterator it = v.begin();
        while (it != v.end())
            cout << int(*it++);
        cout << endl;
    };

    BigInt operator[](BigInt k)
    {
        return k.v;
    };

    BigInt operator++()
    {
        int end = this->v.size() - 1;

        if (this->v[end] > 8)
        {

            this->v.insert(this->v.begin(), 0);
            this->v[end] = this->v[end] + 1;
            for (int i = this->v.size() - 1; i >= 0; i--)
            {
                if (this->v[i] > 9)
                {
                    this->v[i] = this->v[i] - 10;
                    this->v[i - 1] = this->v[i - 1] + 1;
                }
            }
            if (this->v[0] == 0)
            {
                this->v.erase(this->v.begin());
            }
        }
        else
        {
            this->v[end] = this->v[end] + 1;
        }
        return (this->v);
    };
    BigInt operator++(int)
    {

        BigInt temp = this->v;
        int end = this->v.size() - 1;

        if (this->v[end] > 8)
        {
            this->v[end] = this->v[end] + 1;
            this->v.insert(this->v.begin(), 0);

            for (int i = this->v.size() - 1; i >= 0; i--)
            {
                if (this->v[i] > 9)
                {
                    this->v[i] = this->v[i] - 10;
                    this->v[i - 1] = this->v[i - 1] + 1;
                }
            }
            if (this->v[0] == 0)
            {
                this->v.erase(this->v.begin());
            }
        }
        else
        {
            this->v[end] = this->v[end] + 1;
        }
        return temp;
    };

    BigInt operator/(BigInt y)
    {
        BigInt count(0);
        vector<char> num = this->v;
        BigInt new_v(num);
        while (y < new_v)
        {
            new_v = new_v - y;
            count = count + 1;
        }

        return count;
    };

    BigInt operator%(BigInt y)
    {
        BigInt count(0);
        vector<char> num = this->v;
        BigInt new_v(num);
        while (y < new_v)
        {
            new_v = new_v - y;
            count = count + 1;
        }
        BigInt rem = new_v;

        return rem;
    };

    bool operator<(BigInt b)
    {

        if (this->v.size() < b.v.size())
        {
            return true;
        }
        else if (this->v.size() > b.v.size())
        {
            return false;
        }
        else
        {
            for (int i = 0; i < b.v.size(); i++)
            {
                if (this->v[i] < b.v[i])
                {
                    return true;
                }
                else if (this->v[i] > b.v[i])
                {
                    return false;
                }
            }

            return false;
        }

        return false;
    };

    BigInt operator*(BigInt num)
    {
        BigInt new_v = 0;
        if (BigInt(v) < num)
            for (BigInt i = 0; i < BigInt(v); i++)
            {
                new_v = new_v + num;
            }
        else
        {
            for (BigInt i = 0; i < num; i++)
            {
                new_v = new_v + this->v;
            }
        }
        return new_v;
    };

    BigInt fact_helper(BigInt num)
    {
        if (num == 1)
        {
            return 1;
        }
        else
        {
            return (num * fact_helper(num - 1));
        }
    };

    BigInt fact()
    {
        return fact_helper(this->v);
    };

    int size()
    {
        return (this->v.size());
    };
};

void testUnit()
{
    int space = 10;
    cout << "\a\nTestUnit:\n"
         << flush;
    system("whoami");
    system("date");

    BigInt n1(25);
    BigInt s1("25");
    BigInt n2(1234);
    BigInt s2("1234");
    BigInt n3(n2);

    BigInt fibo(12345);
    BigInt fact(50);
    BigInt imax = INT_MAX;
    BigInt big("9223372036854775807");

    cout << "n1(int)    :" << setw(space) << n1 << endl;
    cout << "s1(str)    :" << setw(space) << s1 << endl;
    cout << "n2(int)    :" << setw(space) << n2 << endl;
    cout << "s2(str)    :" << setw(space) << s2 << endl;
    cout << "n3(n2)     :" << setw(space) << n3 << endl;
    cout << "fibo(12345):" << setw(space) << fibo << endl;
    cout << "fact(50)   :" << setw(space) << fact << endl;
    cout << "imax       :" << setw(space) << imax << endl;
    cout << "big        :" << setw(space) << big << endl;
    cout << "big.print(): ";
    big.print();
    cout << endl;

    cout << n2 << "/" << n1 << " = " << n2 / n1 << " rem " << n2 % n1 << endl;
    cout << "fibo(" << fibo << ") = " << fibo.fibo() << endl;
    cout << "fact(" << fact << ") = " << fact.fact() << endl;

    cout << "10 + n1 = " << 10 + n1 << endl;
    cout << "n1 + 10 = " << n1 + 10 << endl;

    cout << "(n1 == s1)? --> " << ((n1 == s1) ? "true" : "false") << endl;
    cout << "n1++ = ? --> before:" << n1++ << " after:" << n1 << endl;
    cout << "++s1 = ? --> before:" << ++s1 << " after:" << s1 << endl;
    cout << "s2 * big = ? --> " << s2 * big << endl;
    cout << "big * s2 = ? --> " << big * s2 << endl;
}

int main()
{
    testUnit();
    return 0;
}
