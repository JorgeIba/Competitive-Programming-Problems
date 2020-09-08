#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

lli nums[101];
lli n; 

lli getLIS(lli l, lli r) {
  vector<lli> u;
  for(int i = l; i<=r; i++)
  {
    lli x = nums[i];
    auto it = lower_bound(u.begin(), u.end(), x);
    if (it == u.end()) {
      u.push_back(x);
    } else {
      *it = x;
    }
  }
  return (int) u.size();
}

lli LIS[103][103];

lli fun(lli k)
{
    vector< lli > dp(n+2, 0);
    for(int L = n; L>=1; L--)
    {
        for(int R = L; R<=n; R++)
        {
            lli lis = LIS[L][R];
            if(lis >= k)
            {
                dp[L] = max(dp[L], lis + dp[R+1]);
            }
            else
            {
                dp[L] = max(dp[L], dp[R+1]);
            }
        }
    }
    return dp[1];
}


void solve()
{
    cin>>n;
    for(int i = 1; i<=n; i++) cin>>nums[i];

    for(int L = n; L>=1; L--)
    {
        for(int R = L; R<=n; R++)
        {
            LIS[L][R] = getLIS(L,R);
        }
    }


    for(int k = 1; k<=n; k++)
    {
        if(k == n) cout << fun(k);
        else cout << fun(k) << " ";
    }
    cout << endl;
}



int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}