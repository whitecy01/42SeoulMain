#include "Data.hpp"

uintptr_t serialize(Data* ptr)
{
	return(reinterpret_cast<uintptr_t>(ptr));
}

Data* deserialize(uintptr_t raw)
{
	return(reinterpret_cast<Data *>(raw));
}

int main(void)
{
	Data prev;
	Data *next;
	uintptr_t ptr;


	prev._data = "jaeyojun";
	std::cout << "prev : " << prev._data << std::endl;

	ptr = serialize(&prev);
	std::cout << "ptr : " << ptr << std::endl;

	next = deserialize(ptr);
	std::cout << "next : " << next->_data << std::endl;

	std::cout << "=========================================\n";

	Data d;
	Data *a;
	uintptr_t memory;

	d._data = "jaeyo";

	memory = serialize(&d);
	std::cout << "memory : " << memory << std::endl;

	a = deserialize(memory);

	std::cout << "a : " << a->_data << std::endl;


	return (0);
}