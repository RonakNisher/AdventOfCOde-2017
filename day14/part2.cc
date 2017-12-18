#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>

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

static int size = 256;

void print(vector<int>& input)
{
    for (auto i : input) 
    {
        cout<<i<<" ";
    }
    cout<<endl;
}


void reverse(int currentPosition, int length, vector<int>& workingList)
{
    int startPos = currentPosition;
    int endPos = (currentPosition + length - 1) % size;
    
    for (int i = 0; i < length/2 ; i++)
    {
        std::swap(workingList[(startPos + i) % size], workingList[(startPos + length - i - 1) % size]);
    }
    
}

void RunKnotHashRound(vector<int>& workingList, int& skipSize, int& currentPosition, vector<int>& input)
{
    for (int j = 0; j < input.size(); j++) 
    {
        int length = input[j];
        
        // select and revert length no of elements
        reverse(currentPosition, length, workingList);
        
        // move forward
        currentPosition = (currentPosition + (length + skipSize))%size;
        
        skipSize++;
    }
}

string GetKnotHash(vector<int>& workingList, vector<int>& input)
{
    int skipSize = 0;
    int currentPosition = 0;
    
    for (int i = 0; i < 64; i++) 
    {
        RunKnotHashRound(workingList, skipSize, currentPosition, input);
    }
    
    // calculate dense hash
    vector<int> denseHash;
    denseHash.reserve(16);
    
    int res;
    
    for (int i = 0; i < 256;) 
    {
        res = workingList[i];
        
        for (int j = 1; j < 16; j++) 
        {
            res = res ^ workingList[i + j];
        }
        
        i = i + 16;
        denseHash.push_back(res);
    }
    
    // convert dense hash to hex
    
    std::stringstream stream;
    for (auto i : denseHash) 
    {
        stream <<setfill('0')<<setw(2) << std::hex << i;
    }
    std::string result( stream.str() );
    
    // cout<<"res is "<<result<<endl;
    
    return result;

}

