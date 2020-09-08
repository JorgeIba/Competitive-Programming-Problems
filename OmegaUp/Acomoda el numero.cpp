#include <iostream> 
int main() 
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	unsigned int num, n, x, contador=0;
	std::cin>>x>>n;
	for(unsigned int i=1;i<x;++i) {
		std::cin >> num;
		n>num?contador++:contador;
	}
	std::cout<<contador;
	return 0;
}
