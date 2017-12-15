#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
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


int main()
{
    string line;
    
    // ifstream myfile ("input.txt");
    // if (myfile.is_open())
    // {
    //     while ( getline (myfile,line) )
    //     {
    //         vector<string> words = split(line,"");
            
    //         // for (auto i : words) {
    //         //     cout<<i<<" ";
    //         // }
    //         // cout<<endl;
            
    //     }
        
    //     myfile.close();
    // }
    
    long genAStart = 289;//65;
    long genBStart = 629;//8921;
    
    long genA;
    long genB;
    
    int count = 0;
    
    long long end = 40000000;
    
    for (long i = 0; i <= end ;i++) 
    {
        genA = (genAStart * 16807) % 2147483647;
        genB = (genBStart * 48271) % 2147483647;
        
        if ((genA&0xFFFF) == (genB&0xFFFF))
            count++;
            
        genAStart = genA;
        genBStart = genB;
    }
    
    cout << count<<endl;
    
    return 0;
}