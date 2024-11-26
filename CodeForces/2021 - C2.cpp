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

void main_() {
    int n, m, q; cin>>n>>m>>q;
    vector<int> nums(n);
    for(auto &x: nums) {
        cin>>x;
        x--;
    }

    vector<int> last(m);
    for(auto &x: last) {
        cin>>x;
        x--;
    }

    vector<int> inv(n);
    forn(i, n) {
        inv[nums[i]] = i;
    }

 
    vector<set<int>> appears(n, {m});
    for(int i = m-1; i >= 0; i--) {
        appears[last[i]].insert(i);
    }

    auto get_pos = [&](int x) {
        return *appears[x].begin();
    };

    set< tuple<int,int,int> > curr_state;
    int matches = 0;

    auto get_prev = [&](int x) -> tuple<int, int, int> {
        auto itr = curr_state.find({get_pos(x), inv[x], x});
        assert(itr != curr_state.end());

        if(itr == curr_state.begin()) return {-1, -1, -1};

        auto prev = next(itr, -1);
        return *prev;
    };

    auto get_next = [&](int x) -> tuple<int, int, int> {
        auto itr = curr_state.find({get_pos(x), inv[x], x});
        assert(itr != curr_state.end());

        auto nextt = next(itr, 1);
        if(nextt == curr_state.end()) return {-1, -1, -1};
        return *nextt;
    };


    auto insert = [&](int x) {
        int pos = get_pos(x);
        curr_state.insert({pos, inv[x], x});
        auto [prev_pos, inv_u, prev_u] = get_prev(x);
        auto [next_pos, inv_v, next_u] = get_next(x);

        if(prev_u != -1 && next_u != -1 && inv_u <= inv_v) matches--;
        if(next_u != -1 && inv[x] <= inv_v) matches++;
        if(prev_u != -1 && inv_u <= inv[x]) matches++;
    };

    auto remove = [&](int x) {
        int pos = get_pos(x);
        auto [prev_pos, inv_u, prev_u] = get_prev(x);
        auto [next_pos, inv_v, next_u] = get_next(x);
        curr_state.erase({pos, inv[x], x});

        if(prev_u != -1 && next_u != -1 && inv_u <= inv_v) matches++;
        if(next_u != -1 && inv[x] <= inv_v) matches--;
        if(prev_u != -1 && inv_u <= inv[x]) matches--;
    };

    auto print_ans = [&]() {
        cout << (matches == n-1 ? "YA" : "TIDAK") << endl;
    };

    forn(i, n) {
        insert(i);
    }

    print_ans();

    while(q--) {
        int idx, x; cin>>idx>>x;
        idx--, x--;
        int y = last[idx];
        if(x == y) {
            print_ans();
            continue;
        }

        remove(y);
        remove(x);

        appears[y].erase(idx);
        insert(y);

        appears[x].insert(idx);
        insert(x);

        assert(matches <= n-1);
        last[idx] = x;
        print_ans();
    } 
}

int main () {
	fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}


	return 0;
}

