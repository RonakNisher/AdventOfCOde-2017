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

    long nextColumnOffset = 0;
    long nextRowOffset = 0;
    string currentDirection = "top";

void Turn(string pos)
{
    if (pos == "right")
    {
        if (currentDirection == "top")
        {
            nextColumnOffset = 1;
            nextRowOffset = 0;
            currentDirection = "right";
            return;
        }
        else if (currentDirection == "right")
        {
            nextColumnOffset = 0;
            nextRowOffset = 1;
            currentDirection = "down";
            return;
        }
        else if (currentDirection == "down")
        {
            nextColumnOffset = -1;
            nextRowOffset = 0;
            currentDirection = "left";
            return;
        }
        else if (currentDirection == "left")
        {
            nextColumnOffset = 0;
            nextRowOffset = -1;
            currentDirection = "top";
            return;
        }
    }
    else // go left
    {
        if (currentDirection == "top")
        {
            nextColumnOffset = -1;
            nextRowOffset = 0;
            currentDirection = "left";
            return;
        }
        else if (currentDirection == "right")
        {
            nextColumnOffset = 0;
            nextRowOffset = -1;
            currentDirection = "top";
            return;
        }
        else if (currentDirection == "down")
        {
            nextColumnOffset = 1;
            nextRowOffset = 0;
            currentDirection = "right";
            return;
        }
        else if (currentDirection == "left")
        {
            nextColumnOffset = 0;
            nextRowOffset = 1;
            currentDirection = "down";
            return;
        }
    }
}

void print(vector<string>& nodeMap, vector<string>& virusMap, int dx, int dy)
{
    for (int i = 0; i < nodeMap.size() ; i++)
    {
        for (int j = 0; j < nodeMap[0].size(); j++)
        {
            // cout<<i<<", "<<j<<endl;
            cout<<virusMap[i + dx][i + dy];
        }
        cout<<endl;
    }
}

int main()
{
    string line;
    vector<string> nodeMap;
    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            // vector<string> words;
            // words = split(line,",=<>");
            nodeMap.push_back(line);
        }
        
        myfile.close();
    }
    
    cout<<"size of nodeMap is "<<nodeMap.size()<<" -> "<<nodeMap[0].size()<<endl;
    
    long infectedCount = 0;
    long map_size = 10001;
    
    vector<string> virusMap(map_size);
    
    for (auto &i : virusMap) {
        i.resize(map_size, '.');
    }
    
    cout<<virusMap[0].size()<<endl;
    
    cout<<"Sz "<<virusMap.size()<<" "<<virusMap[0].size()<<endl;
    
    int dx(map_size/2 - nodeMap.size()/2);
    int dy(map_size/2 - nodeMap[0].size()/2);
    
    cout<<"dx,dy is "<<dx<<", "<<dy<<endl;
    
    for (int i = 0; i < nodeMap.size() ; i++)
    {
        // cout<<i + dx<<", "<<dy<<endl;
        for (int j = 0; j < nodeMap[0].size(); j++)
        {
            // cout<<i<<", "<<j<<endl;
            virusMap[i + dx][j + dy] = nodeMap[i][j];
            // cout<<virusMap[i + dx][i + dy];//<<"->"<<nodeMap[i][j];
        }
        // cout<<endl;
        // cout<<"-----------------------------------"<<endl;
        // print(nodeMap, virusMap, dx, dy);
    }
    
    long currentX = map_size/2;
    long currentY = map_size/2;
    
    cout<<"start at "<<currentX<<", "<<currentY<<endl;
    
    // print(nodeMap, virusMap, dx, dy);
    
    for (long i = 0; i < 10000000; i++) 
    {
        bool isInfected = (virusMap[currentX][currentY] == '#');
        bool isWeakened = (virusMap[currentX][currentY] == 'W');
        bool isFlagged = (virusMap[currentX][currentY] == 'F');
        // bool isCleaned = (virusMap[currentX][currentY] == '.');


        
        // cout<<"burst "<<i<<" "<<isInfected<<virusMap[currentX][currentY]<<"->"<<nodeMap[currentX - dx][currentY - dy]<<endl;
        // cout<<"pos is "<<currentX<<" "<<currentY<<" facing "<<currentDirection<<endl;
        
        if (isInfected)
        {
            Turn("right");
            virusMap[currentX][currentY] = 'F';
        }
        else if (isWeakened)
        {
            virusMap[currentX][currentY] = '#';
            infectedCount++;
        }
        else if (isFlagged)
        {
            virusMap[currentX][currentY] = '.';
            Turn("left");
            Turn("left");
        }
        else // clean
        {
            Turn("left");
            // cout<<"infected in this "<<i<<endl;
            virusMap[currentX][currentY] = 'W';
        }
        
        // debug
        // print(nodeMap, virusMap, dx, dy);
        
        // move
            
        currentX = currentX + nextRowOffset;
        currentY = currentY + nextColumnOffset;
        
        
            
        // if (currentY >= nodeMap[0].size())
        //     cout<<i <<" col "<<currentY<<" "<<nextColumnOffset<<endl;
        
        // if (i > 88)
        //     cout<<"new pos is "<<currentX<<" "<<currentY<<endl;

    }
    
    // for (auto i : nodeMap) 
    // {
    //     for (auto j : i) 
    //     {
    //         cout<<j;
    //     }
    //     cout<<endl;
    // }
    
    cout<<"infected "<<infectedCount<<endl;
    
    return 0;
}