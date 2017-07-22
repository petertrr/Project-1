#include<iostream>
#include<string>

#include"set.h"

inline int min(int a, int b) {return a<b ? a : b ;}

Set::Set() : size_(0), cur_(nullptr), next_(nullptr)
{ 
	std::cout<<"Constructor\n";
}

Set::Set(const Set &set) : size_(0), cur_(nullptr), next_(nullptr)
{
	for (List *ptr = set.cur_;ptr != nullptr;)
	{
		add(ptr->data);
		ptr = ptr->prev;
	}
	std::cout<<"Copy constructor\n";
}

Set::Set(Set &&set) : Set()
{
	swap(*this, set);
	std::cout << "Move constructor\n";
}

Set& Set::operator=(const Set &set)
{
	if (this != &set) {
		Set buf(set);
		swap(*this, buf);
	}
	std::cout << "Assignment\n";
	return *this;
}

Set::~Set()
{
	for (List* ptr = cur_; ;)
	{
		if (ptr != nullptr) { delete ptr->next; ptr = ptr->prev; }
		else if (ptr == nullptr) { delete ptr; break; }
	}
}

void Set::swap(Set& set1, Set& set2)
{
	std::swap(set1.size_, set2.size_);
	std::swap(set1.cur_, set2.cur_);
	std::swap(set1.next_, set2.next_);
}

void Set::add(int a)
{
	if (cur_ == nullptr) // есть ли значения слева?
	{
		++size_;
		cur_ = new List;
		cur_->data = a;
		cur_->next = nullptr;
		cur_->prev = nullptr;
		return;
	}
	if (contains(a)) return;
	++size_;
	next_ = new List;
	next_->data = a;
	next_->next = nullptr;
	next_->prev = cur_;
	cur_->next = next_;
	cur_ = next_;
	return;
	/*
	if (cur_ == nullptr) // есть ли значения слева?
	{
		cur_ = new List;
		cur_->data = a;
		cur_->next = nullptr;
		cur_->prev = nullptr;
		return;
	}
	else for (List* ptr = cur_; ;)
	{
		if (ptr == nullptr) return;
		else if(cur_->data < a) 
		{
			next_ = new List;
			next_->data = a;
			next_->next = nullptr;
			next_->prev = cur_;
			cur_->next = next_;
			cur_ = next_;
			return;
		}
		else if (cur_->data > a && cur_->prev->data < a)
		{
			next_ = new List;
			next_->data = a;
			next_->next = cur_;
			next_->prev = cur_->prev;
			cur_->prev->next = next_;
			cur_->prev = next_;
			cur_ = next_;
			return;
		}
		else if (cur_->data > a && cur_->prev->data > a) ptr = ptr->prev;
		else if (cur_->data == a) return;
	}
	*/
}

void Set::remove(int a)
{
	for (List* ptr = cur_; ptr != nullptr;)
	{
		if (ptr->data == a)
		{
			if (ptr->next == nullptr) //значение стоит с края
			{
				ptr->prev->next = nullptr;
			}
			else if(ptr->prev == nullptr) // с другого края 
			{
				ptr->next->prev = nullptr;
			}
			else
			{
				ptr->next->prev = ptr->prev;
				ptr->prev->next = ptr->next;
			}
			delete ptr;
			--size_;
			return;
		}
		else ptr = ptr->prev;
	}
	return;
}

bool Set::contains(int a)
{
	for (List* ptr = cur_; ptr != nullptr;)
	{
		if (ptr->data == a) return true;
		else ptr = ptr->prev;
	}
	return false;
}

Set Set::unite(Set &set1, Set &set2)
{
	Set result = set1;
	for (List* ptr = set2.cur_; ptr != nullptr;)
	{
		result.add(ptr->data);
		ptr = ptr->prev;
	}
	return result;
}

Set Set::intersect(Set &set1, Set &set2)
{
	Set result;
	for (List* ptr = set2.cur_; ptr != nullptr;)
	{
		if (set1.contains(ptr->data)) result.add(ptr->data);
		ptr = ptr->prev;
	}
	return result;
}

Set Set::subtract(Set &set1, Set &set2)
{
	Set result = set1;
	for (List* ptr = set2.cur_; ptr != nullptr;)
	{
		if (set1.contains(ptr->data)) 
			result.remove(ptr->data);
		ptr = ptr->prev;
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const Set& set)
{
	if(set.size() == 0) {os<<"{O}"; return os;}
	os<<"{ ";
	for(List* ptr = set.cur_; ptr != nullptr;)
	{
		os << ptr->data;
		ptr = ptr->prev;
		if( ptr != nullptr) os<<", ";
		else os<<" }";
	}
	return os;
}

std::istream& operator >> (std::istream& is, Set& set)
{
	Set buf;
	
	std::string str;
	while (1)
	{
		is >> str;
		for (int i = 0; i < str.length(); ++i)
			if (str[i] == '{' || str[i] == ',' || str[i] == ' ') continue;
			else if (str[i] == '}') break;
			else
			{
				int a = str[i] - '0';
				if (i != str.length() - 1)
					while (str[++i] != ',' && str[i] != '}')
						a = a * 10 + str[i] - '0';
				buf.add(a);
			}
			if (str[str.length() - 1] == '}')break;
	}
	set = buf;

	return is;
}