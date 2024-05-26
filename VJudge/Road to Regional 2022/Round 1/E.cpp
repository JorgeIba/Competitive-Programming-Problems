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

#define ull unsigned long long


ull multMod(ull a, ull b, ull mod) {
    ull res = 0;
    a %= mod;
    while(b) {
        if(b & 1){
            res += a;
            res = res >= mod ? res - mod : res;
        };
        b >>= 1;
        a <<= 1;
        a = a >= mod ? a - mod : a;
    }
    return res;
}

lli powerMod(lli a, lli b, lli mod) {
    lli res = 1; 
    while(b) {
        if(b & 1) res = multMod(res, a, mod);
        b >>= 1;
        a = multMod(a, a, mod);
    }
    return res;
}


//22
bool isPrimeMillerRabin(lli n)
{
    if(n < 2) return false;
    if(n <= 3) return true;
    if( ~n & 1) return false;
    lli d = n-1, s = 0; //n-1 = 2^s*k
    for(;(~d&1); d>>=1, s++); //d = k
    for(lli a: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37})
    {
        if(n == a) return true;
        lli residuo = powerMod(a, d, n);
        if(residuo == 1 or residuo == n-1) continue;
        lli x = s;
        while(--x)
        {
            residuo = multMod(residuo, residuo, n);
            if(residuo == n-1) break;
        }
        if(x==0) return false;
    }
    return true; //Probability = 1 - (1/4)^size_of(vector_a)
}




lli getFactor(lli n) {
    lli a = rand(), b = rand();
    lli x = 2, y = 2, d = 1;

    auto f = [&](auto x){ return (multMod(x, x+a, n) + b) % n; };

    while(d == 1) {
        x = f(x);
        y = f(f(y));
        d = __gcd(abs(x-y), n);
    }

    return d;
}


map<lli,int> factors;
void factorizePollardRho(lli n, lli start = true) {
    if(start) factors.clear();
    
    // You can reduce by trial division [2, 3, 5, 7, ...]

    while(n > 1 && !isPrimeMillerRabin(n)) {
        lli factor = n;
        while(factor == n) factor = getFactor(n);
        n /= factor;
        factorizePollardRho(factor, false);
        for(auto &[p, a]: factors) {
            while(n % p == 0) {
                n /= p;
                a++;
            }
        }
    }
    
    if(n > 1) factors[n]++;
}


const lli maxN = 2e5+10;
const lli neutro_lazy_sum = 0;
struct Node{
    lli l, r;

    lli value;
    lli gcd;
    lli lazySUM = neutro_lazy_sum;
};

Node ST[4*maxN]; 

template<typename T>
struct SegmentTree {
    lli N;

    SegmentTree(lli n, const vector<T> &values): N(n){
        build(1, 1, N, values);
    }
    
    void init_leaf(int curr, T value){
        ST[curr].value = value;
        ST[curr].gcd = value;
    }

    //* NODE UPDATES *//
    void updateNodeGCD(int curr, T value){
        ST[curr].gcd = value;
        ST[curr].value = value;
        // ST[curr].lazySUM += value;
    }

    //* LAZY MANAGMENT *//
    void pushToChildren(int curr){
        if(ST[curr].lazySUM != neutro_lazy_sum){
            updateNodeGCD(2*curr, ST[curr].lazySUM);
            updateNodeGCD(2*curr+1, ST[curr].lazySUM);
            // ST[curr].lazySUM = neutro_lazy_sum;
        }
    }

    void updateFromChildren(int curr){
        // Mantain Sum
        ST[curr].gcd = __gcd(ST[2 * curr].gcd, ST[2 * curr + 1].gcd);
    }
    
    //* UPDATES *//
    // SUM
    void updateGCD(int curr, int l, int r, int ql, int qr, T value)
    {
        if( l > qr || r < ql) return;
        else if(ql <= l && r <= qr){
            updateNodeGCD(curr, value);
            return;
        }

        pushToChildren(curr);

        lli mid = l + (r-l)/2;
        updateGCD(2*curr, l, mid, ql, qr, value);
        updateGCD(2*curr+1, mid+1, r, ql, qr, value);

        updateFromChildren(curr);
    }
    void updateGCD(int ql, int qr, T value){
        updateGCD(1, 1, N, ql, qr, value);
    }
    
