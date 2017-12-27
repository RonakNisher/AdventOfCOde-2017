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

long GetGridValue(long x, long y, map<string, long>& grids)
{
    return grids[to_string(x + 1) + "," + to_string(y)] + grids[to_string(x - 1) + "," + to_string(y)] + grids[to_string(x) + "," + to_string(y + 1)] + grids[to_string(x) + "," + to_string(y - 1)] + 
            grids[to_string(x + 1) + "," + to_string(y + 1)] + grids[to_string(x + 1) + "," + to_string(y - 1)] + grids[to_string(x - 1) + "," + to_string(y + 1)] + grids[to_string(x - 1) + "," + to_string(y - 1)];
}


int main()
{
    long input = 289326;
    
    long stride = 1;
    
    // starting positions
    long currentX = 0;
    long currentY = 0;
    
    long currentNumber = 2;
    
    map<string, long> gridValues;
    
    gridValues["0,0"] = 1; // starting position
    
    while (true)
    {
        if (currentNumber > input)
            break;
            
        // place stride number of elements from current to right and then to top
        
        // left to the right
        for (int i = 1; i <= stride; i++) 
        {
            currentX += 1;
            
            // get value at this grid
            currentNumber = GetGridValue(currentX, currentY, gridValues);
            gridValues[to_string(currentX) + "," + to_string(currentY)] = currentNumber;
            
            cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
            
            if (currentNumber > input)
            {
                cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
                break;
            }

        }
        
        if (currentNumber > input)
            break;
        
        // bottom to top
        for (int i = 1; i <= stride; i++) 
        {
            currentY += 1;
            
            currentNumber = GetGridValue(currentX, currentY, gridValues);
            gridValues[to_string(currentX) + "," + to_string(currentY)] = currentNumber;
            
            cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
            
            if (currentNumber > input)
            {
                cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
                break;
            }
            
        }
        
        if (currentNumber > input)
            break;
        
        // Now increase the stride by 1
        stride++;
        
        // right to the left
        for (int i = 1; i <= stride; i++) 
        {
            currentX -= 1;
            
            currentNumber = GetGridValue(currentX, currentY, gridValues);
            gridValues[to_string(currentX) + "," + to_string(currentY)] = currentNumber;
            
            cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
            
            if (currentNumber > input)
            {
                cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
                break;
            }
            
        }
        
        if (currentNumber > input)
            break;
        
        // top to bottom
        for (int i = 1; i <= stride; i++) 
        {
            currentY -= 1;
            
            currentNumber = GetGridValue(currentX, currentY, gridValues);
            gridValues[to_string(currentX) + "," + to_string(currentY)] = currentNumber;
            
            cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
            
            if (currentNumber > input)
            {
                cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
                break;
            }
            
        }
        
        // increase the stride again
        stride++;
    }
    
    cout<<"Distance is "<<abs(currentX) + abs(currentY)<<endl;
    
    
    return 0;
}