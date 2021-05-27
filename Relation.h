//
// Created by Kyle Ellingson on 5/26/21.
//

#ifndef PROJECT_0_RELATION_H
#define PROJECT_0_RELATION_H

#include <vector>
#include <set>
#include <iterator>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Relation {
private:
    string name;
    Header myHeader;
    set<Tuple> myTuples;
public:
    Relation (string& n, Header& h) : name(n), myHeader(h) {}

    void addTuple (Tuple tupleToAdd)
    {
        myTuples.insert(tupleToAdd);
    }

    string getName ()
    {
        return name;
    }

    void toString ()
    {
        cout << endl << "Name:" << name;
        cout << endl << "Header:" << endl;
        myHeader.toString();
        cout << endl << "Tuples:";
        for (Tuple t : myTuples)
        {
            cout << endl;
            t.toString();
        }
    }
};

#endif //PROJECT_0_RELATION_H
