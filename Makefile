all: lru_cache

lru_cache: test_lru_cache test_concurrent_lru_cache

test_lru_cache: test_lru_cache.cpp lru_cache.h
	$(CXX) test_lru_cache.cpp -o$@ -std=c++11

test_concurrent_lru_cache: test_concurrent_lru_cache.cpp concurrent_lru_cache.h
	$(CXX) test_concurrent_lru_cache.cpp -o$@ -std=c++11 -ltbb
