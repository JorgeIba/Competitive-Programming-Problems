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


string s, t;
lli n, m;
const lli INF = 1e18;
const lli maxS = 1e5+10;

lli dp[maxS][100+10];

lli f(lli ids, lli idt) {
    if(ids >= n) {
        if(idt == m) return ids-1;
        else return INF;
    };

    if(idt == m) return ids-1;

    lli &ans = dp[ids][idt];

    if(ans != -1) return ans;

    ans = INF;
    if(s[ids] == t[idt]) {
        return ans = min(f(ids+1, idt+1), f(ids+1, idt));
    } else {
        return ans = f(ids+1, idt);
    }
}



int main () {
	//fastIO();
    memset(dp, -1, sizeof(dp));
    cin>>s>>t;

    n = s.length(), m = t.length();

    lli ans = 0;
    lli last = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == t[0]) {
            lli shortest = f(i+1, 1);
            if(shortest == INF) continue;
            lli to_right = n - shortest;
            // lli to_left = (i-last + 1);
            ans += to_right * (i - last + 1);
            // cout << "desde " << i << " -> " << shortest << " me sobran " << to_right << " pero a la izq solo puedo desde " << last << "  por lo tanto puedo poner " << to_left << endl ;
            last = i + 1;
            
        }
    }
    cout << ans << endl;

    

	return 0;
}

