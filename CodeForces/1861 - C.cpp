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
	
    string s; cin>>s;
    int n = SZ(s);

    int st = 0;

    int last_one = -1, first_zero = 1e9;
    bool zero = false;
    bool ok = true;
    for(int i = 0; i < n; i++){
        auto c = s[i];
        if(c == '+'){
            st++;
        } else if(c == '-'){
            st--;

            if(st < last_one){
                last_one--;
            }
            if(st < first_zero){
                zero = false;
                first_zero = 1e9;
            }

        } else if(c == '1'){
            if(zero) {
                ok = false;
                break;
            }

            last_one = max(last_one, st);
        } else {

            if(st < 2) {
                ok = false;
                break;
            }

            if(last_one >= st){
                ok = false;
                break;
            }

            zero = true;
            first_zero = min(first_zero, st);
        }

        // debugg(first_zero);
        // debugg(st);
        // debugg(zero);
    }


    cout << (ok ? "YES" : "NO") << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}
