#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;

using namespace std;

int main () {
	//fastIO();
	
    string alph; cin>>alph;

    map<char,int> order;
    for(int i = 0; i < SZ(alph); i++) order[ alph[i] ] = i;

    int n; cin>>n;
    vector< string > ss(n);
    for(auto &s: ss) cin>>s;

    sort(all(ss), [&](const string &a, const string &b){
        for(int i = 0; i < min(SZ(a), SZ(b)); i++){
            if(a[i] != b[i]){
                return order[a[i]] < order[b[i]];
            }
        }

        return SZ(a) < SZ(b);
    });

    for(auto s: ss) cout << s << endl;
    

	return 0;
}

