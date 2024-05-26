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

void main_(){
    int n, k, m; cin>>n>>k>>m;
    string s; cin>>s;

    /*
    auto check = [&](const string &check) {
        int j = 0;
        for(int i = 0; i < m; i++) {
            if(j < n) {
                if(s[i] == check[j])
                    j++;
            }
        }

        return j == n;
    };

    for(int i = 0; i < k; i++) {
        string to_check(n, i + 'a');
        if(!check(to_check)) {
            cout << "NO" << endl;
            cout << to_check << endl;
            return;
        }
    }
    */

    vector< vector<int> > pos(26);
    forn(i, m)  {
        pos[s[i] - 'a'].push_back(i);
    }
    forn(i, k) {
        pos[i].push_back(1000+10);
    }


    int idx_n = 0, idx_m = 0;
    string ans;
    while(idx_n < n) {
        int greatest = -1;
        int char_gr = 0;
        for(int i = 0; i < k; i++) {
            auto itr = lower_bound(all(pos[i]), idx_m);
            if(itr == pos[i].end()) continue;
            if(*itr > greatest) {
                greatest = *itr;
                char_gr = i;
            }
        }

        if(greatest > 1000) {
            string last;
            for(int i = idx_n; i < n; i++) {
                last.push_back(char_gr + 'a');
            }
            cout << "NO" << endl;
            cout << ans + last << endl;
            return;
        }

        idx_n++;
        ans.push_back(char_gr + 'a');
        idx_m = greatest+1;
    }


    cout << "YES" << endl;

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

