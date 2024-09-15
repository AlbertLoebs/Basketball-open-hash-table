#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <vector>
#include <cstdlib>



#include "bball.h"
#include "PlayerHash.h"

void readDataFile(vector<Player> &players);
void printPlayers(const vector<Player> &players);
void printPlayers(const vector<Player *> &players);


void printArr(char *arr, int size) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << arr[i];
        if (i != size-1) cout << " ";
    }
    cout << "]" << endl;
    
}


int main()
{
    vector<Player> players;
    
    cout << "\n******************* Reading the data *********************\n";
    readDataFile(players);
    
    string str = "";
        
    bool loop = true;
    double lf = 0;
    char ch;
    string hashOn = "college";
    PlayerHash *ph = nullptr;

    cout<<"Enter a load factor : ";
    cin >> lf;
    cout<<"Hash on college(c) or last name(l) : ";
    cin >> ch;
    if (ch == 'c') {
        hashOn = "college";
    }
    else {
        hashOn = "lastName";
    }
    cout << "Create hash on " << hashOn << " with load factor " << lf << endl;
    ph = new PlayerHash(players, hashOn, lf);

    cout<<"\nMenu:\ns: search on value\np: print the hash table\nq: quit\n";

    while(loop)
    {            
        cout << "Enter a choice: ";
        cin >> ch;
        switch(ch)
        {
            case 'q':
                loop = false;
                break;
            case 'p':
                cout << "Hash table size is " << ph->getTableSize() << endl;
                ph->printTable();
                break;
            case 'c': 
                delete ph;

                break;

            case 's': 
                if (hashOn == "college") {
                    cout<<"Enter college to search : ";
                    string college;
                    cin >> college;
                    cout << "\n*********** Searching for players from << " << college << " **************\n";
                    vector<Player *> collegeplayers;
                    ph->getAllByCollege(college, collegeplayers);
    
                    if (collegeplayers.size() == 0) {
                        cout << "None Found." << endl;
                    }
                    else {
                        printPlayers(collegeplayers);
                    }
                }
                else {
                    cout<<"Enter last name to search : ";
                    string lname;
                    cin >> lname;
                    cout<<"Enter first name to search : ";
                    string fname;
                    cin >> fname;               
                    Player *p = ph->getByName(lname, fname);
                    if (p == nullptr) {
                        cout << "Not Found." << endl;
                    }
                    else {
                        printPlayer(p);
                    }
                }
                break; 

        }
    }
    
    return 0;
}



void printPlayers(const vector<Player> &players) {
    for(size_t i = 0; i < players.size(); i++) {
        cout << players[i].firstName << " " << players[i].lastName << " " <<
        players[i].height << " "<< players[i].weight << " " << players[i].college << endl;
    }
}

void printPlayers(const vector<Player *> &players) {
    for(size_t i = 0; i < players.size(); i++) {
        cout << players[i]->firstName << " " << players[i]->lastName << " " <<
        players[i]->height << " "<< players[i]->weight << " " << players[i]->college << endl;
    }
}

void printPlayer(const Player *p) {
    cout << p->firstName << " " << p->lastName << " " <<
        p->height << " "<< p->weight << " " << p->college << endl;
}

void readDataFile(vector<Player> &players) {
    ifstream inputFile;
    string filename;
    
    //cout << "Enter a filename to read:" << endl;
    //getline (cin, filename);
    filename = "players.txt";
    
    // Open the file.
    inputFile.open(filename);
    
    // If the file successfully opened, process it.
    if (!inputFile.fail())
    {
        char fline[1024];
        inputFile.getline (fline, 1024);  // eat the heading line
        // cout << "read: " << fline << endl;
        
        while(inputFile.getline (fline, 1024)) {
            // cout << "read: " << fline << "\n\n";
            
            // Returns first token
            char* token = strtok(fline, ",");
            
            int field = 1;
            
            Player p;
            
            while (token != NULL) {
                if (field == 2) {
                    p.firstName = token;
                }
                else if (field == 4) {
                    p.lastName = token;
                }
                else if (field == 12) {
                    p.height = atof(token);
                }
                else if (field == 13) {
                    p.weight = atof(token);
                }
                else if (field == 14) {
                    p.college = token;
                }
                else if (field == 16) {
                    char temp[5];
                    for(int i = 0; i<4; i++) {
                        temp[i] = token[i];
                        //if (i==3||i==6) i++;
                    }
                    temp[4]='\0';
                    p.bday = atoi(temp);
                }
                else if (field > 16) {
                    break;
                }
                
                token = strtok(NULL, ",");
                field++;
            }
            
            players.push_back(p);
            
        }
        
        // Close the file.
        inputFile.close();
    }
    
}
