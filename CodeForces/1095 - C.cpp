#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli potenciaCercana(lli n)
{
	lli size= log2(n);
	return pow(2,size);
}

int main()
{
	lli n, k;
	cin>>n>>k;
	lli aux = n;
	priority_queue<lli> q;
	lli ultimo;
	do
	{
		ultimo = potenciaCercana(aux);
		aux = aux-ultimo;
		if (ultimo!=0)
		{
			q.push(ultimo);	
		}
		
	}while(ultimo!=0);
		
	if (q.size() > k)
	{
		cout<<"NO\n";
		return 0;
	}
	
	
	do
	{
		if (q.size()==k)	
		{	
			if (q.top()==0)
			{
				cout<<"NO\n";
				return 0;
			}
			cout<<"YES\n";
			while(!q.empty())
			{
				cout<<q.top()<<" ";
				q.pop();
			}
			return 0;
		}	
		lli numero = q.top();
		q.pop();
		if (numero/2 != 0)
		{
			q.push(numero/2);
			q.push(numero/2);	
		}
		else
		{
			if (q.size()!=k)
			{
				cout<<"NO\n";
				return 0;
			}
		}
		
	}while(q.size()<=k);
	
	
		
	return 0;
}
