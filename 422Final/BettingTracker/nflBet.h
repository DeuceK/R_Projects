//
// Created by caele on 9/20/2022.
//

#ifndef NFL_NFLBET_H
#define NFL_NFLBET_H

float totalBet = 0;
float positiveAmount = 0;
float negativeAmount = 0;
int winCount = 0;
int lossCount = 0;
int singlesCount = 0;
int totalBetsCount;
int parlaysCount;
float wC;
float tBC;
float winPercentage;

//Bets search feature
void search() {
    cout << "Choose of the following options : \n\tteam\n\tweek\n\tparlayid\n\tpoints\n\tspread\n\tmoneyline" << endl;
    cin >> searchPick;
    //Search by week
    if (searchPick == "week") {
        cout << "Which week are you looking for?" << endl;
        string specificWeek;
        cin >> specificWeek;
        cout << "Here is everything you bet on in week " << specificWeek << ":\n" << endl;
        for (int i = 0; i < betsNFL.size(); i++) {
            string buffer = betsNFL[i];
            if(buffer.find(specificWeek) != string::npos) {
                if(buffer.find("-")!= string::npos){
                }
                else{
                    if(buffer.find("+")!= string::npos){
                    }
                    else{
                        cout << betsNFL[i-3] << " vs " << betsNFL[i-2] << "\n\tOdds : " << betsNFL[i-1] << "\n\tParlay ID : " << betsNFL[i] << endl;
                    }
                }
            }
        }
    }
    //Search by team
    if(searchPick == "team"){
        cout << "Which team are you looking for?" << endl;
        string specificTeam;
        cin >> specificTeam;
        cout << "Here is every time you have bet on " << specificTeam << ":\n" << endl;
        for (int i = 0; i < betsNFL.size(); i++) {
            string buffer = betsNFL[i];
            if(buffer.find(specificTeam) != string::npos) {
                if((betsNFL[i+2].find("-") != string::npos) || (betsNFL[i+2].find("+") != string::npos)) {
                    cout << betsNFL[i] << " vs " << betsNFL[i+1] << "\n\tOdds : " << betsNFL[i+2] << "\n\tParlay ID : " << betsNFL[i+3] << endl;
                }
                else {
                    cout << betsNFL[i-1] << " vs " << betsNFL[i] << "\n\tOdds : " << betsNFL[i+1] << "\n\tParlay ID : " << betsNFL[i+2] << endl;
                }
            }
        }
    }
    //Search by parlayid
    if(searchPick == "parlayid"){
        cout << "Which parlay(id) are you looking for?" << endl;
        string parlayPick;
        cin >> parlayPick;
        cout << "Here is what was on the parlay ticket " << parlayPick << ":\n" << endl;
        for (int i = 0; i < betsNFL.size(); i++) {
            string buffer = betsNFL[i];
            if(buffer.find(parlayPick) != string::npos) {
                cout << "\t" << betsNFL[i-3] << " vs " << betsNFL[i-2] << endl;
                cout << "\tOdds : " << betsNFL[i-1] << endl;
            }
        }
    }
    //look up over/under
    if(searchPick == "points"){
        cout << "Are you looking for your stats on the over or under?" << endl;
        string pointsChoice;
        cin >> pointsChoice;
        cout << "Here are your stats on the " << pointsChoice << ":\n" << endl;
        for (int i = 0; i < betsNFL.size(); i++) {
            string buffer = betsNFL[i];
            if (buffer.find(pointsChoice) != string::npos) {
                cout << betsNFL[i] << "\t\t\t\t" << betsNFL[i + 1] << "\t\t\t\t" << betsNFL[i + 2] << "\t\t\t\t"
                     << betsNFL[i + 3] << endl;
            }
        }
    }
    //spread stats
    if(searchPick == "spread"){
        cout << "Here are yous stats on the spread:\n" << endl;
        for(int i = 0;i < betsNFL.size(); i = i+4){
            string buffer = betsNFL[i];
            if(buffer.find("-") != string::npos){
                cout << betsNFL[i] << "\tvs\t" << betsNFL[i + 1] << "\n\t" << betsNFL[i + 2] << "\n\t" << betsNFL[i + 3] << endl;
            }
            if(buffer.find("+") != string::npos){
                cout << betsNFL[i] << "\tvs\t" << betsNFL[i + 1] << "\n\t" << betsNFL[i + 2] << "\n\t" << betsNFL[i + 3] << endl;
            }
        }
    }
    //moneyline stats
    if(searchPick == "moneyline"){
        cout << "Here are yous stats on the moneyline:\n" << endl;
        for(int i = 0;i < betsNFL.size(); i = i+4){
            string buffer = betsNFL[i];
            if(buffer.find("-") != string::npos) {}
            else{
                if(buffer.find("+") != string::npos) {}
                else{
                    if(buffer.find("over")!= string::npos){}
                    else{
                        if(buffer.find("under")!= string::npos){}
                        else{
                            string secondLayer = betsNFL[i+1];
                            if(secondLayer.find("receptions")!= string::npos){}
                            else{
                                if(secondLayer.find("td")!= string::npos){}
                                else{
                                    if(secondLayer.find("yards")!= string::npos) {}
                                    else{
                                        cout << betsNFL[i] << "\tvs\t" << betsNFL[i + 1] << "\n\t" << betsNFL[i + 2] << "\n\t" << betsNFL[i + 3] << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "\nWould you like to keep searching?" << endl;
    string research;
    cin >> research;
    if(research == "yes") {
        search();
    }
}

//searchFiltration
void filter(){
    cout << "-----------------------------------------------------------\n" << endl;
    cout << "Would you like to search for something? ('yes' if so)" << endl;
    string searchQuestion;
    cin >> searchQuestion;
    if(searchQuestion == "yes") {
        //events, name, or parlayid search
        search();
    }
    else{
        cout << "search not ran" << endl;
    }
}

//Gets parlay information and stats
void parlayInformation(){
    ifstream parlayFile ("C:\\Users\\caele\\Downloads\\BettingTxtFiles\\FormattedNFLParlays.txt");

    //assures file is open correctly
    if (parlayFile.is_open()){
        string buffer;
        int count2 = 0;
        //gets each line and prints it out
        while ( getline (parlayFile,buffer) ){
            parlaysNFL.push_back(buffer);
            count2++;
        }
        parlayFile.close();
    }
        //Lets you know if file wasn't opened properly
    else{
        cout << "Unable to open file";
    }
    //Stats section that shows record and calculations
    //Win percentage

    for(int z = 0;z < parlaysNFL.size();z++){
        string checker = parlaysNFL[z];
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
    totalBetsCount = winCount + lossCount;
    parlaysCount = totalBetsCount - singlesCount;
    wC = winCount;
    tBC = totalBetsCount;
    winPercentage = (wC / tBC) * 100;
    positiveAmount -= negativeAmount;

    //ending calculations
    amountOfBets += totalBetsCount;
    totalParlays += parlaysCount;
    totalSingles += singlesCount;
    wins += winCount;
    losses+= lossCount;
    totalMoneySpent += positiveAmount;
}

void printable(){
    cout << "\n---------------------------STATS---------------------------" << endl;
    cout << "During the 2022-2023 NFL season you have placed : " << totalBetsCount << " total bets." << endl;
    cout << singlesCount << " were singles and " << parlaysCount << " were parlays.\n" << endl;
    cout << "You have bet a total amount of = $" << totalBet << endl;
    cout << "With these bets you have come up with a record of " << winCount << " wins and " << lossCount << " losses." <<endl;

    cout << "Giving you a win percentage of " << winPercentage << "%" << endl;
    if(positiveAmount > 0){
        cout << "Congrats! You are positive for a total amount of $" << positiveAmount << endl;
    }
    else{
        cout << "You are negative a total amount of $" << positiveAmount << endl;
    }
}


//Gets Betting Information
void betInformation(){
    //opens file using path
    string currentLine;
    ifstream fileNFL ("C:\\Users\\caele\\Downloads\\BettingTxtFiles\\FormattedNFLBets.txt");

    //assures file is open correctly
    if (fileNFL.is_open()){
        int count = 0;
        //gets each line and prints it out
        while ( getline (fileNFL,currentLine) ){
            for_each(currentLine.begin(), currentLine.end(), [](char & c) {
                c = ::tolower(c);
            });
            betsNFL.push_back(currentLine);
            count++;
        }

        //takes out all the tabs
        for(int z = 0;z < betsNFL.size();z++){
            string checker = betsNFL[z];
            if(checker.find("\t") != string::npos) {
                string tabFound = checker;
                tabFound.erase(remove(tabFound.begin(), tabFound.end(), '\t'), tabFound.end());
                betsNFL[z] = tabFound;
                //cout << "-" << tabFound << "-" << endl;
            }
        }

        fileNFL.close();
    }
        //Lets you know if file wasn't opened properly
    else{
        cout << "Unable to open file";
    }
}



#endif //NFL_NFLBET_H
