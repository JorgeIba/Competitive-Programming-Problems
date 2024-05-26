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


const int MX = 500005, SIG = 26;

int nex[MX][SIG], fail[MX], out[MX], finish[MX], cnt[MX], sz = 1;
vector<int> ocu[MX]; // Almacena las ocurrencias de cada cadena en el texto
int cnt_ocu[MX]; // Cuenta las ocurrencias de cada cadena en el texto

void insert (string &s, int ind) {
	int u = 0;

	for (char c : s) {
		c -= 'a';

		if (!nex[u][c]) {
			nex[u][c] = sz;
			finish[sz] = -1;
			sz++;
		}

		u = nex[u][c];
	}

	finish[u] = ind;
	cnt[u]++;
}

int getFail (int u, int c) {
	while (u && !nex[u][c])
		u = fail[u];
	return nex[u][c];
}

void build () {
	finish[0] = -1;
	queue<int> q;

	for (int i = 0; i < 26; i++)
		if (nex[0][i])
			q.push(nex[0][i]);

	while (q.size()) {
		int u = q.front();
		q.pop();

		for (int i = 0; i < SIG; i++) {
			int v = nex[u][i];

			if (v && u) {
				fail[v] = getFail(fail[u], i);
				cnt[v] += cnt[fail[v]];
				q.push(v);

				// <comentar> Si no necesitan las posiciones exactas de cada patron en el texto
				// Complejidad de esta parte O(sqrt(n))
				out[v] = fail[v];
				if (finish[out[v]] == -1)
					out[v] = out[fail[v]];
				// </comentar>
			}
		}
	}
}


string secret, s, t; 

const int MAXN = 1000 + 100;
const int MAXU = 200;
const int INF = 1e9;

bool visited[MAXN][MAXU];
int dp[MAXN][MAXU];


int g(int u){
    vector<int> cnt_ocu(2);

    int v = u;
    while (v && cnt[v]) {
        if (finish[v] != -1) {
            cnt_ocu[finish[v]]++;
        }
        v = out[v];
    }
    return cnt_ocu[0] - cnt_ocu[1];
}


int f(int idx, int u){
    if(idx == SZ(secret)) return g(u);


    int &ans = dp[idx][u];
    if(visited[idx][u]) return ans;

    visited[idx][u] = true;
    

    ans = -INF;

    auto c = secret[idx];

    char first = (c != '*' ? c : 'a');
    char last  = (c != '*' ? c : 'z');

    for(char it = first; it <= last; it++){
        int cc = it - 'a';
        int val = f(idx+1, (nex[u][cc] ? nex[u][cc] : getFail(fail[u], cc))) + g(u);
        ans = max(ans, val);
    }

    return ans;
}


int main () {
	//fastIO();

    cin>>secret>>s>>t;


    insert(s, 0);
    insert(t, 1);

    build();

    cout << f(0, 0) << endl;

	return 0;
}

