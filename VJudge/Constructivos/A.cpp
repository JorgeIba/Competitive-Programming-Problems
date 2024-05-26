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



int main () {
	fastIO();

    int n, m; cin>>n>>m;

    const int MAXN = 2200;
    vector<int> A(MAXN), B(MAXN, 5);

    A[0] = 5;
    for(int i = 1; i < SZ(A); i++) A[i] = 4;

    reverse(all(A));


    for(auto x: A) cout <<x;
    cout << endl;

    for(auto x: B) cout <<x;
    cout << endl;

	return 0;
}

