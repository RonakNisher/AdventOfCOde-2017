#include <iostream>
#include <string>
#include <fstream>
#include <climits>
#include <vector>
#include <algorithm>


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

int toInt(string input)
{
    return stoi(input);
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
            
            std::vector<int> numbers;
            numbers.resize(words.size());
            transform(words.begin(), words.end(), numbers.begin(), toInt);

            int min = INT_MAX;
            int max = INT_MIN;
            
            bool found = false;
            for (auto i : numbers) {
                {
                    for (auto j : numbers) {
                        if (((i % j) == 0 || (j % i) == 0) && i != j)
                        {
                            cout<<i<<" "<<j<<endl;
                            checksum += (i > j) ? i/j : j/i;
                            found = true;
                            break;
                        }
                    }
                    
                    if (found)
                        break;
                }
            }
            cout<<endl;
            
            // for (auto word : words) {
            //     int currentNumber = stoi(word);
                
            //     if (currentNumber < min)
            //         min = currentNumber;

            //     if (currentNumber > max)
            //         max = currentNumber;
            // }

            // cout<<"Min is "<<min<<" Max is "<<max<<endl;
            // checksum += (max - min);
        }
        myfile.close();
    }
    cout<<"checksum is "<<checksum<<endl;


    return 0;
}