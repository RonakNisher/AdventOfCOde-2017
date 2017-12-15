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

void moveScanner(map<int,int>& mapOfLayerAndDepth, map<int,int>& mapOfLayerAndPosition, map<int,int>& mapOfLayerAndMultiplier)
{
    for (auto i : mapOfLayerAndDepth) 
    {
        int layer = i.first;
        int depth = i.second;
        
        // cout <<"moving layer "<<layer<<" ";
        int currentPosition = mapOfLayerAndPosition[layer];
        
        int multiplier = mapOfLayerAndMultiplier[layer];
        if (currentPosition == 0)
            multiplier = 1;
        else if (currentPosition == depth - 1)
            multiplier = -1;
            
        mapOfLayerAndMultiplier[layer] = multiplier;
            
        int newPosition = currentPosition + 1*multiplier;
        
        mapOfLayerAndPosition[layer] = newPosition;
    }
    // cout<<endl;
}


int main()
{
    string line;
    
    map<int,int> mapOfLayerAndDepth;
    
    map<int,int> mapOfLayerAndPosition;
    
    map<int,int> mapOfLayerAndMultiplier;


    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            vector<string> words = split(line,":");
            
            // for (auto i : words) {
            //     cout<<i<<" ";
            // }
            // cout<<endl;
            
            mapOfLayerAndDepth[stoi(words[0])] = stoi(words[1]);
        }
        
        // for (auto i : mapOfLayerAndDepth) {
        //     cout<<i.first<<endl;
        // }
        cout<<"input size is "<<mapOfLayerAndDepth.size()<<endl;
        
        map<int, int> mapOfLayerAndDivisibilty;
        
        for (auto i : mapOfLayerAndDepth) {
            mapOfLayerAndDivisibilty[i.first] = (i.second - 1)*2;
            cout<<i.first<<" div is "<<(i.second - 1)*2<<endl;
        }
        
        bool isBusted = false;
        int delay = 1;
        
        while (true)
        {
            isBusted = false;
            cout<<"for delay "<<delay<<endl;
            for (auto i : mapOfLayerAndDivisibilty) 
            {
                // cout<<i.first<<" layer "<<(i.first + delay)<<" : "<<i.second<<endl;
                if ((i.first + delay)%i.second == 0)
                {
                    // cout<<"busted"<<endl;
                    delay++;
                    isBusted = true;

                    break;
                }
            }
            if (!isBusted)
                break;
        }
        
        cout <<" delay "<<delay<<endl;

        
        // while (isBusted)
        // {
        //     cout <<"starting delay "<<delay<<endl;
        //     int packetPosition = 0;
        //     int risk = 0;
            
        //     mapOfLayerAndPosition.clear();
        //     mapOfLayerAndMultiplier.clear();
            
        //     // cout<<mapOfLayerAndDepth.rbegin()->first<<endl;
            
        //     // delay
        //     for (int i = 0; i < delay; i++) 
        //     {
        //         moveScanner(mapOfLayerAndDepth, mapOfLayerAndPosition, mapOfLayerAndMultiplier);
        //     }
            
        //     while (packetPosition <= mapOfLayerAndDepth.rbegin()->first)
        //     {
        //         // cout<<"at position "<<packetPosition<<endl;
        //         if (mapOfLayerAndDepth.find(packetPosition) == mapOfLayerAndDepth.end())
        //         {
        //             moveScanner(mapOfLayerAndDepth, mapOfLayerAndPosition, mapOfLayerAndMultiplier);
        //             packetPosition++;
        //             continue;
        //         }
                
        //         // check if busted
                
        //         // cout<<"mapOfLayerAndPosition[packetPosition]= "<<mapOfLayerAndPosition[packetPosition]<<endl;
                
        //         if (mapOfLayerAndPosition[packetPosition] == 0)
        //         {
        //             cout<<"busted at position "<<packetPosition<<endl;
        //             mapOfLayerAndPosition.clear();
        //             mapOfLayerAndMultiplier.clear();
        //             risk = -1;
        //             delay++;
        //             break;
        //             // risk += packetPosition*mapOfLayerAndDepth[packetPosition];
        //         }
                    
        //         // move scanner
        //         moveScanner(mapOfLayerAndDepth, mapOfLayerAndPosition, mapOfLayerAndMultiplier);
                
        //         packetPosition++;
        //     }
        
        //     // cout<<"risk is "<<risk<<endl;
        //     if (risk == 0)
        //         isBusted = false;
        
        // }// while(true) ends
        
        // cout << "delay "<<delay;
    }
    
    return 0;
}