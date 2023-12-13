#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<algorithm>

//"C:\Users\caele\Downloads\UFC BETS LOG.txt"
using namespace std;
//Variable Declerations
vector<string>parlaysVect;
vector<string>betsVect;
string searchSection;

//Bets search feature
string betSearch(string searchSection) {
    //cout << "What section would you like to search? (event, name, parlayid, )" << endl;
    //string searchSection;
    //cin >> searchSection;
    //Search by eventid
    if (searchSection == "event") {
        cout << "Which event are you looking for?" << endl;
        string specificEvent;
        cin >> specificEvent;
        cout << "Here is everything you bet on " << specificEvent << ":\n" << endl;
        for (int i = 0; i < betsVect.size(); i++) {
            string buffer = betsVect[i];
            if(buffer.find(specificEvent) != string::npos) {
                cout << betsVect[i+1] << " vs " << betsVect[i+2] << "\n\tOdds : " << betsVect[i+3] << "\n\tParlay ID : " << betsVect[i+4] << endl;
            }
        }
    }
    //Search by name
    if(searchSection == "name"){
        cout << "Which fighter are you looking for?" << endl;
        string specificName;
        cin >> specificName;
        cout << "Here is every time you have bet on " << specificName << ":\n" << endl;
        for (int i = 0; i < betsVect.size(); i++) {
            string buffer = betsVect[i];
            if(buffer.find(specificName) != string::npos) {
                if((betsVect[i+2].find("-") != string::npos) || (betsVect[i+2].find("+") != string::npos)) {
                    cout << betsVect[i] << " vs " << betsVect[i+1] << "\n\tOdds : " << betsVect[i+2] << "\n\tParlay ID : " << betsVect[i+3] << "\n\tEvent : " << betsVect[i-1] << endl;
                }
                else {
                    cout << betsVect[i-1] << " vs " << betsVect[i] << "\n\tOdds : " << betsVect[i+1] << "\n\tParlay ID : " << betsVect[i+2] << "\n\tEvent : " << betsVect[i-2] << endl;
                }
            }
        }
    }
    //Search by parlayid
    if(searchSection == "parlayid"){
        cout << "Which parlay(id) are you looking for?" << endl;
        string specificParlay;
        cin >> specificParlay;
        cout << "Here is what was on the parlay ticket " << specificParlay << ":\n" << endl;
        for (int i = 0; i < betsVect.size(); i++) {
            string buffer = betsVect[i];
            if(buffer.find(specificParlay) != string::npos) {
                cout << "\t" << betsVect[i-3] << " vs " << betsVect[i-2] << endl;
                cout << "\tOdds : " << betsVect[i-1] << endl;
            }
        }
    }
    return searchSection;
}

//Parlays search
string parlaySearch(string searchSection){
// most bet on fighter
//most profitable fighter

    //Search for fighter that is bet on the most
    if (searchSection == "popular") {
        cout << "popular" << endl;
    }
    //search for fighter that has made the most profit
    if (searchSection == "fighter") {
        cout << "fighter" << endl;
    }
    //profit by method
    if (searchSection == "method"){
        cout << "method" << endl;
        //



    }
    return searchSection;
}

//searchFiltration
void searchFilter(){
    cout << "-----------------------------------------------------------\n" << endl;
    cout << "Would you like to search for something? ('yes' if so)" << endl;
    string searchQuestion;
    cin >> searchQuestion;
    if(searchQuestion == "yes"){
        //cout << "Choose of the following options : (\n\tevent\n\tname\n\tparlayid\n\t'popular' for most bet on fighter\n\t'fighter' for most profitable fighter\n\t'method' for most profitable method" << endl;
        cout << "Choose of the following options : \n\tevent\n\tname\n\tparlayid" << endl;
        cin >> searchSection;
        //events, name, or parlayid search
        if(searchSection == "event" || "name" || "parlayid") {
            betSearch(searchSection);
        }
        //Profit or amount search
        //if(searchSection == "popular" || "method" || "fighter"){
             //parlaySearch(searchSection);
        //}
    }
}

