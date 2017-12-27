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
    long input = 289326;
    
    long stride = 1;
    
    // starting positions
    long currentX = 0;
    long currentY = 0;
    
    long currentNumber = 2;
    
    while (currentNumber <= input + 1)
    {
        if (currentNumber > input)
            break;
            
        // place stride number of elements from current to right and then to top
        
        // left to the right
        for (int i = 1; i <= stride; i++) 
        {
            currentX += 1;
            
            if (currentNumber == input)
            {
                cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
                currentNumber++;
                break;
            }
            
            // cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
            currentNumber++;
        }
        
        if (currentNumber > input)
            break;
        
        // bottom to top
        for (int i = 1; i <= stride; i++) 
        {
            currentY += 1;
            
            if (currentNumber == input)
            {
                cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
                currentNumber++;
                break;
            }
            // cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;

            currentNumber++;
        }
        
        if (currentNumber > input)
            break;
        
        // Now increase the stride by 1
        stride++;
        
        // right to the left
        for (int i = 1; i <= stride; i++) 
        {
            currentX -= 1;
            
            if (currentNumber == input)
            {
                cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
                currentNumber++;
                break;
            }
            // cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;

            currentNumber++;
        }
        
        if (currentNumber > input)
            break;
        
        // top to bottom
        for (int i = 1; i <= stride; i++) 
        {
            currentY -= 1;
            
            if (currentNumber == input)
            {
                cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;
                currentNumber++;
                break;
            }
            // cout<<"currentNumber "<<currentNumber<<" at "<<currentX<<", "<<currentY<<endl;

            currentNumber++;
        }
        
        // increase the stride again
        stride++;
    }
    
    cout<<"Distance is "<<abs(currentX) + abs(currentY)<<endl;
    
    
    return 0;
}