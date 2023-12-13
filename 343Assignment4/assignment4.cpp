#include <iostream>
#include <array>
#include <sstream>
using namespace std;

#include "finite.h"

void test1()
{
    int MAX = 8;
    string arr[MAX] = {"s1", "1", "2", "+", "*", "2", "*", "1"};

    Finite f;
    f.print();
    for(int i = 0;i < MAX;i++)
    {
        f.input(arr[i]);
    }
    f.print();
    cout << "\n\n" << endl;
}

void test2(){
    int MAX = 3;
    string arr[MAX] = {"s1", "1", "2"};
    Finite f;
    for(int i = 0;i < MAX;i++)
    {
        f.input(arr[i]);
    }
    f.print();

    string arr2[MAX] = {"2", "+", "1"};
    for(int i = 0;i < MAX;i++)
    {
        f.input(arr2[i]);
    }
    f.print();
    cout << "\n\n" << endl;
}

int main()
{
    test1();
    test2();
    return 0;
}