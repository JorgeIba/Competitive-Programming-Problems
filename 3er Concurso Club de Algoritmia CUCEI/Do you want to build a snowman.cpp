#include <bits/stdc++.h>

#define lli long long int
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli dp[10][10];
lli n;

set< set<lli> > ans;

void funcion(lli idx, lli freedom, set<lli> s)
{
    //if(s.size() > 3) return;
    if(idx==n)
    {
        if(s.size() == 3)
        {
            ans.insert(s);
        }
        return;
    } 
    funcion(idx+1, freedom + 1, s); //no
    for(int i = 0; i<=freedom; i++)
    {
        set<lli> aux = s;
        aux.insert( dp[freedom][idx] );
        //cout<<idx<<" "<<freedom<<endl;
        funcion(idx+1, 0, aux);
        aux.clear();
    }
}




int main()
{
    fastIO();
    memset(dp,0,sizeof(dp));
    cin>>n;
    vector<lli> nums(n);
    for(auto &x: nums)
    {
        cin>>x;
    }
    for(int i = 0; i<n; i++)
    {
        dp[0][i] = nums[i];
    }

    for(int i = 1; i<n; i++)
    {
        for(int j = i; j<n; j++)
        {
            dp[i][j] = dp[i-1][j-1] + dp[0][j];
        }
    }

    set<lli> np;
    funcion(0,0,np);

    lli contlines = ans.size()-1;
    for(auto x: ans)
    {
        lli sizee = x.size()-1;
        for(auto y: x)
        {
            cout<<y;
            if(sizee)
            {
                cout<<" ";
                sizee--;
            }
        }
        if(contlines)
        {
            cout<<endl;
            contlines--;
        }
    }
    return 0;
}