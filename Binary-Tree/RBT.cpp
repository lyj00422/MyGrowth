#include "RBT.h"
#include <iostream>
#include <vector>

//先是私有函数，因为存在父指针，就不再有递归了
template <typename T>
void RBT<T>::InsertImp(const T& data)
{
	if (!root)
	{
		root = new Node(data);
		root->color = false; //根节点为黑色
		node_count++;
		return;
	}//如果树为空，直接插入并设置为黑色（根为黑）

	Node* parent = NULL;
	Node* current = root;//双指针来找到插入位置
	while (current)
	{
		parent = current;
		if (data < current->data)
			current = current->left;
		else if (data > current->data)
			current = current->right;
		else
			return; //不允许重复元素
	}//找到插入位置

	Node* new_node = new Node(data);
	new_node->parent = parent;//设置为新节点的父节点
	if (data < parent->data)
		parent->left = new_node;
	else
		parent->right = new_node;//按大小插入，和BST一致
	node_count++;

	InsertFixUp(new_node);//插入修复
}

template <typename T>
void RBT<T>::Transplant(Node* u, Node* v)//用v替换u
{
    if (!u->parent)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v)
        v->parent = u->parent;
}

template <typename T>
void RBT<T>::LeftRotate(Node* father)//以三个连续的右子树连在一起的，传入的是最上面的那个节点（爷节点）
{
    Node* son = father->right;
	father->right = son->left;//将子节点的左孩子过继为父节点的右孩子

    if (son->left)
        son->left->parent = father;//为真才有父节点
    //过继完成，接下来将子节点升格
    Transplant(father, son);

    son->left = father; //将父节点下沉
	father->parent = son; 
}

template <typename T>
void RBT<T>::RightRotate(Node* father)//以三个连续的左子树连在一起的，传入的是最上面的那个节点（爷节点）
{//右旋和左旋对称，交换一下left和right就行了
    Node* son = father->left;
    father->left = son->right;
    if (son->right)
        son->right->parent = father;
    Transplant(father, son);
    son->right = father; 
	father->parent = son;
}

template <typename T>
void RBT<T>::InsertFixUp(Node* node)
{
    while (node != root && isRed(node->parent))//因为插入的是红节点，冲突只会是红红冲突了，故父节点为红就一直修复
    {
		if (node->parent == node->parent->parent->left)//分两种，先是父节点是爷节点的左子树
        {
            Node* uncle = node->parent->parent->right;//看叔节点
            if (isRed(uncle))//若为红色
            {//此时，父节点和叔节点都是红，爷节点是黑
				node->parent->color = false;//父节点变黑
				uncle->color = false;//叔节点变黑
				node->parent->parent->color = true;//爷节点变红
                node = node->parent->parent;//冲突往上转移
            }
			else//若为黑色
            {
                if (node == node->parent->right)
                {
                    node = node->parent;//说明是LR型，故先左旋
					LeftRotate(node->parent);//变为LL型
                }//此时父节点为红，爷节点为黑
                node->parent->color = false;//先变色再旋转
				node->parent->parent->color = true;//父节点变黑，爷节点变红
				RightRotate(node->parent->parent);//说明是LL型，右旋
            }
        }
		else//如果是右节点，情况对称，就是将left和right交换一下
        {
            Node* uncle = node->parent->parent->left;
            if (isRed(uncle))
            {
                node->parent->color = false;
                uncle->color = false;
                node->parent->parent->color = true;
                node = node->parent->parent;
            }
            else
            {
                if (node == node->parent->left)
                {
                    node = node->parent;
                    RightRotate(node->parent);
                }
                node->parent->color = false;
                node->parent->parent->color = true;
                LeftRotate(node->parent->parent);
            }
        }
    }
	root->color = false; //保持根节点为黑色，记得连续的黑节点不违反性质
}