int main()
{
    string line;
    
    vector<int> workingList;
    vector<int> input;

    
    // ifstream myfile ("input.txt");
    // if (myfile.is_open())
    // {
    //     vector<string> words;
    //     while ( getline (myfile,line) )
    //     {
    //         input.reserve(line.size() + 5);
    //         for (auto ch : line) 
    //         {
    //             input.push_back(int(ch));
    //         }
    //     }
        
    //     myfile.close();
    // }
    
    line = "flqrgnkx";
    // line = "amgozmfv";

    string res;
    bool grid[128][128] = {0};
    int regionGrid[128][128] = {0};
    int count;
    
    for (int i = 0; i < 128; i++) 
    {
        input.clear();
        workingList.clear();
        for (auto ch : line) 
        {
            input.push_back(int(ch));
        }
        
        input.push_back(int('-'));
        
        for (auto num : to_string(i)) 
        {
            input.push_back(int(num));
        }
            
        input.push_back(17);
        input.push_back(31);
        input.push_back(73);
        input.push_back(47);
        input.push_back(23);
        
        // cout<<"input "<<endl;
        // print(input);
    
        
        for (int i = 0; i < size; i++) 
        {
            workingList.push_back(i);
        }
        
        res = GetKnotHash(workingList, input);
        
         // convert to bits
         for (int j = 0; j < 32; j++) 
         {
             string ch = {res[j]};
             long n = strtol(ch.c_str(), nullptr, 16);
             
             grid[i][j*4]     = n & 0x8;
             grid[i][j*4 + 1] = n & 0x4;
             grid[i][j*4 + 2] = n & 0x2;
             grid[i][j*4 + 3] = n & 0x1;
             
            //  cout<<res[j]<<" "<<n<<" "<<grid[i][j*4]<<" "<<grid[i][j*4 + 1]<<" "<<grid[i][j*4 + 2]<<" "<<grid[i][j*4 + 3]<<endl;;
             
             count += (grid[i][j*4] + grid[i][j*4 + 1] + grid[i][j*4 + 2] + grid[i][j*4 + 3]);
         }
         
        //  break;
    }
    cout << "count of 1's is "<<count<<endl;
    
    // start part 2
    
    for (int i = 0; i < 128; i++) 
    {
        for (int j = 0; j < 128; j++) 
        {
            if (grid[i][j] == 1)
                regionGrid[i][j] = 1;
        }
    }
    
    int currentGrp = 2;
    
    // loop through the 1st column
    
    if (regionGrid[0][0] == 1)
    {
        regionGrid[0][0] = currentGrp;
        currentGrp++;
    }
    
    // see only top to see if connected
    for (int i = 1; i < 128; i++) 
    {
        if (regionGrid[i][0] == 1)
        {
            if (regionGrid[i-1][0] != 0)
            {
                regionGrid[i][0] = regionGrid[i-1][0];
            }
            else
            {
                regionGrid[i][0] = currentGrp;
                currentGrp++;
                // cout<<"New group at "<<i<<" "<<0<<" for new region "<<currentGrp<<endl;
            }
        }
    }
    
    int lastMismatch;
    int currentMismatch;
    
    // for the rest of the columns in the grid, look at the top as well as the left to decide
    for (int column = 1; column < 128; column++) 
    {
        // if (column == 3)
        //     break;
        lastMismatch = 0;
        currentMismatch = 0;
        // row 0
        if (regionGrid[0][column] == 1)
        {
            if (regionGrid[0][column - 1] != 0)
            {
                regionGrid[0][column] = regionGrid[0][column - 1];
            }
            else
            {
                regionGrid[0][column] = currentGrp;
                currentGrp++;
                // cout<<"New group at "<<0<<" "<<column<<" for new region "<<currentGrp<<endl;
            }
        }
        
        // rest of the rows
        for (int row = 1; row < 128; row++) 
        {
            if (regionGrid[row][column] == 1)
            {
                int left = regionGrid[row][column - 1];
                int top = regionGrid[row - 1][column];
                
                if (regionGrid[row][column - 1] != 0 && regionGrid[row - 1][column] != 0) // connected to both
                {
                    if (left == top)
                    {
                        regionGrid[row][column] = left;
                        lastMismatch = 0;
                    }
                    else
                    {
                        if (left < top)
                        {
                            regionGrid[row][column] = left;
                            regionGrid[row - 1][column] = left;
                            currentMismatch = left; // lower no
                        }
                        else
                        {
                            regionGrid[row][column] = top;
                            regionGrid[row][column - 1] = top;
                            currentMismatch = top; // lower no
                        }
                        
                        if (lastMismatch != currentMismatch)
                        {
                            currentGrp--; // because we found a new connected region
                            // cout<<"Mismatch at "<<" current pos "<<row<<" "<<column<<" "<<lastMismatch<<" "<<currentMismatch<<" new grpNo "<<currentGrp<<endl;
                            lastMismatch = currentMismatch;
                        }
                    }
                }
                else if (left != 0) // connected to left
                {
                    regionGrid[row][column] = left;
                }
                else if (top != 0) // connected to top
                {
                    regionGrid[row][column] = top;
                }
                else // separate region
                {
                    regionGrid[row][column] = currentGrp;
                    currentGrp++;
                    lastMismatch = 0;
                    // currentMismatch = 0;
                    // cout<<"New group at "<<row<<" "<<column<<" for new region "<<currentGrp<<endl;
                }
            }
        }
    }
    
    cout<<"no of connected regions is "<<currentGrp-1<<endl;
    
    // for (int i = 0; i < 128; i++) 
    // {
    //     for (int j = 0; j < 60; j++) 
    //     {
    //         cout<<setw(3)<<regionGrid[i][j]<<" ";
    //     }
    //     cout<<endl;
    //     cout<<endl;
    // }
    
    
    return 0;
}