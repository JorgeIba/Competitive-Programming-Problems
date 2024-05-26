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

#define point pair<lli,lli>

// 0-indexed
template <typename T, typename S>
struct SegmentTreeIt{
	T neutro = T();
	int size;
	vector<T> st;
	SegmentTreeIt(int n){
		st.resize(2*n);
		size = n;
	}
	
	void build(){
		for(int i = 0; i < 2*size; i++)
            sort(all(st[i]), greater<pair<lli,lli>>());
	}

	void update(int i, pair<lli,lli> val) {
        i += size;
        st[i].push_back(val);
		for(; i > 1; i >>= 1)
            st[i >> 1].push_back(val);
	}

	vector<lli> query(int l, int r, lli k){
		vector<lli> ans;
		for(l += size, r += size; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) {
                for(auto [y, idx_y]: st[l]) {
                    if(y >= k) ans.push_back(idx_y);
                    else break;
                } 
                l++;
            }
			if (~r & 1) {
                for(auto [y, idx_y]: st[r]){
                    if(y >= k) ans.push_back(idx_y);
                    else break;
                }
                r--;
            }
		}

		return ans;
	}
};


typedef pair<lli,lli> pairi;
typedef vector<pairi> vpairi;


const int P = 5782344;
const int MOD = 1e9+7;
const int MAXN = 1e5 + 100;

int powers[MAXN];


int main () {
	fastIO();

    auto transform = [](lli x, lli y) -> point{
        return {x - 2*y, x + 2*y};
    };

    powers[0] = 1;
    for(int i = 1; i < MAXN; i++)
        powers[i] = 1LL * P * powers[i-1] % MOD;




    int n, q; cin>>n>>q;

    vector< point > points(n);
    for(auto &[x, y]: points) {
        cin>>x>>y;
        tie(x, y) = transform(x, y);
    }
    

    vector<lli> distinct_x;
    for(auto [x, y]: points) distinct_x.push_back(x);

    sort(all(distinct_x));
    distinct_x.erase(unique(all(distinct_x)), distinct_x.end());

    auto get_mapx = [&](lli x) {
        return lower_bound(all(distinct_x), x) - begin(distinct_x);
    };



    int m = SZ(distinct_x);
    SegmentTreeIt< vpairi , pairi > *ST = new SegmentTreeIt< vpairi, pairi > (m+5);

    int idx = 1;
    for(auto &[x, y]: points) {
        ST->update(get_mapx(x), {y, idx});
        idx++;
    }

    ST->build();


    auto get_score = [&](const vector<lli> &ids){
        int sum = 0;
        for(int i = 0; i < SZ(ids); i++) {
            int id = ids[i];
            sum += 1LL * id * powers[i] % MOD;
            if(sum >= MOD) sum -= MOD;
        }
        return sum;
    };


    lli p = 0;
    forn(query, q) {
        lli a, b; cin>>a>>b;

        lli x_m = -1 - ((p+a) % MOD);
        lli y_m = (p+b) % MOD;

        tie(x_m, y_m) = transform(x_m, y_m);

        auto ans = ST->query(get_mapx(x_m), m + 2, y_m);

        sort(all(ans));

        cout << (p = get_score(ans)) << endl;
    }

	return 0;
}

