#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n;
	cin>>n;	
	lli colas[n][2];
	lli aux, mini=1000000100, res=0;
	for(int i=0; i<n; i++)
	{
		cin>>colas[i][0];
	
		if(colas[i][0] - i <=0)
		{
			cout<<i+1<<endl;
			return 0;
		}
		else
		{
			if ((colas[i][0]-i)%n ==0)
			{
				colas[i][1]= (colas[i][0]-i)/n ;
			}
			else
			{
				colas[i][1]= (colas[i][0]-i)/n + 1 ;
			}
		}
		if (mini > colas[i][1])
		{
			mini =colas[i][1];
			res=i+1;
		}
	}
	cout<<res<<endl;
		

	
	return 0;
}
