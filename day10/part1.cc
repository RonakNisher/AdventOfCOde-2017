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
// vector<int> workingList;



void reverse(int currentPosition, int length, vector<int>& workingList)
{
    int startPos = currentPosition;
    int endPos = (currentPosition + length - 1) % size;
    
    std::cout << "startPos" << startPos << std::endl;
    
    std::cout << "endPos" << endPos << std::endl;
    
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

int main()
{
    string line;
    
    vector<int> workingList;

    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        vector<string> words;
        while ( getline (myfile,line) )
        {
            words = split(line,",");
            
            for (auto i : words) {
                cout<<stoi(i)<<" ";
            }
            cout<<endl;
            
        }
        
        std::cout << words.size() << std::endl;
        myfile.close();

        
        for (int i = 0; i < size; i++) 
        {
            workingList.push_back(i);
        }
        
        int skipSize = 0;
        int currentPosition = 0;
        
        for (int j = 0; j < words.size(); j++) 
        {
            // std::cout << "len before"<<len << std::endl;

            int length = stoi(words[j]);
            
            std::cout << "len "<<length << std::endl;
            
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
        
        for (auto i : workingList) {
                std::cout << i << " ";
            }
            cout<<endl;
        
        std::cout << workingList[0] << ", "<< workingList[1] << std::endl;
        // std::cout << workingList[0] * workingList[1] << std::endl;
        
        cout<<"nabsba";
        
        // myfile.close();
    }
    
    return 0;
}