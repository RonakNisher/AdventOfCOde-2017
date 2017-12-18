#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <bitset>

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
    string line;
    vector<string> words;
    
    // ifstream myfile ("input.txt");
    // if (myfile.is_open())
    // {
    //     while ( getline (myfile,line) )
    //     {
    //         words = split(line,",");
            
    //         // for (auto i : words) {
    //         //     cout<<i<<" ";
    //         // }
    //         // cout<<endl;
            
    //     }
        
    //     myfile.close();
    // }
    
    long long noOfSteps = 354;
    
    vector<long long> data;
    data.reserve(50000002);
    data.push_back(0);
    
    long long size = 1;
    long long currentPos = 0;
    
    std::vector<long long>::iterator begin = data.begin();
    
        for (long long i = 1; i <= 50000000; i++) 
    {
        if (i % 500000 == 0)
            cout<<"i "<<i<<endl;
        currentPos = (currentPos + noOfSteps) % size;
        data.insert(begin+currentPos + 1, i);
        currentPos++;
        size++;
    }
    
    auto ans = find(data.begin(), data.end(), 0);
    
    cout<<"currentPos "<<*(ans + 1)<<endl;
    
    cout<<"val "<<data[currentPos]<<" "<<data[currentPos + 1]<<endl;

    
//   for (auto i : data) {
//       cout<<i<<" ";
//   }
    
    return 0;
}