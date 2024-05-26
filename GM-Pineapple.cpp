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

ld a, b, n; 
ld f(ld x) {
    return a*a * (1 - (x / b)*(x / b));
}

ld simpson_rule(ld a, ld b, int n = 1e5)
{
    ld h = (b - a) / n;

    ld sum_odds = 0.0;
    for (int i = 1; i < n; i += 2)
        sum_odds += f(a + i * h);

    ld sum_evens = 0.0;
    for (int i = 2; i < n; i += 2)
        sum_evens += f(a + i * h);

    return (f(a) + f(b) + 2 * sum_evens + 4 * sum_odds) * h / 3;
}

const ld PI = acos(-1);

int main () {
	//fastIO();

    cin>>a>>b>>n;

    ld h = (2*b)/n;

    for(int i = 0; i < n; i++) {
        ld left = -b + i*h, right = -b + (i+1)*h;
        ld ans = simpson_rule(left, right) * PI;
        // ld ans = integrate(left, right) * PI;
        cout << fixed << setprecision(6) <<  ans / 8 << endl;
    }

	return 0;
}