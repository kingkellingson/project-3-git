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

    set<Tuple> GetSetOfTuples ()
    {
        return myTuples;
    }

    void SetSetOfTuples (set<Tuple> input)
    {
        myTuples = input;
    }

    Relation ConstantSelect (string toMatch, size_t index)
    {
        //Relation newRelation = *this; //a copy of the current Relation
        //set<Tuple> oldRelationSet = this->GetSetOfTuples(); // FIXME: Unnecessary copy (for readability)
        set<Tuple> newRelationSet; //the set that I want to return

        for (Tuple t : myTuples) //go through and find the matches
        {
            if (t.getVector().at(index) == toMatch)
            {
                newRelationSet.insert(t);
                //t.setToKeep();
                cout << endl << "Found a Match!";
            }
        }
        this->SetSetOfTuples(newRelationSet);
        return *this;
    }

    string getName ()
    {
        return name;
    }

    int NumberTuples ()
    {
        return myTuples.size();
    }

    Header getHeader ()
    {
        return myHeader;
    }

    void toString ()
    {
        cout << endl << "Tuples:";
        for (Tuple t : myTuples)
        {
            t.toString();
        }
    }
};

#endif //PROJECT_0_RELATION_H
