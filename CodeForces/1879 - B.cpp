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


void main_(){
    int n; cin>>n;
    vector<int> a(n), b(n);
    for(auto &x: a) cin>>x;
    for(auto &x: b) cin>>x;

    lli min_a = *min_element(all(a));
    lli min_b = *min_element(all(b));

    lli sum_a = 0, sum_b = 0;
    for(auto x: a) sum_a += x;
    for(auto x: b) sum_b += x;

    lli ans_1 = 1LL* min_a*n + sum_b;
    lli ans_2 = 1LL* min_b*n + sum_a;

    // debugg(min_a);
    // debugg(min_b);
    // debugg(sum_a);
    // debugg(sum_b);

    cout << min(ans_1, ans_2) << endl;
}


int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}