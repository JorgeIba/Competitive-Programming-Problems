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

const int maxN = 1e7;


bool is_permutation(lli num, lli phi)
{
    string phi_s = to_string(phi);
    string num_s = to_string(num);
    vector<char> fr_phi(10);
    vector<char> fr_num(10);

    for(auto c: phi_s) fr_phi[c-'0']++;
    for(auto c: num_s) fr_num[c-'0']++;

    return fr_num == fr_phi;
}

int main () {
	//fastIO();
    phiSieve(maxN);
    
    auto ans = Fract(1e9, 1);
    for(lli i = 2; i<maxN; i++)
    {
        if( is_permutation(i, Phi[i]) )
            ans = min(ans, Fract(i, Phi[i]));
    }

    cout << ans.num << endl;    
	
	return 0;
}

