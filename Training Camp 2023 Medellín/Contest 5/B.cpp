#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

const int MAXN = 1e5+1;

lli frq[MAXN + 100];
lli dp[MAXN + 100];


lli f(int idx){
    if(idx >= MAXN) return 0;

    lli &ans = dp[idx];
    if(ans != -1) return ans;

    lli yes = f(idx+2) +  frq[idx] * idx;
    lli no  = f(idx+1);

    return ans = max(yes, no);
}


int main () {
	//fastIO();
	
	int n; cin>>n;
    forn(i, n) {
        int x; cin>>x;
        frq[x]++;
    }    

    memset(dp, -1, sizeof(dp));
    cout << f(1) << endl;


	return 0;
}

