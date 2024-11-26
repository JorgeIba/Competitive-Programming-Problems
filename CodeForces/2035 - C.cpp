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
    int n; cin>>n;
    
    auto score = [&](vector<int> perm) {
        int k = 0;
        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) {
                // cout << "AND: " << perm[i] << endl;
                k = k & perm[i];
            } else {
                // cout << "OR: " << perm[i] << endl;
                k = k | perm[i];
            }
        }
        return k;
    };

    auto fill = [&](vector<int> perm) {
        set<int> cnt(all(perm));
        forr(i, 1, n) {
            if(cnt.count(i)) continue;
            perm.push_back(i);
            cnt.insert(i);
        }
        return perm;
    };


    if(n % 2 == 1) {
        vector<int> perm = {n, n-1, 3, 1};
        perm = fill(perm);
        reverse(all(perm));

        cout << score(perm) << endl;
        for(auto x: perm) cout << x << " ";
        cout << endl;
        return;
    }


    int lg = 31 - __builtin_clz(n);
    int sec = 0;
    forn(i, lg) {
        if(!(n & (1 << i))) {
            sec |= (1 << i);
        }
    }

    int third = sec - 1;

    if(sec == 3) {
        vector<int> perm = {n, 3, 1, 2, 6};
        perm = fill(perm);
        reverse(all(perm));

        cout << score(perm) << endl;
        for(auto x: perm) cout << x << " ";
        cout << endl;

        return;
    } else if(sec == 1) {
        vector<int> perm = {n, 1, 3};
        perm = fill(perm);
        reverse(all(perm));
        
        cout << score(perm) << endl;
        for(auto x: perm) cout << x << " ";
        cout << endl;
        return;
    }

    // cout << bitset<10>(n).to_string() << endl;
    // cout << bitset<10>(sec).to_string() << endl;
    // cout << bitset<10>(third).to_string() << endl;

    assert(sec < n);
    assert(third < n);
    assert(sec != third);

    vector<int> perm = {n, sec, third, 3, 1};
    perm = fill(perm);
    reverse(all(perm));

    cout << score(perm) << endl;
    for(auto x: perm) cout << x << " ";
    cout << endl;
}

int main () {
	// fastIO();

	int t = 1;
	cin>>t;

	while(t--) {
		main_();
	}

	return 0;
}




