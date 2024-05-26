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

//20
vector<lli> primes;
vector<bool> isPrime;
void primesSieve(int n)
{
	isPrime.resize(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	primes.push_back(2);
	for(int i = 4; i <= n; i += 2) isPrime[i] = false;
	for(lli i = 3; i <= n; i += 2)
    {
		if(isPrime[i])
        {
			primes.push_back(i);
			if(i * i <= n)
				for(lli j = i * i; j <= n; j += 2 * i)
					isPrime[j] = false;
		}
	}
}


vector<lli> getDigitChange(lli p, int d)
{
	vector<lli> numbers_with_digit_changed = {p};
	string p_string = to_string(p);
	for(int new_digit = d+1; new_digit < 10; new_digit++){
		string new_p = p_string;
		for(auto &c: new_p){
			if(c-'0' == d){
				c = new_digit +'0';
			}
		}
		numbers_with_digit_changed.push_back( stoll(new_p) );
	}
	return numbers_with_digit_changed;
}


const int MAXN = 1e6;

int main () {
	//fastIO();
	primesSieve(MAXN);
	
		
	set<lli> set_primes(all(primes));

	for(auto p: primes)
	{
		vector<int> fr_digits(10);
		string s_number = to_string(p);
		for(auto c: s_number){
			int digit = c-'0';
			fr_digits[digit]++;
		}
		for(int d = 0; d < 10; d++) {
			if(fr_digits[d] > 1){
				vector<lli> numbers_with_digit_changed = getDigitChange(p, d);
				int cnt = 0;
				for(auto number: numbers_with_digit_changed){
					if(set_primes.count(number)){
						cnt++;
					}
				}

				if(cnt > 7){
					cout << "CNT: " << cnt << endl;
					for(auto number: numbers_with_digit_changed){
						cout << number << " ";
					}
					cout << endl;
				}
			}

		}
	}
	

	return 0;
}

