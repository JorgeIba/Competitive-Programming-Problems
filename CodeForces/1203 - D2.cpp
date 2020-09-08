#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	string s, t;
	cin>>s>>t;
	lli arreglo[t.length()][2];
	memset(arreglo, 0, sizeof(arreglo));
	lli j=0;
	for(lli i=0; i<s.length(); i++)
	{
		if( s[i] == t[j] )
		{
			arreglo[j][0] = i;
			j++;
			if(j == t.length())
			{
				break;
			}
		}
	}
	
	/*
	for(int i=0; i<t.length(); i++)
	{
		cout<<arreglo[i][0]<<" ";
	}*/
	
	j = t.length()-1;
	for(lli i = s.length()-1; i>=0; i--)
	{
		if(s[i]==t[j])
		{
			arreglo[j][1] = i;
			j--;
			if(j==-1)
			{
				break;
			}
		}
	}
	
	/*
	for(int i=0; i<t.length(); i++)
	{
		cout<<arreglo[i][1]<<" ";
	}
	cout<<endl;
	*/
	j = t.length()-1;
	lli aux1 = s.length() - arreglo[j][0]-1;
	lli aux2 = arreglo[0][1];
	//cout<<aux1<<" "<<aux2<<endl;
	lli res = max( aux2, aux1);
	
	for(int i=1; i<t.length(); i++)
	{
		lli temp1 = arreglo[i-1][0];
		lli temp2 = arreglo[i][1];
		res = max( res,  temp2-temp1 - 1 );
		
	}
	
	cout<<res<<endl;
	
	return 0;
}
