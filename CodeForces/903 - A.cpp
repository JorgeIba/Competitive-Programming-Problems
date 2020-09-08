#include <bits/stdc++.h>

#define lli long long int
using namespace std;


bool sepuede[1000];

void inicializar()
{
	for (int i=1; i<=100; i++)
	{
		sepuede[i*3]=true;
		sepuede[i*7]=true;
		for (int j=1; j<=100; j++)
		{
			sepuede[i*3 + j*7]=true;
		}
	}
	
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int casos;
	int test;
	cin>>casos;
	inicializar();
	for (int i=0; i<casos; i++)
	{
		cin>>test;
		if (sepuede[test])
		{
			cout<<"YES\n";
		}
		else
		{
			cout<<"NO\n";
		}
	}
	
	
	return 0;
}
