#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;


vector<lli> fib(34);
vector<lli> nim(3000005);

/*
lli MEX(set<lli> check)
{
    for(int i = 0; ; i++)
    {
        if(check.find(i) == check.end())
        {
            return i;
        }
    }
}
*/


void prec()
{
    fib[0] = fib[1] = 1;
    for(int i = 2; i<=33; i++)
    {
        fib[i] = fib[i-1] + fib[i-2];
    }
    nim[0] = 0;
    for(int i = 1; i<=3000000; i++)
    {
        vector<bool> grundy(20);
        lli j = 1;
        while( ( i - fib[j]) >= 0 )
        {
            grundy[ nim[ i - fib[j]  ] ] = true;
            j++;
        }
        lli k = 0;
        while(grundy[k]) k++;
        nim[i] = k;
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    prec();  // 32
    lli n; cin>>n;
    lli res = 0;
    for(int i = 0; i<n; i++)
    {
        lli x; cin>>x;
        res ^= nim[x];
        //cout<<nim[x]<<" ";
    }
    if(res == 0)
    {
        cout<<"Vinit\n";
    } 
    else
    {
        cout<<"Ada\n";  
    } 
    
    
    return 0;
}