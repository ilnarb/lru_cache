#include <iostream>
#include <list>
#include <thread>

#include "concurrent_lru_cache.h"

int main(int argc, char* argv[])
{
	concurrent_lru_cache_t<int, int> cache(3);

	for(int i = 0; i < 10; i++)
	{
		std::cout << "set(" << (i % 5) << ", " << i << ");" << std::endl;
		cache.set((i % 5), i);
	}

	for(auto it = cache.begin(); it != cache.end(); ++it)
	{
		std::cout << "(" << (*it).first << ", " << (*it).second << ") ";
	}
	std::cout << std::endl;

	std::list<std::thread *> threads;
	for(int k = 0; k < 10; k++)
	{
		std::thread *th = new std::thread([&](){
			for(int i = 0; i < 100; i++)
				cache.set((i % 5), i);
		});
		threads.push_back(th);
	}

	while(!threads.empty())
	{
		std::thread *th = threads.front();
		th->join();
		delete th;
		threads.pop_front();
	}

	for(auto it = cache.begin(); it != cache.end(); ++it)
	{
		std::cout << "(" << (*it).first << ", " << (*it).second << ") ";
	}
	std::cout << std::endl;

	return 0;
}

