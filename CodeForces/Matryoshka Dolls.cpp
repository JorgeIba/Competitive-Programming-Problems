#include <bits/stdc++.h>
using namespace std;

int main()
{
	int contador=0;
	int n,x;
	cin>>n>>x;
	while(n!=0)
	{
		n=(int)(n/x);
		contador++;
	}
	cout<<contador<<endl;
	
	return 0;
}
