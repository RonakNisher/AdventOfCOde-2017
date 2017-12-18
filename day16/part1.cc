#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <deque>
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

void print(deque<char>& positions)
{
    for (int i = 0; i < 16; i++)
    {
        cout<<positions.at(i);
    }
    cout<<endl;
}


int main()
{
    string line;
    vector<string> words;
    
    map<deque<char>,int> iterations;
    set<deque<char>> seenMoves;
    int seenAtIteration;
    int stoppedAtIteration;
    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            words = split(line,",");
            
            // for (auto i : words) {
            //     cout<<i<<" ";
            // }
            // cout<<endl;
            
        }
        
        myfile.close();
    }
    
    // set up dequeue
    deque<char> positions;
    
    for (int i = 0; i < 16; i++) 
    {
        positions.push_back((char)i + 'a');
    }
    
    print(positions);
    
     // perform moves
     for (long i = 0; i < 1000000000; i++) 
     {
         if (i % 1000 == 0)
         cout<<"iteration "<<i<<endl;
     
         for (auto ins : words) 
         {
            //  cout<<ins<<endl;
             if (ins[0] == 's')
             {
                 int num = stoi(ins.substr(1));
                //  cout<<" spin "<<num<<endl;
                 
                 while (num > 0)
                 {
                     char charToSpin = positions.back();
                     positions.pop_back();
                     positions.push_front(charToSpin);
                     num --;
                 }
                 
                //  print(positions);
             }
             else if (ins[0] == 'x')
             {
                //  cout<<" exchange "<<endl;
                 int slash = ins.find('/');
                 int num1 = stoi(ins.substr(1,slash-1));
                 int num2 = stoi(ins.substr(slash +1));
                 
                //  cout<<" exchange "<<num1<<" "<<num2<<endl;
    
                 swap(positions.at(num1), positions.at(num2));
                            //   print(positions);
    
             }
             else if (ins[0] == 'p')
             {
                // cout<<" Partner "<<endl;
                char char1 = ins[1];
                char char2 = ins[3];
                
                swap(*find(positions.begin(),positions.end(),char1), *find(positions.begin(),positions.end(),char2));
             }
         }
         
         if (seenMoves.insert(positions).second)
         {
            // cout<<"inserting at "<<i<<endl;
            // print(positions);
            iterations[positions] = i;
         }
         else
         {
             cout<<"current iteration "<<i<<endl;
             cout<<"seen value at "<<iterations[positions]<<endl;
            //  auto a = (iterations.begin()->first);
            //  print(a);
            seenAtIteration = iterations[positions];
            stoppedAtIteration = i;
             
             break;
         }
     
     }
    
    print(positions);
    
    int offset = 1000000000 % stoppedAtIteration + 1;
    
    offset = 39;
    cout << " offset "<<offset<<endl;       
    
    for (auto i : iterations) 
    {
        if (i.second == offset)
        {
            auto t = i.first;
            print(t);
        }
    }
    // cout<<t->second;
    // auto finalPos = iterations.at(positions) + offset;

    return 0;
}