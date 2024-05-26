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

string s;
int n;

const int MAXN = 100 + 10, SIGMA = 29;
int dp[MAXN][SIGMA][SIGMA];

int f(int idx, int me, int rev){

    char c_me =  (me  == -1 ? s[idx] : me + 'a');
    char c_rev = (rev == -1 ? s[n - idx - 1] : rev + 'a');

    if(idx == n/2 - 1) return c_me != c_rev;

    int &ans = dp[idx][me+1][rev+1];
    if(ans != -1) return ans;

    ans = 1e9;
    
    // let idx
    if(c_me == c_rev) 
        return ans = f(idx+1, -1, -1);   


    // move idx e idx+1
    char c_next = s[idx+1];
    for(char c = 'a'; c <= 'z'; c++){
        if(c == c_next) continue;

        ans = min(ans, 1 + f(idx+1, c - 'a', -1));
    }

    // move n-idx-1 y n - (idx+1)-1
    char c_next_rev = s[n - (idx+1) - 1];
    for(char c = 'a'; c <= 'z'; c++){
        if(c == c_next_rev) continue;

        ans = min(ans, 1 + f(idx+1, -1, c - 'a'));
    }

    // both
    for(char c_1 = 'a'; c_1 <= 'z'; c_1++){
        for(char c_2 = 'a'; c_2 <= 'z'; c_2++){
            if(c_1 == c_next || c_2 == c_next_rev) continue;

            ans = min(ans, 2 + f(idx+1, c_1 - 'a', c_2 - 'a'));
        }
    }

    return ans;
}


int main () {
	fastIO();

    memset(dp, -1, sizeof(dp));

	cin>>s;

    n = SZ(s);

    cout << f(0, -1, -1) << endl;

	return 0;
}

