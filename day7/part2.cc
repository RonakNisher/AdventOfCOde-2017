#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <map>
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

int GetUnbalancedDiscWeight(string discName, map<string, Disc*>& discsMap)
{
    Disc* d = discsMap[discName];
    // cout<<"current disc is "<<d->name<<endl;

    if (d->disksAbove.size() != 0)
    {
        map<int,int> mapOfWeightAndCount;
        map<int,string> mapOfWeightAndName;
        
        for (auto diskAbove : d->disksAbove) {
            int weight = GetUnbalancedDiscWeight(discsMap[diskAbove]->name, discsMap);
            mapOfWeightAndCount[weight] += 1;
            mapOfWeightAndName[weight] = discsMap[diskAbove]->name;
        }
        
        // check if all discs had the same weight
        if (mapOfWeightAndCount.size() != 1)
        {
            // unbalanced -> find the weight is which is different than the others and the disk with the different weight
            int idealWeight = 0;
            int actualWeight = 0;
            
            map<int,int>::iterator firstElement = mapOfWeightAndCount.begin();
            map<int,int>::reverse_iterator lastElement = mapOfWeightAndCount.rbegin();
            if (firstElement->second > 1)
            {
                idealWeight = firstElement->first;
                actualWeight = lastElement->first;
            }
            else
            {
                actualWeight = firstElement->first;
                idealWeight = lastElement->first;
            }
            
            cout<<"current root is "<<d->name<<endl;
            cout<<"ideal weight "<<idealWeight<<endl;
            cout<<"actual weight "<<actualWeight<<endl;
            cout<<"weight difference is "<<(actualWeight - idealWeight) <<endl;
            
            // find disc with the anomolous weight
            string anomolousDiscName = mapOfWeightAndName[actualWeight];
            cout<<"Anomolous disc is "<<discsMap[anomolousDiscName]->name<<" weight "<<discsMap[anomolousDiscName]->weight<<endl;
            
            return idealWeight*d->disksAbove.size() + d->weight;
        }
        else
        {
            // balanced -> return sum of sizes of all disks above + current size
            // cout<<"BALANCED : current disc is "<<d->name<<endl;
            // cout<<"returning weight "<<(mapOfWeightAndCount.begin()->first)*d->disksAbove.size() + d->weight<<endl;
            return (mapOfWeightAndCount.begin()->first)*d->disksAbove.size() + d->weight;
        }
    }
    else
    {
        // cout<<"LEAF: current disc is "<<d->name<<endl;
        // cout<<"returning weight "<<d->weight<<endl;
        return d->weight;
    }
}

int main()
{
    int validPhrases = 0;
    string line;
    vector<Disc*> discs;
    map<string, Disc*> discsMap;
    
    set<string> children;
    
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            Disc* d = ToDisc(line);
            discs.push_back(d);
            discsMap[d->name] = d;
        }
        myfile.close();
    }
    
    // make a set of all disks which are children
    for (auto i : discs) {
        // cout << i->name <<endl;
        if (i->disksAbove.size() != 0)
        {
            for_each (i->disksAbove.begin(), i->disksAbove.end(), [&children](string s){children.insert(s);});
        }
    }

    Disc* root;
    // find the disc which is not in the set of children
    for (auto d : discs) {
        if (children.find(d->name) == children.end())
        {
            // cout << "root is "<<d->name <<endl;
            root = d;
        }
    }
    cout << "root is "<<root->name <<endl;

    
    // follow the root recursively to find out the disc which is unbalanced
    GetUnbalancedDiscWeight(root->name, discsMap);

    return 0;
}