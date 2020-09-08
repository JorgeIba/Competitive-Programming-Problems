#include <bits/stdc++.h>
#define lli long long int
#define endl "\n"
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
x
using namespace std;

lli binPow(lli a, lli b){
    lli res = 1;
    while(b){
        if(b&1) res *= a;
        b>>=1; a*=a;
    }
    return res;
}

lli g(lli p, lli a){
    lli pa = binPow(p,a);
    return -1*pa * (pa-1) + pa*pa;
}

lli f(lli p, lli a){
    lli pa = binPow(p,a);
    lli aux = (pa*pa - 1) / (p+1);
    return -pa*aux + pa*pa*pa;
}

vector<lli> F, G;
void sieve(lli n){
    F.resize(n+1);
    G.resize(n+1);
    vector<lli> primes, lp(n+1), cont(n+1), pot(n+1);
    F[1] = G[1] = 1;
    for(int i = 2; i<=n; i++){
        if(!lp[i]){
            lp[i] = pot[i] = i;
            cont[i] = 1;
            F[i] = f(i,1);
            G[i] = g(i,1);
            primes.push_back(i);
        }
        for(auto p: primes){
            lli d = p*i;
            if(d>n) break;
            lp[d] = p;
            if(p==lp[i]){
                F[d] = F[ i/pot[i] ] * f(p, cont[i]+1);
                G[d] = G[ i/pot[i] ] * g(p, cont[i]+1);
                cont[d] = cont[i] + 1;
                pot[d] = pot[i]*p;
                break;
            }
            else{
                F[d] = F[i] * F[p];
                G[d] = G[i] * G[p];
                cont[d] = 1;
                pot[d] = p;
            }
        }
    }
}

int main(){
    fastIO();
    sieve(1000010);
    lli t; cin>>t;
    while(t--){
        lli n; cin>>n;
        cout<< (F[n] + G[n])/2 << endl;
    }
    return 0;
}
