#include <bits/stdc++.h>
 
#define endl '\n'
#define lli long long int
#define ld long double
#define forn(i,n) for (int i = 0; i < n; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define SZ(s) int(s.size())

using namespace std;

typedef vector<lli> VLL;
typedef vector<int> VI;


void print(deque<lli> dq)
{
	for(int i = 0; i<SZ(dq); i++)
	{
		cout << dq[i] << " ";
	}
	cout << endl;
}

int idx_move = 1;
stringstream ss;
int total_comer = 0;

void comer(deque<lli> &dq, int idx_diff) //comer del 0 al idx_diff
{
	lli maximum = -1;
	for(int i = 0; i<idx_diff; i++)
	{
		maximum = max(maximum, dq[i]);
	}

	//cout << maximum << " ME LLEVA TODA LA VRGA\n";

	lli start = -1, dir = 0;
	for(int i = 0; i<idx_diff; i++)
	{
		if(dq[i] == maximum)
		{
			if(i == 0) 
			{
				//cout << "Aqui llegue\n";
				if(dq[i+1] < maximum)
				{
					start = i;
					dir = 1;
				}
				//cout << "Aqui llegue " << start << endl;;
					
			}
			else if(i == idx_diff-1)
			{
				if(dq[i-1] < maximum)
				{
					start = i;	
					dir = -1;
				}
				
			}
			else 
			{
				if(dq[i-1] < maximum)
				{
					dir = -1;
					start = i;
				}
				else if(dq[i+1] < maximum)
				{
					dir = 1;
					start = i;
				}
			}
		}
		//cout << "Aqui llegue " << start << endl;;
	}

	if(start == -1)
	{
		cout << "NO\n";
		exit(0);
	}


	//cout << start << " " << dir << endl;

	if(dir == -1)
	{
		for(int i = start; i >= 1; i-- )
		{
			ss << i + idx_move << " L\n";
		}
		for(int i = 0; i < idx_diff - start - 1; i++)
		{
			ss << idx_move << " R\n";
		}
	}
	else
	{
		for(int i = 0; i < idx_diff - 1 - start; i++)
		{
			ss << start + idx_move << " R\n";
		}
		for(int i = start; i >= 1; i-- )
		{
			ss << i + idx_move << " L\n";
		}
		
	}



}


int main () {
	//fastIO();

	lli n; cin>>n;

	vector<lli> nums(n);
	for(auto &x: nums) cin>>x;


	lli k; cin>>k;

	vector<lli> nums_end(k);
	for(auto &x: nums_end) cin>>x;


	deque<lli> dq_nums;
	for(auto x: nums) dq_nums.push_back(x);

	deque<lli> dq_end;
	for(auto x: nums_end) dq_end.push_back(x);


	bool flag = true;

	

	while(!dq_end.empty())
	{
		//cout << dq_end.front() << " " << dq_nums.front() << " ";
		if(dq_nums.front() == dq_end.front())
		{
			dq_nums.pop_front();
			dq_end.pop_front();
			idx_move++;
			continue;
		}
		else //distintos en front
		{
			if(dq_nums.front() > dq_end.front())
			{
				flag = false;
				break;
			}


			int n_dq = SZ(dq_nums);

			int idx_diff = 0, curr = 0;
			while(idx_diff < n_dq && curr < dq_end.front() )
			{
				curr += dq_nums[idx_diff++];
			}



			if(curr != dq_end.front())
			{
				flag = false;
				break;
			}

			
			comer(dq_nums, idx_diff);
			
			for(int i = 0; i<idx_diff-1; i++)
			{
				lli a = dq_nums.front(); dq_nums.pop_front();
				lli b = dq_nums.front(); dq_nums.pop_front();
				dq_nums.push_front(a+b);
			}
		}
	}

	if( SZ(dq_nums) != 0 ) flag = false;


	if(flag)
	{
		cout << "YES\n";
		cout << ss.str();	
		//assert(total_comer == n-k);
		if(nums == nums_end)
		{
			assert(SZ(ss.str()) == 0);
		}
	}
	else
	{
		cout << "NO\n";
	}
	


	return 0;
}

