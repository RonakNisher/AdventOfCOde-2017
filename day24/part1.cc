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
vector<string> ports;
vector<vector<string>> splitPorts;
map<string, long> cache;
map<string, string> pathCache;


string maxPath = "";

int depth;

long buildBridge(map<int, int>& availablePorts, int currentPortPos, string nextBridge, string& path)
{
    // cout<<"currentPort "<<ports[currentPortPos]<<endl;
    long score = 0;
    int maxPos = 0;
    string localMaxPath = "";
    string maxAvailblePorts;
    
    for (int i = 0; i < availablePorts.size(); i++)
    {
        maxAvailblePorts.append(to_string(availablePorts[i]));
        maxAvailblePorts.append(",");
    }
    // cout<<"maxAvailblePorts str "<<maxAvailblePorts<<endl;
    
    // if (cache[maxAvailblePorts] != 0)
    // {
    //     // cout<<"reusing cache for "<<maxAvailblePorts<<endl;
    //     path = pathCache[maxAvailblePorts];
    //     return cache[maxAvailblePorts];
    // }

    for (int i = 0; i < availablePorts.size(); i++)
    {
        if (availablePorts[i] == 1)
        {
            if (splitPorts[i][0] == nextBridge ||  splitPorts[i][1] == nextBridge)
            {
                // map<int, int> newAvailblePorts = availablePorts;
                // newAvailblePorts[i] = 0;
                availablePorts[i] = 0;
                long s = 0;
                string path;
                
                // try to use that port
                s = buildBridge(availablePorts, i, (splitPorts[i][0] == nextBridge) ? splitPorts[i][1] : splitPorts[i][0], path);
                // s = buildBridge(newAvailblePorts, splitPorts[i]);

                
                availablePorts[i] = 1;
                
                if (s > score)
                {
                    score = s;
                    maxPos = i;
                    localMaxPath = path;
                }
            }
        }
    }
    
    score += stoi(splitPorts[currentPortPos][0]) + stoi(splitPorts[currentPortPos][1]);
    cache[maxAvailblePorts] = score ;
    localMaxPath.append("-"+ports[currentPortPos]);
    pathCache[maxAvailblePorts] = localMaxPath;
    path = localMaxPath;
    // cout<<"adding cache "<<maxAvailblePorts<<" -> "<<score + stoi(currentPort[0]) + stoi(currentPort[1])<<endl;
    // cout<<"currentPort "<<ports[currentPortPos]<<" has max score "<<(score)<<endl;
    // cout<<"from ports "<<ports[maxPos]<<" child score "<<score<<endl;
    
    return score;
}

int main()
{
    string line;
    // vector<string> rightPorts;
    
    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            // words = split(line,",");
            ports.push_back(line);
            
            vector<string> s = split(line,"/");
            splitPorts.push_back(s);
            
            // for (auto i : words) {
            //     cout<<i<<" ";
            // }
            // cout<<endl;
            
        }
        
        cout<<"ports size is "<<ports.size()<<endl;
        
        map<int, int> availablePorts;
        
        for (int i = 0; i < ports.size(); i++) {
            availablePorts[i] = 1;
        }
        
        long maxStrength = 0;
        
        vector<int> zeroPorts;
        
        for (int i = 0; i < splitPorts.size(); i++) 
        {
            if (splitPorts[i][0] == "0" || splitPorts[i][1] == "0")
            {
                zeroPorts.push_back(i);
                availablePorts[i] = 0;
            }
        }
        
        for (int i = 0; i < availablePorts.size(); i++)
        {
            if (splitPorts[i][0] == "0" || splitPorts[i][1] == "0")
            {
                // map<int, int> newAvailblePorts = availablePorts;
                // for (auto k : zeroPorts) {
                //     newAvailblePorts[k] = 0;
                // }
                    
                long strength;
                strength = buildBridge(availablePorts, i, (splitPorts[i][0] == "0") ? splitPorts[i][1] : splitPorts[i][0], maxPath);
                
                if (strength > maxStrength)
                {
                    maxStrength = strength;
                }
            }
        }
        
        cout<<"max strength "<<maxStrength<<endl;
        cout<<maxPath<<endl;
        myfile.close();
        
        // for (auto it = cache.begin(); it != cache.end(); it++)
        // {
        //     cout<<it->first<<endl;
        //     cout<<"has score "<<it->second<<endl;
        // }
    }
    
    return 0;
}