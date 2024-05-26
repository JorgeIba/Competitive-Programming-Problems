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



map< string, int > as = {
	{"tourist", 3858},
	{"ksun48", 3679},
	{"Benq", 3658},
	{"Um_nik", 3648},
	{"apiad", 3638},
	{"Stonefeang", 3630},
	{"ecnerwala", 3613},
	{"mnbvmar", 3555},
	{"newbiedmy", 3516},
	{"semiexp", 3481}
};

int main () {
	//fastIO();
	string s; cin>>s;

	cout << as[s] << endl;


	return 0;
}

