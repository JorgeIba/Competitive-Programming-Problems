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


int main () {
	fastIO();

    vector< string > keyboard = {
        "QWERTYUIOP",
        "ASDFGHJKL",
        "ZXCVBNM"
    };

    vector< string > input_keyboard(3);
    forn(i, 3) cin>>input_keyboard[i];


    bitset< 27 > valid;
    forn(i, 3) {
        forn(j, SZ(keyboard[i])) {
            if(input_keyboard[i][j] == '*') {
                auto c = keyboard[i][j];
                valid[c - 'A'] = 1;
            }
        }
    }

    int q; cin>>q;

    while(q--){
        string s; cin>>s;
        bitset<27> mask;
        for(auto c: s) {
            mask[c - 'A'] = 1;
        }

        cout << (valid == mask ? "POSSIBLE" : "IMPOSSIBLE") << endl;
    }




	return 0;
}

