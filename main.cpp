#include<iostream>

#include"set.h"

int main()
{
	Set set1(5);
	Set set2(6);
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