#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	string memory;
	lli cantidad, moves, countA=0, countB=0, best=0;
	cin>>cantidad>>moves;
	lli j=0, i=1;
	cin>>memory;
	memory='1' + memory;
	while((i<=cantidad))
	{
		if (memory[i] =='a')
		{
			countA++;
		}
		else if (memory[i] =='b')
		{
			countB++;
		}
		
		if ((moves>=countA)or(moves>=countB))
		{
			best=max(i-j, best);
			i++;
		}
		else
		{
			while((moves<countA)and(moves<countB))
			{
				j++;
				if (memory[j]=='a')
				{
					countA--;
				}
				else if (memory[j]=='b')
				{
					countB--;
				}
			}
			best=max(i-j, best);
			i++;
		}
	}
	cout<<best<<endl;
	return 0;
}
