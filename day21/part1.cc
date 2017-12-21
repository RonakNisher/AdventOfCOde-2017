#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <cctype>

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

    vector<string> inputPatterns;
    vector<string> outputPatterns;
    vector<int> sizeOfPattern;
    vector<int> numberOfOnes;
    
string GetOutput(string input, int size)
{
    long ones = count(input.begin(), input.end(), '#');
    
    vector<int> available;
    
    for (int i = 0; i < inputPatterns.size(); i++)
    {
        string inputPattern = inputPatterns[i];
        if (inputPatterns[i] == input)
            return outputPatterns[i];
        
        if (sizeOfPattern[i] != size || numberOfOnes[i] != ones)
            continue;
            
        if (size == 2)
        {
            // diagonal
            int diagIp = input[0] + input[4];
            int diagP1 = inputPattern[0] + inputPattern[4];
            int diagP2 = inputPattern[1] + inputPattern[3];
            
            if (diagIp != diagP1 && diagIp != diagP2)
                continue;

        }
            
        if (size == 3)
        {
            if (inputPattern[5] != input[5]) // center
                continue;
                
            //edge vertices
            // cout<<input<<" "<<inputPattern<<endl;

            int edgesIp = input[0] + input[2] + input[8] + input[10];
            int edgesP = inputPattern[0] + inputPattern[2] + inputPattern[8] + inputPattern[10];
            // cout<<edgesIp<<" "<<edgesP<<endl;
            if (edgesIp != edgesP)
                continue;
                
            int innerIp = input[1] + input[4] + input[6] + input[9];
            int innerP = inputPattern[1] + inputPattern[4] + inputPattern[6] + inputPattern[9];
            
            if (innerIp != innerP)
                continue;
                
            // check for rotation of opposite sides
            int r1Ip = input[0] + input[1] + input[2];
            int r2Ip = input[8] + input[9] + input[10];
            int r3Ip = input[0] + input[4] + input[8];
            int r4Ip = input[2] + input[6] + input[10];
            
            int r1P = inputPattern[0] + inputPattern[1] + inputPattern[2];
            int r2P = inputPattern[8] + inputPattern[9] + inputPattern[10];
            int r3P = inputPattern[0] + inputPattern[4] + inputPattern[8];
            int r4P = inputPattern[2] + inputPattern[6] + inputPattern[10];
            
            if (r1P != r1Ip && r2P != r1Ip && r3P != r1Ip && r4P != r1Ip)
                continue;
                
            if (r1P != r2Ip && r2P != r2Ip && r3P != r2Ip && r4P != r2Ip)
                continue;
                
            if (r1P != r3Ip && r2P != r3Ip && r3P != r3Ip && r4P != r3Ip)
                continue;
                
            if (r1P != r4Ip && r2P != r4Ip && r3P != r4Ip && r4P != r4Ip)
                continue;
                
            if ((r1Ip + r2Ip) != (r1P + r2P) && ((r1Ip + r2Ip) != (r3P + r4P)))
                continue;
                
            if ((r3Ip + r4Ip) != (r1P + r2P) && ((r3Ip + r4Ip) != (r3P + r4P)))
                continue;
                
            if ((r1Ip + r4Ip) != (r1P + r4P) && ((r1Ip + r4Ip) != (r1P + r3P))
                && (r1Ip + r4Ip) != (r2P + r4P) && ((r1Ip + r4Ip) != (r2P + r3P)))
                continue;
                
            if ((r1Ip + r3Ip) != (r1P + r4P) && ((r1Ip + r3Ip) != (r1P + r3P))
                && (r1Ip + r3Ip) != (r2P + r4P) && ((r1Ip + r3Ip) != (r2P + r3P)))
                continue;
                
            if ((r2Ip + r4Ip) != (r1P + r4P) && ((r2Ip + r4Ip) != (r1P + r3P))
                && (r2Ip + r4Ip) != (r2P + r4P) && ((r2Ip + r4Ip) != (r2P + r3P)))
                continue;
                
            if ((r2Ip + r3Ip) != (r1P + r4P) && ((r2Ip + r3Ip) != (r1P + r3P))
                && (r2Ip + r3Ip) != (r2P + r4P) && ((r2Ip + r3Ip) != (r2P + r3P)))
                continue;
                
            // find flip
            int f1 = inputPattern.find(input.substr(0,3));
            if (f1 != string::npos)
            {
                string temp = inputPattern;
                inputPattern.erase(f1,3);
                int f2 = inputPattern.find(input.substr(4,3));
                
                if (f2  != string::npos)
                {
                    inputPattern.erase(f2,3);
                    bool f3 = inputPattern.find(input.substr(8,3)) != string::npos;
                    if (f3)
                    {
                        // cout<<"inputPattern "<<inputPattern<<" "<<i<<endl;
                        return outputPatterns[i];
                    }
                }
            }
            
            

            // if (count(edgesIp.begin(), edgesIp.end(), '#') != count(edgesP.begin(), edgesP.end(), '#'))
                // continue;
            
        }
            
        available.push_back(i);
    }
    
    if (available.size() == 1)
        return outputPatterns[available[0]];
        
    // TODO: rotate and swap
    // cout<<"TODODODODOD "<<available.size()<<" "<<input<<endl;
    
    for (auto i : available) 
    {
        string temp = inputPatterns[i];
        
        // check rotations
        // top is left
        if (input[0] == temp[8] && input[1] == temp[4] && input[2] == temp[0]
        &&  input[4] == temp[9] && input[5] == temp[5] && input[6] == temp[1]
        &&  input[8] == temp[10] && input[9] == temp[6] && input[10] == temp[2])
            return outputPatterns[i];
            
        // top is right
        if (input[0] == temp[2] && input[1] == temp[6] && input[2] == temp[10]
        &&  input[4] == temp[1] && input[5] == temp[5] && input[6] == temp[9]
        &&  input[8] == temp[0] && input[9] == temp[4] && input[10] == temp[8])
            return outputPatterns[i];
            
        // top is down
        if (input[0] == temp[10] && input[1] == temp[9] && input[2] == temp[8]
        &&  input[4] == temp[6] && input[5] == temp[5] && input[6] == temp[4]
        &&  input[8] == temp[2] && input[9] == temp[1] && input[10] == temp[0])
            return outputPatterns[i];
        
    }
        cout<<"cound not find stuff "<<input<<endl;
    if (size == 2)
        return "$$$/$$$/$$$";
    else
        return "$$$$/$$$$/$$$$/$$$$";

}


