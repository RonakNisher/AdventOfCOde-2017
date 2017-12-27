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
#include <cctype>

using namespace std;

int cnt;

int main()
{

    long b, c , d, e, f, g, h = 0;
    long a  = 1;
    cout<<b<<endl;
    
    // part 1
    
    b = 79;
    c = b;
    
    if (a != 0)
    {
        b = b*100 + 100000;
        c = b + 17000;
    }
    
    cout<<"b = "<<b<<", c = "<<c<<endl;


    while(true)
    {
        f = 1;
        d = 2;
        
        // cout<<b<<endl;
    
        while(g != 0)
        {
            e = 2;
            // while (g != 0)
            // {
            //     g = d * e - b;
            //     if (g == 0)
            //         f = 0;
            //     e++;
            //     g = e - b;
            // }
            // gets substituted to below expr
            if (b % d == 0)
                f = 0;
            
            d++;
            g = d - b;
        }
        
        if (f == 0)
            h++;
        
        g = b - c;
        
        if (g == 0)
        {
            break;
        }
        b = b + 17;
    }
    
    cout<<b<<endl;
    cout<<"h is "<<h<<endl;
    
    return 0;
}