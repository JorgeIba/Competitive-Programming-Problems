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

//13
const lli maxN = 2e6+10;
const lli MOD = 1e9+7; // Initialize
vector<lli> fact(maxN+1, 1), inv(maxN+1, 1), invFact(maxN+1,1);
void prec()
{
    for(lli i = 2; i < maxN; ++i)
    {
        fact[i] = i*fact[i-1] %MOD;
        inv[i] = MOD - (MOD/i)*inv[MOD%i]%MOD;
        invFact[i] = (lli)inv[i]*invFact[i-1]%MOD;
	}
}

lli nCr(lli n, lli r){
    if(r < 0 || n < r) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}



lli binPow(lli a, lli b, lli mod = MOD) {
    lli res = 1;
    while(b) {
        if(b&1) res = res * a % mod;
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}


int main () {
	//fastIO();
    prec();
    
    lli n, G, I, E; cin>>n>>G>>I>>E;

    G = min(G, 2*n);
    E = min(E, 2*n - G);
    I = min(I, 2*n-G-E);

    assert(G+I+E <= 2*n);

    lli ans = 0;
    for(int pairs = 0; pairs <= G/2; pairs++) {
        lli g = G, i = I, e = E;

        // Primero acomodo los pares y los que estarán sólos
        lli singles_g = g - 2*pairs;
        //* WAYS_G
        lli ways_g = nCr(n, pairs) * nCr(n - pairs, singles_g) % MOD * binPow(2, singles_g) % MOD;
        lli prob_ways_g = ways_g * binPow(  nCr(2*n, g),  MOD-2  ) % MOD;

        lli happiness = g;

        // Cuantos lugares estan totalmente vacios
        lli total_empties = n - pairs - singles_g;
        // Cuantos lugares tienen a una persona
        lli semi_empties_g = singles_g;

        /*
        cerr << "Emparejando a " << pairs << " pares de g y a " << singles_g << " solitos, me quedan que: " << endl;
        cerr << "total_empties: " << total_empties << " semi_empties con g's: " << semi_empties_g << " hapiness " << happiness << endl;
        cerr << endl;
        //! Toca emparejar a los extrovertidos
        */

        // emparejar todos los extrovertidos que pueda con los singles_g
        lli how_many_matches_with_g = min(e, semi_empties_g);

        // los asientos con al menos una persona les quito a los que pude emparejar con extrovertidos
        semi_empties_g -= how_many_matches_with_g;
        // los extrovertidos que se emparejaron con alguien, agregan felicidad
        (happiness += how_many_matches_with_g) %= MOD;

        /*
        cerr << "Emparejando a " << how_many_matches_with_g << " vatos de e con g"<< endl;
        cerr << "total_empties: " << total_empties << " semi_empties con g's: " << semi_empties_g << " hapiness " << happiness << endl;
        cerr << endl;
        */


        lli left_e = e - how_many_matches_with_g;

        lli pairs_with_e = left_e / 2;
        // los extrovertidos que me sobraron, los pongo en parejas en los asientos vacios que me quedaron
        //* WAYS_PAIRS_BETWEEN_E
        total_empties -= pairs_with_e;
        (happiness += 2*pairs_with_e) %=  MOD;

        /*
        cerr << "Me quedaron: " << left_e << " extrovertidos, entonces emparejo a " << pairs_with_e << endl;
        cerr << "total_empties: " << total_empties << " semi_empties con g's: " << semi_empties_g << " hapiness " << happiness << endl;
        cerr << endl;
        */

        // si hay un wey single lo pongo en cualquier asiento de los que me quedan
        lli singles_e = left_e % 2;
        // de esta manera pierdo un asiento completamente vacio pero agrego uno semivacio
        total_empties -= singles_e;
        lli semi_empties_e = singles_e;


        /*
        cerr << "Me quedo este extrovertido solo: " << singles_e << endl;
        cerr << "total_empties: " << total_empties << " semi_empties con g's: " << semi_empties_g << " semi_empties con e's " << semi_empties_e  << " hapiness " << happiness << endl;
        cerr << endl;
        */

        //! Toca emparejar a los introvertidos


        // Primero los pongo solitos
        lli good_sit = min(i, total_empties);
        (happiness += good_sit) %= MOD;
        total_empties -= good_sit;
        lli semi_empties_i = good_sit;
        i -= good_sit;

        /*
        cerr << "Ahora voy a poner a los introvertidos solitos, de esto puedo poner a : " << good_sit << " por lo que ahora me quedan " << i << " introvertidos disponibles" << endl;
        cerr << "total_empties: " << total_empties << " semi_empties con g's: " << semi_empties_g << " semi_empties con e's " << semi_empties_e << " semi_empties con i's " << semi_empties_i << endl;
        cerr << endl;
        */

        assert(!(semi_empties_e > 0 && semi_empties_g > 0));


        if(semi_empties_e > 0) {    
            // Luego los trato de poner con los extrovertidos que quedaron solos, esto da felicidad a los extrovertidos
            lli matches_with_i = min(i, semi_empties_e);
            (happiness += matches_with_i) %= MOD;
            i -= matches_with_i;
            semi_empties_e -= matches_with_i;

            /*
            cerr << "Ahora voy a ponerlos con los extrovertidos, de esto puedo poner a : " << matches_with_i << " por lo que ahora me quedan " << i << " introvertidos disponibles" << endl;
            cerr << "total_empties: " << total_empties << " semi_empties con g's: " << semi_empties_g << " semi_empties con e's " << semi_empties_e << " semi_empties con i's " << semi_empties_i << endl;
            cerr << endl;
            */

        } else if(semi_empties_g > 0){
            // Luego los trato de poner con los easygoing que quedaron solos
            lli matches_with_i = min(i, semi_empties_g);
            i -= matches_with_i;
            semi_empties_g -= matches_with_i;

            // cerr << "Ahora voy a ponerlos con los easygoing, de esto puedo poner a : " << matches_with_i << " por lo que ahora me quedan " << i << " introvertidos disponibles" << endl;
            // cerr << "total_empties: " << total_empties << " semi_empties con g's: " << semi_empties_g << " semi_empties con e's " << semi_empties_e << " semi_empties con i's " << semi_empties_i << endl;
            // cerr << endl;

        }
        

        // Luego si me quedan, los pongo juntos y esto me quita felicidad que les había puesto
        lli matches_between_i = min(semi_empties_i, i);
        happiness = (happiness - matches_between_i + MOD) % MOD;

        // cerr << "Ahora voy a poner a los introvertidos con otros introvertidos, de esto puedo poner a : " << matches_between_i << " por lo que ahora me quedan " << endl;
        // cerr << "total_empties: " << total_empties << " semi_empties con g's: " << semi_empties_g << " semi_empties con e's " << semi_empties_e << " con felicidad total: " << happiness << endl;

        // cerr << "Donde hay probabilidad: " << ways_g << " / nCr(" << 2*n << ", " << g << ")"  << endl;
        
        // cerr << " ----------------- " << endl;


        (ans += happiness * prob_ways_g % MOD) %= MOD;
    }

    
    cout << ans << endl;

    // ans = ans * invFact[2*n] % MOD;

    // cout << ans << endl;



	return 0;
}
