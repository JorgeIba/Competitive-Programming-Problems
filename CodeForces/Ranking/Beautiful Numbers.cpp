#include <bits/stdc++.h>
#define lli long long int
#define MOD 1000000007

using namespace std;

lli factorial[1000001];
lli inverso[1000001];
lli a,b;

lli BinPower(lli a, lli b) //a^b
{
	lli res=1;
	a=a%MOD;
	while(b)
	{
		if(b&1) 
		{
			res = res*a%MOD;
		}
		b>>=1;
		a=a*a%MOD;
	}
	return res;
}



void inicializar()
{
	factorial[0]=1;
	for(int i=1; i<1000000; i++)
	{
		factorial[i] = i*factorial[i-1]%MOD;
		inverso[i] = BinPower(factorial[i], MOD-2)%MOD;
	}
}

lli Permutacion(lli n, lli x)
{
	return (factorial[n]/(inverso[n-x]*inverso[x]));
}

bool checar(lli n)
{
	if(n==0)
	{
		return false;
	}
	while(n>0)
	{
		lli res = n%10;
		n/=10;
		if((res!=a)and(res!=b))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	inicializar();
	lli n;
	cin>>a>>b>>n;
	lli aux = min(a,b);
	a = max(a,b);
	b = aux; // a -> maximo, b -> minimo
	lli total = b*n;
	lli diff = a-b;
	lli suma=0;
	
	for(int i=0; i<=n; i++)
	{
		lli sumDigits = total%9;
		cout<<total<<" "<<sumDigits<<" "<<checar(sumDigits)<<endl;
		if( checar(sumDigits)  )
		{
			//cout<<"I'm here\n";
			suma+= Permutacion(n,i);
		}

		total = total + diff;
	}
	
	cout<<suma%MOD<<endl;
	
	
	return 0;
}
