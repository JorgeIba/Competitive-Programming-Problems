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

vector<int> Phi;
void phiSieve(int n)
{
	Phi.resize(n + 1);
	for(int i = 1; i <= n; ++i) Phi[i] = i;
	for(int i = 2; i <= n; ++i)
		if(Phi[i] == i)
			for(int j = i; j <= n; j += i)
				Phi[j] -= Phi[j] / i;
}

struct Fract{
    lli num, den;
    Fract(lli num, lli den): num(num), den(den) {}

    bool operator<(const Fract &F)const { return num*F.den < den*F.num; }
};

const int maxN = 1e6;

int main () {
	//fastIO();
    phiSieve(maxN);

    auto ans = Fract(6, 2);
    for(lli i = 1; i<=maxN; i++)
    {
        ans = max(ans, Fract(i, Phi[i]));
    }

    cout << ans.num << endl;

	
	return 0;
}

