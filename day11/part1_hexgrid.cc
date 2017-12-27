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


void Move(string currentDirection, long& x, long& y, long& z)
{
    if (currentDirection == "n")
    {
        y = y + 1;
        z = z - 1;
    }
    else if (currentDirection == "s")
    {
        y = y - 1;
        z = z + 1;
    }
    else if (currentDirection == "nw")
    {
        x = x - 1;
        y = y + 1;
    }
    else if (currentDirection == "se")
    {
        x = x + 1;
        y = y - 1;
    }
    else if (currentDirection == "ne")
    {
        x = x + 1;
        z = z - 1;
    }
    else if (currentDirection == "sw")
    {
        x = x - 1;
        z = z + 1;
    }
    
     if ((x + y + z) != 0)
    {
        cout<<"panic "<<endl;
        return;
    }
}

int main()
{
    string line;
    
    vector<string> workingList;
    vector<string> words;
    
    long posX = 0;
    long posY = 0;
    long posZ = 0;
    
    long maxDist = 0;
    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            words = split(line,",");
            
        }
        
        std::cout << words.size() << std::endl;
        myfile.close();

    }
    
    cout<<"input initial size is "<<words.size()<<endl;
    
    int lastPos = 0;
    string currentDirection;
    string lastDirection = words[0];
    
    // workingList.push_back(words[0]);
    
    for (int i = 0; i < words.size(); i++) 
    {
        // currentDirection = words[i];
        // cout<<words[i]<<endl;
        Move(words[i], posX, posY, posZ);
        // cout<<posX<<", "<<posY<<", "<<posZ<<endl;
        
        if (max(max(abs(posX), abs(posY)), abs(posZ)) > maxDist)
            maxDist = max(max(abs(posX), abs(posY)), abs(posZ));
    }
    
    cout<<"End Coords are "<<posX<<", "<<posY<<", "<<posZ<<endl;
    cout<<"distance is "<<max(max(abs(posX), abs(posY)), abs(posZ))<<endl;
    cout<<"max is "<<maxDist<<endl;

    // if (posX == 0)
    //     cout<<"distance is "<<abs(posY)<<endl;
    // else if (posY == 0)
    //     cout<<"distance is "<<abs(posY)<<endl;
    // else
    // {
    //     cout<<"distance is "<<ceil((abs(posX) + abs(posY))/2)<<endl;
    // }
    
    return 0;
}