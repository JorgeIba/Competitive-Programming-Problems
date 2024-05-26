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


const int SIG = 26;

bool exist[SIG][SIG];
bool visited[SIG][SIG];

int main () {
	fastIO();


    int m, n; cin>>m>>n;

    forn(i, m) {
        char a, b; cin>>a>>b;
        exist[a - 'a'][b - 'a'] = true;
    }
    forn(i, SIG) {
        exist[i][i] = true;
    }


    auto dfs = [&](const auto &dfs, int start, int curr) -> void {
        if(visited[start][curr]) return;
        exist[start][curr] = true;
        visited[start][curr] = true;


        forn(i, SIG) {
            if(exist[curr][i]) {
                dfs(dfs, start, i);
            }
        }
        return;
    };

    forn(i, SIG) dfs(dfs, i, i);


    forn(i, n) {
        string a, b; cin>>a>>b;
        if(SZ(a) != SZ(b)) {
            cout << "no" << endl;
            continue;
        }

        bool no = false;
        for(int j = 0; j < SZ(a); j++) {
            if(exist[a[j] - 'a'][b[j] - 'a']) continue;
            else {
                no = true;
            }
        }

        if(no) {
            cout << "no" << endl;
        } else {
            cout << "yes" << endl;
        }

    }


    


	return 0;
}
