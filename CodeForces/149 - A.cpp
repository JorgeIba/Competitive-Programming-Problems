#include <bits/stdc++.h>
using namespace std;

int main()
{
	vector<int> meses(12);
	int acum=0, mes=0;
	int k;
	cin>>k;
	for (int i=0; i<12; i++)
	{
		cin>>meses[i];
	}
	
	sort(meses.rbegin(), meses.rend());
	
	for (int i=0; i<12; i++)
	{
		
		if(k==0)
		{
			cout<<0<<endl;
			return 0;
		}
		
		acum+=meses[i];
		mes++;
		
		if (acum>=k)
		{
			cout<<mes<<endl;
			return 0;
		}	
	}
	cout<<-1<<endl;
	
	return 0;
}
