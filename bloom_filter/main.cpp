#include<cstdlib>
#include<iostream>

#include"bloomFilter.h"

int main()
{
	BloomFilter<int> bf;
	const int maxInt = 1000;
	for (int i = 0; i < bf.size(); ++i)
		bf.add(rand() % maxInt);
	for (int i = 0; i < maxInt; ++i)
		if (!bf.contains(i)) std::cout << i << " definetely not in set" << std::endl;
		//else if (bf.find(i) != nullptr) std::cout << i << " True positive result" << std::endl;
		else std::cout << i << " false positive result" << std::endl;
	return 0;
}