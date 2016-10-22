#pragma once

class Set
{
public:
	Set(int size = 0);
	Set(const Set &set);
	//Set(Set &&set);
	Set &operator=(const Set &set);
	~Set() { delete data_; };

	Set unite(Set &set1, Set &set2);
	Set intersect(Set &set1, Set &set2);
	Set subtract(Set &set1, Set &set2);

	Set operator+(Set &set) { return unite((*this), set); };
	Set operator*(Set &set) { return intersect((*this), set); };
	Set operator-(Set &set) { return subtract((*this), set); };

	friend std::ostream& operator<<(std::ostream& os, const Set& set);

	const int size() const { return size_; }

private:
	int size_;
	int* data_;
};