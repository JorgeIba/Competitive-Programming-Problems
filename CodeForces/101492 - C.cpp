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


vector<int> nums;

vector<int> lowestPrime;
void lowestPrimeSieve(int n){
	lowestPrime.resize(n + 1, 1);
	lowestPrime[0] = lowestPrime[1] = 0;
	for(int i = 2; i <= n; ++i) lowestPrime[i] = (i & 1 ? i : 2);
	int limit = sqrt(n);
	for(int i = 3; i <= limit; i += 2)
		if(lowestPrime[i] == i)
			for(int j = i * i; j <= n; j += 2 * i)
				if(lowestPrime[j] == j) lowestPrime[j] = i;
}

vector<int> mu;
void muSieve(int n){
	mu.resize(n+1, -1);
	mu[0] = 0, mu[1] = 1;
	for(int i = 2; i <= n; ++i)
		if(mu[i])
			for(int j = 2*i; j <= n; j += i)
				mu[j] -= mu[i];
}


int sum_total = 0;
const int maxA = 5e5+1000;

vector<int> fr_nums(maxA), sum_mu(maxA);
vector< vector<int> > divs_sqfree;


void add(int i){
    vector<int> divs = divs_sqfree[i];
    
    for(auto d: divs){
        sum_total += mu[d] * fr_nums[d];
        fr_nums[d]++;
        sum_total += mu[d] * fr_nums[d];
    }
	
}
void remove(int i){
    vector<int> divs = divs_sqfree[i];

    for(auto d: divs){
        sum_total -= mu[d] * fr_nums[d];
        fr_nums[d]--;
        sum_total -= mu[d] * fr_nums[d];
    }
}
int getAns(){
	return sum_total;
}

const int BLOCK = 200;

struct Query{
	int l, r, indx;
    lli order;
	bool operator<(const Query& q) const{
		return order < q.order;
	}
};

inline lli hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) return 0;

	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;

	lli subSquareSize = 1LL << (2*pow - 2);
	lli ans = seg * subSquareSize;
	lli add = hilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}


vector<int> mosAlgo(vector<Query> Q){
    int n = SZ(Q);
	vector<int> ans(n);
	sort(all(Q));
	int L = 0;
	int R = -1;
	for(int i = 0; i < n; i++){
		Query q = Q[i];
        while(L > q.l) add(--L);
		while(R < q.r) add(++R);
		
        while(L < q.l) remove(L++);
		while(R > q.r) remove(R--);
		
		ans[q.indx] = getAns();
	}
	return ans;
}


vector<int> factorize(int n){
    vector<int> primes;
    while(n > 1){
        int lp = lowestPrime[n];
        primes.push_back(lp);
        while(n % lp == 0) 
            n /= lp;
    }
    return primes;
}

vector<int> get_divs(const vector<int> facts){
    vector<int> divs;
    int m = SZ(facts);
    for(int mask = 0; mask < (1 << m); mask++){
        int num = 1;
        for(int j = 0; j < m; j++) { 
            if(mask & (1 << j))
                num *= facts[j];
        }
        divs.push_back(num);
    }
    return divs;
}


int main () {
	//fastIO();

    lowestPrimeSieve(maxA);
    muSieve(maxA);

    int n, q; cin>>n>>q;

    nums.resize(n);
    divs_sqfree.resize(n);

    for(auto &x: nums) cin>>x;

    vector< Query > queries(q);
    for(int i = 0; i < q; i++){
        int l, r; cin>>l>>r; l--, r--;
        queries[i] = {l, r, i, hilbertOrder(l, r, 19, 0)};
    }


    for(int i = 0; i < n; i++){
        auto num = nums[i];
        auto divs = get_divs(  factorize(num)   );
        divs_sqfree[i] = divs;
    }

    auto ans = mosAlgo(queries);

    for(auto x: ans){
        cout << (x ? "S" : "N") << endl;
    }


	return 0;
}

