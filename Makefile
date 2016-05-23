all: lru_cache

lru_cache: lru_cache.cpp lru_cache*.h
	$(CXX) lru_cache.cpp -olru_cache -std=c++11 -ltbb
