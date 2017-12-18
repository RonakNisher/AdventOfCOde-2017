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
    
    int noOfSteps = 354;
    
    list<int> data;
    // data.reserve(2018);
    data.push_back(0);
    
    int size = 1;
    int currentPos = 0;
    
    auto begin = data.begin();
    
    for (int i = 1; i < 2018; i++) 
    {
        currentPos = (currentPos + noOfSteps) % size;
        
        auto r = data.begin();
        advance(r, currentPos + 1);
        
        // auto t = find(data.begin(), data.end(), )
        data.insert(r, i);
        currentPos++;
        size++;
    }
    
    auto r = data.begin();
    advance(r, currentPos);
    
    cout<<"currentPos "<<currentPos<<endl;
            
    cout<<"val "<<*r<<" "<<*(++r)<<endl;

        // cout<<"val "<<data[currentPos]<<" "<<data[currentPos + 1]<<endl;

    
//   for (auto i : data) {
//       cout<<i<<" ";
//   }
    
    return 0;
}