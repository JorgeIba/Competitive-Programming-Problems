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


const int MAXN = 100'000;
const int MAXG = 128;
vector<int> grundy(MAXN+1);

lli dp[MAXN+20][MAXG+10][4];

int n = MAXN;
lli f(int idx, int xors, int how_many) {
    if(idx == n+1 || how_many == 3) return how_many == 3 && xors == 0;

    lli &ans = dp[idx][xors][how_many];

    if(ans != -1) return ans;
    ans = 0;
    
    ans = (f(idx, xors ^ grundy[idx], how_many+1) + f(idx+1, xors, how_many));
    return ans;
}


int main () {
	//fastIO();

    memset(dp, -1, sizeof(dp));
    
    grundy[0] = 0;

    for(int i = 1; i <= MAXN; i++) {
        bitset< MAXG > nims;
        for(int j = 1; i - j*j >= 0; j++) {
            if(grundy[i-j*j] > i) continue;
            nims[ grundy[i-j*j] ] = 1;
        }

        int g = 0;
        while(nims[g]) g++;
        grundy[i] = g;
    }

    cout << f(0, 0, 0) << endl;

	return 0;
}

