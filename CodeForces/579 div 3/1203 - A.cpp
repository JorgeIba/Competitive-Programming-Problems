#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
 
void funcion()
{
	lli n, posFinal, posUno, numero;
	vector<lli> vec;
	bool flag1=false;
	bool flag2=true;
	cin>>n;
	for (int i=1; i<=n; i++ ) // O(n)
	{
		cin>>numero; // O(cnt)
		vec.push_back(numero); //O(cnt)
		if (numero==n)
		{
			posFinal=i;
		}
		if (numero==1)
		{
			posUno=i;
		}

		// O(cnt)
	}
	
	if (((posUno==1)and(posFinal==n))or((posUno==n)and(posFinal==1)))
	{
		flag1=true;
	}
	
	for (int i=0; i<n-1; i++) // O(n)
	{
		if ((vec[i]==1)and(flag1==false))
		{
			if (vec[i-1]==n)
			{
				flag1=true;
			}
			if(vec[i+1]==n)
			{
				flag1=true;
			}
		}
		
		else if ((vec[i]==n)and(flag1==false))
		{
			if (vec[i-1]==1)
			{
				flag1=true;
			}
			else if(vec[i+1]==1)
			{
				flag1=true;
			}
		}
		
		else if ((vec[i+1]!=n)or(vec[i+1]!=1))
		{
			
			if ( abs(vec[i]-vec[i+1]) !=1 )
			{
				flag2=false;
			}
		}
	}
 
	
	
	if ((flag1)and(flag2))
	{
		cout<<"YES\n";
	}
	else
	{
		cout<<"NO\n";
	}
	
	
}
 
 
int main()
{
	lli q;
	cin>>q;
	for (int i=0; i<q; i++)
	{
		funcion();
	}
	return 0;
}
