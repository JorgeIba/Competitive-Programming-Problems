#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector< vector< vector<lli> > > adj;
vector< vector<lli> > grundy;

lli MEX(set<lli> nums)
{
    for(int i = 0; ; i++)
    {
        if(nums.find(i) == nums.end()) return i;
    }
}


int main()
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    lli n, t; cin>>n>>t;
    adj.resize(n);
    grundy.resize(n);
    for(int i = 0; i<n; i++)
    {
        lli b, r; cin>>b>>r;
        vector< lli > aux(b, 0);
        grundy[i] = aux;
        vector< vector<lli> > adje(b);
        for(int j = 0; j<r; j++)
        {
            lli x, y; cin>>x>>y;
            x--, y--;
            if(x>y) swap(x,y);
            adje[y].push_back(x);
        }
        adj[i] = adje;
    }

    for(int i = 0; i<n; i++)
    {
        for(int j = 1; j< grundy[i].size(); j++)
        {
            set<lli> check;
            for(int q = 0; q<adj[i][j].size(); q++)
            {
                check.insert( grundy[i][adj[i][j][q]]  );
            }
            grundy[i][j] = MEX(check);
        }
    }

    
    for(int i = 0; i<t; i++)
    {
        lli res = 0;
        for(int j = 0; j<n; j++)
        {
            lli x; cin>>x; x--;
            res ^= grundy[j][x];
        }
        if(res!=0) cout<<"Alice\n";
        else cout<<"Bob\n";
    }
    
    
    return 0;
}