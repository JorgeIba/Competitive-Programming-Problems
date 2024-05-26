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


void main_(){
	int n, k; cin>>n>>k;

    vector<int> fr(n+1);

    for(int i = 0; i <= n; i++){
        fr[i] = i * (i-1) / 2;
    }

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            if(i + j == n && fr[i] + fr[j] == k){
                vector<int> s; forn(k, i) s.push_back(1);
                forn(k, j) s.push_back(-1);

                cout << "YES" << endl;
                for(auto x: s) cout << x << " ";
                cout << endl;
                return;
            }
        }
    }

    cout << "NO" << endl;

}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

