
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


tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		lli d, x, y;
	    tie(d,x,y) = extendedGcd(b, a%b);
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
	fastIO();
    lli m; cin>>m;

    if(__gcd(9LL, m) != 1)
    {
        cout << -1 << endl;
        return 0;
    }
    if(m == 1)
    {
        cout << 1 << endl;
        return 0;
    }


    lli x = modularInverse(9, m);

    lli izq = (-9*x % m + m)%m;

    //lli s = (9*x%m - 1 + m) % m;
    

    vector<lli> ans;
    for(int i = 0; i<x; i++) ans.push_back(9);

    bool breaked = false;

    while(izq > 0)
    {
        lli put;

        if(breaked)
        {
            if(izq >= 9)
            {
                put = 9;
                izq -= 9;
            }
            else
            {
                put = izq;
                izq = 0;
            }
        }
        else
        {
            put = min(8LL, izq);
            izq -= put;
            breaked = true;
        }
        
        ans.push_back(put);
    }

    reverse(all(ans));

    for(auto x: ans) cout << x;
    cout << endl;


	


	return 0;
}

