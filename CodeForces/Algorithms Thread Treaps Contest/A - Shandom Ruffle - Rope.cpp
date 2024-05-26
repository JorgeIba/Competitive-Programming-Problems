#include <bits/stdc++.h>
#include <ext/rope>
 
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
using namespace __gnu_cxx;


int main () {
	//fastIO();

    int n; cin>>n;
    rope<int> v;
    forr(i, 1, n) v.push_back(i);

    forn(iter, n) {
        int l, r; cin>>l>>r; l--, r--;
        if(r <= l) continue;
        int l_left = l, l_right = r - 1;
        int r_left = r, r_right = n-1;

        int sizee = min( l_right - l_left + 1,  r_right - r_left + 1 );
        auto left = v.substr(l_left, sizee);
        auto right = v.substr(r_left, sizee);

        v.erase(l_left, sizee);
        v.erase(r_left - sizee, sizee);

        v.insert(l_left, right);
        v.insert(r_left, left);
    }

    forn(i, n) {
        cout << v[i] << " ";
    }
    cout << endl;

	return 0;
}