template <typename T>
typename RBT<T>::Node* RBT<T>::Search(Node* node, const T& data) const
{
	if (!node)
		return NULL;
	if (data < node->data)
		return Search(node->left, data);
	else if (data > node->data)
		return Search(node->right, data);
	else
		return node;
}//搜索和BST一样，递归实现

template <typename T>
void RBT<T>::RemoveImpl(const T& data)//删除很操蛋,先删除，后调整颜色和旋转
{
	Node* node = Search(root, data);//先找到节点
	if (!node)
	{
		std::cout << "Illegal input!" << std::endl;
		return; // 元素不存在
	}

	Node* tran = node; //作用1.记录删除节点的颜色。2.在第一二中情况中作为node的别名。3.在第三种情况中作为转移的代替节点
	Node* tran_son = nullptr; //记录被移动节点的子节点，用于替换tran原来的位置
	Node* fix = nullptr; // 修复时使用的父节点
	bool tran_original_color = tran->color; //记录删除节点的颜色，用于判断是否需要修复

	// 分三种主要情况
	if (!node->left) // 没有左子树，直接用右子树替换
	{
		tran_son = node->right;
		fix = node->parent;
		Transplant(node, node->right);
	}
	else if (!node->right) // 没有右子树，直接用左子树替换
	{
		tran_son = node->left;
		fix = node->parent;
		Transplant(node, node->left);
	}
	else // 左右子树都存在，找到右子树的最小节点作为后继来替换
	{
		tran = FindMin(node->right); // tran现在为后继（最小节点）
		tran_original_color = tran->color;
		tran_son = tran->right;

		if (tran->parent == node)
		{
			fix = tran; // 后继直接为 node 的右子节点
		}
		else
		{
			fix = tran->parent;
			Transplant(tran, tran->right);//将右节点替换掉tran
			tran->right = node->right;//将node的右子树过继给tran，以便替换
			if (tran->right)
				tran->right->parent = tran;//真才有父节点
		}

		Transplant(node, tran);
		tran->left = node->left;
		if (tran->left)
			tran->left->parent = tran;
		tran->color = node->color;//直接替换颜色，保持性质
	}

	delete node;//没有左右孩子就直接删除
	node_count--;//删除节点

	//只要需要被删除的节点为黑色，就需要修复。因为破坏了黑路同。红的不做处理，和BST一样的删除罢了。
	if (!tran_original_color)
		RemoveFixUp(tran_son, fix);
}

template <typename T>
void RBT<T>::RemoveFixUp(Node* node, Node* parent)//作为上面函数的衔接，传入的是替换节点，和这个节点的父节点。因为替换节点可能为NULL，所以父节点也要传入 。传入的是双黑节点
{//思想：当删除一个黑色节点后，经过该节点的路径上黑色节点数少 1。我们把这个“缺少的黑色”向上传递，通过旋转和变色，直到遇到一个红色节点（将其涂黑）或到达根节点
	//这里的while对应删除的节点为黑
	while (node != root && !isRed(node))//只要没遇到红节点，就一直向上传递。或者来到根节点直接涂黑
	{	//分两种情况,是为了确定兄弟节点的位置，和旋转的方向（对称）
		if (node == parent->left)//若兄节点为右子树
		{
			Node* sibling = parent->right;
			if (isRed(sibling))//如果兄弟节点为红色
			{
				sibling->color = false;
				parent->color = true;//兄父变色，父变红，父朝双黑节点方向旋转。左子树就左旋，右子树就右旋。
				LeftRotate(parent);
				sibling = parent->right;//更新兄节点，一定为黑色
			}
			//如果兄节点为黑色
			if (!isRed(sibling->left) && !isRed(sibling->right))//兄节点均为黑色
			{
				sibling->color = true;//兄节点变红，双黑上移
				node = parent;
				parent = node->parent;//接着while判断
			}
			else//兄节点至少有一个红色子节点
			{
				if (!isRed(sibling->right))//只有一个左红节点（RL）
				{
					if (sibling->left)//if多余了，但是ai这样写，说是什么防御式编程，不理解但是加入
						sibling->left->color = false;
					sibling->color = true;//兄变红，子节点变黑
					RightRotate(sibling);//右旋，变为RR型
					sibling = parent->right;//更新兄节点，一定为黑色
				}
				sibling->color = parent->color;//兄节点继承父节点颜色
				parent->color = false;//强制涂黑
				if (sibling->right)
					sibling->right->color = false;//强制涂黑
				LeftRotate(parent);//强制让双黑节点node变为parent的子树，多了一个黑
				node = root;//调整完成
			}
		}
		else//完全对称
		{
			Node* sibling = parent->left;
			if (isRed(sibling))
			{
				sibling->color = false;
				parent->color = true;
				RightRotate(parent);
				sibling = parent->left;
			}
			if (!isRed(sibling->left) && !isRed(sibling->right))
			{
				sibling->color = true;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!isRed(sibling->left))
				{
					if (sibling->right)
						sibling->right->color = false;
					sibling->color = true;
					LeftRotate(sibling);
					sibling = parent->left;
				}
				sibling->color = parent->color;
				parent->color = false;
				if (sibling->left)
					sibling->left->color = false;
				RightRotate(parent);
				node = root;
			}
		}
	}

	if (node)//对应remove中只有左孩子或者右孩子的情况，直接变黑即可。补全缺少的黑色
		node->color = false;
}

