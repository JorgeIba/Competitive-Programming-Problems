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




int n;

ld f(int i, int won) {
    if(i == n+1) return won >= (n/2 + 1);

    if(won >= (n/2 + 1)) return 1;

    ld prob = (ld) 1 / (i+1);

    return prob*f(i+1, won+1) + (1-prob)*f(i+1, won);
}

int main () {
	//fastIO();
    cin>>n;
    ld prob_win = f(1, 0);

    ld E = 0;

    for(ld x = 1; x <= 1'000'000; x++) {
        E += x * (pow( (1-prob_win) , x-1)) * (prob_win);
    }
    cout << E << endl;


	return 0;
}

