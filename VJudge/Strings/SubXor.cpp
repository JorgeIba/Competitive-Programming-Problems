#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

struct Node
{
    lli count = 0, value = 0;
    Node *l = NULL, *r = NULL; // l-> 0, r -> 1
};

void insert(lli num, Node *root)
{
    Node *aux = root;
    for(lli i = 22; i>=0; i--)
    {
        if(num & (1LL<<i)) // pa la derecha
        {
            if(aux->r == NULL)
            {
                aux->r = new Node();
            }
            aux = aux->r;
        }
        else 
        {
            if(aux->l == NULL)
            {
                aux->l = new Node();
            }
            aux = aux->l;
        }
        aux->count++;
    }
    aux->value = num;
}

lli query(lli sum, Node *root, lli k)
{
    Node *aux = root;
    lli mask = sum^k, ans = 0;
    for(lli i = 22; i>=0; i--)
    {
        if(!aux) break;
        if(mask&(1LL<<i)) // Si es un uno en esa posicion, entonces todos los ceros son menores y me muevo a los 1's
        {
            if(!(sum & (1LL<<i)))
            {
                if(aux->l != NULL)
                {
                    ans += aux->l->count;
                }
            }
            aux = aux->r;
        }
        else //Si es un 0, entonces con un 1 son todos mayores, tons no lo agrego y me muevo a los 0's
        {
            if((sum & (1LL<<i))) 
            {
                if(aux->r)
                {
                    ans += aux->r->count;
                }
            }
            aux = aux->l;
        }
    }
    return ans;
}


void solve()
{
    lli n, k; cin>>n>>k;
    vector< lli > nums(n+1);
    for(int i = 1; i<=n; i++) cin>>nums[i];
    vector< lli > sumXOR(n+1, 0);
    for(int i = 1; i<=n; i++)
    {
        sumXOR[i] = sumXOR[i-1] ^ nums[i];
    }
    Node *root = new Node();
    lli ans = 0;
    for(int i = 0; i<=n; i++)
    {
        //lli looking = sumXOR[i] ^ k;
        ans += query(sumXOR[i], root, k);
        //cout << query(sumXOR[i], root, k) << " ";
        insert(sumXOR[i], root);
    }
    cout << ans << endl;

}


int main()
{
    fastIO();
    lli t; cin>>t;
    while(t--) solve();
    return 0;
}