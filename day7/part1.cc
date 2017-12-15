#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef struct disc
{
    string name;
    int weight;
    vector<string> disksAbove;
} Disc;

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

Disc* ToDisc(string line)
{
    vector<string> words = split(line,",()->");
    
    // for (auto word : words) {
    //     cout<<word<<" ";
    // }
    cout<<endl;
    
    Disc* d = new Disc();
    d->name = words[0];
    d->weight = stoi(words[1]);
    
    if (words.size() > 2)
    {
        for (int i = 2; i < words.size(); i++) 
        {
            d->disksAbove.push_back(words[i]);
        }
    }
    
    return d;
}

int main()
{
    int validPhrases = 0;
    string line;
    std::vector<Disc*> discs;
    
    set<string> children;
    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            discs.push_back(ToDisc(line));
        }
        myfile.close();
    }
    
    cout << discs.size() << endl;
    
    // make a set of all disks which are children
    for (auto i : discs) {
        // cout << i->name <<endl;
        if (i->disksAbove.size() != 0)
        {
            for_each (i->disksAbove.begin(), i->disksAbove.end(), [&children](string s){children.insert(s);});
        }
    }
    cout << "size of children set "<<children.size()<<endl;
    
    // find the disc which is not in the set of children
    for (auto d : discs) {
        if (children.find(d->name) == children.end())
            cout << "root is "<<d->name <<endl;
    }

    return 0;
}