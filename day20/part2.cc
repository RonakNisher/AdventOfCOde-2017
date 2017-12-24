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
    bool didCollide = false;
    bool didMinChange = false;
    
    map<long, vector<long>> positionsSeen;
    
    set<vector<long>> seenSet;

    set<long> collisionSet;
    long numOfCollisions = 0;
    
    int count = 0;
    // while(avl.size() != 1)
    while(count != 5000)
    {
        positionsSeen.clear();
        seenSet.clear();
        
        didMinChange = false;
        didCollide = false;
        for (int i = 0; i < size; i++) 
        {
            if (discard.find(i) != discard.end())
                continue;
                
            long total = 0;
            for (int j = 0; j < 3; j++) 
            {
                velocity[i][j] = velocity[i][j] + acceleration[i][j];
                
                position[i][j] = position[i][j] + velocity[i][j];
                
                // cout<<velocity[i][j]<<" "<<position[i][j]<<endl;
                
                total += abs(position[i][j]);
            }
            // cout<<total<<endl;
             if (total < minVal)
             {
                //  cout<<"new min val "<<total<<" at "<<minPos<<endl;
                 minVal = total;
                 minPos = i;
                 didMinChange = true;
             }
             else if (total > maxVal)
             {
                 maxVal = total;
                 maxPos = i;
             }
             
             auto inserted = seenSet.insert(position[i]);
             if (inserted.second)
             {
                //  cout<<"no collision "<<total<<endl;
                 positionsSeen[i] = position[i];
             }
             else
             {
                 // collision
                 collisionSet.insert(i);
                 cout<<"collision "<<i<<" total "<<total<<endl;
                 
                //  for (auto l : position[i])
                //  {
                //      cout<<l<<" ";
                //  }
                //  cout<<endl;

                //  cout<<"collision "<<i<<" and "<<positionsSeen[total]<<" total "<<total<<endl;
                 
                 didCollide = true;
                 
                 avl.remove(i);
                 discard.insert(i);
                 collisionSet.insert(i);
                 
                 numOfCollisions++;
                 
                 
                 for (auto k : positionsSeen) 
                 {
                     if(k.second == position[i])
                     {
                        cout<<"collision insert "<<k.first<<" val "<<total<<endl;
                        collisionSet.insert(k.first);
                        discard.insert(k.first);
    
                        avl.remove(k.first);
                        numOfCollisions++;
                        positionsSeen.erase(k.first);
                     }
                 }
                //  auto it = find(positionsSeen.begin(), positionsSeen.end(), position[i]);
                //  if (it != positionsSeen.end())
                //  {
                //     collisionSet.insert(it->first);
                //     discard.insert(it->first);

                //     avl.remove(it->first);
                //     numOfCollisions++;
                //     positionsSeen.erase(it->first);
                //  }
                 
             }
        }
        
        // if (!didMinChange)
        // {
        //     long nextTotal = 0;
        //     for (int j = 0; j < 3; j++) 
        //     {
        //         velocity[maxPos][j] = velocity[maxPos][j] + acceleration[maxPos][j];
                
        //         position[maxPos][j] = position[maxPos][j] + velocity[maxPos][j];
                
        //         // cout<<velocity[i][j]<<" "<<position[i][j]<<endl;
                
        //         nextTotal += abs(position[maxPos][j]);
        //     }
            
        //     if (nextTotal < maxVal)
        //     {
        //         // cout<<"cannot discard "<<maxPos<<" for "<<nextTotal<<endl;
        //         continue;
        //     }
        //     else
        //     {
        //         // cout<<"discarding "<<maxPos<<" for "<<nextTotal<<" cmax is "<<maxVal<<endl;
        //         discard.insert(maxPos);
        //         avl.remove(maxPos);
        //         maxVal = -1;
        //     }
        // }
        
        count++;
        
    }
    
    // cout<<"winner "<<avl.front()<<" "<<minVal<<endl;
    cout<<"avl size "<<avl.size()<<endl;
    cout<<"no of coll "<<numOfCollisions<<" || "<<collisionSet.size()<<endl;
    
    
    int k = 0;
    // for (auto i : collisionSet) 
    // {
    //     // cout<<i<<" ";
    //     if (i != k)
    //         cout<<"missing "<<k<<endl;
    //     k++;
    // }
    // cout<<endl;
    
    cout<<collisionSet.size()<<endl;

    
    
    return 0;
}