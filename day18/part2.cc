#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
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

void run(long& currentPos, map<string, long>& registers, queue<long>& sendQueue, queue<long>& recvQueue, bool& isWaiting, vector<string>& instructions, int pNo)
{
    string currentIns = instructions[currentPos];
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

        
        if (insName == "snd")
        {
            if (pNo == 1)
                cnt++;
                
            sendQueue.push(val1);
            // cout<<pNo<<" sending "<<val1<<endl;
            // shouldBreak = true;
            // continue;
        }
        else if (insName == "set")
        {
            registers[words[1]] = val2;
        }
        else if (insName == "add")
        {
            registers[words[1]] = val1 + val2;
        }
        else if (insName == "mul")
        {
            registers[words[1]] = val1 * val2;

        }
        else if (insName == "mod")
        {
            registers[words[1]] = val1 % val2;
        }
        else if (insName == "rcv")
        {
            if (!recvQueue.empty())
            {
                registers[words[1]] = recvQueue.front();
                recvQueue.pop();
                // cout<<pNo<<" recv "<<val1<<endl;

            }
            else
            {
                cout<<pNo<<" waiting "<<val1<<endl;

                isWaiting = true;
                
                return;
            }
        }
        else if (insName == "jgz")
        {
            if (val1 > 0)
            {
                currentPos = currentPos + val2;
                return;
            }
        }
        
        currentPos++;
}

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
        
        myfile.close();
    }
    
    map<string,long> registers1;
    map<string,long> registers2;

    long playedSound;
    
    long currentPos1 = 0;
    long currentPos2 = 0;
    
    
    bool isWaiting1;
    bool isWaiting2;
    
    bool isDone1;
    bool isDone2;
    
    queue<long> q1; // q for program1
    queue<long> q2; //

    registers1["p"] = 0; //p0
    registers2["p"] = 1; //p1

    
    // string currentIns;
    
    // bool shouldBreak = false;
    while (true)
    {
        if (!isWaiting1 || !q1.empty())
            run(currentPos1, registers1, q2 /*sendQ*/, q1, isWaiting1, instructions, 0); //p0
            
        if (!isWaiting2 || !q2.empty())
            run(currentPos2, registers2, q1, q2, isWaiting2, instructions, 1); //p1
            
        if (isWaiting1 && isWaiting2 && q1.empty() && q2.empty())
            break;
    }
    
    cout<<"cnt is "<<cnt<<endl;
    
    return 0;
}