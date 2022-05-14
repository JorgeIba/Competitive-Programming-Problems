#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


bool divisible(vector<lli> poly, lli k) {
    lli a_0 = -poly[0];
    for(int i = 1; i < SZ(poly); i++){
        if(a_0 % k) return false;
        a_0 = a_0/k - poly[i];

    }
    return a_0 == 0;
}


int main () {
	//fastIO();

    lli n, k; cin>>n>>k;
    vector<lli> poly(n+1);

    lli INF = 1e18;
    lli turns = 0;
    for(auto &x: poly) {
        string a; cin>>a;
        if(a == "?") {
            x = -INF;
        } else {
            turns++;
            x = stoll(a);
        }
    }

    lli who_goes = turns % 2, turns_left = n+1-turns;
    // cout << who_goes << " " << turns_left << endl;
    if(k == 0) {
        if(poly[0] != -INF) {
            cout << (poly[0] == 0 ? "Yes" : "No")<< endl;
            return 0;
        }

        if(who_goes == 0) cout << "No" << endl;
        else cout << "Yes" << endl;
        return 0;

    } else {
        

        if(turns_left == 0) {
            if(divisible(poly, k)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
            return 0;
        }

        if(who_goes == 0){ // computer
            if(turns_left % 2 == 1) {
                cout << "No" << endl;
            } else {
                cout << "Yes" << endl;
            }
        } else { // person
            if(turns_left % 2 == 0) {
                cout << "No" << endl;
            } else {
                cout << "Yes" << endl;
            }
        }

    }


	return 0;
}

