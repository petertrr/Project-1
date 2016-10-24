#include<iostream>
#include<cstdlib>

#include"set.h"

inline int random(int min, int max) { return min + rand() % (max - min); }

int main()
{
	Set set1;
	Set set2;
	while (set1.size() < 4)
		set1.add(random(0, 5));
	while (set2.size() < 5)
		set2.add(random(3, 8));

	std::cout<<"set1 = "<<set1<<"\n"<<"set2 = "<<set2<<std::endl;

	//Set set = set.unite(set1, set2);
	Set set = set1 + set2;
	std::cout<<"s1 + s2 = "<<set<<std::endl;
	set = set1*set2;
	std::cout<<"s1*s2 = "<<set<<std::endl;
	set = set2 - set1;
	std::cout<<"s2 - s1 = "<<set<<std::endl;
	
	std::cin.get();
	return 0;
}