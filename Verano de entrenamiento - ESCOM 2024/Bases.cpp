#include <bits/stdc++.h>
 
#define endl '\n'
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

typedef long long int lli;
typedef long double ld;

const int HASHES = 9;
lli hashes[HASHES] = {
    122527843LL,
    217645199LL,
    219616097LL,
    961757387LL,
    314606891LL,
    122527843,
    217645199,
    219616097,
    236447707
};


struct poly {
    vector<lli> P;

    poly(): P(1,0) {}
    poly(int n, lli val = 0): P(n, 0) {}

    poly(string s) {
        int n = SZ(s);
        P.resize(n);
        reverse(all(s));
        for(int i = 0; i < n; i++) {
            assert('0' <= s[i] && s[i] <= '9');
            P[i] = s[i] - '0';
        }
    }

    int size() const {return SZ(P);}
    lli operator[](int idx) const {return P[idx];}

    poly operator+(const poly &Q) {
        int sz = max(SZ(P), SZ(Q));
        poly ans(sz);
        for(int i = 0; i < sz; i++) {
            lli a = 0, b = 0;
            if(i < SZ(P)) a = P[i];
            if(i < SZ(Q)) b = Q[i];

            ans.P[i] = a + b;
        }
        ans.trim();
        return ans;
    }

    poly operator-(const poly &Q) {
        int sz = max(SZ(P), SZ(Q));
        poly ans(sz);
        for(int i = 0; i < sz; i++) {
            lli a = 0, b = 0;
            if(i < SZ(P)) a = P[i];
            if(i < SZ(Q)) b = Q[i];

            ans.P[i] = a - b;
        }
        ans.trim();
        return ans;
    }

    poly operator*(const poly &Q) {
        poly C(SZ(P) + SZ(Q) - 1);
        for(int i = 0; i < SZ(P); i++) {
            for(int j = 0; j < SZ(Q); j++) {
                C.P[i+j] += P[i] * Q[j];
                assert(C.P[i+j] <= 1e18);
            }
        }
        C.trim();
        return C;
    }

    void trim() {
        while(size()>1 && P.back() == 0) P.pop_back();
    }

    lli evalHash(__int128 x, const lli MOD) const {
        assert(0 <= MOD);
        __int128 p = 1;
        __int128 ans = 0;
        x %= MOD;
        for(int i = 0; i < SZ(P); i++) {
            __int128 q = __int128(P[i])%MOD;
            if(q < 0) q += MOD;
            (ans += q * p % MOD) %= MOD;
            p = p * x % MOD;
        }
        return ans;
    }
};

// template<typename T>
ostream &operator<<(ostream &os, const poly &P){
    os << "P: [";
    // for(T x: P.P) {
    for(int i = 0; i < SZ(P); i++){
        os << P.P[i] << ", ";
    }
    os << "]";
    return os;
}


struct Symbol{
    string symbol;
    bool oper;
    Symbol() {}
    Symbol(string symbol, bool oper): symbol(symbol), oper(oper) {}
};

ostream &operator<<(ostream &os, const Symbol &S){
    os << S.symbol;
    return os;
}

vector<Symbol> tokenize(string s) {
    vector<Symbol> tokens;
    int i = 0;
    int n = SZ(s);

    while(i < n) {
        if(s[i] == '*' || s[i] == '+') {
            Symbol S(string(1,s[i]), true);
            tokens.push_back(S);
            i++;
            continue;
        }

        string num;
        while(i < n && s[i] != '*' && s[i] != '+') {
            num.push_back(s[i]);
            lli x = stoll(num);
            assert(x >= 0);
            i++;
        }

        Symbol S(num, false);
        tokens.push_back(S);
    }
    return tokens;
}


// template< typename T=lli >
poly parse(const vector<Symbol> &tokens) {
    stack< poly > nums;
    stack< string > opers;

    for(int i = 0; i < SZ(tokens); i++) {
        Symbol S = tokens[i];
        if(S.oper) {
            opers.push(S.symbol);
        } else {
            poly curr(S.symbol);
            if(opers.empty()) {
                nums.push(curr);
                continue;
            }

            if(opers.top() == "+") {
                nums.push(curr);
            } else {
                opers.pop();
                poly last = nums.top(); nums.pop();
                poly C = last * curr;

                nums.push(C);
            }
        }
    }

    while(nums.size() > 1) {
        poly P = nums.top(); nums.pop();
        poly Q = nums.top(); nums.pop();
        assert(opers.top() == "+"); opers.pop();

        nums.push(P + Q);
    }

    assert(opers.empty());

    return nums.top();
}


int max_char(const string &expression) {
    int maxi = 0;
    // for(auto S: symbols) {
    for(int i = 0; i < SZ(expression); i++){
        char c = expression[i];
        if(c == '+' || c == '*' || c == '=') continue;
        assert('0' <= c && c <= '9');
        maxi = max(maxi, c - '0');
    }
    return maxi;
}

vector<lli> get_divs(lli num) {
    num = abs(num);
    vector<lli> divs;   
    for(lli i = 1; i*i <= num; i++) {
        if(num % i == 0) {
            divs.push_back(i);
            if(i*i != num) divs.push_back(num/i);
        }
    }
    return divs;
};

bool is_root(lli x, const poly &P) {
    for(int i = 0; i < HASHES; i++) {
        if(P.evalHash(x, hashes[i]) != 0)  return false;
    }
    return true;
};

void main_(string s){
    string::iterator itr = find(all(s), '=');
    vector<Symbol> tokens_1 = tokenize(string(s.begin(),itr));
    vector<Symbol> tokens_2 = tokenize(string(itr+1,s.end()));

    poly poly_1 = parse(tokens_1);
    poly poly_2 = parse(tokens_2);

    int B = max_char(s) + 1;
    B = max(2, B);

    poly P = poly_1 - poly_2;
    P.trim();
    assert(SZ(P));
    if(SZ(P) == 1 && P[0] == 0) {
        cout << B << "+" << endl;
        return;
    }

    int first = 0;
    while(!P[first]) first++;
    assert(P.P.back() != 0);
    assert(P[first] != 0);

    vector<lli> ps = get_divs(P[first]);
    vector<lli> ans;
    for(int i = 0; i < SZ(ps); i++) {
        lli p = ps[i];
        if(p < B) continue;
        if(is_root(p, P)) {
            ans.push_back(p);
        }
    }

    if(SZ(ans) == 0) {
        cout << "*" << endl;
        return;
    }
    assert(!(SZ(P) == 1 && P[0] != 0));

    sort(all(ans));
    ans.erase(unique(all(ans)), ans.end());
    for(int i = 0; i < SZ(ans); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main () {
	fastIO();

	while(true) {
        string s; cin>>s;
        if(s == "=") break;
        main_(s);
	}

	return 0;
}

