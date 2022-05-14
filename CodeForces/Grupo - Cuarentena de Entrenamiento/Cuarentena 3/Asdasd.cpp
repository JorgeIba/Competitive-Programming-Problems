#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
    lli n; cin>>n;
    vector<lli> aux;
    for(lli i = 1; i*i <= n; i++)
    {
        if( n% i == 0)
        {
            aux.push_back(i);
            aux.push_back(n/i);
        }
    }

    for(auto x: aux)
    {
        if(x % 60 ==0) cout<<x<<" 9931\n";
        
    }

}