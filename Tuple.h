//
// Created by Kyle Ellingson on 5/26/21.
//

#ifndef PROJECT_0_TUPLE_H
#define PROJECT_0_TUPLE_H

#include <vector>
#include <set>
#include <iterator>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Tuple {
private:
    vector<string> values;
public:

    bool operator< (const Tuple& other) const
    {
        if (this->getVector() < other.getVector())
        {
            return true;
        }
        else return false;
    }

    vector<string> getVector () const
    {
        return values;
    }

    void addValueToTuple (string valueToAdd)
    {
        values.push_back(valueToAdd);
    }

    void toString ()
    {
        for (size_t i = 0; i < values.size(); ++i)
        {
            if (i == 0)
            {
                cout << values.at(i);
            }
            else
            {
                cout << "," << values.at(i);
            }
        }
    }
};

class Header {
private:
    vector<string> attributes;
public:
    Header (vector<string> input) : attributes (input) {}
    Header () {}

    void addAttributeToHeader (string valueToAdd)
    {
        attributes.push_back(valueToAdd);
    }

    void toString ()
    {
        for (size_t i = 0; i < attributes.size(); ++i)
        {
            if (i == 0)
            {
                cout << attributes.at(i);
            }
            else
            {
                cout << "," << attributes.at(i);
            }
        }
    }
};

#endif //PROJECT_0_TUPLE_H
