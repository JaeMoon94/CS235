#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <set>
#include <unordered_set>
#include "LinkedList.h"
// #include "BST.h"
// #include "AVL.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Not enough arguments.  Expected and integer N" << endl;
        return -1;
    }

    srand(time(NULL));
    int N = atoi(argv[1]);
    long theStart, theEnd;
    int num;

    // select one of the following implementations of a set by declaring the variable s to be of that type
    // set<int> s;
    // unordered_set<int> s;
    LinkedList<int> s;
    // BST s;
    // AVL s;

    for (int i = 0; i < N; i++) {
        num = rand(); // this is for random data. To get ordered data, change it to: num = i;
        s.insertHead(num); // for BST and AVL sets, you'll need to change this to s.add(num)
                       // for a LinkedList set, you can change it to s.insertHead(num)
    }


    theStart = clock();

    for (int i = 0; i < N; i++) {
        num = rand();
        s.remove(num);  // for LinkedList, BST, and AVL sets, you'll need to change this to s.remove(num)
    }

    theEnd = clock();
    cout << "time required to delete " << N << " integers into the set: " << ((theEnd - theStart)/(double)CLOCKS_PER_SEC) << endl;

    return 0;
}