//Gets parlay information and stats
void getParlayInformation(){
    ifstream parlayFile ("C:\\Users\\caele\\Downloads\\BettingTxtFiles\\parlayIDFormatted.txt");

    //assures file is open correctly
    if (parlayFile.is_open()){
        string buffer;
        //gets each line and prints it out
        while ( getline (parlayFile,buffer) ){
            parlaysVect.push_back(buffer);
        }
        parlayFile.close();
    }
        //Lets you know if file wasn't opened properly
    else{
        cout << "Unable to open file";
    }
    //Stats section that shows record and calculations
    cout << "\n---------------------------STATS---------------------------" << endl;
    //Win percentage
    float totalBet = 0;
    float positiveAmount = 0;
    float negativeAmount = 0;
    int winCount = 0;
    int lossCount = 0;
    int singlesCount = 0;
    for(int z = 0;z < parlaysVect.size();z++){
        string checker = parlaysVect[z];
        //check for wins
        if(checker.find("W") != string::npos){
            winCount++;
        }
        //check for losses
        if(checker.find("L") != string::npos){
            lossCount++;
        }
        //check for total amount bet
        if(checker.find("$") != string::npos){
            string moneySign = checker;
            moneySign.erase(remove(moneySign.begin(), moneySign.end(), '$'), moneySign.end());
            moneySign.erase(remove(moneySign.begin(), moneySign.end(), '\t'), moneySign.end());
            if(checker.find("-") != string::npos){
                moneySign.erase(remove(moneySign.begin(), moneySign.end(), '-'), moneySign.end());
                float betAmnt = stof (moneySign);

                negativeAmount +=betAmnt;
            }
            float betAmnt = stof (moneySign);
            totalBet +=betAmnt;
        }
        //adding up total money made
        if(checker.find("+") != string::npos){
            string posiSign = checker;
            posiSign.erase(remove(posiSign.begin(), posiSign.end(), '+'), posiSign.end());
            posiSign.erase(remove(posiSign.begin(), posiSign.end(), '\t'), posiSign.end());
            float betAmnt = stof (posiSign);
            positiveAmount +=betAmnt;
        }
        //
        if(checker.find("single") != string::npos){
            singlesCount++;
        }
    }
    //Final print out with all stats
    int totalBetsCount = winCount + lossCount;
    int parlaysCount = totalBetsCount - singlesCount;
    cout << "Since August 13th 2022 you have placed : " << totalBetsCount << " total bets." << endl;
    cout << singlesCount << " were singles and " << parlaysCount << " were parlays.\n" << endl;
    cout << "You have bet a total amount of = $" << totalBet << endl;
    cout << "With these bets you have come up with a record of " << winCount << " wins and " << lossCount << " losses." <<endl;
    float wC = winCount;
    float tBC = totalBetsCount;
    float winPercentage = (wC / tBC) * 100;
    cout << "Giving you a win percentage of " << winPercentage << "%" << endl;
    positiveAmount -= negativeAmount;
    if(positiveAmount > 0){
        cout << "Congrats! You are positive for a total amount of $" << positiveAmount << endl;
    }
    else{
        cout << "You are negative a total amount of $" << positiveAmount << endl;
    }
}

//Gets Betting Information
void getBetInformation(){
    //opens file using path
    string currentLine;
    ifstream myfile ("C:\\Users\\caele\\Downloads\\BettingTxtFiles\\ufcLogFormatted.txt");

    //assures file is open correctly
    if (myfile.is_open()){
        int count = 0;
        //gets each line and prints it out
        while ( getline (myfile,currentLine) ){
            for_each(currentLine.begin(), currentLine.end(), [](char & c) {
                c = ::tolower(c);
            });
            betsVect.push_back(currentLine);
            count++;
        }

        //takes out all the tabs
        for(int z = 0;z < betsVect.size();z++){
            string checker = betsVect[z];
            if(checker.find("\t") != string::npos) {
                string tabFound = checker;
                tabFound.erase(remove(tabFound.begin(), tabFound.end(), '\t'), tabFound.end());
                betsVect[z] = tabFound;
                //cout << "-" << tabFound << "-" << endl;
            }
        }

        myfile.close();
    }
    //Lets you know if file wasn't opened properly
    else{
        cout << "Unable to open file";
    }
}

int main() {
    //Goes through parlay file and prints out money and record stats
    getParlayInformation();

    //Pulls in betting data
    getBetInformation();

    //search feature
    searchFilter();
    return 0;
}