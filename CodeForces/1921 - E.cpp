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
    lli h, w, xa, ya, xb, yb;
    cin>>h>>w>>xa>>ya>>xb>>yb;

    lli row_diff = xb - xa;
    if(row_diff <= 0) {
        cout << "Draw" << endl;
        return;
    }


    auto alice_can_reach = [&]() -> bool {
        if(abs(ya - yb) <= 1) return true;

        if(ya < yb) {
            // Se va a querer ir por la derecha
            // right
            int moves_bob = w - yb;
            int target_bob = xb - moves_bob; // en que posicion llega

            int moves_alice = w - ya;
            int target_alice = xa + moves_alice;

            if(target_bob <= 0) return false;

            int will_be = target_bob - (moves_alice - moves_bob);
            // debugg(will_be);
            // debugg(moves_alice);
            // debugg(target_alice);
            // debugg(moves_bob);
            // debugg(target_bob);

            return target_alice-1 <= will_be;
        } else {
            // left
            int moves_bob = yb - 1;
            int target_bob = xb - moves_bob;

            int moves_alice = ya - 1;
            int target_alice = xa + moves_alice;

            if(target_bob <= 0) return false;

            int will_be = target_bob - (moves_alice - moves_bob);

            // debugg(will_be);
            // debugg(moves_alice);
            // debugg(target_alice);
            // debugg(moves_bob);
            // debugg(target_bob);


            return target_alice-1 <= will_be;
        }
    };

    auto alice_can_escape = [&]() -> bool {
        if(abs(ya - yb) == 0) return false;

        if(ya > yb) {
            // me quiero ir a la derecha
            // right
            int moves_bob = w - yb;
            int target_bob = xb - moves_bob; 

            int moves_alice = w - ya;
            int target_alice = xa + moves_alice;

            if(target_alice >= h) return true;

            int will_be = target_alice + (moves_bob - moves_alice);

            return target_bob < will_be;
        } else {
            // left
            int moves_bob = yb - 1;
            int target_bob = xb - moves_bob;

            int moves_alice = ya - 1;
            int target_alice = xa + moves_alice;

            if(target_alice >= h) return true;

            int will_be = target_alice + (moves_bob - moves_alice);

            // debugg(will_be);
            // debugg(moves_alice);
            // debugg(target_alice);
            // debugg(moves_bob);
            // debugg(target_bob);


            return target_bob < will_be;
        }

    };


    if(row_diff % 2 == 1) { // ALice puede ganar

        if(alice_can_reach()) {
            cout << "Alice" << endl;
        } else {
            cout << "Draw" << endl;
        }

    } else {

        if(alice_can_escape()) {
            cout << "Draw" << endl;
        } else {
            cout << "Bob" << endl;
        }
    }
}

int main () {
	fastIO();

	int t = 1; 
	cin>>t;

	while(t--) {
		main_();
	}

	return 0;
}

