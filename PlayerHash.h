#include <list>
#include <functional>   
#include <iomanip>
#include <vector>

#include "bball.h"

class PlayerHash {
    // Finish this class definition
private: 
    list<Player *> *hashTable;
    int tableSize;

    unsigned int calcHash(const string &s) {
    hash<string> str_hash;              
    unsigned int hashValue = str_hash(s);

    unsigned int bucketNum = hashValue % tableSize;
    return bucketNum;
    }

public:
    PlayerHash(vector <Player> &players, string fieldName, double loadFactor){
         tableSize = players.size() / loadFactor; // calculate size of hastable array
       
        // create an empty hashtabale with tablesize elements
        hashTable = new list<Player *>[tableSize];

        // add all player objects from the players vector into our hashtable
        for(unsigned int idx = 0; idx < players.size(); idx++){
            Player *current = &(players[idx]);
            // calc where to add into the table
            string valToHash;
            if(fieldName == "college"){
                valToHash = current->college;
            } else {
                valToHash = current->lastName;
            }
            int hashIdx = calcHash(valToHash);

            hashTable[hashIdx].push_back(current);
        }

    }

    int getTableSize(){
        return tableSize;
    }

    void printTable(){
        for(int i = 0; i < tableSize; i++){
            cout << "[" << i << "]" << "->";
            for(list<Player *>::iterator it = hashTable[i].begin(); it != hashTable[i].end(); it++ ){
                cout << "(" << (*it)->lastName << (*it)->firstName << "," << (*it)->college << ")->";
            }
            cout << endl;
        }
    }
         
Player *getByName(string lName, string fName){
    for(int i = 0; i < tableSize; i++){
        for(list<Player *>::iterator it = hashTable[i].begin(); it != hashTable[i].end(); it++ ){
            if(lName == (*it)->lastName && fName == (*it)->firstName){
                cout << "Found at index " << i << endl;
                return (*it);
            } 
        }
    }
    return nullptr;
}


void getAllByCollege(string col, vector<Player *> &plyrsFromCol){
 int hashIdx = calcHash(col);

    for(int i = 0; i < tableSize; i++){
        for(list<Player *>::iterator it = hashTable[i].begin(); it != hashTable[i].end(); it++ ){
            if(col == (*it)->college){
                plyrsFromCol.push_back(*it);
    }
}
}


}


};
