#include "AVL.h"
#include <algorithm>

//先是辅助私有函数，递归实现
template <typename T>
typename AVL<T>::Node* AVL<T>::Insert(Node* node, const T& data)
{
	if (!node)
	{
		node_count++;
		return new Node(data);
	}
	if (data < node->data)
		node->left = Insert(node->left, data);
	else if (data > node->data)
		node->right = Insert(node->right, data);
		
	UpdateHeight(node);
	return Balance(node);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::Search(Node* node, const T& data) const
{
	if (!node)
	{
		return NULL;
	}
	if (data < node->data)
		return Search(node->left, data);
	else if (data > node->data)
		return Search(node->right, data);
	else
		return node;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::Remove(Node* node, const T& data)
{
	if (!node)
	{
		return NULL;
	}
	if (data < node->data)
		node->left = Remove(node->left, data);
	else if (data > node->data)
		node->right = Remove(node->right, data);
	else
	{
		if (!node->left || !node->right)
		{
			Node* temp = node->left ? node->left : node->right;
			if (!temp)
			{
				temp = node;
				node = NULL;
			}
			else
				*node = *temp;
			delete temp;
			node_count--;
		}
		else
		{
			Node* temp = FindMin(node->right);
			node->data = temp->data;
			node->right = Remove(node->right, temp->data);
		}
	}
	
	if (!node)
		return NULL;

	UpdateHeight(node);
	return Balance(node);
}

template <typename T>
typename AVL<T>::Node* AVL<T>::FindMin(Node* node) const
{
	while (node && node->left)
		node = node->left;
	return node;
}

template <typename T>
void AVL<T>::InOrder(Node* node, std::vector<T>& result) const
{
	if (node)
	{
		InOrder(node->left, result);
		result.push_back(node->data);
		InOrder(node->right, result);
	}
}

template <typename T>
void AVL<T>::PreOrder(Node* node, std::vector<T>& result) const
{
	if (node)
	{
		result.push_back(node->data);
		PreOrder(node->left, result);
		PreOrder(node->right, result);
	}
}

template <typename T>
void AVL<T>::PostOrder(Node* node, std::vector<T>& result) const
{
	if (node)
	{
		PostOrder(node->left, result);
		PostOrder(node->right, result);
		result.push_back(node->data);
	}
}

template <typename T>
void AVL<T>::Clear(Node* node)
{
	if (node)
	{
		Clear(node->left);
		Clear(node->right);
		delete node;
		node_count--;
	}
}

template <typename T>
int AVL<T>::GetHeight(Node* node) const
{
	return node ? node->height : 0;
}

template <typename T>
int AVL<T>::GetBalance(Node* node) const
{
	return node ? GetHeight(node->left) - GetHeight(node->right) : 0;
}

template <typename T>
void AVL<T>::UpdateHeight(Node* node)
{
	node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::RotateRight(Node* imbalance)
{
	Node* x = imbalance->left;
	Node* y = x->right;
	x->right = imbalance;
	imbalance->left = y;
	UpdateHeight(imbalance);
	UpdateHeight(x);
	return x;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::RotateLeft(Node* imbalance)
{
	Node* x = imbalance->right;
	Node* y = x->left;
	x->left = imbalance;
	imbalance->right = y;
	UpdateHeight(imbalance);
	UpdateHeight(x);
	return x;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::Balance(Node* node)
{
	int balance = GetBalance(node);
	if (balance > 1)
	{
		if (GetBalance(node->left) < 0)
			node->left = RotateLeft(node->left);
		return RotateRight(node);
	}
	else if (balance < -1)
	{
		if (GetBalance(node->right) > 0)
			node->right = RotateRight(node->right);
		return RotateLeft(node);
	}
	return node;
}

//这是公共接口的实现，调用私有函数
template <typename T>
void AVL<T>::Insert(const T& data)
{
	root = Insert(root, data);
}

template <typename T>
void AVL<T>::Search(const T& data)
{
	Node* result = Search(root, data);
	if (result)
	{
		std::cout << "FIND!" << std::endl;
	}
	else
	{
		std::cout << "NOT FOUND " << std::endl;
	}
}

template <typename T>
void AVL<T>::Remove(const T& data)
{
	root = Remove(root, data);
}

template <typename T>
void AVL<T>::Clear()
{
	Clear(root);
	root = NULL;
}

template <typename T>
void AVL<T>::InOrder() const
{
	if (!root)
	{
		std::cout << "Illegal" << std::endl;
		return;
	}
	std::vector<T> result;
	InOrder(root, result);
	for (const T& data : result)
		std::cout << data << " ";
	std::cout << std::endl;
}

template <typename T>
void AVL<T>::PreOrder() const
{
	if (!root)
	{
		std::cout << "Illegal" << std::endl;
		return;
	}
	std::vector<T> result;
	PreOrder(root, result);
	for (const T& data : result)
		std::cout << data << " ";
	std::cout << std::endl;
}

template <typename T>
void AVL<T>::PostOrder() const
{
	if (!root)
	{
		std::cout << "Illegal" << std::endl;
		return;
	}
	std::vector<T> result;
	PostOrder(root, result);
	for (const T& data : result)
		std::cout << data << " ";
	std::cout << std::endl;
}

// 显式实例化以解决链接器“无法解析的外部符号”问题
template class AVL<int>;
template class AVL<float>;
template class AVL<double>;
template class AVL<char>;
template class AVL<unsigned int>;
template class AVL<long>;
template class AVL<long long>;
template class AVL<short>;

