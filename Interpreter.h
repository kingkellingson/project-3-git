//
// Created by Kyle Ellingson on 5/26/21.
//

#ifndef PROJECT_0_INTERPRETER_H
#define PROJECT_0_INTERPRETER_H

#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <iostream>
#include <sstream>
#include "Token.h"
#include "Tuple.h"
#include "Relation.h"
#include "Parser.h"
#include "DataStructures.h"

using namespace std;

///Class to hold all of the relations in a Map of strings to Relations

class Database {
private:
    map<string, Relation> myRelations;
public:
    void addRelationToMap (Relation& relationToAdd)
    {
        myRelations.insert(pair<string,Relation> (relationToAdd.getName(), relationToAdd));
    }

    map<string, Relation>& getMap ()
    {
        return myRelations;
    }

    void toString ()
    {
        for (map<string, Relation>::iterator it = myRelations.begin(); it != myRelations.end(); it++)
        {
            cout << endl << endl << "MY RELATION:";
            it->second.toString();
        }
    }
};

///Class to Interpret the vectors of Schemes, Rules, Facts, and Queries from the DatalogProgram the Parser created.

class Interpreter {
private:
    DatalogProgram myProgramToInterpret; //has a DatalogProgram object in it
    Database myDatabase;
public:
    Interpreter (DatalogProgram& parserOutput) : myProgramToInterpret (parserOutput)
    {
        cout << endl << "Received!";
        run();
    }

    void run ()
    {
        CreateRelations(); //Creates the Database according to the Schemes
        FillFacts(); //Fills the Relations with Tuples
        EvaluateQueries();
        cout << endl << "You Made it to the Database toString Function!";
        //myDatabase.toString();
    }

    Relation EvaluatePredicate(Predicate predicate)
    {
        string nameToMatch = predicate.getDescription(); //Determines the name of the desired Relation
        //Tuple tuple = CreateTuple (myProgramToInterpret.getFacts().at(i)); //Creates a tuple from the Fact's parameters

        Relation& myRelation = myDatabase.getMap().at(nameToMatch); //creates an alias of the Relation that matched the name

        for(size_t i = 0; i<predicate.getParameters().size(); ++i) //for every parameter in the predicate list.
        {
            if (predicate.getParameters().at(i)->getDescription().at(0) == '\'' ) //if the first character of the selected predicate is a \'
            {
                cout << endl << "Found a Constant";
                myRelation.ConstantSelect();
            }
            else //if not, then it must be a variable.
            {
                cout << endl << "Found a Variable";
            }
        }

        //myRelation.addTuple(tuple); //Adds the created Tuple to that relation, into its set of Tuples.


        Header header2;
        header2.addAttributeToHeader("D");
        header2.addAttributeToHeader("E");
        header2.addAttributeToHeader("F");

        Tuple first;
        first.addValueToTuple("1");
        first.addValueToTuple("2");
        first.addValueToTuple("3");
        first.setHeaderPointer(header2);

        Tuple second;
        second.addValueToTuple("4");
        second.addValueToTuple("5");
        second.addValueToTuple("6");
        second.setHeaderPointer(header2);

        string toInsert = "Second Relation";

        Relation myRelation2(toInsert, header2);
        myRelation2.addTuple(first);
        myRelation2.addTuple(second);
        return myRelation2;
    }

    void EvaluateQueries ()
    {
        for (size_t i = 0; i < myProgramToInterpret.getQueries().size(); ++i) //for every Fact in the program's Fact vector
        {
            cout << endl;
            myProgramToInterpret.getQueries().at(i)->toString(); //Print out the Query we are looking at.
            cout << "? ";

            //string nameToMatch = myProgramToInterpret.getQueries().at(i)->getDescription(); //Determines the name of the desired Relation
            //Tuple tuple = CreateTuple (myProgramToInterpret.getFacts().at(i)); //Creates a tuple from the Fact's parameters

            Relation EvaluatedPredicate = EvaluatePredicate(*myProgramToInterpret.getQueries().at(i)); //Make a Relation that is evaluated

            if (EvaluatedPredicate.NumberTuples()==0) //Outputs "No" if it does not have any tuples
            {
                cout << "No";
            }
            else
            {
                cout << "Yes(" << EvaluatedPredicate.NumberTuples() << ")"; //And "Yes" with the number of Tuples that matched
                EvaluatedPredicate.toString(); //then prints them out
            }

            //Relation& myRelation = myDatabase.getMap().at(nameToMatch); //creates an alias of the Relation that matched the name
            //myRelation.addTuple(tuple); //Adds the created Tuple to that relation, into its set of Tuples.
        }
    }

    void FillFacts ()
    {
        for (size_t i = 0; i < myProgramToInterpret.getFacts().size(); ++i) //for every Fact in the program's Fact vector
        {
            string nameToMatch = myProgramToInterpret.getFacts().at(i)->getDescription(); //Determines the name of the desired Relation
            Tuple tuple = CreateTuple (myProgramToInterpret.getFacts().at(i)); //Creates a tuple from the Fact's parameters

            Relation& myRelation = myDatabase.getMap().at(nameToMatch); //creates an alias of the Relation that matched the name
            //tuple.setHeaderPointer(myRelation.getHeaderPointer()); //sets the header pointer of that created Tuple.
            myRelation.addTuple(tuple); //Adds the created Tuple to that relation, into its set of Tuples.
        }
    }

    Tuple CreateTuple (Predicate* predicate)
    {
        Tuple newTuple; //makes a new header
        vector <Parameter*> parameters_ = predicate->getParameters(); //makes a vector of Parameter pointers from Predicate
        for (size_t i = 0; i < parameters_.size(); ++i) //for each pointer
        {
            newTuple.addValueToTuple(parameters_.at(i)->getDescription()); //add its description to the Tuple
        }
        return newTuple; //returns the new Tuple
    }

    void CreateRelations ()
    {
        for (size_t i = 0; i < myProgramToInterpret.getSchemes().size(); ++i) //for every Scheme in the program's Scheme vector
        {
            Header header = CreateHeader (myProgramToInterpret.getSchemes().at(i)); //create a header from the parameters
            string name = myProgramToInterpret.getSchemes().at(i)->getDescription(); //gets the name of the Relation

            Relation newRelation (name, header); //Creates a relation from the name and header
            myDatabase.addRelationToMap(newRelation); //adds it to the Database
        }
    }

    Header CreateHeader (Predicate* predicate)
    {
        Header newHeader; //makes a new header
        vector <Parameter*> parameters_ = predicate->getParameters(); //makes a vector of Parameter pointers from Predicate
        for (size_t i = 0; i < parameters_.size(); ++i) //for each pointer
        {
            newHeader.addAttributeToHeader(parameters_.at(i)->getDescription()); //add its description to the Header
        }
        return newHeader; //returns the new Header
    }

};

#endif //PROJECT_0_INTERPRETER_H
