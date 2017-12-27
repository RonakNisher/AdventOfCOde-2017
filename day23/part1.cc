#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <bitset>
#include <iterator>
#include <cctype>

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

// void print(list<int>& positions)
// {
//     for (int i = 0; i < positions.size(); i++)
//     {
//         cout<<positions.at(i);
//     }
//     cout<<endl;
// }

int cnt;

int main()
{
    string line;
    vector<string> instructions;
    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            // words = split(line,",");
            instructions.push_back(line);
            
            // for (auto i : words) {
            //     cout<<i<<" ";
            // }
            // cout<<endl;
            
        }
        
        cout<<"ins size is "<<instructions.size()<<endl;
        
        myfile.close();
    }
    
    map<string,long> registers;
    long playedSound;
    
    long currentPos = 0;
    
    string currentIns;
    
    long mulCount = 0;
    
    bool shouldBreak = false;
    while (currentPos < instructions.size())
    {
        currentIns = instructions[currentPos];
        
        
        vector<string> words = split(currentIns, "");
        
        // for (auto i : words) 
        // {
        //     cout<<i<<" ";
        // }
        // cout<<endl;
        
        string insName = words[0];
        long val1;
        long val2;
        
         if (words[1][0] == '-' || (words[1][0]>='0' && words[1][0]<='9'))
            val1 = stoi(words[1]);
        else
            val1 = registers[words[1]];
            
        if (words.size() == 3)
        {
            if (words[2][0] == '-' || (words[2][0]>='0' && words[2][0]<='9'))
                val2 = stoi(words[2]);
            else
                val2 = registers[words[2]];
        }
        
        // cout<<currentPos<<" "<<currentIns<<" -> "<<val1<<" "<<val2<<endl;

        
        if (insName == "set")
        {
            registers[words[1]] = val2;
        }
        else if (insName == "sub")
        {
            registers[words[1]] = val1 - val2;
        }
        else if (insName == "mul")
        {
            registers[words[1]] = val1 * val2;
            mulCount++;
        }
        else if (insName == "jnz")
        {
            if (val1 != 0)
            {
                currentPos = currentPos + val2;
                cnt++;
                continue;
            }
        }
        
        currentPos++;
        cnt++;
    }
    
    cout<<"mul is "<<mulCount<<endl;
    
    return 0;
}