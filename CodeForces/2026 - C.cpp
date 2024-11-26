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

void main_() {
    int n; cin>>n;
    string s; cin>>s;

    lli ans = 1LL * n * (n+1) / 2;
    vector<bool> visited(n);
    vector< deque<int> > pos(2);

    forn(i, n) {
        pos[s[i] - '0'].push_back(i);
    }


    for(int i = n-1; i >= 0; i--) {
        if(visited[i]) continue;
        

        assert(pos[s[i] - '0'].back() == i);

        if(s[i] == '0') {
            pos[0].pop_back();
        } else {
            if(!pos[0].empty()) {
                auto idx_zero = pos[0].back(); pos[0].pop_back();
                pos[1].pop_back();
                assert(idx_zero < i);

                ans -= i+1;
                visited[idx_zero] = true;
                visited[i] = true;
            } else if(SZ(pos[1]) > 1) {
                auto idx_one = pos[1].front(); pos[1].pop_front();
                pos[1].pop_back();

                ans -= i+1;
                visited[idx_one] = true;
                visited[i] = true;
            }
        }
    }

    cout << ans << endl;
}

int main () {
	fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

