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
	
    lli n; cin>>n;
    string s; cin>>s;

    auto get_ans = [&](char border, char inside) {
        lli ans = 0;
        for(lli L = 3; L*L <= n; L++) {
            deque<char> window;
            lli ans_L = 0;

            int q_border = 0;
            int q_fill = 0;
            for(int i = 0; i < n; i++) {
                char next = s[i];

                q_border += (next == border);
                q_fill   += (next == inside);
                window.push_back(next);

                while(SZ(window) > L*L) {
                    auto to_remove = window.front();
                    window.pop_front();

                    q_border -= (to_remove == border);
                    q_fill   -= (to_remove == inside);
                }

                if(SZ(window) == L*L) {
                    if(q_border == (4*(L-1)) && q_fill == ((L-2)*(L-2))) {
                        ans_L++;
                    }
                }
            }

            ans += ans_L;
        }

        return ans;
    };


    lli ans = get_ans('X', 'O') + get_ans('O', 'X');
    cout << ans << endl;


	return 0;
}

