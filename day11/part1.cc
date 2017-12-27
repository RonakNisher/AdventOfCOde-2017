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
    
    vector<string> workingList;
    vector<string> words;
    
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
    
    workingList.push_back(words[0]);
    
    for (int i = 1; i < words.size(); i++) 
    {
        currentDirection = words[i];
        
        if (lastPos < 0)
            lastDirection = "";
        else
            lastDirection = workingList[lastPos];
        
        if (currentDirection == "s" && lastDirection == "n") // transformations that cancel each other out
        {
            workingList.pop_back();
            lastPos--;
        }
        else if (currentDirection == "n" && lastDirection == "s")
        {
            workingList.pop_back();
            lastPos--;
        }
        else if (currentDirection == "ne" && lastDirection == "sw")
        {
            workingList.pop_back();
            lastPos--;
        }
        else if (currentDirection == "sw" && lastDirection == "ne")
        {
            workingList.pop_back();
            lastPos--;
        }
        else if (currentDirection == "nw" && lastDirection == "se")
        {
            workingList.pop_back();
            lastPos--;
        }
        else if (currentDirection == "se" && lastDirection == "nw")
        {
            workingList.pop_back();
            lastPos--;
        } // Other transformations
        else if ((currentDirection == "ne" && lastDirection == "s") || (currentDirection == "s" && lastDirection == "ne"))
        {
            workingList[lastPos] = "se";
        }
        else if ((currentDirection == "nw" && lastDirection == "s") || (currentDirection == "s" && lastDirection == "nw"))
        {
            workingList[lastPos] = "sw";
        }
        else if ((currentDirection == "se" && lastDirection == "n") || (currentDirection == "n" && lastDirection == "se"))
        {
            workingList[lastPos] = "ne";
        }
        else if ((currentDirection == "sw" && lastDirection == "n") || (currentDirection == "n" && lastDirection == "sw"))
        {
            workingList[lastPos] = "nw";
        }
        else if ((currentDirection == "ne" && lastDirection == "nw") || (currentDirection == "nw" && lastDirection == "ne"))
        {
            workingList[lastPos] = "n";
        }
        else if ((currentDirection == "se" && lastDirection == "sw") || (currentDirection == "sw" && lastDirection == "se"))
        {
            workingList[lastPos] = "s";
        }
        else
        {
            workingList.push_back(currentDirection);
            lastPos++;
        }

    }
    
    cout<<"size of transformed list is "<<workingList.size()<<endl;
    
    // for (auto i : workingList) 
    // {
    //     cout<<i<<", ";
    // }
    // cout<<endl;
    
    // Process the remaining directions for count
    if (workingList.size() == 0)
    {
        cout<<"count is 0"<<endl;
        return 0;
    }
    
    lastDirection = workingList[0];
    long count = 1; // to factor in the first move
    
    cout<<lastDirection<<" "<<workingList[1]<<endl;
    
    long directionUpDown = 0;
    long directionDiagonalRightLeft = 0;
    long directionDiagonalLeftRight = 0;
    
    set<vector<string>> notIncrementing;
    
    cout<<"counted path "<<endl;
    
    for (int i = 1; i < workingList.size(); i++)
    {
        currentDirection = workingList[i];
        
        if (lastDirection == currentDirection)
        {
            count++;
        }
        else if ((currentDirection == "ne" && lastDirection == "se") || (currentDirection == "se" && lastDirection == "ne"))
        {
            count++;
        }
        else if ((currentDirection == "nw" && lastDirection == "sw") || (currentDirection == "sw" && lastDirection == "nw"))
        {
            count++;
        }
        else if ((currentDirection == "sw" || currentDirection == "se") && lastDirection == "s")
        {
            count++;
        }
        else if ((lastDirection == "sw" || lastDirection == "se") && currentDirection == "s")
        {
            count++;
        }
        else if ((currentDirection == "nw" || currentDirection == "ne") && lastDirection == "n")
        {
            count++;
        }
        else if ((lastDirection == "nw" || lastDirection == "ne") && currentDirection == "n")
        {
            count++;
        }// deduct
        else if (currentDirection == "s" && lastDirection == "n") // transformations that cancel each other out
        {
            directionUpDown--;
            count--;
        }
        else if (currentDirection == "n" && lastDirection == "s")
        {
            directionUpDown--;
            count--;
        }
        else if (currentDirection == "ne" && lastDirection == "sw")
        {
            directionDiagonalRightLeft--;
            count--;
        }
        else if (currentDirection == "sw" && lastDirection == "ne")
        {
            directionDiagonalRightLeft--;
            count--;
        }
        else if (currentDirection == "nw" && lastDirection == "se")
        {
            directionDiagonalLeftRight--;
            count--;
        }
        else if (currentDirection == "se" && lastDirection == "nw")
        {
            directionDiagonalLeftRight--;
            count--;
        }
        else
        {
            // cout<<"not incrementing "<<lastDirection<<" "<<currentDirection<<endl;
            if (lastDirection == currentDirection)
                break;
                
            notIncrementing.insert(vector<string>{lastDirection, currentDirection});
                
            // change directions
            if ((currentDirection == "ne" && lastDirection == "s") || (currentDirection == "s" && lastDirection == "ne"))
            {
                lastDirection = "se";
            }
            else if ((currentDirection == "nw" && lastDirection == "s") || (currentDirection == "s" && lastDirection == "nw"))
            {
                lastDirection = "sw";
            }
            else if ((currentDirection == "se" && lastDirection == "n") || (currentDirection == "n" && lastDirection == "se"))
            {
                lastDirection = "ne";
            }
            else if ((currentDirection == "sw" && lastDirection == "n") || (currentDirection == "n" && lastDirection == "sw"))
            {
                lastDirection = "nw";
            }
            else if ((currentDirection == "ne" && lastDirection == "nw") || (currentDirection == "nw" && lastDirection == "ne"))
            {
                lastDirection = "n";
            }
            else if ((currentDirection == "se" && lastDirection == "sw") || (currentDirection == "sw" && lastDirection == "se"))
            {
                lastDirection = "s";
            }
        }
        
        if (currentDirection == "s")
            directionUpDown+= -1;
        else if (currentDirection == "n")
            directionUpDown += 1;
        else if (currentDirection == "ne")
            directionDiagonalRightLeft += 1;
        else if (currentDirection == "sw")
            directionDiagonalRightLeft -= 1;
        else if (currentDirection == "nw")
            directionDiagonalLeftRight += 1;
        else if (currentDirection == "se")
            directionDiagonalLeftRight -= 1;
        
        lastDirection = currentDirection;
    }
    
    cout<<endl<<"count is "<<count<<endl;
    cout<<"direction are "<<endl;
    cout<<"Up down "<<directionUpDown<<endl;
    cout<<"directionDiagonalRightLeft "<<directionDiagonalRightLeft<<endl;
    cout<<"directionDiagonalLeftRight "<<directionDiagonalLeftRight<<endl;
    
    cout<<"not incrementing"<<endl;
    for (auto i : notIncrementing) 
    {
        cout<<i[0]<<" "<<i[1]<<endl;
    }
    
    
    return 0;
}