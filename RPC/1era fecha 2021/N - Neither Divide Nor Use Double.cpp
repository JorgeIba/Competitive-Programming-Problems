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


typedef complex<ld> cd;
const ld PI = acos(-1);

int nearestPowerTwo(int n)
{
    int r = 1;
    while(r < n) r<<=1;
    return r;
}

void fft(vector<cd> &A, bool inv)
{
    int n = SZ(A);
    for(int i = 1, j = 0; i < n - 1; i++){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(A[i], A[j]);
	}
    
    vector< cd > w(n>>1);

    for(int k = 2; k<=n; k<<=1)
    {
        cd w1 = polar((ld)1, (inv?-1:1) * 2 * PI / k) ;
        w[0] = 1;
        for(int j = 1; j<k>>1; j++)
            w[j] = w[j-1]*w1;

        for(int i = 0; i<n; i+=k)
        {
            for(int j = 0; j<k>>1; j++)
            {
                cd u = A[i+j], v = A[i+j+(k>>1)] * w[j];
                A[i+j] = u + v;
                A[i+j+(k>>1)] = u - v;
            }
        }
    }
    if(inv)
        for(auto &x: A) x/=n;
}

string normalize(VLL &v)
{
    string ss;
    int carry =0;
    for(int i = SZ(v)-1; i>=0; i--)
    {
        v[i] += carry;
        carry = v[i] / 10;
        v[i] %= 10;
    }

    if(carry>0)
        ss+=(carry+'0');
    for(auto x: v) ss+=(x+'0');
    return ss;
}

string multiply_numbers(string &s1, string &s2)
{
    int degree = s1.length() + s2.length() - 1;
    int sz = nearestPowerTwo(degree);   
    if(s1 == "0" || s2 == "0") return "0";

    vector<cd> FA(sz), FB(sz);
    for(int i = 0; i<(int)s1.length(); i++) FA[i] = (s1[i] - '0');
    for(int i = 0; i<(int)s2.length(); i++) FB[i] = (s2[i] - '0');

    fft(FA, false);
    fft(FB, false);

    for(int i = 0; i<sz; i++)
    {
        FA[i]*=FB[i];
    }
    fft(FA, true);
    VLL ans(degree);
    for(int i = 0; i<degree; i++)
    {
        ans[i] = (lli)(round(FA[i].real()));
    }

    return normalize(ans);
}


string binPow(string a, lli b)
{
    string res = "1";
    while(b)
    {
        if(b&1) res = multiply_numbers(res, a);
        b>>=1;
        a = multiply_numbers(a,a);
    }
    return res;
}


map<lli,lli> factors;

void getFactors(lli n)
{
    factors.clear();
    for(lli i = 2; i*i<=n; i++)
    {
        while(n % i == 0)
        {
            factors[i]++;
            n /= i;
        }
    }
    if(n>1) factors[n]++;
}

int main () {
	fastIO();

    lli a, n;

    while(cin>>a>>n)
    {
        if(n == 0)
        {
            cout << 0 << " " << 1 << endl;
            continue;
        }
        getFactors(a);
        bool periodic = false;
        for(auto x: factors)
        {
            if(x.first != 2 && x.first != 5) periodic = true;
        }

        if(periodic)
        {
            cout << "Precision Error" << endl;
            continue;
        }

        lli m = max(factors[2]*n, factors[5]*n);

        string choose;
        lli pot;

        if(factors[2] > factors[5]){
            choose = "5";
            pot = factors[2] - factors[5];
        }
        else{
            choose = "2";
            pot = factors[5] - factors[2];
        }

        //cout << choose << " " << pot << endl;
        cout << m << " " << binPow(choose, pot*n) << endl;
    }  
	return 0;
}