template <typename T>
typename RBT<T>::Node* RBT<T>::FindMin(Node* node) const
{
    while (node && node->left)
        node = node->left;
    return node;
}//最下面的左孩子最小

template <typename T>
void RBT<T>::InOrder(Node* node, std::vector<T>& result) const
{
	if (!node)
		return;
	InOrder(node->left, result);
	result.push_back(node->data);
	InOrder(node->right, result);
}//中序遍历

template <typename T>
void RBT<T>::PreOrder(Node* node, std::vector<T>& result) const
{
	if (!node)
		return;
	result.push_back(node->data);
	PreOrder(node->left, result);
	PreOrder(node->right, result);
}//先序遍历

template <typename T>
void RBT<T>::PostOrder(Node* node, std::vector<T>& result) const
{
	if (!node)
		return;
	PostOrder(node->left, result);
	PostOrder(node->right, result);
	result.push_back(node->data);
}//后序遍历

template <typename T>
void RBT<T>::Clear(Node* node)
{
	if (!node)
		return;
	Clear(node->left);
	Clear(node->right);
	delete node;
}//递归清空树

//以下是公共接口的实现，调用私有函数
template class RBT<int>;
template class RBT<double>;
template class RBT<float>;
template class RBT<char>;

template <typename T>
void RBT<T>::Insert(const T& data)
{
	InsertImp(data);
}

template <typename T>
void RBT<T>::Search(const T& data)
{
	Node* node = Search(root, data);
	if (node)
		std::cout << "Found " << std::endl;
	else
		std::cout << "Not found!" << std::endl;
}

template <typename T>
void RBT<T>::Remove(const T& data)
{
	RemoveImpl(data);
}

template <typename T>
void RBT<T>::Clear()
{
	Clear(root);
	root = NULL;
	node_count = 0;
}

template <typename T>
void RBT<T>::InOrder() const
{
	std::vector<T> result;
	InOrder(root, result);
	for (const T& data : result)
		std::cout << data << " ";
	std::cout << std::endl;
}

template <typename T>
void RBT<T>::PreOrder() const
{
	std::vector<T> result;
	PreOrder(root, result);
	for (const T& data : result)
		std::cout << data << " ";
	std::cout << std::endl;
}

template <typename T>
void RBT<T>::PostOrder() const
{
	std::vector<T> result;
	PostOrder(root, result);
	for (const T& data : result)
		std::cout << data << " ";
	std::cout << std::endl;
}
