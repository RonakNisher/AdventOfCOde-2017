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
    
    string genAStr;
    string genBStr;
    
    int count = 0;
    
    long long end = 5000000;
    
    cout<<end<<endl;
    
    for (long i = 0; i <= end ;i++) 
    {
        if (i%1000000 == 0)
            cout<<"i is "<<i<<endl;
        // cout<<i<<endl;
        
        genA = (genAStart * 16807) % 2147483647;
        
        while (genA%4 != 0)
        {
            genAStart = genA;
            genA = (genAStart * 16807) % 2147483647;
        }
        
        
        genB = (genBStart * 48271) % 2147483647;
        
        while (genB%8 != 0)
        {
            genBStart = genB;
            genB = (genBStart * 48271) % 2147483647;
        }
        
        // std::cout << genA << " "<<genB << std::endl;
        
        genAStr = std::bitset<32>(genA).to_string(); //to binary
        genBStr = std::bitset<32>(genB).to_string(); //to binary
        
        // cout<<genAStr<<endl;
        // cout<<genBStr<<endl;
        
        // cout<<genAStr.substr(16)<<endl;
        
        // break;

        if (genAStr.substr(16) == genBStr.substr(16))
            count++;
            
        genAStart = genA;
        genBStart = genB;
    }
    
    cout << count<<endl;
    // std::string binary = std::bitset<8>(128).to_string(); //to binary

    
    
    
    
    
    return 0;
}