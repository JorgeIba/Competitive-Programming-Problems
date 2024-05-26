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


int main () {
	//fastIO();
	

    int n, m; cin>>n>>m;
    vector<lli> L(n);
    for(auto &x: L) cin>>x;


    auto check = [&](lli w){
        lli lines = 1;
        lli pointer = 1;
        for(auto word: L){
            if(word > w) return false;

            // debugg(pointer);

            if(pointer > w) {
                pointer = 1;
                lines++;
            };

            if((word + pointer - 1) <= w){
                pointer = (word + pointer - 1);

                pointer+=2;
            } else {
                lines++;
                pointer = 1;
                pointer = (word + pointer - 1);
                pointer+=2;
            }
        }

        return lines <= m;
    };

    
    lli l = 1, r = 1e15, ans = r;

    while(l <= r){
        lli mid = (l+r) / 2;
        if(check(mid)){
            r = mid-1;
            ans = mid;
        } else {
            l = mid+1;
        }
    }

    cout << ans << endl;


	return 0;
}

