#pragma once
#include "tree.h"
#include <vector>
#include <iostream>

//这是平衡二叉树的AVL树（Adelson-Velsky and Landis Tree）
template <typename T>
class AVL : public Tree<T>
{
private:
 struct Node
 {
 T data;
 Node* left;
 Node* right;
 int height;
 Node(const T& data) :data(data), left(NULL), right(NULL), height(1) {}
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

 //相对于BST特有的私有函数
 int GetHeight(Node* node) const;
 int GetBalance(Node* node) const;
 void UpdateHeight(Node* node);
 Node* RotateRight(Node* y);
 Node* RotateLeft(Node* x);
 Node* Balance(Node* node);

public:
 AVL() :root(NULL), node_count(0) {}
 ~AVL() { Clear(); }

 //基本操作
 void Insert(const T& data) override;
 void Search(const T& data) override;
 void Remove(const T& data) override;
 void Clear() override;
 //遍历（升序）
 void InOrder() const override;
 void PreOrder() const override;
 void PostOrder() const override;
 //获取节点个数，判断非空
 int Size() const override { return node_count; }
 bool Empty() const override { return node_count ==0; }
};
