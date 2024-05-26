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

tuple<lli, lli, lli> extendedGcd(lli a, lli b){
	if(b == 0){
		if(a > 0) return {a, 1, 0};
		else return {-a, -1, 0};
	}else{
		auto[d, x, y] = extendedGcd(b, a%b);
		return {d, y, x - y*(a/b)};
	}
}

pair<lli, lli> crt(const vector<lli>& a, const vector<lli>& m){
	lli x = a[0], mod = m[0];
	for(int i = 1; i < a.size(); ++i){
		auto[d, s, t] = extendedGcd(mod, -m[i]);
		if((a[i] - x) % d != 0) return {-1, -1};
		lli step = m[i] / d;
        lli right = ((a[i] - x) / d) % step;
        lli left = s % step;
		lli k = left * right % step;
		if(k < 0) k += step;
		x += mod*k;
		mod *= step;
	}
	return {x, mod};
}


const lli LIMIT = 1e12 + 100;


int main () {
	//fastIO();
    lli n, m, k; cin>>n>>m>>k;

    vector<lli> nums(k);
    for(auto &x: nums) cin>>x;

    vector<lli> a(k);
    for(int i = 0; i < k; i++) {
        a[i] = (nums[i] - i) % nums[i];
        if(a[i] < 0) a[i] += nums[i];
    }

    lli lcm = 1;
    for(auto x: nums) {
        lli g = gcd(x, lcm);
        lli aux = lcm / g;
        if(aux > (LIMIT + x - 1) / x) {
            cout << "NO" << endl;
            return 0;
        }

        lcm = aux * x;
    }
    
    assert(lcm <= LIMIT);
    

    auto [j, i] = crt(a, nums);

    if(i == 0) i += i;
    if(j == 0) j += i;

    if(i > n || j + k - 1 > m || i == -1 || j == -1) {
        cout << "NO" << endl;
        return 0;
    } 

    for(int l = 0; l < k; l++) {
        if(gcd(i, j + l) != nums[l]) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;


	return 0;
}

