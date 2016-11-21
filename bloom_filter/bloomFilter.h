#pragma once
#include<vector>
#include<set>
#include<cstdlib>

template <class T> 
class BloomFilter
{
	std::set<T> data;

	const static int m = 100;
	std::vector<bool> index;
	const static int numberOfHashes = 2;
	int h(T, int) {return rand() % m; };
	int hashes[numberOfHashes];

public:
	BloomFilter();
	BloomFilter(const T&);
	~BloomFilter();

	void add(T);
	void remove(T);
	bool contains(T) const;
	auto find(T t) { if (contains(t)) return data.find(t); else return data.end(); };
	int size() { return m; }
};