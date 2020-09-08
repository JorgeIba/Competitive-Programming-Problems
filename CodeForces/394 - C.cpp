#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n,m, ccu=0, cuu=0, ccc=0;
	bool flag=true;
	cin>>n>>m;
	string aux;
	for (int i=0; i<n*m; i++)
	{
		cin>>aux;
		if ((aux=="10")or(aux=="01"))
		{
			ccu++;
		}
		else if(aux=="00")
		{
			ccc++;
		}
		else
		{
			cuu++;
		}
	}
	
	for (int i=0; i<n; i++)
	{
		aux.clear();
		for (int j=0; j<m; j++)
		{
			if (cuu!=0)
			{
				aux+="11 ";
				cuu--;
			}
			else if ((cuu==0)and(ccu!=0))
			{
				aux+="10 ";
				ccu--;
			}
			else if ((cuu==0)and(ccu==0)and(ccc!=0))
			{
				aux+="00 ";
				ccc--;
			}
		}
		if (i%2==0)
		{
			cout<<aux<<endl;
		}
		else
		{
			aux.resize( aux.length() -1 );
			reverse(aux.begin(), aux.end());
			cout<<aux<<endl;
		}

		
	}
	
	return 0;
}
