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

    int n; cin>>n;

    vector<lli> piles(n);
    for(auto &x: piles) cin>>x;

    lli xorr = 0;
    for(auto x: piles) xorr ^= (x & 1);

    if(n & 1){
        cout << (xorr ? "Yalalov" : "Shin") << endl;
        return;
    }

    lli mini = *min_element(all(piles));

    if(xorr == 0 && mini % 2 == 0) xorr = 1;
    else if(xorr == 1 && mini % 2 == 0) xorr = 0;

    cout << (xorr ? "Yalalov" : "Shin") << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

