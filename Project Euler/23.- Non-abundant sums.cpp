#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector<bool> abundants(28130);

bool isAbundant(lli n)
{
    vector<lli> divs;
    divs.push_back(1);
    for(lli i=2; i*i<=n; i++)
    {
        if( n%i == 0 )
        {
            divs.push_back(i);
            if(i*i != n)
            {
                
                divs.push_back(n/i);
            }
        }
    }
    lli sum = 0;
    for(auto x: divs)
    {
        sum += x;
    }
    if(n < sum) return true;
    return false;
}

vector<lli> ab;

bool checking(lli n)
{
    set<lli> check;
    for(int i = 0; i<ab.size(); i++ )
    {
        lli actual = ab[i];
        if(actual > n) return false;
        if( check.find(actual) != check.end()   or (actual*2 == n)) return true;
        check.insert( n-actual  );
    }
    return false;
}

int main()
{
    
    for(int i = 1; i<=28124; i++)
    {
        abundants[i] = isAbundant(i);
    }
    for(int i = 1; i<=29123; i++)
    {
        if(abundants[i]) ab.push_back(i);
    }

    vector<bool> checkSum(29123*2 + 10, 0);
    lli suma = 0;
    for(int i = 0; i<ab.size(); i++)
    {
        for(int j = 0; j <= i; j++ )
        {
            checkSum[ ab[i] + ab[j] ] = 1;
        }   
    }

    for(int i = 1; i<28124; i++)
    {
        if(!checkSum[i]) suma += i;
    }
    cout<<suma<<endl;

    

    return 0;
}