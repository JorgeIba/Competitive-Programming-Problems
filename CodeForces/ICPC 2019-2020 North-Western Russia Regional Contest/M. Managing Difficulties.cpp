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

void solve()
{
    int n; read(n);
    vector<int> nums(n);
    for(auto &x: nums) cin>>x;

    int ans = 0;
    unordered_map<int, int> fr;
    for(int j = 0; j<n; j++)
    {
        for(int k = j+1; k<n; k++)
        {
            ans += fr[ (nums[j]<<1) - nums[k] ];
        }
        fr[nums[j]]++;
    }

    write(ans);
    printf("\n");
}



int main () {
    lli t; read(t);
    while(t--) solve();
    
	return 0;
}