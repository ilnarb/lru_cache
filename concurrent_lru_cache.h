#ifndef __CONCURRENT_LRU_CACHE_H__
#define __CONCURRENT_LRU_CACHE_H__

#include <list>
#include <tbb/concurrent_hash_map.h>

template<
	typename Key,
	typename Value,
	// lets allow to change hash comparer
	typename HashCompare = tbb::tbb_hash_compare<Key>
>
class concurrent_lru_cache_t
{
public:
	typedef Key key_type;
	typedef Value value_type;
	typedef HashCompare hash_compare_type;
	typedef typename std::pair<key_type, value_type> pair_type;
	typedef typename std::list<pair_type>::iterator iterator;
	typedef typename std::list<pair_type>::const_iterator const_iterator;
	//
	concurrent_lru_cache_t(size_t max_size): _max_size(max_size)
	{
	}
	void set(const key_type &key, const value_type &value)
	{
		typename mapper_type::const_accessor it;
		if (_mapper.find(it, key))
		{
			auto lit = (*it).second;
			// move to the head
			_elements.splice(_elements.begin(), _elements, lit);
			// set new value
			(*lit).second = value;
		}
		else
		{
			if (_elements.size() >= _max_size)
			{
				auto pair = _elements.back();
				_mapper.erase(pair.first);
				_elements.pop_back();
			}
			//
			_elements.emplace_front(key, value);
			_mapper.insert(std::make_pair(key, _elements.begin()));
		}
	}
	bool get(const key_type &key, value_type &value)
	{
		typename mapper_type::const_accessor it;
		if (_mapper.find(it, key))
		{
			auto lit = (*it).second;
			// move to the head
			_elements.splice(_elements.begin(), _elements, lit);
			value = (*lit).second;
			return true;
		}
		return false;
	}
	bool get(const key_type &key, value_type &value) const
	{
		typename mapper_type::const_accessor it;
		if (_mapper.find(it, key))
		{
			auto lit = (*it).second;
			value = (*lit).second;
			return true;
		}
		return false;
	}
	void erase(const key_type &key)
	{
		typename mapper_type::const_accessor it;
		if (_mapper.find(it, key))
		{
			auto lit = (*it).second;
			_elements.erase(lit);
			_mapper.erase(it);
		}
	}
	// iterators
	iterator begin()
	{
		return _elements.begin();
	}
	iterator end()
	{
		return _elements.end();
	}
	const_iterator begin() const
	{
		return _elements.begin();
	}
	const_iterator end() const
	{
		return _elements.end();
	}
	// 
	size_t size() const
	{
		return _elements.size();
	}
	size_t max_size() const
	{
		return _max_size;
	}
	size_t empty() const
	{
		return _elements.empty();
	}
private:
	size_t _max_size;
	std::list<pair_type> _elements;
	typedef tbb::concurrent_hash_map<key_type, iterator, hash_compare_type> mapper_type;
	tbb::concurrent_hash_map<key_type, iterator, hash_compare_type> _mapper;
};

#endif // __CONCURRENT_LRU_CACHE_H__
