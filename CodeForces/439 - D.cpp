#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


vector<lli> a, b;
lli n, m;

lli f(lli k)
{
    lli sum = 0;
    for(auto x: a)
    {
        if(x < k) sum += abs(k-x);
    }

    for(auto x: b)
    {
        if(x > k) sum += abs(k-x);
    }
    return sum;
}





int main () {
	//fastIO();
    cin>>n>>m;

    a.resize(n);
    b.resize(m);

    for(auto &x: a) cin>>x;
    for(auto &x: b) cin>>x;



    lli l = 1, r = 1e9;

    while((r-l) >= 3)
    {
        lli tercio1 = l + (r-l)/3;
        lli tercio2 = r - (r-l)/3;


        if(f(tercio1) < f(tercio2)) r = tercio2;
        else l = tercio1;
    }


    lli ans = 1e18;
    for(lli k = l; k <= r; k++) // 3
    {
        ans = min(ans, f(k));
    }

    cout << ans << endl;



    

	


	return 0;
}

