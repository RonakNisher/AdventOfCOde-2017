#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
            input.push_back(stoi(line));
        }
        myfile.close();
    }
    cout<<"size of input"<<input.size()<<endl;
    
    int numberOfSteps = 0;
    int currentIndex = 0;
    int nextIndex = 0;
    
    while (nextIndex >= 0 && nextIndex <= input.size() - 1) 
    {
        numberOfSteps++;
        
        nextIndex = currentIndex + input[currentIndex];
        input[currentIndex]+=1;
        currentIndex = nextIndex;
        
        // cout<<"Next Index"<<nextIndex<<endl;

    }
    cout<<"Number of steps "<<numberOfSteps<<endl;

    return 0;
}