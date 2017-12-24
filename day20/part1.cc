#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
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
    vector<string> words;
    
    long minPos;
    long minVal = 10000;
    
    long maxPos;
    long maxVal = -1;
    
    map<int,vector<long>> position;
    map<int,vector<long>> velocity;
    map<int,vector<long>> acceleration;
    
    int size = 0;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            words = split(line,",=<>");
            vector<long> pos = {stoi(words[1]), stoi(words[2]), stoi(words[3])};
            position[size] = pos;
            
            vector<long> vel = {stoi(words[5]), stoi(words[6]), stoi(words[7])};
            velocity[size] = vel;
            
            vector<long> acc = {stoi(words[9]), stoi(words[10]), stoi(words[11])};
            acceleration[size] = acc;
            
            size++;
            
        }
        
        myfile.close();
    }
    
    set<long> discard;
    list<long> avl;
    
    for (int i = 0; i < size; i++) 
    {
        avl.push_back(i);
    }
    
    cout <<"size is "<<size<<endl;
    bool isVelPos = false;
    bool didMinChange = false;
    
    int count = 0;
    while(avl.size() != 1)
    {
        didMinChange = false;
        isVelPos = false;
        for (int i = 0; i < size; i++) 
        {
            if (discard.find(i) != discard.end())
                continue;
                
            long total = 0;
            for (int j = 0; j < 3; j++) 
            {
                velocity[i][j] = velocity[i][j] + acceleration[i][j];
                
                // if (velocity[i][j] > 0)
                // {
                //     // std::cout << "is val pos " << std::endl;
                //     isVelPos = true;
                // }
                
                position[i][j] = position[i][j] + velocity[i][j];
                
                // cout<<velocity[i][j]<<" "<<position[i][j]<<endl;
                
                total += abs(position[i][j]);
            }
            // cout<<total<<endl;
             if (total < minVal)
             {
                 cout<<"new min val "<<total<<" at "<<minPos<<endl;
                 minVal = total;
                 minPos = i;
                 didMinChange = true;
             }
             else if (total > maxVal)
             {
                 maxVal = total;
                 maxPos = i;
             }
        }
        
        if (!didMinChange)
        {
            long nextTotal = 0;
            for (int j = 0; j < 3; j++) 
            {
                velocity[maxPos][j] = velocity[maxPos][j] + acceleration[maxPos][j];
                
                position[maxPos][j] = position[maxPos][j] + velocity[maxPos][j];
                
                // cout<<velocity[i][j]<<" "<<position[i][j]<<endl;
                
                nextTotal += abs(position[maxPos][j]);
            }
            
            if (nextTotal < maxVal)
            {
                cout<<"cannot discard "<<maxPos<<" for "<<nextTotal<<endl;
                continue;
            }
            else
            {
                cout<<"discarding "<<maxPos<<" for "<<nextTotal<<" cmax is "<<maxVal<<endl;
                discard.insert(maxPos);
                avl.remove(maxPos);
                maxVal = -1;
            }
        }
        
        count++;
        // if (!isVelPos)
        //  {
        //     //  discard.insert(i);
        //     //  cout<<"discard "<<i<<endl;
        //     cout<<"winner "<<minPos<<" "<<minVal<<endl;
        //     break;
        //  }
        
    }
    
    cout<<"winner "<<avl.front()<<" "<<minVal<<endl;

    
    
    return 0;
}