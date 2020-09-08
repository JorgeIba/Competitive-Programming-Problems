#include<cstdio>
#include<map>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
#include<set>
using namespace std;
typedef long long LL;
 
//
//long long bn[1000][1000];
//int main(void) {
//	memset(bn, 0, sizeof(bn));
//	long long sum = 0;
//	for (int i = 0; i <= 1000;i++) {
//		printf("%d-", i);
//		if (i == 0) {
//			bn[0][0] = 1;
//			//printf("1" );
//		}
//		else {
//			bn[i][0] = 1;
//			printf("1");
//			for (int z = 1; z <= i-1; z++) {
//				bn[i][z] = (bn[i - 1][z] + bn[i - 1][z - 1])%7;
//				if (bn[i][z] == 0) {
//					sum++;
//					printf("*");
//				}
//				else {
//					printf("1");
//				}
//			}
//			bn[i][i] = 1;
//			printf("1");
//			printf("*****%lld", sum);
//		}
//		//printf("%lld\n", sum);
//		printf("\n");
//	}
//	return 0;
//}
 
const LL mod = 1e9 + 7;
LL ax[40];
LL gx[40] = { 0,7 };
LL mi2;
LL powmod(LL a, LL b, LL m) {
	LL ans = 1;
	while (b > 0) {
		if (b & 1) {
			ans = ans*a%m;
		}
		a = a*a%m;
		b >>= 1;
	}
	return ans;
}
LL solve(LL num, LL cen) {
	if (num == 0) {
		return 0;
	}
	LL gg = cen / gx[num];
	LL ans = cen % gx[num];
	LL sum1 = (gx[num] % mod - 1 + mod) % mod*(gx[num] % mod) % mod*mi2 % mod;
	LL sum2 = (1 + gg)*(gg) % mod*ax[num - 1] % mod*mi2 % mod;
	LL sum4;
	if (gg <= 1) {
		sum4 = 0;
	}
	else {
		sum4 = (gg - 1)*(1 + (gg - 2) + 1) % mod*sum1 % mod*mi2 % mod;
	}
	LL sum3 = ((gx[num] % mod - 1 + gx[num] % mod - 1) % mod - ans%mod + 1 + mod) % mod*(ans%mod) % mod*mi2 % mod;
	LL sum5 = solve(num - 1, ans);
	return (((sum4 + sum2) % mod + sum3*gg%mod) % mod + sum5 % mod*(gg + 1) % mod) % mod;
}
int main(void) {
	LL t1 = 7 * 7;
	LL t2 = 21 * 21;
	ax[0] = 0;
	ax[1] = 21 * 21;
	mi2 = powmod(2, mod - 2, mod) % mod;
	int ff = 1;
	for (int i = 2; i <= 22; i++) {
		gx[i] = t1;
		//printf("%lld\n", gx[i]);
		ax[i] = (ax[i - 1] * 28 % mod + (t1 - 1 + 1) % mod*((t1 - 1) % mod) % mod * 21 % mod * mi2) % mod;
		t2 = ax[i];
		t1 = t1 * 7;
	}
	int t;
	scanf("%d", &t);
	while (t--) {
		LL n;
		scanf("%lld", &n);
		int ans;
		printf("Case %d: ", ff++);
		for (int i = 0; i <= 22; i++) {
			if (gx[i] > n) {
				ans = i - 1;
				break;
			}
		}
		if (ans == -1) {
			printf("0\n");
			continue;
		}
		printf("%lld\n", solve(ans, n + 1));
	}
}