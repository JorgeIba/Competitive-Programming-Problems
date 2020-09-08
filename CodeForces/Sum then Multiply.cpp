#include <bits/stdc++.h>

#define lli long long int
#define ld __float128
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

const lli MAXN = 4e5;

lli nums[MAXN], sums[MAXN];
ld dp[MAXN];
lli where[MAXN];


lli suma(lli r, lli l)
{
    return sums[l] - (r-1>=0? sums[r-1]: 0);
}

int main()
{
    fastIO();
    lli n; cin>>n;
    for(int i = 0; i<n; i++)
    {
        cin>>nums[i];
    }
    for(int i = 0; i<n; i++)
    {
        sums[i] = nums[i] +  (i-1>=0? sums[i-1] : 0);
        dp[i] = log(nums[i]);
    }

    for(lli i = n-1; i>=0; i--)
    {
        for(lli j = i; j<=min(n-1, i+5); j++)
        {
            ld p = log(suma(i,j))  +  ((j!=n-1)? dp[j+1]: 0) ; //log(1) = 0
            if( p > dp[i])
            {
                dp[i] = p;
                where[i] = j;
            }
        }
    }
    lli last = where[0];
    for(int i = 0; i<n; i++)
    {
        cout<<nums[i]<<" ";
        if(i == last && i != n-1)
        {
            cout<<"/ ";
            last = where[i+1];
        }
    }
    cout<<endl;

    return 0;
}