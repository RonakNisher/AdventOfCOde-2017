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

bool processCondition(string lhs, string op, string rhs, map<string, int>& registers)
{
        if (op == ">")
            return registers[lhs] > stoi(rhs);
        
        if (op == "<")
            return registers[lhs] < stoi(rhs);
            
        if (op == ">=")
            return registers[lhs] >= stoi(rhs);
        
        if (op == "<=")
            return registers[lhs] <= stoi(rhs);
            
        if (op == "==")
            return registers[lhs] == stoi(rhs);
        
        if (op == "!=")
            return registers[lhs] != stoi(rhs);
}


int main()
{
    string line;

    map<string, int> registers;

    int max = -1; // INT_MIN for correctness

    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            vector<string> words = split(line,"");
            
            // for (auto i : words) {
            //     cout<<i<<" ";
            // }
            // cout<<endl;
            
            if (processCondition(words[4], words[5], words[6], registers))
            {
                if (words[1] == "inc")
                    registers[words[0]] += stoi(words[2]);
                else if (words[1] == "dec")
                    registers[words[0]] -= stoi(words[2]);
                    
                if (registers[words[0]] > max)
                    max = registers[words[0]];
            }
        }
        
        // cout << "size of map "<<pipes.size()<<endl;
        myfile.close();
        
        
        cout<<"size of registers "<<registers.size()<<endl;
        // for (auto r : registers) 
        // {
        //     // cout << r.second <<endl;
        //     if (r.second > max)
        //         max = r.second;
        // }
        
        cout<<"max is "<<max<<endl;
        
    }
    

    return 0;
}