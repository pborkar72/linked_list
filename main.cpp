#include <iostream>
#include "linkedlist.h"

int main() {
    linkedlist<int> list;
    for(int i = 0; i < 11; i++)
        list.push_back(i);

    linkedlist<int> list2;
    list2 = list;
    list2.print();
    list.remove(5);
    list2.print();
    list.print();
}
