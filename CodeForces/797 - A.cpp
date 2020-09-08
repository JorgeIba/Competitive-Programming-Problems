#include <bits/stdc++.h>
#define lli long long int
using namespace std;


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lli n, k;
	cin>>n>>k;
	priority_queue<lli> divisores;
	
	if (k==1)
	{
		cout<<n<<endl;
		return 0;
	}
	
	for (lli i=2; i*i<=n; i++)
	{
		if (n%i==0)
		{
			divisores.push(i);
			divisores.push(n/i);
			break;
		}
	}
	if (divisores.empty())
	{
		cout<<-1<<endl;
		return 0;
	}
	
	while (!divisores.empty())
	{
	//	cout<<divisores.top()<<" ";
		if (divisores.size() == k)	
		{
//			cout<<"Si entre alv\n";
			while(!divisores.empty())
			{
				cout<<divisores.top()<<" ";
				divisores.pop();
			}
			return 0;
		}
		
		
		
		lli top1 = divisores.top();
		divisores.pop();
		
		
		
	
		
		for (lli j=2; j*j<=top1; j++)
		{
			if ((top1%j==0)and( top1/j !=1))
			{
				divisores.push(j);
				divisores.push(top1/j);
				break;
			}
		}
		
//		priority_queue<lli> quePedo = divisores;
//		while(!quePedo.empty())
//		{
//			cout<<quePedo.top()<<" ";
//			quePedo.pop();
//		}
//		cout<<endl<<endl;	
	}
	cout<<-1<<endl;
	
	
	return 0;
}
