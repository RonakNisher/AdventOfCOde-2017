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

    map<int, vector<int>> pipes;
    set<int> seenPipes;
    queue<int> unprocessedPipes;
    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            vector<string> words = split(line,"<->,");
            
            int first = stoi(words[0]);
            
            vector<int> second;
            
            for (int i = 1; i < words.size(); i++) 
            {
                second.push_back(stoi(words[i]));
            }
            pipes[first] = second;
        }
        
        cout << "size of map "<<pipes.size()<<endl;
        myfile.close();
        
        // find out the number of connected pipes
        int totalGroups = 0;
        
        while (!pipes.empty())
        {
            int startingElement = pipes.begin()->first;
            seenPipes.insert(startingElement);
            
            for (auto pipe : pipes[startingElement])
            {
                {
                    unprocessedPipes.push(pipe);
                }
            }
        
            while (!unprocessedPipes.empty())
            {
                auto currentPipe = unprocessedPipes.front();
                if (seenPipes.find(currentPipe) != seenPipes.end())
                {
                    unprocessedPipes.pop();
                    continue;
                }
                
                // cout<<"Current pipe "<<currentPipe<<endl;
                
                for (auto pipe : pipes[currentPipe]) 
                {
                    // cout << "for pipe "<<pipe<<endl;
                    if (seenPipes.find(pipe) == seenPipes.end())
                    {
                        unprocessedPipes.push(pipe);
                    }
                }
                
                unprocessedPipes.pop();
                seenPipes.insert(currentPipe);
            }
        
            cout << "connected pipes "<<seenPipes.size()<<endl;
            
            for (auto p : seenPipes) 
            {
                pipes.erase(p);
            }
            
            seenPipes.clear();
            
            totalGroups++;
        }
        
        cout<<"totalGroups "<<totalGroups<<endl;
        
    }
    

    return 0;
}