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

int sizeOfRow;
int sizeOfCol;

int cnt;
int c = 0;

bool isValid(int row, int col)
{
    return (row >= 0) && (row < sizeOfRow) && (col >= 0) && (col <= sizeOfCol);
}

int main()
{
    string line;
    vector<string> path;
    
    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            // words = split(line,",");
            path.push_back(line);
            
            // for (auto i : words) {
            //     cout<<i<<" ";
            // }
            // cout<<endl;
            
        }
        
        myfile.close();
    }
    
    cout<<"path size "<<path.size()<<endl;
    
    sizeOfRow = path.size();
    sizeOfCol = path[0].size();
    
    int currentPosRow = 0;
    int currentPosCol = path[0].find('|');
    
    int directionModifierRow = 1; // + is going down, - is going up
    int directionModifierCol = 1; // + is right, - is left
    
    char lastCharacterSeen;
    
    bool isGoingVertical = true;
    
    bool shouldEnd = false;
    
    cout<<"starting at "<<currentPosCol<<endl;
    // process the path
    while(!shouldEnd)
    {
        ++c;
        // cout << "at pos "<<currentPosRow<<" "<<currentPosCol<<endl;
        switch (path[currentPosRow][currentPosCol])
        {
            case '|':
                    // currentPosRow = currentPosRow + directionModifierRow;
                    // lastCharacterSeen = '|';
                    if (isGoingVertical)
                    {
                        int newRow = currentPosRow + directionModifierRow;
                        if (isValid(newRow, currentPosCol) && !isblank(path[newRow][currentPosCol]))
                        {
                            currentPosRow = newRow;
                            cnt++;
                        }
                        else
                        {
                            cout<<"Ended on | at "<<currentPosRow<<" "<<currentPosCol<<endl;
                            shouldEnd = true;
                        }
                        break;
                    }
                    else
                    {
                        int newCol = currentPosCol + directionModifierCol;
                        if (isValid(currentPosRow, newCol) && !isblank(path[currentPosRow][newCol]))
                        {
                            currentPosCol = newCol;
                            cnt++;
                            break;
                        }
                        else
                        {
                            cout<<"Ended on | at "<<currentPosRow<<" "<<currentPosCol<<endl;
                            shouldEnd = true;
                        }
                    }
                    break;
                    
            case '-':
                    if (isGoingVertical)
                    {
                        int newRow = currentPosRow + directionModifierRow;
                        if (isValid(newRow, currentPosCol) && !isblank(path[newRow][currentPosCol]))
                        {
                            currentPosRow = newRow;
                            cnt++;
                        }
                        else
                        {
                            cout<<"Ended on - at "<<currentPosRow<<" "<<currentPosCol<<endl;
                            shouldEnd = true;
                        }
                        break;
                    }
                    else
                    {
                        int newCol = currentPosCol + directionModifierCol;
                        if (isValid(currentPosRow, newCol) && !isblank(path[currentPosRow][newCol]))
                        {
                            currentPosCol = newCol;
                            cnt++;
                            break;
                        }
                        else
                        {
                            cout<<"Ended on - at "<<currentPosRow<<" "<<currentPosCol<<endl;
                            shouldEnd = true;
                        }
                    }
                    break;
                    
            case '+':
                    if (isGoingVertical)
                    {
                        if (isValid(currentPosRow, currentPosCol + 1) && !isblank(path[currentPosRow][currentPosCol + 1]))
                        {
                            currentPosCol = currentPosCol + 1;
                            directionModifierCol = 1;
                        }
                        else
                        {
                            currentPosCol = currentPosCol - 1;
                            directionModifierCol = -1;
                        }
                        isGoingVertical = false;
                        cnt++;
                    }
                    else
                    {
                        if (isValid(currentPosRow + 1, currentPosCol) && !isblank(path[currentPosRow + 1][currentPosCol]))
                        {
                            currentPosRow = currentPosRow + 1;
                            directionModifierRow = 1;
                        }
                        else
                        {
                            currentPosRow = currentPosRow - 1;
                            directionModifierRow = -1;
                        }
                        isGoingVertical = true;
                        cnt++;
                    }
                    // cout <<"switching pos to "<<currentPosRow<<" "<<currentPosCol<<endl;
                    break;
                    
            default:
                    cout<<"handling case "<<path[currentPosRow][currentPosCol]<<endl;
                    
                    if (isGoingVertical)
                    {
                        currentPosRow = currentPosRow + directionModifierRow;
                    }
                    else
                    {
                        currentPosCol = currentPosCol + directionModifierCol;
                    }
                    
                    if (isblank(path[currentPosRow][currentPosCol]))
                    {
                        cout<<"End this"<<endl;
                        shouldEnd = true;
                    }
                    else
                        cnt++;
                        
                    break;
        }
    }
    
    cout<<"count is "<<cnt<<endl;
        cout<<"count2 is "<<c<<endl;

    
    return 0;
}