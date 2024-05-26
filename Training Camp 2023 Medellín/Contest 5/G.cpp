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
    string s, t; cin>>s>>t;


    vector<int> parity(n);
    forn(i, n){
        parity[i] = (s[i] - '0')^(t[i] - '0');
    }

    int len = 0;
    int how_many = 0;
    for(int i = 0; i < n; ){
        if(parity[i] == 0){
            i++;
            continue;
        }

        int j = i;
        while(j < n && parity[j] == 1) j++;

        how_many++;
        len = j - i;

        i = j;
    }


    
    if(how_many == 0) {
        cout << 1LL * n * (n+1) / 2 << endl;
        return;
    } else if(how_many == 2) {
        cout << 2*3 << endl;
        return;
    } else if(how_many > 2) {
        cout << 0 << endl;
        return;
    } else {
        assert(how_many == 1);
        cout << 2*(n-1) << endl;
        return;
    }
}


int main () {
	// fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

