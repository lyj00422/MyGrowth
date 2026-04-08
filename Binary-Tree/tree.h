#pragma once
#include <iostream>
#include <vector>

//这是树类，包含之后所有树的必要操作，故为父类
//不同树的结点结构会不同，故这里不加
template <typename T>
class Tree
{
public:
 virtual ~Tree() = default; //虚析构，保证派生类正常释放

 //基本操作
 virtual void Insert(const T& data) =0;
 virtual void Search(const T& data) =0;
 virtual void Remove(const T& data) =0;
 virtual void Clear() =0;

 //遍历（升序）
 virtual void InOrder() const =0; //中序遍历
 virtual void PreOrder() const =0;
 virtual void PostOrder() const =0;

 //获取节点个数，判断非空
 virtual int Size() const =0;
 virtual bool Empty() const =0;
};
