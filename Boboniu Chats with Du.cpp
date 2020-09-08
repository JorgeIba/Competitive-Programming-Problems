#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

/*
vector< lli > nums, ans, no;
lli n, d, m; 
lli dp[100010];

lli fun(lli idx)
{
    if(idx >= n) return 0;
    lli funFact = ans[idx];
    lli &res = dp[idx];
    if(res != -1) return res;
    if(funFact > m)
    {
        lli si = fun(idx + d + 1) + funFact;
        lli no = fun(idx + 1);
        return res = max(si,no);
    }
    else
    {
        return res = fun(idx + 1) + funFact;
    }
}
*/


int main () {
	fastIO();
    lli n, d, m; cin>>n>>d>>m;
    //nums.resize(n);
    //memset(dp, -1 , sizeof(dp));
    vector< lli > s, b;
    for(int i = 0; i<n; i++)
    {
        lli x; cin>>x;
        if(x > m) b.push_back(x);
        else s.push_back(x);
    }
    sort(all(s), greater<lli>());
    sort(all(b), greater<lli>());

    vector< lli > sl = s, sb = b;
    for(int i = 1; i<SZ(s); i++) sl[i] += sl[i-1];
    for(int i = 1; i<SZ(b); i++) sb[i] += sb[i-1];

    if(SZ(b) == 0)
    {
        cout << sl[n-1] << endl;
        return 0;
    }
    lli ans = -1;
    for(int i = 0; i<=SZ(b); i++)
    {
        lli seVan = d*(i-1);
        if(seVan < 0) seVan = 0;
        lli quedan = SZ(b) - i;
        lli quitar = max(0LL, seVan - quedan);
        if(quitar > SZ(s)) continue;
        lli vanIr = SZ(s) - quitar;
        ans = max(ans, (i?sb[i-1]:0)  + (vanIr?sl[vanIr-1]:0));
    }
    cout << ans << endl;

	return 0;
}