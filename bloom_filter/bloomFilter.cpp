#include"bloomFilter.h"

template class BloomFilter<int>;
template class BloomFilter<double>;

template <class T> 
BloomFilter<T>::BloomFilter() : index(m)
{
	for (int i = 0; i < m; ++i)
		index[i] = 0;
}

template<class T>
void BloomFilter<T>::swap(BloomFilter& bf1, BloomFilter& bf2)
{
	std::swap(bf1.data, bf2.data);
	std::swap(bf1.index, bf2.index);
}

template <class T>
BloomFilter<T>::BloomFilter(const BloomFilter& bf) : data(bf.data), index(bf.index) {}

template <class T>
BloomFilter<T>& BloomFilter<T>::operator=(const BloomFilter& bf)
{
	if (this != &bf)
	{
		BloomFilter result(bf);
		swap(*this, result);
	}
	return *this;
}

template<class T>
BloomFilter<T>::BloomFilter(BloomFilter&& bf)
{
	swap(*this, bf);
}

template <class T>
BloomFilter<T>::~BloomFilter()
{
	index.~vector();
//	data.~set();
}

template <class T> 
void BloomFilter<T>::add(T a)
{
	data.insert(a);
	for (int i = 0; i < numberOfHashes; ++i)
		index[h(a, i)] = 1;
}

template <class T> 
void BloomFilter<T>::remove(T a)
{	
	for (int i = 0; i < numberOfHashes; ++i)
		index[h(a, i)] = 0;
	data.erase(a);
}
template <class T> 
bool BloomFilter<T>::contains(T a) const
{
	for (int i = 0; i < numberOfHashes; ++i)
		if (!index[h(a, i)]) return false;
	return true;
}

template <class T>
bool BloomFilter<T>::testContains(T a) const
{
	return data.count(a)!=0 ? true : false;
}

