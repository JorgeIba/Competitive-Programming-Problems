#include <bits/stdc++.h>
#define lli long long int
using namespace std;

vector< pair<lli, string> > jugos1;
vector< pair<lli, string> > jugos2;
vector< pair<lli, string> > jugos3;

void checar1()
{
	for (int i=0; i<jugos1.size(); i++)
	{
		
	}
}



int main()
{
	lli canJugos;
	cin>>canJugos;
	
	
	for (int i=0; i<canJugos; i++)
	{
		lli precio;
		string jugo;
		cin>>precio>>jugo;
		
		if (jugo.length()==1)
		{
			jugos1.push_back( make_pair(precio,jugo) );	
		}
		else if ((jugo.length())==2)
		{
			jugos2.push_back( make_pair(precio,jugo) );
		}
		else
		{
			jugos3.push_back( make_pair(precio,jugo) );
		}
	}
	sort(jugos1.begin(),jugos1.end());
	sort(jugos2.begin(),jugos2.end());
	sort(jugos3.begin(),jugos3.end());
	
	
	
	return 0;
}

