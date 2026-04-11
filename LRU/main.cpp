#include "Lru.h"
#include <iostream>
#include <string>

int main()
{
	int n;
	int capacity;
	std::cin >> capacity >> n;
	if (capacity <= 0)
	{
		std::cout << "Illegal Input!" << std::endl;
	}
	LRU cache(capacity);

	for(int i = 0; i < n; i++)
	{
		std::string op;
		std::cin >> op;
		if(op == "put")
		{
			int key, value;
			std::cin >> key >> value;
			cache.put(key, value);
		}
		else if(op == "get")
		{
			int key;
			std::cin >> key;
			std::cout << cache.get(key) << std::endl;
		}
	}

	return 0;
}