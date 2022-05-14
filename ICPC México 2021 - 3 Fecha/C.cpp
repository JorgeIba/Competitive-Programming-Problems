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


lli binPow(lli a, lli b, lli mod)
{
    lli res = 1;
    while(b)
    {
        if(b & 1) res = res * a % mod;
        b >>= 1;
        a = a*a % mod;
    }
    return res;
}

tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
        lli d, x, y;
        tie(d,x,y) =  extendedGcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

lli modularInverse(lli a, lli m){
    lli d, x, y;
    tie(d,x,y) = extendedGcd(a, m);
	if(d != 1) return -1; // inverse doesn't exist
	if(x < 0) x += m;
	return x;
}



int main () {
	//fastIO();
    lli b, l; cin>>b>>l;


    const int maxN = 1e6;
    vector<lli> pows(maxN+10, 1);

    lli m = b+1;

    for(int i = 1; i<=maxN; i++)
    {
        pows[i] = b*pows[i-1] % m;
    }


    vector<lli> D(l);
    for(auto &x: D) cin>>x;

    reverse(all(D));

    lli res = 0;

    for(int i = 0; i<l; i++)
    {
        res = (res + D[i]*pows[i]) % m;
    }

    if(res == 0)
    {
        cout << 0 << " " << 0 << endl;
        return 0;
    }

    lli idx_ans = -1, ans = -1, idx_ans_display = -1;

    for(int i = 0; i<l; i++)
    {
        lli m = b+1;
        lli x = res * modularInverse( pows[i] , m) % m;
        if( D[i] - x >= 0)
        {
            idx_ans_display = l - i, ans = x;
            idx_ans = i;
        }
    }


    if(idx_ans != -1)
    {
        cout << idx_ans_display << " " << D[idx_ans] - ans << endl;
    }
    else {
        cout << -1 << " " << -1 << endl;
    }
    

	


	return 0;
}

