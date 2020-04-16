#include <bits/stdc++.h>
#define long long int lli

using namespace std;


int posible[1000010];
int contador=0;

void inicializar(int n)
{
	vector<int> aux(n+1);
	for (int i=1; i<=n; i++)
	{
		cin>>aux[i];
	}
	for (int i=1; i<=n; i++)
	{
		posible[aux[i]]=aux[i+1];
	}
}

void solve(int n)
{
	int temp;
	int last;
	vector<int> pos;
	bool flag=true;
	while (flag)
	{
		flag=false;
		for (int i=1; i<=n; i++)
		{
			if ((i>posible[i]))
			{
				temp = posible[posible[i]];
				posible[posible[i]]=0;
				posible[i]=temp;
			}
		}
		contador++;
		for (int i=i; i<=n; i++)
		{
			if (posible[i]!=0)
			{
				pos.push_back(i);
			}
		}
		for (int i=pos.size()-1; i>=0; i--)
		{
			if ((pos[i]>posible[pos[i]])and(posible[pos[i]]!=0))
			{
				flag=true;
				break;
			}
		}
	}
}

int main()
{
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n,aux;
	cin>>n;
	inicializar(n);
	solve(n);
	cout<<contador<<endl;
	return 0;
}
