#include <bits/stdc++.h>
#define lli long long int
using namespace std;

deque<lli> conver;
set<lli> numeros;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lli k, m;
	cin>>k>>m;
		
	for (lli i=0; i<k; i++)
	{
		lli aux;
		cin>>aux;
		if (numeros.find(aux)!=numeros.end())
		{
			//cout<<"ASD "<< aux<<" ";
			continue;
		}
		if (conver.size() == m)
		{
			numeros.erase( conver.front()  );
			conver.pop_front();
			conver.push_back(aux);
		}
		else
		{
			conver.push_back(aux);
		}
		numeros.insert(aux);
	}
	cout<<(lli)(conver.size())<<endl;
	while(!conver.empty())
	{
		cout<<conver.back()<<" ";
		conver.pop_back();
	}
	
	
	
	return 0;
}
