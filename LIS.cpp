#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli dp[1005][1005];
lli A[1005];
int contador=0;
lli t;
lli conta=0;

lli funcionB(lli indice, lli anterior)
{
	if (indice>=contador+1) return 0;
	
	if (dp[indice][anterior]!=-1)
	{
		return dp[indice][anterior];
	}
	
	if (A[indice] > A[anterior])
	{
		int si = 1 + funcionB(indice + 1, indice);
		int no = funcionB(indice + 1, anterior);
		return dp[indice][anterior] = max(si,no);
	}
	
	return dp[indice][anterior] = funcionB(indice + 1, anterior);
}


void recLis(lli indice, lli anterior, vector<lli> &respuesta1)
{
	if (indice>=contador+1) return;
	
	if (A[indice] > A[anterior])
	{
		lli si = 1 + funcionB(indice + 1, indice);
		lli no = funcionB(indice + 1, anterior);
		if(si>no)
		{
			respuesta1.push_back(A[indice]);
			recLis(indice+1, indice, respuesta1);
		}
	}
	recLis(indice+1, anterior, respuesta1);
}



void funcion1(int indice)
{
	memset(dp, -1, sizeof(dp));
	memset(A, -1, sizeof(A));
	vector<lli> respuesta1;
	string TAux;
	contador=1;
	while(getline(cin,TAux)and(!TAux.empty()))
	{
			A[contador]=stoi(TAux);
			contador++;
	}
	lli res= funcionB(1,0);
	cout<<"Max hits: "<<res<<endl;
	recLis(1,0, respuesta1);
	for (lli i=0; i<res; i++)
	{
		cout<<respuesta1[i]<<endl;
	}
	if (indice+1 !=t)
	{
		cout<<endl;	
	}
	return;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	string aux;
	getline(cin, aux);
	getline(cin, aux);
	for (lli i=0; i<t; i++)
	{
		funcion1(i);
	}
	return 0;
}