int main()
{
    string line;

    vector<string> output;
    output.reserve(30);
    output.push_back(".#.");
    output.push_back("..#");
    output.push_back("###");
    
    cout<<"output 0"<<output[0]<<endl;

    // long outputRows = 3;

    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            vector<string> words;

            words = split(line,"=>");
            
            // cout<<words[0]<<" => "<<words[1]<<endl;
            inputPatterns.push_back(words[0]);
            outputPatterns.push_back(words[1]);
            sizeOfPattern.push_back(count(words[0].begin(), words[0].end(), '/') + 1);
            numberOfOnes.push_back(count(words[0].begin(), words[0].end(), '#'));
        
        }
        myfile.close();
    }
    
    cout<<"size of input "<<inputPatterns.size()<<endl;
    
    for (int i = 0; i < 18; i++) 
    {
        vector<string> newOutput;
        
        if (output.size()%2 == 0)
        {
            int rowBlocks = (output.size())/2;
            for (int i = 0; i < rowBlocks * 3; i++) {
                newOutput.push_back("");
            }
            
            for (int r = 0; r < rowBlocks; r++) 
            {
                for (int c = 0; c < rowBlocks; c++)
                {
                    string p = output[2*r].substr(2*c, 2) + "/" + output[2*r + 1].substr(2*c, 2);
                    // cout<<"string is "<<p<<endl;
                    string o = GetOutput(p, 2);
                    // cout<<"o/p is "<<o<<endl;

                    
                    // put in new o/p
                    newOutput[r*3] = newOutput[r*3] + o.substr(0,3);
                    newOutput[r*3 + 1] = newOutput[r*3 + 1] + o.substr(4,3);
                    newOutput[r*3 + 2] = newOutput[r*3 + 2] + o.substr(8,3);
                }
            }
        }
        else
        {
            int rowBlocks = (output.size())/3;
            
            for (int i = 0; i < rowBlocks * 4; i++) {
                newOutput.push_back("");
            }
            
            for (int r = 0; r < rowBlocks; r++) 
            {
                for (int c = 0; c < rowBlocks; c++)
                {
                    // cout<<output[3*r]<<endl;
                    string p = output[3*r].substr(3*c, 3) + "/" + output[3*r + 1].substr(3*c, 3) + "/" + output[3*r + 2].substr(3*c, 3);
                    // cout<<"string is "<<p<<endl;

                    string o = GetOutput(p, 3);
                    // cout<<"o/p is "<<o<<endl;

                    
                    // put in new o/p
                    newOutput[r*4] = newOutput[r*4] + o.substr(0,4);
                    newOutput[r*4 + 1] = newOutput[r*4 + 1] + o.substr(5,4);
                    newOutput[r*4 + 2] = newOutput[r*4 + 2] + o.substr(10,4);
                    newOutput[r*4 + 3] = newOutput[r*4 + 3] + o.substr(15,4);
                }
            }
        }
        
        output = newOutput;
    }
    
    int cnt = 0;
    cout<<"final o/p is "<<endl;
    for (auto i : output) 
    {
        // cout<<i<<endl;
        cnt += count(i.begin(), i.end(), '#');
    }
    cout<<cnt<<endl;
    return 0;
}