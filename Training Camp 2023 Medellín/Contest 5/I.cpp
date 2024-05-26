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

const string B = "black";
const string W = "white";

int query(int x, int y){
    cout << x << " " << y << endl;
    cout.flush();
    string color; cin>>color;
    return color == B;
}

int main () {
	//fastIO();
    
    int n; cin>>n;


    const int MAXN = 1e9;

    int l = 0, r = 1e9;
    int y = (l+r)/2;

    int last_black = 0, last_white = r;

    int first_query = query(0, y);
    bool ok = true;
    if(first_query == 0) {
        ok = false;
        last_white = 0;
        last_black = r;
    }

    forn(t, n-1){
        int mid = (l+r)/2;

        int color = query(mid, y);
        
        if(ok){
            if(color == 1) {
                last_black = mid;
                l = mid;
            } else {
                last_white = mid;
                r = mid;
            }
        } else {
            if(color == 0) {
                last_white = mid;
                l = mid;
            } else {
                last_black = mid;
                r = mid;
            }
        }
    }


    cout << last_black << " " << 0 << " " << last_white << " " << MAXN << endl;

	return 0;
}

