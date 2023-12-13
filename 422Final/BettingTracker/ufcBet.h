//
// Created by caele on 9/20/2022.
//

#ifndef NFL_UFCBET_H
#define NFL_UFCBET_H
float UFCtotalBet = 0;
float UFCpositiveAmount = 0;
float UFCnegativeAmount = 0;
int UFCwinCount = 0;
int UFClossCount = 0;
int UFCsinglesCount = 0;
int UFCtotalBetsCount;
int UFCparlaysCount;
float UFCwC;
float UFCtBC;
float UFCwinPercentage;


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

    for(int z = 0;z < parlaysVect.size();z++){
        string checker = parlaysVect[z];
        //check for wins
        if(checker.find("W") != string::npos){
            UFCwinCount++;
        }
        //check for losses
        if(checker.find("L") != string::npos){
            UFClossCount++;
        }
        //check for total amount bet
        if(checker.find("$") != string::npos){
            string moneySign = checker;
            moneySign.erase(remove(moneySign.begin(), moneySign.end(), '$'), moneySign.end());
            moneySign.erase(remove(moneySign.begin(), moneySign.end(), '\t'), moneySign.end());
            if(checker.find("-") != string::npos){
                moneySign.erase(remove(moneySign.begin(), moneySign.end(), '-'), moneySign.end());
                float betAmnt = stof (moneySign);

                UFCnegativeAmount +=betAmnt;
            }
            float betAmnt = stof (moneySign);
            UFCtotalBet +=betAmnt;
        }
        //adding up total money made
        if(checker.find("+") != string::npos){
            string posiSign = checker;
            posiSign.erase(remove(posiSign.begin(), posiSign.end(), '+'), posiSign.end());
            posiSign.erase(remove(posiSign.begin(), posiSign.end(), '\t'), posiSign.end());
            float betAmnt = stof (posiSign);
            UFCpositiveAmount +=betAmnt;
        }
        //
        if(checker.find("single") != string::npos){
            UFCsinglesCount++;
        }
    }
    //Final print out with all stats
    UFCtotalBetsCount = UFCwinCount + UFClossCount;
    UFCparlaysCount = UFCtotalBetsCount - UFCsinglesCount;
    UFCwC = UFCwinCount;
    UFCtBC = UFCtotalBetsCount;
    UFCwinPercentage = (UFCwC / UFCtBC) * 100;
    UFCpositiveAmount -= UFCnegativeAmount;
    //ending calculations
    amountOfBets += UFCtotalBetsCount;
    totalParlays += UFCparlaysCount;
    totalSingles += UFCsinglesCount;
    wins += UFCwinCount;
    losses+= UFClossCount;
    totalMoneySpent += UFCpositiveAmount;
}
void printStats(){
    cout << "\n---------------------------STATS---------------------------" << endl;
    cout << "Since August 13th 2022 you have placed : " << UFCtotalBetsCount << " total bets." << endl;
    cout << UFCsinglesCount << " were singles and " << UFCparlaysCount << " were parlays.\n" << endl;
    cout << "You have bet a total amount of = $" << UFCtotalBet << endl;
    cout << "With these bets you have come up with a record of " << UFCwinCount << " wins and " << UFClossCount << " losses." <<endl;
    cout << "Giving you a win percentage of " << UFCwinPercentage << "%" << endl;
    if(UFCpositiveAmount > 0){
        cout << "Congrats! You are positive for a total amount of $" << UFCpositiveAmount << endl;
    }
    else{
        cout << "You are negative a total amount of $" << UFCpositiveAmount << endl;
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



#endif //NFL_UFCBET_H

