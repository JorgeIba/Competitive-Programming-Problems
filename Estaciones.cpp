#include <bits/stdc++.h>
using namespace std;

int main()
{
	long long int n;
	cin>>n;
	if ((n==12)or(n==1)or(n==2))
	{
		cout<<"INVIERNO\n";
	}
	else if ((n==3)or(n==4)or(n==5))
	{
		cout<<"PRIMAVERA\n";
	}
	else if ((n==6)or(n==7)or(n==8))
	{
		cout<<"VERANO\n";
	}
	else if ((n==9)or(n==10)or(n==11))
	{
		cout<<"OTONIO\n";
	}
	else
	{
		cout<<"ERROR \n";
	}
	return 0;
}
