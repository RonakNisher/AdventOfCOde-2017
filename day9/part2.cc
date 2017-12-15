#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

vector<string> split(string input, string delimiters)
{
    vector<string> res;
    
    string val = "";
    for (auto i : input) {
        if(!isspace(i) && delimiters.find(i) == -1)
        {
            val.push_back(i);
        }
        else
        {
            if (val != "")
            {
                res.push_back(val);
                val = "";
            }
        }
    }
    
    if(val != "")
        res.push_back(val);
    return res;
}


int main()
{
    string line;
    int finalCount = 0;
    int garbageNonCancelledCount = 0;
    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            // vector<string> words = split(line,"");
            
            // for (auto i : line) {
            //     cout<<i<<" ";
            // }
            // cout<<endl;
            
            bool isGarbage = false;
            bool shouldIgnoreNextCharacter = false;
            int groupCount = 0;
            int currentGroup = 0;
            
            for (char character : line) 
            {
                if (!isGarbage && character == '<')
                    isGarbage = true;
                else if (isGarbage && character == '>' && !shouldIgnoreNextCharacter)
                    isGarbage = false;
                else if (isGarbage && character == '!' && !shouldIgnoreNextCharacter)
                    shouldIgnoreNextCharacter = true;
                else if (isGarbage && shouldIgnoreNextCharacter)
                {
                    // cout<<"ignored "<<character<<endl;
                    shouldIgnoreNextCharacter = false;
                    continue;
                }
                else if (isGarbage && !shouldIgnoreNextCharacter)
                    garbageNonCancelledCount++;
                else if (!isGarbage && character == '{')
                {
                    currentGroup++;
                }
                else if (!isGarbage && character == '}')
                {
                    groupCount+= currentGroup;
                    currentGroup--;
                }
            }
            
            cout<<"groupCount is "<<groupCount<<endl;
            finalCount+= groupCount;
            
        }
        
        cout<<"finalCount "<<finalCount<<endl;
        cout<<"garbageNonCancelledCount "<<garbageNonCancelledCount<<endl;
        // cout << "size of map "<<pipes.size()<<endl;
        myfile.close();
        
    }
    

    return 0;
}