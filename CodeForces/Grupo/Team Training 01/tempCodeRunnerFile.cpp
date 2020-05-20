#include <bits/stdc++.h>

#define lli unsigned long long int
#define endl "\n"
#define debug(n) cout<<n<<endl
#define debug2(a, b) cout<<a<<" "<<b<<endl;
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

void calculate(vector<lli> s, lli p)
{
    lli n = s.size();
    map<lli,lli> mp;
    mp[0] = 1;
    lli pot = 1, before = 0, answer = 0;
    for(int i = 0; i<n; i++)
    {
        lli digit = s[i]%p;
        lli newNum = (before*10 + digit)%p;
        answer += mp[newNum];
        mp[newNum]++;
        before = newNum;
    }
    cout<<answer<<endl;
}


void solve()
{
    lli a, b, n, p; cin>>a>>b>>n>>p;
    lli aux = a;
    vector<lli> s;
    lli index = 0;
    while(n--)
    {
        aux*=10;
        lli fl = aux/b;
        s.push_back(fl);
        aux -= b*fl;
    }
   
    calculate(s, p);
}

int main()
{
    //fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}