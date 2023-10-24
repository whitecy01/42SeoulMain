#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <list>
#include <stack>
#include <iostream>

template<typename T>
class MutantStack : public std::stack<T>
{
	public:
	MutantStack() {};
	~MutantStack(){};
	MutantStack( const MutantStack &mutantStack)
	{
		*this = mutantStack;
	}
	MutantStack& operator=( const MutantStack  &mutantStack)
	{
		if (this == &mutantStack)
		{
			return *this;
		}
		return *this;
	}

	/* iterator */
	typedef typename MutantStack<T>::stack::container_type::iterator iterator;
	iterator begin(void) { return this->c.begin();};
	iterator end(void) { return this->c.end();};

	/* reverse_iterator */
	typedef typename MutantStack<T>::stack::container_type::reverse_iterator reverse_iterator;
	reverse_iterator rbegin(void) { return this->c.rbegin();};
	reverse_iterator rend(void) { return this->c.rend();};

	/* const_iterator */
	typedef typename MutantStack<T>::stack::container_type::const_iterator const_iterator;
	const_iterator cbegin(void)  { return this->c.cbegin();};
	const_iterator cend(void)  { return this->c.cend();};

	/* const_reverse_iterator */
	typedef typename MutantStack<T>::stack::container_type::const_reverse_iterator const_reverse_iterator;
	const_reverse_iterator crbegin(void)  { return this->c.crbegin();};
	const_reverse_iterator crend(void)  { return this->c.crend();};
};


#endif