#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define i128 __int128
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


unsigned long long mulMod( unsigned long long a,
                            unsigned long long b,
                            unsigned long long m){

    unsigned long long res = 0, tmp = a % m;

    while (b)
    {
        if (b & 1)
        {
            res = res + tmp;
            res = (res >= m ? res - m : res);
        }
        b >>= 1;
        tmp <<= 1;
        tmp = (tmp >= m ? tmp - m : tmp);
    }

    return res;
}

long long powMod(long long a, long long b, long long m){
    long long res = 1 % m, tmp = a % m;
    while (b)
    {
        if (b & 1)
        {
            //res = (res * t) % m;
            res = mulMod(res, tmp, m);
        }
        //t = t * t % m;
        tmp = mulMod(tmp, tmp, m);
        b >>= 1;
    }
    return res;
}

bool millerRabin(long long n){
    int a[5] = { 2, 3, 7, 61, 24251 };

    if (n == 2) return true;
    if (n == 1 || (n & 1) == 0) return false;

    long long b = n - 1;

    for (int i = 0; i < 5; i++)
    {
        if (a[i] >= n) break;

        while ((b & 1) == 0) b >>= 1;

        long long t = powMod(a[i], b, n);

        while (b != n - 1 && t != 1 && t != n - 1){
            t = mulMod(t, t, n);
            b <<= 1;
        }

        if (t == n - 1 || (b & 1)) continue;
        else return false;
    }
    return true;
}

long long gcd(long long a, long long b){
    while (b > 0){
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long pollard_rho(long long n){

    long long x = 2 % n, y = x, k = 2, i = 1;
    long long d = 1;

    while (true)
    {
        i++;
        x = (mulMod(x, x, n) + 1) % n;
        d = gcd((y - x + n) % n, n);

        if (d > 1 && d < n)
        {
            return d;
        }

        if (y == x)
        {
            long long d = 2;
            while (n % d) d++;
            return d;
        }

        if (i == k)
        {
            y = x;
            k <<= 1;
        }
    }
}


map<lli,lli> fact[1005];

void _factorize(long long n, int idx){
    if (n <= 1) return;

    if (millerRabin(n)){
        fact[idx][n]++;
        return;
    }

    long long d = pollard_rho(n);
    _factorize(d, idx);
    _factorize(n / d, idx);
}

void factorizePollardRho(long long n, int idx)
{
    _factorize(n, idx);
}


lli m, n, k;
vector<lli> nums;

void getFactors()
{
    int n = SZ(nums);
    for(int i = 0; i<n; i++)
    {
        factorizePollardRho(nums[i], i);
    }
}


int main () {
	fastIO();
    cin>>m>>n>>k;
    nums.resize(n);
    for(int i = 0; i<n; i++) cin>>nums[i];

    vector<lli> ans(m);
    getFactors();

    vector< vector<lli> > adjList(n);

    for(int i = 0; i<k; i++)
    {
        lli u, v, c; cin>>u>>v>>c; u--,v--;
        adjList[v].push_back(u);
    }

    for(int i = 0; i<n; i++)
    {
        sort(all(adjList[i]));
    }

    for(int i = 0; i<n; i++)
    {
        int j = 0;
        for(auto v: fact[i])
        {
            int u = adjList[i][j++];
            ans[u] = v.first;
        }
    }

    for(auto x: ans) cout << x << " ";
    cout << endl;
    /*
    for(int i = 0; i<n; i++)
    {
        for(auto v: fact[i])
        {
            cout << v.first << " ";
        }
        cout << endl;
    }
    */
    
	return 0;
}