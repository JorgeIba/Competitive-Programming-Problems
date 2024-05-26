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

const int SZ_BLOCK = 900;
const int MAXN = 5e5+SZ_BLOCK+1;
const int BLOCKS = MAXN / SZ_BLOCK;

int dragons[MAXN], best_block[BLOCKS], lazies[MAXN];
vector<int> updates_block[BLOCKS];


void push(int block){
    if(updates_block[block].empty()) return;

    int m = SZ(updates_block[block]);
    for(int i = m-1; i >= 0; i--){
        auto upd_x = updates_block[block][i];
        lazies[upd_x] = lazies[upd_x+1];
    }

    int ans = 0;
    for(int i = SZ_BLOCK * block; i < SZ_BLOCK * (block+1); i++){
        dragons[i] = lazies[dragons[i]];
        ans = max(ans, dragons[i]);
    }

    for(auto upd_x: updates_block[block]){
        lazies[upd_x] = upd_x;
    }

    updates_block[block].clear();
    best_block[block] = ans;
}


void update(int l, int r, int x) {
    int block_l = l / SZ_BLOCK;
    int block_r = r / SZ_BLOCK;

    push(block_l);
    push(block_r);

    for(int i = l; i < SZ_BLOCK * (block_l+1) && i <= r; i++){
        if(dragons[i] == x) {
            dragons[i] = x+1;
            best_block[block_l] = max(best_block[block_l], x+1);
        }
    }

    for(int i = block_l+1; i < block_r; i++){
        if(best_block[i] == x)
            best_block[i] = x+1;
        
        updates_block[i].push_back(x);

        if(SZ(updates_block[i]) > 10*SZ_BLOCK)
            push(i);
    }

    for(int i = r; i >= SZ_BLOCK * (block_r) && i >= l; i--){
        if(dragons[i] == x) {
            dragons[i] = x+1;
            best_block[block_r] = max(best_block[block_r], x+1);
        }
    }
}




int query(int l, int r){

    int block_l = l / SZ_BLOCK;
    int block_r = r / SZ_BLOCK;

    push(block_l);
    push(block_r);

    int ans = 0;
    for(int i = l; i < SZ_BLOCK * (block_l+1) && i <= r; i++){
        ans = max(ans, dragons[i]);
    }

    for(int i = block_l+1; i < block_r; i++){
        ans = max(ans, best_block[i]);
    }

    for(int i = r; i >= SZ_BLOCK * (block_r) && i >= l; i--){
        ans = max(ans, dragons[i]);
    }

    return ans;
}


int main () {
	fastIO();

    for(int i = 0; i < MAXN; i++) lazies[i] = i;
	
    int n, q; cin>>n>>q;

    while(q--){
        int t, l, r; cin>>t>>l>>r;
        l--, r--;
        if(t == 1) {
            int x; cin>>x;
            update(l, r, x);
        } else{
            cout << query(l, r) << endl;
        }
    }

	return 0;
}

