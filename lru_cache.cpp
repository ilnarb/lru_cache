#include <iostream>

#include "lru_cache.h"
#include "lru_cache_tbb.h"

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

	lru_cache_tbb_t<int, int> cache_tbb(3);

	for(int i = 0; i < 10; i++)
	{
		std::cout << "set(" << (i % 5) << ", " << i << ");" << std::endl;
		cache_tbb.set((i % 5), i);
	}

	for(auto it = cache_tbb.begin(); it != cache_tbb.end(); ++it)
	{
		std::cout << "(" << (*it).first << ", " << (*it).second << ") ";
	}
	std::cout << std::endl;

	
	return 0;
}