    //? QUERIES ?//
    // GCD
    lli queryGCD(int curr, int l, int r, int ql, int qr)
    {
        if(l > qr || r < ql) return 0;
        else if(ql <= l && r <= qr) return ST[curr].gcd;
        else {
            pushToChildren(curr);
            lli mid = (l+r) / 2;
            return __gcd(queryGCD(2*curr, l, mid, ql, qr), queryGCD(2*curr+1, mid+1, r, ql, qr));
        }
    }
    lli queryGCD(int ql, int qr){
        return queryGCD(1, 1, N, ql, qr);
    }


    void searchCoprimes(int curr, int l, int r, lli val, vector<lli> &coprimes, lli &how_many) {
        if(l == r) {
            if(ST[curr].gcd % val != 0) {
                coprimes.push_back(ST[curr].value);
            }
        } else {
            if( ST[curr].gcd % val == 0 ) return;

            lli mid = (l+r)/2;
            bool coprLeft = (ST[2*curr].gcd % val != 0);
            bool coprRight = (ST[2*curr+1].gcd % val != 0);

            if(coprLeft && coprRight) {

                if(how_many > 0) {
                    coprimes.push_back(-1);
                    return;
                }

                how_many++;
                searchCoprimes(2*curr, l, mid, val, coprimes, how_many);
                searchCoprimes(2*curr+1, mid+1, r, val, coprimes, how_many);
            } else if(coprLeft && !coprRight) {
                searchCoprimes(2*curr, l, mid, val, coprimes, how_many);
            } else if(!coprLeft && coprRight){
                searchCoprimes(2*curr+1, mid+1, r, val, coprimes, how_many);
            } else {
                return;
            }
        }
    }


    void build(int curr, int l, int r, const vector<T> &values){
        ST[curr].l = l, ST[curr].r = r;
        if(l == r) {
            init_leaf(curr, values[l-1]);
        } else {
            lli mid = (l+r)/2;
            build(2*curr, l, mid, values);
            build(2*curr+1, mid+1, r, values);
            updateFromChildren(curr);
        }
    }
};


vector<lli> getDivs(vector<pair<lli,lli>> &factors)
{
    int n = SZ(factors);
    lli factors_count = 1;
    for (int i = 0; i < n; ++i)
    {
        factors_count *= (1+factors[i].second);
    }
    vector<lli> divs(factors_count); divs[0] = 1;
    int count = 1;
    for (int stack_level = 0; stack_level < n; ++stack_level)
    {
        int count_so_far = count;
        lli prime = factors[stack_level].first;
        int exponent = factors[stack_level].second;
        lli multiplier = 1;
        for (int j = 0; j < exponent; ++j)
        {
            multiplier *= prime;
            for (int i = 0; i < count_so_far; ++i)
            {
                divs[count++] = divs[i] * multiplier;
            }
        }
    }
    return divs;
}


void solve() {
    lli n; cin>>n;

    vector<lli> nums(n);
    for(auto &x: nums) cin>>x;

    SegmentTree<lli> *ST = new SegmentTree<lli>(n, nums);

    if(n == 2) {
        cout << nums[0] * nums[1] << endl;
        return;
    }


    vector<lli> allDivs;

    for(int i = 0; i < 3; i++) {
        factorizePollardRho(nums[i]);
        vector<pair<lli,lli>> facts_i(all(factors));
        auto divs_i = getDivs(facts_i);

        allDivs.insert(allDivs.end(), all(divs_i));
    }
    
    set<lli> st(all(allDivs));
    allDivs.assign(all(st));

    
    lli ans = ST->queryGCD(1, n);
    for(auto d: allDivs) {
        vector<lli> coprimes;
        lli how_many = 0;
        ST->searchCoprimes(1, 1, n, d, coprimes, how_many);


        int flag = count(all(coprimes), -1);
        if(flag) continue;

        if(SZ(coprimes) <= 1) ans = max(ans, d);
        else {
            // assert(SZ(coprimes) == 2);
            if(((__int128)coprimes[0])*coprimes[1] % d == 0) {
                ans = max(ans, d);
            }
        }
    }

    cout << ans << endl;
}



int main () {
	//fastIO();

    lli t; cin>>t;

    while(t--) solve();

	return 0;
}

