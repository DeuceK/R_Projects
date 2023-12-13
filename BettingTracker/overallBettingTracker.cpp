#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>

using namespace std;
//Variable Declerations
vector<string>parlaysNFL;
vector<string>betsNFL;
string searchPick;
vector<string>parlaysVect;
vector<string>betsVect;
string searchSection;

vector<string>parlaysNBA;
vector<string>betsNBA;
//overall stats variables
int amountOfBets = 0;
int totalParlays = 0;
int totalSingles = 0;
int wins = 0;
int losses = 0;
float totalMoneySpent = 0;
float percentage = 0;

//header files
#include "ufcBet.h"
#include "nflBet.h"
#include "nba.h"

void nfl(){
    //gets all the parlay information from file and prints out stats
    parlayInformation();
    //prints out stats
    printable();
    //gets all the bets placed along with parlay information
    betInformation();
    //search function
    filter();
}
void ufc(){
    //Goes through parlay file
    getParlayInformation();
    //stats
    printStats();
    //Pulls in betting data
    getBetInformation();
    //search feature
    searchFilter();
}

void nba(){
    //Goes through parlay file
    NBAParlayInformation();
    //stats
    NBAprintable();
    //Pulls in betting data
    NBABetInformation();
    //search feature
    NBAfilter();
}

void stats(){
    getParlayInformation();
    parlayInformation();
    NBAParlayInformation();
    cout << "------------------------STATS------------------------" << endl;
    cout << "Total amount of bets : " << amountOfBets << endl;
    cout << "Total parlays : " << totalParlays << endl;
    cout << "Total singles : " << totalSingles << endl;
    cout << "Record : " << wins << " - " << losses << endl;
    float fwin = wins;
    float floss = losses;
    percentage = (fwin / floss) * 100;
    cout << "Win percentage : " << percentage << "%" << endl;
    cout << "Current bankroll stance : " << totalMoneySpent << endl;
}

int main(){
    cout << "What type of bets are you looking for?\n\tnfl\n\tufc\n\tnba\n\tall" << endl;
    string bettingSport;
    cin >> bettingSport;

    if(bettingSport == "nfl"){
        nfl();
    }
    if(bettingSport == "ufc"){
        ufc();
    }
    if(bettingSport == "all"){
        stats();
    }

    if(bettingSport == "nba"){
        nba();
    }
    return 0;
}