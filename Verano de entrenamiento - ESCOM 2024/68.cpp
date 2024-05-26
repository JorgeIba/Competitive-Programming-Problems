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

int main () {
	// fastIO();

    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int n = 5;
    vector< tuple<int,int,int> > indexes(n);
    indexes[0] = {0, 1, 2};
    indexes[1] = {9, 2, 3};
    indexes[2] = {8, 3, 4};
    indexes[3] = {7, 4, 5};
    indexes[4] = {6, 5, 1};

    vector<string> solutions;

    do{
        set<int> sums;
        vector< tuple<int,int,int> > solution_set;
        for(auto [i, j, k]: indexes) {
            sums.insert(nums[i] + nums[j] + nums[k]);
            solution_set.push_back({nums[i], nums[j], nums[k]});
        }

        if(SZ(sums) > 1) continue;

        int idx = 0;
        for(int i = 0; i < n; i++) {
            if(get<0>(solution_set[i]) < get<0>(solution_set[idx])) {
                idx = i;
            }
        }

        string s;
        for(int i = idx, j = 0; j < n; i = (i+1)%n, j++){
            auto [l, m, n] = solution_set[i];
            s += to_string(l) + to_string(m) + to_string(n);
        }

        solutions.push_back(s);
    }while(next_permutation(all(nums)));


    lli ans = 0;
    for(auto x: solutions)
        if(SZ(x) == 16)
            ans = max(ans, stoll(x));

    cout << ans << endl;


	return 0;
}

