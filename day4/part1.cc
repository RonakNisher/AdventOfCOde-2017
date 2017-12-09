#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>


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
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            std::vector<string> words = split(line);

            set<string> passPhraseWords;
            bool isValid = true;
            
            for (auto word : words) 
            {
                if (!passPhraseWords.insert(word).second)
                {
                    isValid = false;
                    break;
                }
            }
            if (isValid)
                validPhrases++;
        }
        myfile.close();
    }
    cout<<"validPhrases "<<validPhrases<<endl;

    return 0;
}