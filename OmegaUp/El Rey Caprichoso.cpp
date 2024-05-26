#pragma GCC optimize("O3,Ofast,unroll-loops,omit-frame-pointer,no-stack-protector")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt,sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,abm,mmx,avx,fma")
#pragma GCC option("arch=native", "no-zero-upper")
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
	fastIO();

    const int MAXA = 1e6+5;
    int n; cin>>n;

    bitset< MAXA > first, second;

    while(n--){
        int x; cin>>x;
        if(!first[x]) first[x].flip();
        else if(!second[x]) second[x].flip();
    }

    for(int d = MAXA-1; d; d--){
        int max_1 = 0, max_2 = 0;
        for(int j = d; j < MAXA; j += d) {
            if(first[j]) {
                if(j > max_1) {
                    max_2 = max_1;
                    max_1 = j;
                } else if(j > max_2) {
                    max_2 = j;
                }
            }
            if(second[j]) {
                if(j > max_1) {
                    max_2 = max_1;
                    max_1 = j;
                } else if(j > max_2) {
                    max_2 = j;
                }
            }
        }

        if(max_1 && max_2) {
            cout << (lli) max_1 / d * max_2 << endl;
            return 0;
        }
    }

	return 0;
}