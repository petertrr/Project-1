#include<cstdlib>
#include<iostream>

#include"bloomFilter.h"

int main()
{
/*	BloomFilter<int> bf;
	const int maxInt = 1000;
	int maxValue = maxInt;
	for (int i = 0; i < maxInt; ++i)
		bf.add(rand() % maxInt);
*/
	BloomFilter<double> bf;
	const int maxDouble = 1000;
	int maxValue = int(maxDouble);
	for (int i = 0; i < maxValue; ++i)
		bf.add(rand() % maxValue * (1 + 1/maxDouble));

	double ratioPositives = 0;
	double ratioFalsePositives = 0;
	double ratioNegatives = 0;
	double ratioFalseNegatives = 0;
	for (int i = 0; i < maxValue; ++i)
		if (!bf.contains(i))
			//std::cout << i << " definetely not in set" << std::endl;
			if (!bf.testContains(i)) ++ratioNegatives;
			else ++ratioFalseNegatives;
		else
		{
			//std::cout << i << " false positive result" << std::endl;
			if (bf.testContains(i)) ++ratioPositives;
			else ++ratioFalsePositives;
		}
	std::cout << "Negatives: " << ratioNegatives / maxValue << "\n"
		<< "False negatives: " << ratioFalseNegatives / maxValue << "\n"
		<< "Positives: " << ratioPositives / maxValue << "\n"
		<< "False positives: " << ratioFalsePositives / maxValue << "\n"
		<< "max value was " << maxValue << ", size was " << bf.size()
		<< std::endl;
	std::cin.get();
	return 0;
}

class Test1
{
	double *data;
	int size;

public:
	Test1(int s) { size = s; data = new double[size]; }
	~Test1() { delete[] data; }
};