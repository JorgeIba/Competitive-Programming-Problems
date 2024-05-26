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
	queue<int> q;
	
	for (int i = 0; i < 26; i++)
		if (nex[0][i])
			q.push(nex[0][i]);

	while (q.size()) {
		int u = q.front();
		q.pop();

		for (int i = 0; i < SIG; i++) {
			int v = nex[u][i];

			if (v) {
				fail[v] = getFail(fail[u], i);
				cnt[v] += cnt[fail[v]];
				q.push(v);

				// <comentar> Si no necesitan las posiciones exactas de cada patron en el texto
				// Complejidad de esta parte O(sqrt(n))
				out[v] = fail[v];
				if (finish[out[v]] == -1)
					out[v] = fail[out[v]];
				// </comentar>
			}
		}
	}
}

// Regresa la cantidad total de ocurrencia
int match (string &t) {
	int u = 0, res = 0;

	for (int i = 0; i < t.size(); i++) {
		char c = t[i] - 'a';
		
		if (nex[u][c])
			u = nex[u][c];
		else
			u = getFail(fail[u], c);
		res += cnt[u];

		// <comentar> Si no necesitan las ocurrencias exactas de cada patron en el texto
		// Complejidad de esta parte O(n*sqrt(n))
		int v = u;
		while (v && cnt[v]) {
			if (finish[v] != -1) {
				// <comentar> Si no necesitan las posiciones exactas de cada patron en el texto
				// Dejar esta parte cuando no es necesario puede dar TLE por el costo de hacer push_back en un vector
				// ocu[finish[v]].push_back(i);
				// </comentar>
				cnt_ocu[finish[v]]++;
			}
			v = out[v];
		}
		// </comentar>
	}

	return res;
}


int main () {
	//fastIO();
	
    string s; cin>>s;

    

    int n; cin>>n;

    map< string, int > to_unique;
    vector< string > all_ss;
    forn(i, n) {
        string t; cin>>t;
        if(!to_unique.count(t)) {
            to_unique[t] = i;
            insert(t, i);
        }
        all_ss.push_back(t);
    }

    build();

    match(s);

    
    for(int i = 0; i < n; i++) {
        string t = all_ss[i];
        auto x = cnt_ocu[ to_unique[ t ] ];
        cout << (x ? "YES" : "NO") << endl;
    }



	return 0;
}

