#include"bloomFilter.h"

template <class T> 
BloomFilter<T>::BloomFilter() : index(m)
{
	for (int i = 0; i < m; ++i)
		index[i] = 0;
	for (int i = 0; i < numberOfHashes; ++i)
		hashes[i] = 0;
}

//BloomFilter(const T&);

//~BloomFilter();

template <class T> 
void BloomFilter<T>::add(T a)
{
	data.add(a);
	for (int i = 0; i < numberOfHashes; ++i)
		index[hashes[i] = h(a, i)] = 1;
}

template <class T> 
void BloomFilter<T>::remove(T a)
{	
	for (int i = 0; i < numberOfHashes; ++i)
	{
		index[hashes[i]] = 0;
		hashes[i] = 0;
	}
	data.remove(a);
}
template <class T> 
bool BloomFilter<T>::contains(T a) const
{
	for (int i = 0; i < numberOfHashes; ++i)
		if (!index[h(a, i)]) return false;
	return true;
}