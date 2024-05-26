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

lli modularInverse(lli a, lli m){
	auto[d, x, y] = extendedGcd(a, m);
	if(d != 1) return -1; // inverse doesn't exist
	if(x < 0) x += m;
	return x;
}


lli power(lli b, lli e){
	lli ans = 1;
	while(e){
		if(e & 1) ans *= b;
		e >>= 1;
		b *= b;
	}
	return ans;
}

lli powerMod(lli b, lli e, lli m){
	lli ans = 1;
	b %= m;
	if(e < 0){
		b = modularInverse(b, m);
		e = -e;
	}
	while(e){
		if(e & 1) ans = ans * b % m;
		e >>= 1;
		b = b * b % m;
	}
	return ans;
}

vector<pair<lli, int>> factorize(lli n){
	vector<pair<lli, int>> f;
    lli aux = n;
	for(lli i = 2; i * i <= n; i++){
        if(aux % i == 0) {
            lli pot = 0;
            while(aux % i == 0) {
                pot++;
                aux /= i;
            }
            f.push_back({i, pot});
        }
    }

    if(aux > 1) {
        f.push_back({aux, 1});
    }
    return f;
}


//number of coprimes with n less than n
lli phi(lli n){
	lli ans = n;
	auto f = factorize(n);
	for(auto & factor : f)
		ans -= ans / factor.first;
	return ans;
}

lli multiplicativeOrder(lli x, lli m){
	if(gcd(x, m) != 1) return 0;
	lli order = phi(m);
	for(auto[p, a] : factorize(order)){
		order /= power(p, a);
		lli tmp = powerMod(x, order, m);
		while(tmp != 1){
			tmp = powerMod(tmp, p, m);
			order *= p;
		}
	}
	return order;
}



// Solves for x in the equation a^x = b mod m
pair<lli, lli> discreteLogarithm(lli a, lli b, lli m){
	lli m1 = m, pw = 1, div, nonRep = 0;
	for(; (div = gcd(a, m1)) > 1; ++nonRep, m1 /= div, pw = pw * a % m){
		if(pw == b) return {nonRep, 0}; //aperiodic solution found
	}
	auto[d, x, y] = extendedGcd(pw, m);
	if(b % d > 0) return {-1, 0}; //solution not found
	b = x * (b / d) % m;
	if(b < 0) b += m;
	lli order = multiplicativeOrder(a, m1);
	lli n = sqrt(order) + 1;
	lli a_n = powerMod(a, n, m1);
	unordered_map<lli, lli> firstHalf;
	pw = a_n;
	for(lli p = 1; p <= n; ++p, pw = pw * a_n % m1){
		firstHalf[pw] = p;
	}
	pw = b % m1;
	for(lli q = 0; q <= n; ++q, pw = pw * a % m1){
		if(firstHalf.count(pw)) return {nonRep + (n * firstHalf[pw] - q) % order, order}; //periodic solution found
	}
	return {-1, 0}; //solution not found
}



void main_(){

    lli a, b, s, p, v; cin>>a>>b>>s>>p>>v;

    lli ans = 0;
    if(a == 1) {
        lli left = (v - s + p) % p;
        lli right = powerMod(b, p-2, p);

        ans = left*right % p;

        assert( (s + ans*b % p)% p == v);

    } else {
        lli inv_a1 = powerMod((a - 1 + p) % p, p-2, p);
        lli right = (s + b * inv_a1 % p) % p;

        if(right == 0) {
            if(v == s) {
                cout << 0 << endl;
            } else {
                cout << "IMPOSSIBLE" << endl;
            }
            
            return;
        }



        right = powerMod(right, p-2, p);

        lli left = (v + b * inv_a1 % p) % p;

        lli total_right = left * right % p;

        auto [n, period] = discreteLogarithm(a, total_right, p);

        ans = n;

        if(ans != -1) {
            
            
            ans = (ans) % period;

            if(ans < 0) ans += period;
            if(ans >= period) ans -= period;


            assert(ans >= 0 && ans < p);

            lli an = powerMod(a, n, p);
            lli an_1 = (an - 1 + p) % p;
            lli left = an * s % p;
            lli inv_a = powerMod((a-1+p)%p, p-2, p);
            lli right = inv_a * an_1 % p * b % p;

            assert( (left + right)%p == v );
        }

    }    

    if(ans == -1){
        cout << "IMPOSSIBLE" << endl;
    } else {
        assert(0 <= ans && ans < p);
        cout << ans << endl;
    }
}


int main () {
	fastIO();
	
	int t = 1; 
	cin>>t;
	while(t--) 
		main_();


	return 0;
}

