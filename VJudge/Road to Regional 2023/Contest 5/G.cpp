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

struct WaveletTree{
	int low,high;
	WaveletTree *left, *right;
	vector<int> mapLeft;

	WaveletTree( vector<int>::iterator from, vector<int>::iterator to, int x, int y ): low(x), high(y){
		if(from >= to) return;
		int m = (low+high)/2;
		auto f = [m](int x){ return x <= m; };
		mapLeft.reserve( to-from+1 );
		mapLeft.push_back(0);
		for(auto it=from; it!=to; it++){
			auto leq = f(*it);
			mapLeft.push_back( mapLeft.back()+ leq );
		}
		if(high != low){
			auto pivot = stable_partition(from,to,f);
			left = new WaveletTree(from,pivot,low,m);
			right = new WaveletTree(pivot,to,m+1,high);
		}
	}

	//counts the elements in the range[l,r] such that its value is in the range [a,b]
	int elementsInRange(int l, int r, int a,int b){
		if(l > r || (a < low && b < low) || (a > high && b > high) || (a > b))
			return 0;
		if(a <= low && b >= high)
			return r - l + 1;
		int lb = mapLeft[l - 1], rb = mapLeft[r];
		return left->elementsInRange(lb + 1, rb, a, b) + right->elementsInRange(l - lb, r - rb, a, b);
	}
};


const int INF = 1e9;
void main_(){
    int n; cin>>n;
    vector<int> nums(n);

    for(auto &x: nums) cin>>x;

    auto aux = nums;
    WaveletTree WT(all(aux), *min_element(all(aux)), *max_element(all(aux)));

    nums.insert(nums.begin(), 0);

    lli all_inv = 0;
    forr(i, 1, n){
        auto x = nums[i];
        all_inv += WT.elementsInRange(1, i-1, x+1, n);
    }

    map<pair<int,int>, lli> rangess;
    multiset<lli> values;
    
    auto get_ans = [&](){ return *values.rbegin(); };
    auto get_range = [&](int idx){
        auto itr = rangess.upper_bound({idx, INF});
        itr--;
        return *itr;
    };
    auto insert_range = [&](int l, int r, lli inv) -> void {
        rangess[{l, r}] = inv;
        values.insert(inv);
    };

    rangess[{1, n}] = all_inv;
    values.insert(all_inv);

    
    forn(_, n){
        lli p; cin>>p;

        cout << get_ans() << " ";

        int idx_p = p ^ get_ans();

        auto val_p = nums[idx_p];

        auto [rangee, inv_total] = get_range(idx_p);
        auto [l, r] = rangee;

        rangess.erase({l, r});
        values.extract(inv_total);

        if((r-l+1) == 1) continue;

        if(idx_p == l) {
            l++;
            int inv_invalid = WT.elementsInRange(idx_p+1, r, 1, val_p - 1);
            inv_total -= inv_invalid;

            insert_range(l, r, inv_total);
        } else if(idx_p == r){
            r--;
            int inv_invalid = WT.elementsInRange(l, idx_p-1, val_p + 1, n);
            inv_total -= inv_invalid;

            insert_range(l, r, inv_total);
        } else {
            int l_1 = l, r_1 = idx_p-1;
            int l_2 = idx_p+1, r_2 = r;

            int sz_1 = (r_1 - l_1 + 1);
            int sz_2 = (r_2 - l_2 + 1);

            int inv_p = WT.elementsInRange(l, idx_p-1, val_p + 1, n) + WT.elementsInRange(idx_p+1, r, 1, val_p - 1);
            inv_total -= inv_p;

            if(sz_1 < sz_2){
                lli inv_between = 0;
                lli valid_in_left = 0;
                for(int i = l_1; i <= r_1; i++){
                    inv_between += WT.elementsInRange(l_2, r_2, 1, nums[i]-1);
                    valid_in_left += WT.elementsInRange(l_1, i-1, nums[i]+1, n);
                }
                
                lli valid_in_right = inv_total - inv_between - valid_in_left;

                insert_range(l_1, r_1, valid_in_left);
                insert_range(l_2, r_2, valid_in_right);
            } else {

                lli inv_between = 0;
                lli valid_in_right = 0;
                for(int i = l_2; i <= r_2; i++){
                    inv_between += WT.elementsInRange(l_1, r_1, nums[i]+1, n);
                    valid_in_right += WT.elementsInRange(l_2, i-1, nums[i]+1, n);
                }
                
                lli valid_in_left = inv_total - inv_between - valid_in_right;

                insert_range(l_1, r_1, valid_in_left);
                insert_range(l_2, r_2, valid_in_right);
            }
        }
    }
    cout << endl;
}


int main () {
	fastIO();
	
    int t; cin>>t;
    while(t--) main_();



	return 0;
}

