#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
#define endl '\n'
#define lli long long int
#define ld long double
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())
#define debugg(x) cerr << #x << " = " << x << endl;
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forr(i, a, b) for(int i = (a); i <= (b); i++)

using namespace __gnu_pbds;
using namespace std;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

vector<int> find_order(const vector<int> &perm){
    int n = SZ(perm);
    ordered_set<int> s;
    forn(i, n) s.insert(i);


    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        int x = perm[i];
        int order = s.order_of_key(x);
        ans[i] = order;

        s.erase(s.find(x));
    }

    return ans;
}


vector<int> get_perm_by_order(const vector<lli> &order){
    int n = SZ(order);
    ordered_set<int> s;
    forn(i, n) s.insert(i);

    vector<int> perm(n);

    for(int i = 0; i < n; i++){
        int ord = order[i];
        perm[i] = *s.find_by_order(ord);

        s.erase(s.find(perm[i]));
    }

    return perm;
}


int main () {
	//fastIO();

    int n; cin>>n;
    vector<int> perm_1(n), perm_2(n);

    for(auto &x: perm_1) cin>>x;
    for(auto &x: perm_2) cin>>x;
    
    auto order_1 = find_order(perm_1);
    auto order_2 = find_order(perm_2);

    vector<lli> next_order(n);
    for(int i = n-1, j = 0; i >= 0; i--, j++){
        lli val = next_order[i] + order_1[i] + order_2[i];

        lli val_next = val / (j+1);
        lli val_curr = val - val_next*(j+1);
        next_order[i] = val_curr;

        if(i > 0) { 
            next_order[i-1] += val_next;
        }
    }

    auto ans = get_perm_by_order(next_order);

    for(auto x: ans) cout << x << " ";
    cout << endl;


	return 0;
}

