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


// 1-indexed
struct Fenwick {
  vector<long long> tree;
  int n;

  Fenwick(int _n) {
    n = _n;
    tree.resize(n+1, 0);
    for (int i = 0 ; i <= n ; i++) {
      tree[i] = 0;
    }
  }

  void update(int idx, long long val) {
    for (; idx <= n ; idx += idx & -idx) {
      tree[idx] += val;
    }
  }

  long long query(int idx) {
    long long ret = 0;
    while (idx > 0) {
      ret += tree[idx];
      idx -= idx & -idx;
    }
    return ret;
  }

  long long query(int x, int y) {
    return query(y) - query(x-1);
  }
};


void main_(){
    int n; cin>>n;

    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    map< int, set<int> > indexes;

    forn(i, n){
        indexes[nums[i]].insert(i);
    }

    Fenwick F(n);

    int l = 0, r = n-1;
    lli ans = 0;
    while(l < r){
        int num_l = nums[l];
        int num_r = nums[r];

        // cout << "Try: " << endl;
        // cout << l << " " << r << endl;

        if(F.query(l+1, l+1)) {
            // cout << "QUERY L: " << l << " --> " << F.query(l) << endl;
            l++; continue;
        }

        if(F.query(r+1, r+1)){
            // cout << "QUERY R: " << r << " --> " << F.query(r) << endl;
            r--; continue;
        }

        if(SZ(indexes[num_l]) == 1) {
            // cout << "SZ: " << l << endl;
            l++;
            continue;
        }

        if(SZ(indexes[num_r]) == 1) {
            // cout << "SZ: " << r << endl;
            r--;
            continue;
        }

        // cout << "Ok: " << endl;
        // cout << l << " " << r << endl;

        int lowest_l = l;
        assert(indexes[num_l].count(l));
        int greatest_l = *indexes[num_l].rbegin();


        int greatest_r = r;
        assert(indexes[num_r].count(r));
        int lowest_r = *indexes[num_r].begin();


        int score_l = greatest_l - lowest_l - F.query(lowest_l+1, greatest_l+1);
        int score_r = greatest_r - lowest_r - F.query(lowest_r+1, greatest_r+1);

        // debugg(lowest_l);
        // debugg(greatest_l);

        // debugg(lowest_r);
        // debugg(greatest_r);

        // debugg(score_l);
        // debugg(score_r);


        if(score_l >= score_r){
            // cout << "UPDATING: " << lowest_l << " and " << greatest_l << endl;
            F.update(lowest_l + 1, 1);
            F.update(greatest_l + 1, 1);
            ans += score_l;
            l++;
            indexes[num_l].erase(lowest_l);
            indexes[num_l].erase(greatest_l);
        } else{
            // cout << "UPDATING: " << lowest_r << " and " << greatest_r << endl;
            F.update(lowest_r + 1, 1);
            F.update(greatest_r + 1, 1);
            ans += score_r;
            r--;
            indexes[num_r].erase(lowest_r);
            indexes[num_r].erase(greatest_r);
        }
    }

    cout << ans << endl;
}


int main () {
	//fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

