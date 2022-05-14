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


vector<lli> multiply(const vector<lli> &A, const vector<lli> &B) {
    auto [n, m] = pair<lli,lli>{SZ(A), SZ(B)};
    vector<lli> C(n + m - 1);
    
    for(int i = 0 ; i < n; i++) {
        for(int j = 0; j < m; j++) {
            C[i+j] += A[i] * B[j];
        }
    }

    return C;
}




int main () {
	//fastIO();

    // Only works for n s.t (n+1)! <= MAX_DATA_TYPE
    int n; cin>>n;
    vector<lli> multiplication = {1};
    for(int i = 1; i <= n; i++)
        multiplication = multiply(multiplication, {1, i});

    lli fact = 1;
    for(lli i = 2; i <= n+1; i++) fact *= i;


    lli ways = 0;
    for(lli choosen = n; choosen >= (n/2 + 1); choosen--) {
        ways += multiplication[n - choosen];
    }

    cout << ways << " / " << fact << endl;


    cout << fact / ways << endl;


	return 0;
}

