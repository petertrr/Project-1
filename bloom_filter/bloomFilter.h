#pragma once
#include<vector>
#include<set>
#include<cstdlib>

template <class T> 
class BloomFilter
{
	std::set<T> data;

	const static int m = 19927;
	std::vector<bool> index;
	const static int numberOfHashes = 3;
	int h(T a, int i) const {return int(a*i) % m; };

public:
	BloomFilter();
	void swap(BloomFilter&, BloomFilter&);
	BloomFilter(const BloomFilter&);
	BloomFilter<T>& operator=(const BloomFilter&);
	BloomFilter(BloomFilter&&);
	~BloomFilter();

	void add(T);
	void remove(T);
	bool contains(const T) const;
	bool testContains(const T) const;
	auto find(T t) { if (contains(t)) return data.find(t); else return data.end(); };
	int size() { return data.size(); }
};