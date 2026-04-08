#pragma once
#include "tree.h"

//这是红黑树（Red-Black Tree），是弱化版本的平衡二叉树
//插入和删除的效率更高，AVL树则是查找更快
template <typename T>
class RBT : public Tree<T>
{
private:
	struct Node
	{
		T data;
		Node* left;
		Node* right;
		Node* parent;
		bool color; //这里以bool为颜色判断，true为红色，false为黑色
		Node(const T& data) :data(data), left(NULL), right(NULL), parent(NULL), color(true) {}
	};

	Node* root;
	int node_count;

	bool isRed(Node* node) const
	{
		if (node == NULL) return false;
		return node->color;
	}

	//私有函数
	void InsertImp(const T& data);
	Node* Search(Node* node, const T& data) const;
	void RemoveImpl(const T& data);
	Node* FindMin(Node* node) const;
	void InOrder(Node* node, std::vector<T>& result) const;
	void PreOrder(Node* node, std::vector<T>& result) const;
	void PostOrder(Node* node, std::vector<T>& result) const;
	void Clear(Node* node);

	//特有的私有函数
	void LeftRotate(Node* x);//左旋
	void RightRotate(Node* x);//右旋
	void InsertFixUp(Node* node);//插入修复
	void RemoveFixUp(Node* node, Node* parent);//删除修复
	void Transplant(Node* u, Node* v);//用v替换u

public:
	RBT() : root(NULL), node_count(0) {}
	~RBT() { Clear(); }

	//公共接口
	void Insert(const T& data) override;
	void Search(const T& data) override;
	void Remove(const T& data) override;
	void Clear() override;

	void InOrder() const override;
	void PreOrder() const override;
	void PostOrder() const override;

	int Size() const override { return node_count; }
	bool Empty() const override { return node_count == 0; }
};