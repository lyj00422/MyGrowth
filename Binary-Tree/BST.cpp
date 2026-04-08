#include "BST.h"

//先是辅助私有函数，递归实现
template <typename T>
typename BST<T>::Node* BST<T>::Insert(Node* node, const T& data)
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

    return node;
}

template <typename T>
typename BST<T>::Node* BST<T>::Search(Node* node, const T& data) const
{
    if (!node)
    {
        return node;
    }
    else if (data > node->data)
    {
        return Search(node->right, data);
    }
    else if (data < node->data)
    {
        return Search(node->left, data);
    }
    else
    {
        return node;
    }
}

template <typename T>
typename BST<T>::Node* BST<T>::FindMin(Node* node) const
{
    while (node && node->left)
    {
        node = node->left;
    }
    return node;
}

template <typename T>
typename BST<T>::Node* BST<T>::Remove(Node* node, const T& data)
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
    return node;
}

template <typename T>
void BST<T>::InOrder(Node* node, std::vector<T>& result) const
{
    if (node)
    {
        InOrder(node->left, result);
        result.push_back(node->data);
        InOrder(node->right, result);
    }
}

template <typename T>
void BST<T>::PreOrder(Node* node, std::vector<T>& result) const
{
    if (node)
    {
        result.push_back(node->data);
        PreOrder(node->left, result);
        PreOrder(node->right, result);
    }
}

template <typename T>
void BST<T>::PostOrder(Node* node, std::vector<T>& result) const
{
    if (node)
    {
        PostOrder(node->left, result);
        PostOrder(node->right, result);
        result.push_back(node->data);
    }
}

template <typename T>
void BST<T>::Clear(Node* node)
{
    if (node)
    {
        Clear(node->left);
        Clear(node->right);
        delete node;
        node_count--;
    }
}

//公共接口的实现

template <typename T>
void BST<T>::Insert(const T& data)
{
    root = Insert(root, data);
}

template <typename T>
void BST<T>::Search(const T& data)
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
void BST<T>::Remove(const T& data)
{
    root = Remove(root, data);
}

template <typename T>
void BST<T>::Clear()
{
    Clear(root);
    root = NULL;
}

template <typename T>
void BST<T>::InOrder() const
{
    if (!root)
    {
        std::cout << "Illegal" << std::endl;
        return;
    }
    std::vector<T> result;
    InOrder(root, result);
    for (const T& data : result)
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void BST<T>::PreOrder() const
{
    if (!root)
    {
        std::cout << "Illegal" << std::endl;
        return;
    }
    std::vector<T> result;
    PreOrder(root, result);
    for (const T& data : result)
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void BST<T>::PostOrder() const
{
    if (!root)
    {
        std::cout << "Illegal" << std::endl;
        return;
    }
    std::vector<T> result;
    PostOrder(root, result);
    for (const T& data : result)
    {
        std::cout << data << " ";
    }
    std::cout << std::endl;
}

// 显式实例化以解决链接器“无法解析的外部符号”问题
template class BST<int>;
template class BST<float>;
template class BST<double>;
template class BST<char>;
template class BST<unsigned int>;
template class BST<long>;
template class BST<long long>;
template class BST<short>;