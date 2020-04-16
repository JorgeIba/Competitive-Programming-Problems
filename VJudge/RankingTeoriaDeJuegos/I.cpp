#include <bits/stdc++.h>
#define lli long long int

using namespace std;
/*
int MEX(set<int> check)
{
    for(int i = 0; ; i++)
    {
        if(check.find(i) == check.end()) return i;
    }
}
*/

void solve()
{
    lli n, k; cin>>n>>k;
    vector<lli> rules(k);
    vector<int> nim(100005);
    for(auto &x: rules)
    {
        cin>>x;
    }
    sort(rules.begin(), rules.end());
    nim[0] = 0;
    for(int i = 1; i<100001; i++)
    {
        vector<bool> check(k+10, false);
        int j = 0;
        //set<int> check;
        while( (j<k) and ( (i - rules[j]) >= 0 ))
        {
            //check.insert( nim[ i-rules[j] ] );
            check[ nim[i - rules[j]]  ] = true;
            j++;
        }
        lli q = 0;
        while(check[q]) q++;
        nim[i] = q;
    }

    lli res= 0;
    for(int i = 0; i < n; i++)
    {
        lli x; cin>>x;
        res ^= nim[x];
    }
    if(!res) cout<<"Vinit\n";
    else cout<<"Ada\n";
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}