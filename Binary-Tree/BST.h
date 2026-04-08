#pragma once
#include "tree.h"
#include <vector>
#include <iostream>

template <typename T>
class BST : public Tree<T>
{
private:
 struct Node
 {
 T data;
 Node* left;
 Node* right;
 Node(const T& data) :data(data), left(NULL), right(NULL) {}
 };

 Node* root;
 int node_count;

 Node* Insert(Node* node, const T& data);
 Node* Search(Node* node, const T& data) const;
 Node* Remove(Node* node, const T& data);
 Node* FindMin(Node* node) const;
 void InOrder(Node* node, std::vector<T>& result) const;
 void PreOrder(Node* node, std::vector<T>& result) const;
 void PostOrder(Node* node, std::vector<T>& result) const;
 void Clear(Node* node);

public:
 BST() :root(NULL), node_count(0) {}
 ~BST() { Clear(); }

 void Insert(const T& data) override;
 void Search(const T& data) override;
 void Remove(const T& data) override;
 void Clear() override;

 void InOrder() const override;
 void PreOrder() const override;
 void PostOrder() const override;

 int Size() const override { return node_count; }
 bool Empty() const override { return node_count ==0; }
};
