lli binPow(lli a, lli b)
{
    lli res = 1;
    while(b)
    {
        if(b&1) res = res * a % MOD;
        b>>=1;
        a = a*a%MOD;
    }
    return res;
}