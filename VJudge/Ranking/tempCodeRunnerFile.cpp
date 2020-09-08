#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"

using namespace std;


void solve(lli n, lli limit)
{
    vector<lli> numeros(n);
    for(auto &x: numeros)
    {
        cin>>x;
    }

    lli res = n+1, suma = 0, l = 0, r = -1;
    while(r<n)
    {
        if(suma < limit)
        {
            r++;
            suma+=numeros[r];
        }
        else
        {
            lli size = r-l+1;
            res = min(res,size);
            suma -= numeros[l];
            l++;
        }
    }
    cout<<res<<endl;




}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli n, limit;
    while(cin>>n>>limit)
    {
        solve(n, limit);
    }

    return 0;
}