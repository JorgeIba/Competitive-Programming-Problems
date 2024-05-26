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


bool are_equal(string &a, string &b){
    forn(i, SZ(b)){
        if(a == b) return true;
        rotate(b.begin(), b.begin()+1, b.end());
    }
    return false;
}



int main () {
	//fastIO();
	
    int n; cin>>n;

    vector<string> ss(n);
    for(auto &s: ss) cin>>s;


    vector< string > reprs;
    for(int i = 0; i < n; i++){
        bool is_equal = false;
        for(int j = 0; j < SZ(reprs); j++){
            if(are_equal(ss[i], reprs[j]))
                is_equal = true;
        }

        if(!is_equal){
            reprs.push_back(ss[i]);
        }
    }

    cout << SZ(reprs) << endl;


	return 0;
}

