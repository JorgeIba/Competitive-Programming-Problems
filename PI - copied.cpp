ll check(ll v, ll n, ll ndr, ll nv) {
    return v >= ndr ? (n / v - 1) : (nv - v);
}

ll pi_0(ll n) // O(n^(3/4))
{
  assert(n>=1);
  ll r = (ll)sqrt(n);
  ll ndr = n / r;
  assert(r*r <= n && (r+1)*(r+1) > n);
  ll nv = r + ndr - 1;
  vector<ll> S(nv+1);
  vector<ll> V(nv+1);
  for(ll i=0;i<r;i++) {
    V[i] = n / (i+1);
  }
  for(ll i=r;i<nv;i++) {
    V[i] = V[i-1] - 1;
  }
  for(ll i = 0;i<nv;i++) {
    S[i] = V[i] - 1; //primes number
  }
  for(ll p=2;p<=r;p++) {
    if(S[nv-p] > S[nv-p+1]) {
      ll sp = S[nv-p+1]; // sum of primes smaller than p
      ll p2 = p*p;
      for(ll i=0;i<nv;i++) {
        if(V[i] >= p2) 
        {
          S[i] -= 1LL  * (S[check(V[i] / p, n, ndr, nv)] - sp);
        }
        else break;
      }
    }
  }
  ll ans = S[0];
  return ans;
}