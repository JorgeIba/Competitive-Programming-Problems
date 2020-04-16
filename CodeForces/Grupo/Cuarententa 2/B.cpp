#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    lli n, k; cin>>n>>k;
    vector<lli> problems(n);
    for(auto &x: problems)
    {
        cin>>x;
    }
    sort(problems.begin(), problems.end());
    lli res = 0, l = 0, r = n-1;
    while(k>1 and l<=r)
    {
        res += (problems[r] - problems[l]);
        l++;
        r--;
        k--;
    }
    if(l<r)
    {
        map<lli,lli> frequency;
        for(int i = l; i<=r; i++)
        {
            frequency[ problems[i]   ] ++;
        }
        lli minimo = 10000000000LL, maximo = -1;
        for(auto x: frequency)
        {
            minimo = min(minimo, x.second);
            maximo = max(maximo, x.second);
        }
//        cout<<minimo<<" "<<maximo<<endl;
        lli numMinimo = -1, numMaximo = -1;
        for(auto x: frequency)
        {
            if(x.second == minimo)
            {
                numMinimo = x.first;
                break;
            }
        }
        for(auto x: frequency)
        {
            if(x.second == maximo)
            {
                numMaximo = x.first;
            }
        }
        res += (numMaximo - numMinimo);
    }
    cout<<res<<endl;
    

    return 0;
}
