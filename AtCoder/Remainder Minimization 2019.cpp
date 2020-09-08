#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	long long int L,R, divL, divR;
	long long int minimo=2018, temp=0;
	
	cin>>L>>R;
	
	divL=(int) ((L-1)/2019);
	divR=(int) (R/2019);
	
	L=L%2019;
	R=R%2019;
	
	if (divL != divR)
	{
		cout<<0<<endl;
		return 0;
	}
	
	for (int i=L; i<R; i++)
	{
		for ( int j=i+1; j<=R; j++)
		{
			temp=(i*j)%2019;
			minimo=min(minimo,temp);
		}
	}
	cout<<minimo<<endl;
	return 0;
}
