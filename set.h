#pragma once

class Set;
struct List;

struct List
{
	int data;
	List *prev;
	List *next;
};

class Set
{
public:
	Set();
	Set(const Set &set);
	//Set(Set &&set);
	Set &operator=(const Set &set);
	~Set();

	void add(int a);
	void remove(int a);
	bool contains(int a);
	
	Set unite(Set &set1, Set &set2);
	Set intersect(Set &set1, Set &set2);
	Set subtract(Set &set1, Set &set2);

	Set operator+(Set &set) { return unite((*this), set); };
	Set operator*(Set &set) { return intersect((*this), set); };
	Set operator-(Set &set) { return subtract((*this), set); };

	friend std::ostream& operator<<(std::ostream& os, const Set& set);
	friend std::istream& operator>>(std::istream& is, Set& set);

	const int size() const { return size_; }

private:
	int size_;
	List *next_;
	List* cur_;
};