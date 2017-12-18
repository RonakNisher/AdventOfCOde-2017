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

void floodfill(int row, int col, int (&regionGrid)[128][128], int currentGrp)
{
    if (row < 0 || row > 127 || col < 0 || col > 127)
        return;
        
    if (regionGrid[row][col] != -1)
        return;
        
    regionGrid[row][col] = currentGrp;
    
    floodfill(row-1, col, regionGrid, currentGrp); // top
    floodfill(row+1, col, regionGrid, currentGrp); // bottom
    floodfill(row, col - 1, regionGrid, currentGrp); // left
    floodfill(row, col + 1, regionGrid, currentGrp); //right
    
    return;
}

int main()
{
    string line;
    
    vector<int> workingList;
    vector<int> input;
    
    // line = "flqrgnkx";
    line = "amgozmfv";

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
                regionGrid[i][j] = -1;
        }
    }
    
    int currentGrp = 1;
    
    
    // for the rest of the columns in the grid, look at the top as well as the left to decide
    for (int column = 0; column < 128; column++) 
    {
        // rest of the rows
        for (int row = 0; row < 128; row++) 
        {
            if (regionGrid[row][column] == -1)
            {
                floodfill(row, column, regionGrid, currentGrp);
                currentGrp++;
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