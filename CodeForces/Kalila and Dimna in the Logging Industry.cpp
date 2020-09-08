#include <bits/stdc++.h>

#define lli long long int
#define ld long double
#define endl "\n"
#define forn(i, in, fin) for(int i = in; i<fin; i++)
#define all(v) v.begin(), v.end()
#define fastIO(); ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

bool Q = 0;
struct Line {
	mutable lli m, b, x;
 
	bool operator < (const Line L) const {
		return Q ? x < L.x : m < L.m; 
	}
};
const lli INF = numeric_limits<lli>::max();
struct Hull : multiset<Line> {

    lli ceil (lli a, lli b) {
	if (a < 0 != b < 0) return a / b; // Si uno es negativos y otro no
	return (abs(a) + abs(b) - 1) / abs(b); 
    }
    
    lli intersection (const Line &p, const Line &q) {
        return ceil(q.b - p.b, p.m - q.m);
    }


	bool valid (auto it) {
		if (it == begin()) { // Si el iterador quedo hasta el inicio, entonces su interseccion en X con el anterior es en -INF
			auto sig = it;
			sig++;
			if (sig != end()) sig->x = intersection(*it, *sig); // Si existe una recta con pendiente mayor a it, entonces sig-> x gaurda el
			return it->x = -INF;                                // punto donde se intersectan
		}
 
		auto ant = it, sig = it;
		ant--, sig++;
 
		if (sig == end()) { // Si el iterador quedo hasta el final
			it->x = intersection(*it, *ant);
			return 1;
		}
        // Esta parte es por si quedó entre otras dos rectas, hay que checar el punto de interseccion con el de atras,
        // Si esta mas a la derecha que el punto de interseccion de adelante, significa que no forma parte del convex hull
        // Pero si está mas a la izq, significa que el intervalo es [ant, x] U [x, y] U [y, sig] (Esto para buscar maximos)
		lli x = intersection(*it, *ant); 
		lli y = intersection(*it, *sig);
 
		if (x > y) return 0;
		it->x = x, sig->x = y;
		return 1;
	}
 
	void add (lli m, lli b) {
		auto it = lower_bound({m, b, -INF}); // Pa ver en donde lo voy a poner
                                             // Recuerda que estan ordenados por pendientes
		
        if (it != end() && it->m == m) { //por si enconte una recta con igual pendiente
			if (it->b > b) return; //Si la recta que encontre en el lower bound esta mas hacia arriba, entonces la nueva que 
                                   //quiero insertar no forma parte del Convex Hull
			it->b = b; //Ya no creo otra recta, sino que mofidico la que me encontré
		} else {
			it = insert({m, b, -INF}); //Si no encontré ninguna parecida, creo una nueva recta
		}
 
		if (!valid(it)) { // Checar si el it forma parte del convex hull, además de encontrar los puntos de interseccion
			erase(it);
			return;
		}
 
		auto ant = it;
		while (ant != begin()) { // Para borrar todos las lineas anteriores a it, que no forman parte del convex hull
			if (valid(--ant)) break; // Si una linea forma part del convex hull, todas las anteriores tambien
			erase(ant);
			if (it == begin()) { it->x = -INF; break; }
			ant = it;
		}
 
		auto sig = it;
		sig++;
		while (sig != end() && !valid(sig)) // Para borrar todas las lineas despues de it, que no forman parte dle convex hull
			erase(sig++);
	}
 
	lli query (lli x) {
		if (empty()) return 0; //Si no hay ninguna linea antes
 
		Q = 1; // el comparador de la estructura, ahora compara con las intersecciones
		auto it = upper_bound({0, 0, x});
		it--; // Para obtener la linea con interseccion punto de interseccion mas grande pero que sea menor a x
              // Es decir, obtener el punto de interseccion de la recta que contiene a X, en el convex hull
		Q = 0; // el comparador de la estructura vuelve a comparar respecto a las pendientes y no respecto a los puntos de interseccion
		return x * it->m + it->b; //regresa la evaluacion de la recta en x.
	}
};


int main()
{
    fastIO();
    lli n; cin>>n;
    vector< lli > a(n+1), b(n+1);

    for(int i = 1; i<=n; i++) cin>>a[i];
    for(int i = 1; i<=n; i++) cin>>b[i];

    vector< lli > dp(n+1, INF);
    Hull H;

    dp[n] = 0;
    H.add(-a[n], 0);
    for(int i = n-1; i>=1; i--)
    {
        dp[i] = H.query(b[i]);
        //for(int j = n; j>=i; j--)
        {
            //dp[i] = min(dp[i], b[i]*a[j] + dp[j]);
        }
        H.add(-a[i], dp[i]);
    }
    cout << (-dp[1]) << endl;

    return 0;
}