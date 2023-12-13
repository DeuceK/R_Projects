//
// Created by caele on 10/19/2022.
//

#ifndef NBA_H
#define NBA_H

float NBAtotalBet = 0;
float NBApositiveAmount = 0;
float NBAnegativeAmount = 0;
int NBAwinCount = 0;
int NBAlossCount = 0;
int NBAsinglesCount = 0;
int NBAtotalBetsCount;
int NBAparlaysCount;
float NBAwC;
float NBAtBC;
float NBAwinPercentage;

//Bets search feature
void NBAsearch() {
    cout << "Choose of the following options : \n\tteam\n\tparlayid\n\tpoints\n\tspread\n\tmoneyline" << endl;
    cin >> searchPick;

    //Search by team
    if(searchPick == "team"){
        cout << "Which team are you looking for?" << endl;
        string specificTeam;
        cin >> specificTeam;
        cout << "Here is every time you have bet on " << specificTeam << ":\n" << endl;
        for (int i = 0; i < betsNBA.size(); i++) {
            string buffer = betsNBA[i];
            if(buffer.find(specificTeam) != string::npos) {
                if((betsNBA[i+2].find("-") != string::npos) || (betsNBA[i+2].find("+") != string::npos)) {
                    cout << betsNBA[i] << " vs " << betsNBA[i+1] << "\n\tOdds : " << betsNBA[i+2] << "\n\tParlay ID : " << betsNBA[i+3] << endl;
                }
                else {
                    cout << betsNBA[i-1] << " vs " << betsNBA[i] << "\n\tOdds : " << betsNBA[i+1] << "\n\tParlay ID : " << betsNBA[i+2] << endl;
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
        for (int i = 0; i < betsNBA.size(); i++) {
            string buffer = betsNBA[i];
            if(buffer.find(parlayPick) != string::npos) {
                cout << "\t" << betsNBA[i-3] << " vs " << betsNBA[i-2] << endl;
                cout << "\tOdds : " << betsNBA[i-1] << endl;
            }
        }
    }
    //look up over/under
    if(searchPick == "points"){
        cout << "Are you looking for your stats on the over or under?" << endl;
        string pointsChoice;
        cin >> pointsChoice;
        cout << "Here are your stats on the " << pointsChoice << ":\n" << endl;
        for (int i = 0; i < betsNBA.size(); i++) {
            string buffer = betsNBA[i];
            if (buffer.find(pointsChoice) != string::npos) {
                cout << betsNBA[i] << "\t\t\t\t" << betsNBA[i + 1] << "\t\t\t\t" << betsNBA[i + 2] << "\t\t\t\t"
                     << betsNBA[i + 3] << endl;
            }
        }
    }
    //spread stats
    if(searchPick == "spread"){
        cout << "Here are yous stats on the spread:\n" << endl;
        for(int i = 0;i < betsNBA.size(); i = i+4){
            string buffer = betsNBA[i];
            if(buffer.find("-") != string::npos){
                cout << betsNBA[i] << "\tvs\t" << betsNBA[i + 1] << "\n\t" << betsNBA[i + 2] << "\n\t" << betsNBA[i + 3] << endl;
            }
            if(buffer.find("+") != string::npos){
                cout << betsNBA[i] << "\tvs\t" << betsNBA[i + 1] << "\n\t" << betsNBA[i + 2] << "\n\t" << betsNBA[i + 3] << endl;
            }
        }
    }
    //moneyline stats
    if(searchPick == "moneyline"){
        cout << "Here are yous stats on the moneyline:\n" << endl;
        for(int i = 0;i < betsNBA.size(); i = i+4){
            string buffer = betsNBA[i];
            if(buffer.find("-") != string::npos) {}
            else{
                if(buffer.find("+") != string::npos) {}
                else{
                    if(buffer.find("over")!= string::npos){}
                    else{
                        if(buffer.find("under")!= string::npos){}
                        else{
                            string secondLayer = betsNBA[i+1];
                            if(secondLayer.find("receptions")!= string::npos){}
                            else{
                                if(secondLayer.find("td")!= string::npos){}
                                else{
                                    if(secondLayer.find("yards")!= string::npos) {}
                                    else{
                                        cout << betsNBA[i] << "\tvs\t" << betsNBA[i + 1] << "\n\t" << betsNBA[i + 2] << "\n\t" << betsNBA[i + 3] << endl;
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
void NBAfilter(){
    cout << "-----------------------------------------------------------\n" << endl;
    cout << "Would you like to search for something? ('yes' if so)" << endl;
    string searchQuestion;
    cin >> searchQuestion;
    if(searchQuestion == "yes") {
        //events, name, or parlayid search
        NBAsearch();
    }
    else{
        cout << "search not ran" << endl;
    }
}

//Gets parlay information and stats
void NBAParlayInformation(){
    ifstream parlayFile ("C:\\Users\\caele\\Downloads\\BettingTxtFiles\\FormattedNBAParlays.txt");

    //assures file is open correctly
    if (parlayFile.is_open()){
        string buffer;
        int count2 = 0;
        //gets each line and prints it out
        while ( getline (parlayFile,buffer) ){
            parlaysNBA.push_back(buffer);
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

    for(int z = 0;z < parlaysNBA.size();z++){
        string checker = parlaysNBA[z];
        //check for wins
        if(checker.find("W") != string::npos){
            NBAwinCount++;
        }
        //check for losses
        if(checker.find("L") != string::npos){
            NBAlossCount++;
        }
        //check for total amount bet
        if(checker.find("$") != string::npos){
            string moneySign = checker;
            moneySign.erase(remove(moneySign.begin(), moneySign.end(), '$'), moneySign.end());
            moneySign.erase(remove(moneySign.begin(), moneySign.end(), '\t'), moneySign.end());
            if(checker.find("-") != string::npos){
                moneySign.erase(remove(moneySign.begin(), moneySign.end(), '-'), moneySign.end());
                float betAmnt = stof (moneySign);

                NBAnegativeAmount +=betAmnt;
            }
            float betAmnt = stof (moneySign);
            NBAtotalBet +=betAmnt;
        }
        //adding up total money made
        if(checker.find("+") != string::npos){
            string posiSign = checker;
            posiSign.erase(remove(posiSign.begin(), posiSign.end(), '+'), posiSign.end());
            posiSign.erase(remove(posiSign.begin(), posiSign.end(), '\t'), posiSign.end());
            float betAmnt = stof (posiSign);
            NBApositiveAmount +=betAmnt;
        }
        //
        if(checker.find("single") != string::npos){
            NBAsinglesCount++;
        }
    }
    //Final print out with all stats
    NBAtotalBetsCount = NBAwinCount + NBAlossCount;
    NBAparlaysCount = NBAtotalBetsCount - NBAsinglesCount;
    NBAwC = NBAwinCount;
    NBAtBC = NBAtotalBetsCount;
    NBAwinPercentage = (NBAwC / NBAtBC) * 100;
    NBApositiveAmount -= NBAnegativeAmount;

    //ending calculations
    amountOfBets += NBAtotalBetsCount;
    totalParlays += NBAparlaysCount;
    totalSingles += NBAsinglesCount;
    wins += NBAwinCount;
    losses+= NBAlossCount;
    totalMoneySpent += NBApositiveAmount;
}

void NBAprintable(){
    cout << "\n---------------------------STATS---------------------------" << endl;
    cout << "During the 2022-2023 NBA season you have placed : " << NBAtotalBetsCount << " total bets." << endl;
    cout << NBAsinglesCount << " were singles and " << NBAparlaysCount << " were parlays.\n" << endl;
    cout << "You have bet a total amount of = $" << NBAtotalBet << endl;
    cout << "With these bets you have come up with a record of " << NBAwinCount << " wins and " << NBAlossCount << " losses." <<endl;

    cout << "Giving you a win percentage of " << NBAwinPercentage << "%" << endl;
    if(NBApositiveAmount > 0){
        cout << "Congrats! You are positive for a total amount of $" << NBApositiveAmount << endl;
    }
    else{
        cout << "You are negative a total amount of $" << NBApositiveAmount << endl;
    }
}


//Gets Betting Information
void NBABetInformation(){
    //opens file using path
    string currentLine;
    ifstream fileNBA ("C:\\Users\\caele\\Downloads\\BettingTxtFiles\\FormattedNBABets.txt");

    //assures file is open correctly
    if (fileNBA.is_open()){
        int count = 0;
        //gets each line and prints it out
        while ( getline (fileNBA,currentLine) ){
            for_each(currentLine.begin(), currentLine.end(), [](char & c) {
                c = ::tolower(c);
            });
            betsNBA.push_back(currentLine);
            count++;
        }

        //takes out all the tabs
        for(int z = 0;z < betsNBA.size();z++){
            string checker = betsNBA[z];
            if(checker.find("\t") != string::npos) {
                string tabFound = checker;
                tabFound.erase(remove(tabFound.begin(), tabFound.end(), '\t'), tabFound.end());
                betsNBA[z] = tabFound;
                //cout << "-" << tabFound << "-" << endl;
            }
        }

        fileNBA.close();
    }
        //Lets you know if file wasn't opened properly
    else{
        cout << "Unable to open file";
    }
}





#endif //NBA_H
