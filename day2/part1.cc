#include <iostream>
#include <string>
#include <fstream>
#include <climits>
#include <cstddef>
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
    int checksum = 0;
    string line;
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            std::vector<string> words = split(line);

            int min = INT_MAX;
            int max = INT_MIN;
            
            for (auto word : words) {
                int currentNumber = stoi(word);
                
                if (currentNumber < min)
                    min = currentNumber;

                if (currentNumber > max)
                    max = currentNumber;
            }

            cout<<"Min is "<<min<<" Max is "<<max<<endl;
            checksum += (max - min);
        }
        myfile.close();
    }
    cout<<"checksum is "<<checksum<<endl;


    return 0;
}