//constructor
Finite::Finite()
{
    currentState = "s1";
    currentEx = "";
    finalPrintOut = "INPUT\t\tSTATE\tNUM1\tNUM2\tEXPRESSION\tOUTPUT\n";
}

//Destructor
Finite::~Finite()
{
    currentArray[1] = "";
    currentArray[2] = "";
    currentArray[4] = "";
    currentState = "s1";
    currentEx = "";
}

void Finite::print()
{
    cout << finalPrintOut << endl;
}

void Finite::input(string input)
{
    finalPrintOut += input + "\t:\t";    
    if(input == "+" || input == "*")
    {
        expressionInput(input);
    }
    if(input == "s1" || input == "s2" || input == "s3")
    {
        stateInput(input);
    }
    if(input == "1" || input == "2")
    {
        numInput(input);
    }
    statusCheck();
    printHelper();
}

void Finite::printHelper()
{
    currentArray[0] = currentState;
    currentArray[3] = currentEx;
    for(int i = 0;i < 5;i++)
    {
        if(i == 3)
        {
            finalPrintOut += "    ";
        }
        if(i == 4)
        {
            finalPrintOut += "\t   ";
        }
        finalPrintOut += currentArray[i] + "\t";
    }
    finalPrintOut += "\n___________________________________________________________________\n";
    if(currentState == "s3" && currentArray[4] != "")
    {
        reset("");
    }
    currentArray[4] = "";
}

bool Finite::expressionInput(string express)
{
    if(currentEx == "")
    {
        currentEx = express;
        return true;
    }
    else
    {
        reset("junk");
        return false;
    }
}

bool Finite::numInput(string num)
{
    if(currentArray[1] == "")
    {
        currentArray[1] = num;
        return true;
    }
    else
    {
        if(currentArray[2] == "")
        {
            currentArray[2] = num;
            return true;
        }
        else
        {
            reset("junk");
            return false;
        }
    }
}

void Finite::stateInput(string state)
{
    currentState = state;
}

bool Finite::doubleNumInput(string arr[])
{
    if(currentArray[1] == "" || currentArray[2] == "")
    {
        currentArray[1] = arr[0];
        currentArray[2] = arr[1];
        statusCheck();
        printHelper();
        return true;
    }
    else
    {
        reset("junk");
        return false;
    }
}

void Finite::statusCheck()
{
    if(currentState == "s1")
    {
        if(currentArray[1] != "")
        {
            currentState = "s2";
        }
    }
    else
    {
        if(currentState == "s2")
        {
            if(currentArray[1] != "" && currentArray[2] != "")
            {
                currentState = "s3";
            }
        }
        else
        {
            if(currentState == "s3")
            {
                if(currentEx != "")
                {
                    int first = stoi(currentArray[1]);
                    int second = stoi(currentArray[2]);
                    int result;
                    stringstream ss;
                    string str;
                    if(currentEx == "+")
                    {
                        result = first + second;
                    }
                    if(currentArray[3] == "*")
                    {
                        result = first * second;
                    }
                    ss << result;
                    str = ss.str();
                    currentArray[4] = str;
                }
            }
        }
    }
    
}

void Finite::reset(string err)
{
    currentArray[1] = "";
    currentArray[2] = "";
    currentArray[4] = err;
    currentState = "s1";
    currentEx = "";
}