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

const int MAXN = 2e5 + 100;

const int SIG = 3;
const int A = 0;
const int B = 1;
const int C = 2;

const lli INF = 1e17;


/*
    Type 0
    ABCABCABCABC
    BCABCABCABCA
    CABCABCABCAB

    Type 1
    ACBACBACBACB
    BACBACBACBAC
    CBACBACABCAB

    dp[ABCABCABC...][final]
    ABCABCABC... 0 ----- dp[A][A|B|C][0]
    ACBACBACB... 1 ----- dp[A][A|B|C][1]

    BACBACBAC... 2 ----- dp[B][A|B|C][1]
    BCABCABCA... 3 ----- dp[B][A|B|C][0]
    
    CABCABCAB... 4 ----- dp[C][A|B|C][0]
    CBACBACBA... 5 ----- dp[C][A|B|C][1]
*/

int values[MAXN];
string s;

struct Node{
    lli dp[SIG][SIG][2];

    Node(){
        forn(i, SIG)
            forn(j, SIG)
                forn(k, 2)
                    dp[i][j][k] = -INF;
    }

    Node(int idx) {
        forn(i, SIG)
            forn(j, SIG)
                forn(k, 2)
                    dp[i][j][k] = -INF;


        char c = s[idx];
        int cc;
        if(c == 'A') cc = A;
        if(c == 'B') cc = B;
        if(c == 'C') cc = C;

        dp[cc][cc][0] = values[idx];
        dp[cc][cc][1] = values[idx];
    }

    lli getAns(){
        lli ans = 0;
        forn(start, SIG){
            forn(ends, SIG){
                forn(typee, 2) {
                    ans = max(ans, dp[start][ends][typee]);
                }
            }
        }
        return ans;
    }
};

int next_in_seq(int me, int typee) {
    if(typee == 0){
        if(me == A) return B;
        if(me == B) return C;
        if(me == C) return A;
    } else {
        if(me == A) return C;
        if(me == B) return A;
        if(me == C) return B;
    }
    assert(false);
    return -1;
}

Node operator+(const Node &L, const Node &R) {
    Node M;

    forn(i, SIG){
        forn(j, SIG){
            forn(k, 2){
                M.dp[i][j][k] = max(L.dp[i][j][k], R.dp[i][j][k]);
            }
        }
    }

    for(int start_l = 0; start_l < SIG; start_l++){
        for(int end_r = 0; end_r < SIG; end_r++){
            for(int end_l = 0; end_l < SIG; end_l++){
                for(int typee = 0; typee < 2; typee++){

                    M.dp[start_l][end_r][typee] = max(

                        M.dp[start_l][end_r][typee], 
                        L.dp[start_l][end_l][typee] + R.dp[  next_in_seq(end_l, typee) ][end_r][typee]

                    );

                }
            }
        }
    }
    return M;
}


// 0-indexed
template <typename T, typename S>
struct SegmentTreeIt{
	T neutro = T();
	int size;
	vector<T> st;
	SegmentTreeIt(int n){
		st.resize(2*n);
		size = n;
		
        forn(i,n) st[i+size] = set(i);
		build();
	}
	T merge(T a, T b){
    	return a + b;
	}
	void build(){
		for(int i = size - 1; i; i--)
			st[i] = merge(st[i << 1], st[i << 1 | 1]);
	}
	void update(int i) {
        i += size;
        st[i] = Node(i - size);
		for(; i > 1; i >>= 1)
			if(i & 1)
				st[i >> 1] = merge(st[i^1], st[i]);
            else 
                st[i >> 1] = merge(st[i], st[i^1]);
	}
	T query(int l, int r){
		T ansL = neutro;
        T ansR = neutro;
		for(l += size, r += size; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ansL = merge(ansL, st[l++]);
			if (~r & 1) ansR = merge(st[r--], ansR);
		}
		return merge(ansL, ansR);
	}
	T set(S x){
		return T(x);
	}
};


int main () {
	fastIO();

    int n, q; cin>>n>>q;
    cin>>s;
    forn(i, n) cin>>values[i];

    SegmentTreeIt<Node, int> ST(n);

    while(q--){
        int t; cin>>t;
        if(t == 1){
            int p; char z; cin>>p>>z; p--;
            s[p] = z;

            ST.update(p);
        } else{
            int p, x; cin>>p>>x; p--;
            values[p] = x;

            ST.update(p);
        }

        cout << (ST.query(0, n-1)).getAns() << endl;
    }


	return 0;
}

