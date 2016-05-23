#include <iostream>

#include "lru_cache.h"
#include "concurrent_lru_cache.h"

int main(int argc, char* argv[])
{
	lru_cache_t<int, int> cache(3);

	for(int i = 0; i < 10; i++)
	{
		std::cout << "set(" << (i % 5) << ", " << i << ");" << std::endl;
//		cache.set((i % 5), i);
		cache[(i % 5)] = i;
	}

	for(auto it = cache.begin(); it != cache.end(); ++it)
	{
		std::cout << "(" << (*it).first << ", " << (*it).second << ") ";
	}
	std::cout << std::endl;

	concurrent_lru_cache_t<int, int> ccache(3);

	for(int i = 0; i < 10; i++)
	{
		std::cout << "set(" << (i % 5) << ", " << i << ");" << std::endl;
		ccache.set((i % 5), i);
	}

	for(auto it = ccache.begin(); it != ccache.end(); ++it)
	{
		std::cout << "(" << (*it).first << ", " << (*it).second << ") ";
	}
	std::cout << std::endl;

	
	return 0;
}

