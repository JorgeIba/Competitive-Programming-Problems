#pragma GCC optimize("O3,unroll-loops")
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

const int INF = 1e9;
const int MAXN = 1e6 + 100;
int is[MAXN], js[MAXN];

void main_(){
    int n, m; cin>>n>>m;

    int mat[n][m];
    forn(i, n){
        forn(j, m){
            cin>>mat[i][j];
        }
    }

    forn(i, n){
        forn(j, m){
            is[ mat[i][j] ] = i;
            js[ mat[i][j] ] = j;
            // pos[ mat[i][j] ] = {i, j};
        }
    }
    
    auto check = [&](int mex){
        vector< pair<int,int> > points(mex);

        forn(i, mex) {
            points[i] = {js[i], is[i]};
        }
        sort(all(points));

        // for(auto [x, y]: points) cout << x << ", " << y <<endl;

        int max_height = -INF;
        for(int i = 0; i < mex; ){
            int max_y = -INF;
            int j = i;
            // cout << i << ": " << endl;
            while(j < mex && points[i].first == points[j].first){
                // cout << j << " ---- " << points[j].second << " -- " << max_height << endl;
                if(points[j].second < max_height) return false;
                max_y = max(max_y, points[j].second);

                j++;
            }
            
            // debugg(max_y);
            max_height = max(max_height, max_y);

            i = j;
        }

        return true;
    };


    int l = 0, r = n*m, ans = 0; 
    while(l <= r){
        int mid = (l + r) / 2;
        if(check(mid)){
            ans = mid;
            l = mid+1;
        } else{
            r = mid-1;
        }
    }

    cout << ans << endl;
}

int main () {
	fastIO();
	
	int t = 1;
	cin>>t;
	
	while(t--) main_();


	return 0;
}

