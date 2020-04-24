#include "llist.h"
#include "llist.cpp"
#include <iostream>


using namespace std;

void dump(const LList& l)
{
    for(size_t i = 0; i < l.size(); ++i, cout << " ") cout << l[i];
}

int main()
{
    LList l;
    for (int i = 0; i < 100000; ++i) {
        l.push_back(1);
    }
    //cout << "l is full" << endl;
    //LList l1(l);//Было 4.688
    //cout << "l1 is full" << endl;
    LList l2(move(l));//После move стало 2.344
    //cout << "l2 is full" << endl;
    //cout << "l1 size is: " << l1.size() << endl;
    //cout << "l2 size is: " << l2.size() << endl;
    return 0;
}
