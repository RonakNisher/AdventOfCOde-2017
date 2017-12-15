#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

vector<string> split(string input)
{
    vector<string> res;
    
    string val = "";
    for (auto i : input) {
        if(!isspace(i))
        {
            val.push_back(i);
        }
        else
        {
            res.push_back(val);
            val = "";
        }
    }
    
    if(val != "")
        res.push_back(val);
    return res;
}

int main()
{
    int validPhrases = 0;
    string line;
    std::vector<int> input;
    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            for (auto word : split(line)) {
                input.push_back(stoi(word));
            }
        }
        myfile.close();
    }
    
    // cout<<"input "<<endl;
    // for (auto i : input) 
    // {
    //   cout<<i<<" ";
    // }
    // cout<<endl;
    
    int numberOfSteps = 0;
    int size = input.size();
    cout<<"size of input "<<input.size()<<endl;
    
    set<std::vector<int>> seenMemoryBlockPatterns;
    int loopSize = 0;
    bool shouldIncrementLoopSize = false;
    
    while (true) 
    {
        int maximumValue = input[0];
        int maximumValueIndex = 0;
        
        // find max element position and value
        for(int i = 1; i < size; i++)
        {
            if (input[i] > maximumValue)
            {
                maximumValue = input[i];
                maximumValueIndex = i;
            }
        }
        
        // cout<<"maximumValue "<<maximumValue<<endl;
        
        // redistribute the blocks
        input[maximumValueIndex] = 0;
        
        maximumValueIndex++; //to start redistributing from next index
        
        while (maximumValue != 0)
        {
            input[maximumValueIndex%size]+= 1;
            maximumValueIndex++;
            maximumValue--;
        }
        
        numberOfSteps++;
        
        // Check the size of the loop
        if (!seenMemoryBlockPatterns.insert(input).second)
        {
            if (shouldIncrementLoopSize)
                break;
            
            shouldIncrementLoopSize = true;
            seenMemoryBlockPatterns.clear();
            seenMemoryBlockPatterns.insert(input);
        }
        
        if (shouldIncrementLoopSize)
            loopSize++;
        
    }
    
    cout<<"Number of steps "<<numberOfSteps - loopSize<<endl;
    cout<<"Loop size "<<loopSize<<endl;

    return 0;
}