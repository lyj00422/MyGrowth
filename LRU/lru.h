#pragma once
#include <unordered_map>

class LRU
{
private:
	struct Node
	{
		struct Node* prev;
		struct Node* next;
		int key;
		int value;
		Node(int key, int value) :prev(nullptr), next(nullptr), key(key), value(value) {};
	};

	int capacity;
	int size;
	Node* head;
	Node* tail;//头和尾都不存储数据
	std::unordered_map<int, Node*> index;

	void Put(int key, int value);
	int Get(int key);
	void MoveFront(Node* node);
	void Del(Node* node);
	void MoveHead(Node* node);
public:
	LRU(int cap);
	~LRU();
	void put(int key, int value);
	int get(int key);
};