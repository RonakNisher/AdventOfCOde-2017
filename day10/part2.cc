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
    
    cout<<"res is "<<result<<endl;
    
    return result;

}

int main()
{
    string line;
    
    vector<int> workingList;
    vector<int> input;

    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        vector<string> words;
        while ( getline (myfile,line) )
        {
            input.reserve(line.size() + 5);
            for (auto ch : line) 
            {
                input.push_back(int(ch));
            }
        }
        
        myfile.close();
        
        input.push_back(17);
        input.push_back(31);
        input.push_back(73);
        input.push_back(47);
        input.push_back(23);
        
        cout<<"input "<<endl;
        print(input);

        
        for (int i = 0; i < size; i++) 
        {
            workingList.push_back(i);
        }
        
        GetKnotHash(workingList, input);
    }
    
    return 0;
}