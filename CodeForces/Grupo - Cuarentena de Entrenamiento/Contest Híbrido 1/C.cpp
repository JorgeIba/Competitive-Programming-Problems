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



vector<lli> getDivisors(lli n){
    VLL ans;
    for(lli i = 1; i * i <= n; i++) {
        if(n % i == 0) {
            ans.push_back(i);
            if(i*i != n) ans.push_back(n/i);
        }
    }
    return ans;
}



int main () {
	//fastIO();
    lli n, k; cin>>n>>k;

    auto divisors = getDivisors(n);

    sort(all(divisors));


    if(SZ(divisors) < k) {
        cout << -1 << endl;
    } else {
        cout << divisors[k-1] << endl;
    }

	return 0;
}

