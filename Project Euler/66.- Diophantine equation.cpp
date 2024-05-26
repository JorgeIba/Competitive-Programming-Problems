#include <bits/stdc++.h>
 
#define endl '\n'
#define lli __int128
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(sse) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

ostream &operator<<(ostream &os, const __int128 & value){
	char buffer[64];
	char *pos = end(buffer) - 1;
	*pos = '\0';
	__int128 tmp = value < 0 ? -value : value;
	do{
		--pos;
		*pos = tmp % 10 + '0';
		tmp /= 10;
	}while(tmp != 0);
	if(value < 0){
		--pos;
		*pos = '-';
	}
	return os << pos;
}

pair<vector<lli>, int> ContinuedFraction(lli p, lli n, lli q){
	vector<lli> coef;
	lli r = sqrt((long long) n);
	if((n - p * p) % q != 0){
		n *= q * q;
		p *= q;
		q *= q;
		r = sqrt((long long) n);
	}
	lli a = (r + p) / q;
	coef.push_back(a);
	int period = 0;
	map<pair<lli, lli>, int> pairs;
	while(true){
		p = a * q - p;
		q = (n - p * p) / q;
		a = (r + p) / q;
		
		if(pairs.count({p, q})){
			period -= pairs[{p, q}];
			break;
		}
		coef.push_back(a);
		pairs[{p, q}] = period++;
	}
	return {coef, period};
}

pair<lli, lli> PellEquation(lli n){
	vector<lli> cf = ContinuedFraction(0, n, 1).first;
	lli num = 0, den = 1;
	int k = cf.size() - 1;
	for(int i = ((k & 1) ? (2 * k - 1) : (k - 1)); i >= 0; i--){
		lli tmp = den;
		int pos = i % k;
		if(pos == 0 && i != 0) pos = k;
		den = num + cf[pos] * den;
		num = tmp;
	}
	return {den, num};
}

bool is_perfect(lli x) {
    lli sqr = sqrtl((ld)x);
    for(lli i = sqr-2; i <= sqr+2; i++) {
        if(i * i == x)
            return true;
    }
    return false;
}

int main () {
	//fastIO();

	const int MAXD = 1000;

	lli ans_d = 5, ans_x = 9;
	for(int d = 1; d <= MAXD; d++){
		if(is_perfect(d))
			continue;


		auto [x, y] = PellEquation(d);

		if(ans_x < x) {
			ans_x = x;
			ans_d = d;
		}
	}

	cout << ans_d << " " << ans_x << endl;


	return 0;
}

