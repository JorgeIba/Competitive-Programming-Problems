#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;




set<char> vowels = {
    'A', 'E', 'I', 'O', 'U', 'Y'
};


int main () {
	// fastIO();

    int n; cin>>n;

    vector<string> words(n);
    for(auto &w: words) {
        string s; cin>>s;
        for(int i = 0; i < min(3, SZ(s)); i++) {
            w.push_back(s[i]);
        }
    }

    auto is_vowel = [&](char c) {
        return vowels.count(c);
    };


    vector< array<int, 3> > dp(n, {-1, -1, -1});

    const int INF = 1e9;
    auto f = [&](const auto &f, int idx, int many) {
        if(many >= 3) return INF;
        if(idx == n) return 0;

        int &ans = dp[idx][many];
        if(ans != -1) return ans;

        ans = INF;
        int cons = many;
        for(int i = 0; i < SZ(words[idx]); i++) {
            auto c = words[idx][i];
            if(is_vowel(c)) {
                cons = 0;
            } else {
                cons++;
            }

            if(cons == 3) break;

            
            ans = min(ans, f(f, idx+1, cons) + (i+1));
        }

        return ans;
    };

    auto ans = f(f, 0, 0);
    if(ans >= INF) {
        cout << "*" << endl;
    } else {
        cout << ans << endl;
    }







	return 0;
}

