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

const int MOD = 998244353;

const int MAXN = 2e5 + 1000;
lli fact[MAXN];

void main_(){
    string s; cin>>s;


    auto get_ans = [](string s) -> pair<int,lli> {
        int n = SZ(s);
        vector< pair<char, int> > ss;
        for(int i = 0; i < n;){
            char c = s[i];
            int j = i;
            while(j < n && s[j] == c) j++;

            ss.push_back({c, j-i});
            i = j;
        }

        int min_cant = n - SZ(ss);
        lli ways = 1;
        for(auto [c, w]: ss){
            ways = ways * w % MOD;
        }
        ways = ways * fact[min_cant] % MOD;
        return {min_cant, ways};
    };

    auto [cant_1, ways_1] = get_ans(s);
    cout << cant_1 << " " << ways_1 << endl;
}


int main () {
	fastIO();

    fact[0] = fact[1] = 1;
    for(lli i = 2; i < MAXN; i++){
        fact[i] = i * fact[i-1] % MOD;
    }
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

