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


const int maxN = 410;
const int maxC = 160010;

//13
const lli maxF = 3*maxN;
const lli MOD = 998244353; // Initialize
vector<lli> fact(maxF+1, 1), inv(maxF+1, 1), invFact(maxF+1,1);
void prec()
{
    for(lli i = 2; i <= maxF; ++i){
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = inv[i]*invFact[i-1]%MOD;
	}
}

int nCr(lli n, lli r) {
    if(n < 0 || r > n || r < 0) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}


int n;
int mat[maxN][maxN];
int matMap[maxN][maxN];
vector<pair<int,int>> indices[maxC];
int fr[maxC];
bitset<maxC> is_big;


bool is_inside(int x, int y){
    if(x < 1 || x > n || y < 1 || y > n) return false;
    return true;
}

int dp[maxN][maxN][maxN];
lli f(int x, int y, int color) {
    if(!is_inside(x, y)) return 0;

    if(dp[x][y][color] != -1) return dp[x][y][color];

    lli ans = 0;
    if(matMap[x][y] == color) ans++;

    lli ret = ans + f(x, y+1, color) + f(x+1, y, color);
    while(ret >= MOD) ret -= MOD;

    return dp[x][y][color] = ret;
}


const int THRESHOLD = 450;


int main () {
	fastIO();
    prec();

    cin>>n;

    forr(i, 1, n){
        forr(j, 1, n){
            cin>>mat[i][j];
            fr[  mat[i][j]  ]++;
        }
    }
        
    forr(i, 1, n)
        forr(j, 1, n)
            if(fr[mat[i][j]] > THRESHOLD)
                is_big[(mat[i][j])] = true;


    map< int, int > mapp;
    auto mapping = [&](int color) {
        if(!mapp.count(color))
            mapp[color] = SZ(mapp);
        return mapp[color];
    };

    forr(i, 1, n){
        forr(j, 1, n){
            if(is_big[(mat[i][j])]) 
                matMap[i][j] = mapping(mat[i][j]);
            else 
                matMap[i][j] = -1;      
        }
    }

    memset(dp, -1, sizeof(dp));

    lli ans = 0;
    forr(i, 1, n){
        forr(j, 1, n) {
            if(matMap[i][j] != -1) {
                ans += f(i, j, matMap[i][j]);
                if(ans >= MOD) ans -= MOD;
            }
        }
    }    

    forr(i, 1, n){
        forr(j, 1, n){
            if(!is_big[(mat[i][j])])
                indices[mat[i][j]].push_back({i, j});
        }
    }

    auto get_ways = [&](int x, int y) {
        return nCr(x+y, x);
    };

    forn(i, maxC) {
        lli ret = 0;
        for(int j = 0; j < SZ(indices[i]); j++) {
            auto [x_i, y_i] = indices[i][j];
            for(int k = j; k < SZ(indices[i]); k++){
                auto [x_j, y_j] = indices[i][k];

                ret += get_ways(x_j - x_i, y_j - y_i);
                if(ret >= MOD) ret -= MOD;
            }
        }

        ans += ret;
        if(ans >= MOD) ans -= MOD;
    }

    cout << ans << endl;



	
	return 0;
}

