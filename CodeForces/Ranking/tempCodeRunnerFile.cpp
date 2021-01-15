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

const lli MOD = 1e9+7;
const lli inv2 = 500000004;

lli add(lli n, lli m)
{
	n = n%MOD, m = m%MOD;
	return n+m<MOD? n+m: n+m-MOD;
}

lli sub(lli n, lli m)
{
	n = n%MOD, m = m%MOD;
	return n-m<0? n-m+MOD: n-m;
}

lli mult(lli n, lli m)
{
	n = n%MOD, m = m%MOD;
	return (n*m)%MOD;
}


lli gauss(lli n)
{
	return mult(n, mult(n+1, inv2));
}


int main () {
	//fastIO();
	lli n, m; cin>>n>>m;
	lli suma = mult(n, m);

	m = min(n, m);

	lli quitar = 0;

	lli minValue = m;
	/*
	for(lli i = 1; i*i <= n; i++)
	{
		quitar = add(quitar, mult(n/i, i));
	}
	*/
	for(lli v = 1; v*v<=n; v++)
	{
		lli l = n/(v+1), r = n/v;
		r = min(r, m);
		if(l >= r) continue;
		minValue = min(l, minValue);
		lli aux = sub( gauss(r), gauss(l) );
		quitar = add(quitar, mult(aux, v));
	}

	for(lli i = 1; i <= minValue; i++)
	{
		quitar = add(quitar, mult(n/i, i));
	}
	//cout << quitar << endl;
	cout << sub(suma, quitar) << endl;


	return 0;
}
