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

static int size = 256;


void reverse(int currentPosition, int length, vector<int>& workingList)
{
    int startPos = currentPosition;
    int endPos = (currentPosition + length - 1) % size;
    
    // std::cout << "startPos" << startPos << std::endl;
    
    // std::cout << "endPos" << endPos << std::endl;
    
    // int iteration = 0;
    for (int i = 0; i < length/2 ; i++)
    {
        // std::cout << "i" << i << std::endl;

        int temp = workingList[startPos];
        workingList[startPos] = workingList[endPos];
        workingList[endPos] = temp;
        
        startPos = (startPos + 1)%size;
        
        if (endPos == 0)
            endPos = size - 1;
        else
            endPos = (endPos - 1)%size;
        
        // iteration++;
    }
    
    std::cout << "end" << std::endl;
}

void RunKnotHashRound(vector<int>& workingList, int& skipSize, int& currentPosition, vector<int>& input)
{
    for (int j = 0; j < input.size(); j++) 
    {
        // std::cout << "len before"<<len << std::endl;

        int length = input[j];
        
        // std::cout << "len "<<length << std::endl;
        
        // select and revert length no of elements
        reverse(currentPosition, length, workingList);
        
        // for (auto i : workingList) {
        //     std::cout << i << " ";
        // }
        // cout<<endl;
        
        // move forward
        currentPosition = (currentPosition + (length + skipSize))%size;
        
        cout << "currentPosition " << currentPosition<<" element is "<<workingList[currentPosition]<<endl;
        
        skipSize++;
    }
}

void GetKnotHash(vector<int>& workingList, vector<int>& input)
{
    int skipSize = 0;
    int currentPosition = 0;
    
    for (int i = 0; i < 63; i++) 
    {
        RunKnotHashRound(workingList, skipSize, currentPosition, input);
    }
    
    // calculate dense hash
    vector<int> denseHash;
    denseHash.reserve(16);
    
    int res;
    
    for (int i = 0; i < 256; i+=16) 
    {
        res = workingList[i];
        
        for (int j = 1; j < 16; j++) 
        {
            res = res ^ workingList[i + j];
        }
        
        denseHash.push_back(res);
    }
    
    // convert dense hash to hex

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
            // words = split(line,",");
            
            // for (auto i : words) {
            //     cout<<stoi(i)<<" ";
            // }
            // cout<<endl;
            
        }
        
        myfile.close();
        
        input.push_back(17);
        input.push_back(31);
        input.push_back(73);
        input.push_back(47);
        input.push_back(23);

        // for (auto i : input) {
        //     cout<<i<<" ";
        // }
        // cout<<endl;
        
        for (int i = 0; i < size; i++) 
        {
            workingList.push_back(i);
        }
        
        GetKnotHash(workingList, input);
        
        // for (auto i : workingList) {
        //         std::cout << i << " ";
        //     }
        //     cout<<endl;
        
        std::cout << workingList[0] << ", "<< workingList[1] << std::endl;
        // std::cout << workingList[0] * workingList[1] << std::endl;
        
        // myfile.close();
    }
    
    return 0;
}