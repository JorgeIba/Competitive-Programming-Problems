#include <bits/stdc++.h>
//Don't hack me plz :((
#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

vector< lli > fr;
vector<lli> check;
vector<char> ans;
vector<lli> b; 
lli n; 

char getLast()
{
    for(int i = 26; i>=0; i--)
    {
        if(fr[i] >  0)
        {
            return i + 'a';
        }
    }
}

void propagate(lli j)
{
    for(int i =  0; i<n; i++)
    {
        check[i] += abs(i-j);
    }
}

const lli INF = 1e18;

void solve()
{
    string s; cin>>s;
    cin>>n;
    fr.clear(); fr.resize(27);
    b.clear(); b.resize(n);
    ans.clear(); ans.resize(n, 'F');
    check.clear(); check.resize(n);

    for(auto &x: b)
    {
        cin>>x;
    }
    for(int i = 0; i<s.length(); i++)
    {
        fr[ s[i] -'a' ]++;
    }

    vector< lli > same;
    bool flag = true;
    
    while(flag)    
    {
        lli small = INF; same.clear();
        char letra;
        for(int i = 0; i<n; i++)
        {
            if(ans[i] == 'F')
            {
                small = min(small, b[i]);
            }
        }
        for(int i = 0; i<n; i++)
        {
            if(check[i] == b[i] && ans[i] == 'F')
            {
                same.push_back(i);
                letra = getLast();
            }
        }
        if(same.size() <= fr[letra-'a'])
        {
            for(auto x: same)
            {
                ans[x] = letra;
                propagate(x);
            }
        }
        fr[letra-'a'] = 0;
        flag = false;
        for(int i = 0; i<n; i++)
        {
            if(ans[i] == 'F')
            {
                flag = true;
                break;
            }
        }
    }

    for(auto x: ans)
    {
        cout<<x;
    }
    cout<<endl;
    


}



int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}