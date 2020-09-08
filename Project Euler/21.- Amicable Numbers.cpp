#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli desc(lli n)
{
    lli sum = 0;
    for(lli i = 2; i*i <= n; i++)
    {
        if(n%i == 0)
        {
            if( i*i != n)
            {
                sum += (n/i) + i;
            }
            else
            {
                sum += i;
            }
        }
    }

    return sum+1;
}

int main()
{  
    vector< pair< bool  ,lli> > sums(10000);

    for(int i = 1; i< 10000; i++)
    {
        sums[i] = {true, desc(i)};
    }
    lli res = 0;
    for(int i = 1; i<10000; i++)
    {
        lli a = sums[i].second;
        if(a < 10000 )
        {
            lli b = sums[a].second;    
            if((i == b)and(i != a))
            {
                if(sums[i].first and sums[a].first)
                {
                    cout<<i<<" "<<a<<endl;
                    res += i+a;
                }
                sums[i].first = false;
                sums[a].first = false;
            }            
        }
        else
        {
            continue;
        }
    }
    cout<<res<<endl;


    
    return 0;
}