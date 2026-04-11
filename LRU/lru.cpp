#include "Lru.h"

void LRU::MoveFront(Node* node)
{
	node->prev = head;
	node->next = head->next;
	head->next->prev = node;
	head->next = node;
	return;
}

void LRU::Del(Node* node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
	return;
}

void LRU::MoveHead(Node* node)
{
	Del(node);
	MoveFront(node);
	return;
}

LRU::LRU(int cap) : capacity(cap), size(0)
{
	head = new Node(0,0);
	tail = new Node(0,0);
	head->next = tail;
	tail->prev = head;
};

LRU::~LRU()
{
	while (tail != head)
	{
		Node* node = tail;
		tail = tail->prev;
		delete node;
	}
	delete head;
}

void LRU::Put(int key, int value)
{
	auto it = index.find(key);
	if (it != index.end())
	{
		it->second->value = value;
		MoveHead(it->second);
	}
	else
	{
		if (size < capacity)
		{
			Node* node = new Node(key, value);
			index[key] = node;
			++size;
			MoveFront(node);
		}
		else
		{
			Node* node = tail->prev;
			index.erase(node->key);
			node->key = key;
			node->value = value;
			index[key] = node;
			MoveHead(node);
		}
	}
	return;
}

void LRU::put(int key, int value)
{
	Put(key, value);
}

int LRU::Get(int key)
{
	auto it = index.find(key);
	if (it != index.end())
	{
		Node* node = it->second;
		MoveHead(node);
		return node->value;
	}
	else
		return -1;
}

int LRU::get(int key)
{
	return Get(key);
}