#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int main()
{
    fastIO();
    lli n; cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    stack< pair<lli,lli> > pila;
    vector< pair<lli,lli> > ans(n);
    for(int i = 0; i<n; i++)
    {
        lli num = nums[i];
        while(!pila.empty() && nums[i] >= pila.top().first)
        {
            pila.pop();
        }
        if(pila.empty()) ans[i].first = -1;
        else  ans[i].first = pila.top().second;

        pila.push({num,i});
    }

    stack< pair<lli,lli> > pilaReverseadaALV;
    for(int i = n-1; i>=0; i--)
    {
        lli num = nums[i];
        while(!pilaReverseadaALV.empty() && nums[i] >= pilaReverseadaALV.top().first)
        {
            pilaReverseadaALV.pop();
        }
        if(pilaReverseadaALV.empty()) ans[i].second = n;
        else  ans[i].second = pilaReverseadaALV.top().second;

        pilaReverseadaALV.push({num,i});
    }
    
    for(auto x: ans)
    {
        //cout<<x.first<<" "<<x.second<<endl;
        cout<< (x.second - 1 - (x.first + 1) + 1 ) << " ";
    }
    cout<<endl;
    return 0;
}