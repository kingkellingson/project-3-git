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

    void ConstantSelect ()
    {

    }

    string getName ()
    {
        return name;
    }

    int NumberTuples ()
    {
        return myTuples.size();
    }

    Header* getHeaderPointer ()
    {
        return &myHeader;
    }

    void toString ()
    {
        //cout << endl << "  ";
        /*for (size_t i = 0; i < myTuples.size(); ++i)
        {
            for (size_t j = 0; j < myHeader.size(); ++j)
            {
                myHeader.toString(i);
                cout << "=";
                myHeader.toString(i)
            }
        }
        cout << endl << "Header:" << endl;
        myHeader.toString();*/
        cout << endl << "Tuples:";
        for (Tuple t : myTuples)
        {
            t.toString();
        }
    }
};

#endif //PROJECT_0_RELATION_H
