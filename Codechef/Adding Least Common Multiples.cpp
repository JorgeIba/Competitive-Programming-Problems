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

const uint32_t MOD = (1<<30);

uint32_t g(uint32_t p, uint32_t a)
{
    if(a == 1)
    {
        return (1-p);
    }
    else if(a == 2)
    {
        return (-p);
    }
    return 0;
}

vector<uint32_t> sieveMulFunction(lli n)
{
    vector<uint32_t> primes, lp(n+1), f(n+1), cnt(n+1), pot(n+1);
    f[1] = 1;
    for(uint32_t i = 2; i<=n; i++){
        if(!lp[i]){
            lp[i] = pot[i] = i; cnt[i] = 1;
            f[i] = g(i,1);
            primes.push_back(i);
        }
        for(auto p: primes){
            uint32_t d = i*p;
            if(d>n) break;
            lp[d] = p;
            if(p == lp[i]){ // lowestPrime[i] == p
                f[d] = f[ i/pot[i] ] * g(p,cnt[i]+1);
                pot[d] = pot[i]*p;
                cnt[d] = cnt[i]+1;
                break;
            }
            else{ //Coprimes
                f[d] = f[i]*f[p];
                pot[d] = p;
                cnt[d] = 1;
            }
        }
    }
    for(uint32_t i = 1; i<=n; i++)
        f[i] = f[i-1] + f[i]*i;
    return f;
}


const int maxN = 4e6 + 5;

uint32_t gauss(uint32_t n)
{
    return n*(n+1)/2;
}

template<class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool flag = 0;
    while (!isdigit(c)) {
        if (c == '-')
            flag = 1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    x = flag ? -x : x;
}

template<class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x >= 10)
        write(x / 10);
    putchar(x % 10 + '0');
}

int main () {
	//fastIO();
    //time_t begin = clock();
    auto prefix = sieveMulFunction(maxN);
    //cout << (double)(clock() - begin)/(CLOCKS_PER_SEC) << endl;

    int T; read(T);
    while(T--)
    {
        int a, b; read(a), read(b);
        if(a>b) swap(a,b);
        lli ans = 0;
        for(int i = 1, r; i<=min(a,b); i = r + 1)
        {
            int la = a/i, ra = a/la;
            int lb = b/i, rb = b/lb;
            r = min(ra, rb);
            ans += (prefix[r] - prefix[i-1]) * gauss(la) *gauss(lb);
        }
        write(ans & (MOD - 1));printf("\n");
    }
	return 0;
}