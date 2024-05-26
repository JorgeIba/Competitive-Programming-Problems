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


// sqrt(n) + a / b
pair< vector<lli>, int > continuedFraction(lli n, lli a, lli b){
    lli sq = sqrtl(n);
    if(sq * sq == n) return {{-1}, 0}; // No tiene periodo

    vector<lli> seq;
    map< pair<lli,lli>, int > first_appear;
    for(int period = 0; ; period++) {
        // asume you have to find (sqrt(n) + a) / b

        lli div = (sq + a) / b;
        
        if(first_appear.count({a,b})) {
            period -= first_appear[{a, b}];
            return {seq, period};
        }

        first_appear[{a,b}] = period;
        seq.push_back(div);

        a -= b*div;
        b = (n - a*a) / b;
        a = -a;
    }
}


int main () {
	//fastIO();

    const int MAXN = 10'000;

    lli odds = 0;
    for(int n = 2; n <= MAXN; n++) {
        auto [seq, period] = continuedFraction(n, 0, 1);
        if(period & 1) odds++;
    }

    cout << odds << endl;

	return 0;
}

