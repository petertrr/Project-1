#include<iostream>
#include<cstdlib>

#include"set.h"

inline int min(int a, int b) {return a<b ? a : b ;}
inline int random(int min, int max) {return min + rand()%(max - min);}

Set::Set(int size)
{ 
	size_ = size; 
	data_ = new int[size_]; 
	for(int i = 0; i < size_; ++i)
		data_[i] = random(0, 5);
	std::cout<<"Constructor\n";
}

Set::Set(const Set &set)
{
	if(size_>0) delete data_;
	size_ = set.size();
	data_ = new int[size_];
	for(int i = 0; i < size_; ++i)
		data_[i] = set.data_[i];
	std::cout<<"Copy constructor\n";
}

Set& Set::operator=(const Set &set)
{
	if(this == &set) return *this;
	if(size_>0)delete data_;
	size_ = set.size();
	data_ = new int[size_];
	for(int i = 0; i < size_; ++i)
		data_[i] = set.data_[i];
	std::cout<<"Assignment\n";
	return *this;
}

Set Set::unite(Set &set1, Set &set2)
{
	Set result( set1.size() + set2.size() );
	for(int i = 0; i < set1.size(); ++i)
	{
		result.data_[i] = set1.data_[i];
	}
	for(int i = set1.size(); i < result.size(); ++i)
	{
		result.data_[i] = set2.data_[i - set1.size()];
	}
	return result;
}

Set Set::intersect(Set &set1, Set &set2)
{
	int size = 0;
	int *indeces1 = new int[ min(set1.size(), set2.size()) ];
	int *indeces2 = new int[ min(set1.size(), set2.size()) ];
	for(int i = 0; i < set2.size(); ++i)
		for(int j = 0; j < set1.size(); ++j)
		{
			for(int k = 0; k < size; ++k)
			{
				if(j == indeces1[k]) ++j;
				else if(i == indeces2[k]) ++i;
			}
			if(set1.data_[j] == set2.data_[i])
			{
				indeces1[size] = j;
				indeces2[size] = i;
				++size;
				++i;  j=0;
			}
		}
	Set result(size);
	for(int i = 0; i < size; ++i)
		result.data_[i] = set1.data_[indeces1[i]];

	return result;
}

Set Set::subtract(Set &set1, Set &set2)
{
	int size = 0;
	int *indeces1 = new int[ set1.size()];
	int *indeces2 = new int[ set1.size()];
	for(int i = 0; i < set2.size(); ++i)
		for(int j = 0; j < set1.size(); ++j)
		{
			for(int k = 0; k < size; ++k)
			{
				if(j == indeces1[k]) ++j;
				else if(i == indeces2[k]) ++i;
			}
			if(set1.data_[j] == set2.data_[i])
			{
				indeces1[size] = j;
				indeces2[size] = i;
				++size;
				++i; j = -1; // потому что выполнится ++j и сделает 0
			}
		}
	Set result(set1.size() - size);
	for(int i = 0; i < result.size(); ++i)
	{
		static int j = 0;
		for(int k = 0; k < size; ++k)
			if(j == indeces1[k]) {++j; k = 0;}
		result.data_[i] = set1.data_[j];
		++j;
	}

	return result;
}

std::ostream& operator<<(std::ostream& os, const Set& set)
{
	if(set.size() == 0) {os<<"{O}"; return os;}
	os<<"{ ";
	for(int i = 0; i < set.size(); ++i)
	{
		 os<<set.data_[i];
		if(i < set.size()-1) os<<", ";
		else os<<" }";
	}
	return os;
}