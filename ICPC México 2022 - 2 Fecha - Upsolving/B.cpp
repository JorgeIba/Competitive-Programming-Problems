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


set<lli> palis;
string getBinary(lli n) {
    string ans;
    while(n > 0) {
        if(n % 2 == 0) {
            ans += '0';
        } else {
            ans += '1';
        }
        n /= 2;
    }
    reverse(all(ans));
    return ans;
}

const lli MAX = (1<<16);
void prec(){
    
    for(int i = 1; i <= MAX; i++) {
        string binary = getBinary(i);
        string r_binary = binary;
        reverse(all(r_binary));

        string pal1 = binary + r_binary;
        string pal2 = binary + '1' + r_binary;
        string pal3 = binary + '0' + r_binary;

        palis.insert( bitset<33>(pal1).to_ullong()   );
        palis.insert( bitset<33>(pal2).to_ullong()   );
        palis.insert( bitset<33>(pal3).to_ullong()   );
    }
    palis.insert(1);
}


int main () {
	fastIO();

    prec();

    lli q; cin>>q;

    vector<lli> palis_v(all(palis));

    while(q--) {
        lli l, r; cin>>l>>r;

        auto idx_r = upper_bound(all(palis_v), r) - palis_v.begin();
        auto idx_l = upper_bound(all(palis_v), l-1) - palis_v.begin();

        cout << idx_r - idx_l << endl;
    }

	return 0;
}

