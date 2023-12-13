#include <iostream>
#include <vector>

using namespace std;

class TurtleProgram{
    public:
    TurtleProgram(){}

    void setVect(string direction, string amount)
    {
        entries.clear();
        entries.push_back(direction);
        entries.push_back(amount);
    } 
    
    void setVect(vector<string> vect)
    {
        entries.clear();
        for(int i = 0;i < vect.size();i++)
        {
            entries.push_back(vect[i]);
        }
    } 
    
    vector<string> getVect() const 
    { 
        return entries;
    }
        
    TurtleProgram(TurtleProgram const &obj)
    {
        setVect(obj.getVect());
    }

    TurtleProgram(string direction, string amount)
    {
        setVect(direction,amount);
    }
        

    friend ostream &operator<<(ostream &outStream, TurtleProgram &obj)
    {
        vector<string> vect = obj.getVect();
        cout << "[";
        for(int i = 0;i < vect.size();i++)
        {
            if(i == vect.size()-1)
            {
                cout << vect[i];
            }
            else
            {
                cout << vect[i] << " ";
            }
        }
        cout << "]";
        return outStream;
    }
    
    TurtleProgram operator + (TurtleProgram const &obj)
    {
        TurtleProgram add;
        vector<string> newVect = getVect();
        vector<string> begVect = obj.getVect();

        for(int i = 0;i < begVect.size();i++)
        {
            newVect.push_back(begVect[i]);
        }

        add.setVect(newVect);
        return add;
    }

    TurtleProgram operator = (TurtleProgram const &obj)
    {
        setVect(obj.getVect());
        return obj;
    }


    TurtleProgram operator * (int multiply)
    {
        vector<string> vect;
        vector<string> old = getVect();
        while(multiply > 0)
        {
            for(int i = 0;i < old.size();i++)
            {
                vect.push_back(old[i]);
            }
            multiply--;
        }
        TurtleProgram obj;
        obj.setVect(vect);
        return obj;
    }

    TurtleProgram operator == (TurtleProgram &obj)
    {
        vector<string> first = getVect();
        vector<string> second = obj.getVect();
        int errorCount = 0;
        //first assures they are the same size
        if(first.size() == second.size())
        {
            //then checks the contents
            for(int i = 0;i < first.size();i++)
            {
                if(first[i] != second[i])
                {
                    //found something that doesn't match
                    errorCount++;
                }
            }
        }
        else
        {
            errorCount++;
        }
        if(errorCount == 0)
        {
            cout << true;
        }
        else
        {
            cout << false;
        }
        return obj;
    }
    
    TurtleProgram operator != (TurtleProgram &obj)
    {
        vector<string> first = getVect();
        vector<string> second = obj.getVect();
        int errorCount = 0;
        //if the sizes are different they can't be the same
        if(first.size() != second.size())
        {
            errorCount++;
        }
        else
        {
            //checks to see if there are any differences
            for(int i = 0;i < first.size();i++)
            {
                if(first[i] != second[i])
                {
                    errorCount++;
                }
            }
        }
        if(errorCount == 0)
        {
            cout << false;
        }
        else
        {
            cout << true;
        }
        return obj;
    }
    
    void setIndex(int index,string newEntry)
    { 
        vector<string> vect = getVect();
        vect[index] = newEntry;
        setVect(vect);
    }
    
    string getIndex(int index)
    { 
        vector <string> vect = getVect();
        return vect[index];
    }

    int getLength()
    {
        vector<string> vect = getVect();
        return vect.size();
    }

    TurtleProgram operator += (TurtleProgram &obj)
    {
        vector<string> initial = getVect();
        vector<string> addition = obj.getVect();
        for(int i = 0;i < addition.size();i++)
        {
            initial.push_back(addition[i]);
        }
        setVect(initial);
        return obj;
    }
    
    operator *= (int multiply)
    {
        vector<string> base = getVect();
        vector<string> newVect;
        while(multiply > 0)
        {
            for(int i = 0;i < base.size();i++)
            {
                newVect.push_back(base[i]);
            }
            multiply--;
        }
        setVect(newVect);
    }
    
    private:
    vector <string> entries;
};