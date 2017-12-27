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


int main()
{
    string line;
    
    map<long, long> tape;
    long currentPos = 0;
    char state = 'A';
    long countOfOne = 0;
    long oldPos = 0;
    
    for (long j = 0; j < 12261543; j++)
    {
        oldPos = currentPos;
        
        switch(state)
        {
            case 'A':
                if (tape[currentPos] == 0)
                {
                    tape[currentPos] = 1;
                    currentPos++;
                    state = 'B';
                    countOfOne++;
                }
                else
                {
                    tape[currentPos] = 0;
                    currentPos--;
                    countOfOne--;
                    state = 'C';
                }
                break;
                
            case 'B':
                if (tape[currentPos] == 0)
                {
                    tape[currentPos] = 1;
                    countOfOne++;
                    currentPos--;
                    state = 'A';
                }
                else
                {
                    // tape[currentPos] = 1;
                    currentPos++;
                    // countOfOne++;
                    state = 'C';
                }
                break;
                
            case 'C':
                if (tape[currentPos] == 0)
                {
                    tape[currentPos] = 1;
                    countOfOne++;
                    currentPos++;
                    state = 'A';
                }
                else
                {
                    tape[currentPos] = 0;
                    countOfOne--;
                    currentPos--;
                    state = 'D';
                }
                break;
                
            case 'D':
                if (tape[currentPos] == 0)
                {
                    tape[currentPos] = 1;
                    countOfOne++;
                    currentPos--;
                    state = 'E';
                }
                else
                {
                    // tape[currentPos] = 1;
                    currentPos--;
                    // countOfOne++;
                    state = 'C';
                }
                break;
                
            case 'E':
                if (tape[currentPos] == 0)
                {
                    tape[currentPos] = 1;
                    countOfOne++;
                    currentPos++;
                    state = 'F';
                }
                else
                {
                    // tape[currentPos] = 1;
                    currentPos++;
                    // countOfOne++;
                    state = 'A';
                }
                break;
                
            case 'F':
                if (tape[currentPos] == 0)
                {
                    tape[currentPos] = 1;
                    countOfOne++;
                    currentPos++;
                    state = 'A';
                }
                else
                {
                    // tape[currentPos] = 1;
                    currentPos++;
                    // countOfOne++;
                    state = 'E';
                }
                break;
        }
        
        // cout<<j<<" currentPos "<<oldPos<<"->"<<currentPos<<" value "<<tape[oldPos]<<" countOfOne "<<countOfOne<<endl;
        
    }
    
    cout<<"countOfOne "<<countOfOne<<endl;
    
    return 0;
}