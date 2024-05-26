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
    int n, k; cin>>n>>k;


    set<int> available, others;
    for(int i = 0; i <= k; i++) {
        available.insert(n - i - 1);
    }
    for(int i = k+1; i < n; i++) 
        others.insert(n - i - 1);

    vector<int> ans;
    for(auto x: available) ans.push_back(x);
    vector<int> aux(all(others));

    reverse(all(aux));
    ans.insert(ans.end(), aux.begin(), aux.end());

    for(auto x: ans) cout << x+1 << " ";
    cout << endl;



}

int main () {
	// fastIO();

	int t = 1; 
	cin>>t;

	while(t--) {
		main_();
	}

	return 0;
}

