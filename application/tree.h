#pragma once

#include<iostream>
#include <string>
using namespace std;

//结点类型
template <typename T>
struct BinTreeNode{
    T data;                                                                     //结点中存储的数据
    BinTreeNode<T> *leftChild, *rightChild;                                     //左子树和右子树
    BinTreeNode() : leftChild(nullptr), rightChild(nullptr) {}                  //无参构造函数
    BinTreeNode(const T& x, BinTreeNode<T> *l = nullptr,
        BinTreeNode<T> *r = nullptr)
        : data(x), leftChild(l), rightChild(r) {}           //带默认值的有参构造参数
    BinTreeNode(const BinTreeNode<T>*& node) 
        : data(node->data), leftChild(nullptr), rightChild(nullptr){}
    virtual ~BinTreeNode() {}
};

//线索二叉树节点类型
template <typename T>
struct ThreadBTNode : public BinTreeNode<T>{
    int ltag, rtag;                                        //标记线索: 1为线索, 0为孩子节点
    ThreadBTNode() : BinTreeNode<T>(), ltag(0), rtag(0) {}
    ThreadBTNode(const T& x, ThreadBTNode<T>* l = nullptr,
        ThreadBTNode<T>* r = nullptr)
        : BinTreeNode<T>(x, l, r), ltag(0), rtag(0) {}     //带默认值的构造函数
    ThreadBTNode(const BinTreeNode*& node) 
        : BinTreeNode<T>(node), ltag(0), rtag(0) {}
    virtual ~ThreadBTNode() {}
};

//二叉树类
template <typename T>
class BinaryTree{
public:
//==========二叉树构造与析构==========//

    //构造函数
    BinaryTree() : root(nullptr) {}

    //指定结束标志的构造函数
    BinaryTree(T value) : root(nullptr), RefValue(value) {}

    //析构函数
    ~BinaryTree() { Destroy(root); }

//==========二叉树的创建==========//

    //使用广义表创建二叉树，以'#'字符代表结束
    void CreateBinTree() { CreateBinTree(root); }

    //前序遍历创建二叉树(前序遍历的应用)，用#表示空结点
    void CreateBinTree_PreOrder() { CreateBinTree_PreOrder(root); }

    //使用先序遍历和中序遍历创建二叉树
    void CreateBinTreeBy_Pre_In(const char *pre, const char *in){
        int n = strlen(pre);
        CreateBinTreeBy_Pre_In(root, pre, in, n);
    }

    //使用后序遍历和中序遍历创建二叉树
    void CreateBinTreeBy_Post_In(const char *post, const char *in){
        int n = strlen(post);
        CreateBinTreeBy_Post_In(root, post, in, n);
    }

//==========二叉树的遍历==========//
    //先序遍历（递归）
    void PreOrder() { PreOrder(root); }

    //中序遍历(递归)
    void InOrder() { InOrder(root); }

    //后序遍历（递归）
    void PostOrder() { PostOrder(root); }

    //先序遍历(非递归)
    void PreOrder_NoRecurve() { PreOrder_NoRecurve(root); }

    //中序遍历(非递归)
    void InOrder_NoRecurve() { InOrder_NoRecurve(root); }

    //后序遍历(非递归)
    void PostOrder_NoRecurve() { PostOrder_NoRecurve(root); }

    //层次遍历(非递归)
    void LevelOrder() { LevelOrder(root); }

//==========获取结点==========//

    //获取二叉树的根节点
    BinTreeNode<T> *getRoot() const{
        return root;
    }

    //获取current结点的父节点
    BinTreeNode<T> *Parent(BinTreeNode<T> *current){
        return (root == nullptr || root == current) ? nullptr : Parent(root, current); //如果没有根节点或current结点就是root结点，就没有父节点
    }

    //获取current结点的左结点
    BinTreeNode<T> *LeftChild(BinTreeNode<T> *current){
        return (current != nullptr) ? current->leftChild : nullptr;
    }

    //获取current结点的右结点
    BinTreeNode<T> *RightChild(BinTreeNode<T> *current){
        return (current != nullptr) ? current->rightChild : nullptr;
    }

//==========成员函数==========//

    //销毁函数
    void Destroy() { Destroy(root); }

    //拷贝二叉树(前序遍历的应用)
    BinaryTree(BinaryTree<T> &s){
        root = Copy(s.getRoot());
    }

    //判断两颗二叉树是否相等(前序遍历的应用)
    bool operator==(BinaryTree<T> &s){
        return (equal(this->getRoot(), s.getRoot()));
    }

    //计算二叉树的结点的个数(后序遍历的应用)
    int Size() { return Size(root); }

    //计算二叉树的高度（后序遍历的应用）
    int Height() { return Height(root); }

    //判断二叉树是否为空
    bool Empty() { return (root == nullptr) ? true : false; }

    //以广义表的形式输出二叉树(前序遍历的应用)
    void PrintBinTree() { PrintBinTree(root); }

protected:
//==========内部函数==========//

    //使用广义表创建二叉树函数,这里以“字符”创建二叉树,以'#'字符代表结束
    void CreateBinTree(BinTreeNode<T>*& BT);

    //创建二叉树(利用已知的二叉树的前序遍历创建)用#表示空结点
    void CreateBinTree_PreOrder(BinTreeNode<T>*& subTree);

    //使用先序遍历和中序遍历创建二叉树
    void CreateBinTreeBy_Pre_In(BinTreeNode<T>*& cur, const char* pre, const char* in, int n);

    //使用后序遍历和中序遍历创建二叉树
    void CreateBinTreeBy_Post_In(BinTreeNode<T>*& cur, const char* post, const char* in, int n);
    
    //访问元素
    void visit(BinTreeNode<T>*& node) const;

    //先序遍历(递归)
    void PreOrder(BinTreeNode<T>*& subTree) const;

    //中序遍历(递归)
    void InOrder(BinTreeNode<T>*& subTree) const;

    //后序遍历(递归)
    void PostOrder(BinTreeNode<T>*& subTree) const;

    //先序遍历（非递归）
    void PreOrder_NoRecurve(BinTreeNode<T>* p) const;

    //中序遍历(非递归)
    void InOrder_NoRecurve(BinTreeNode<T>* root) const;

    //后序遍历(非递归)
    void PostOrder_NoRecurve(BinTreeNode<T>* p) const;

    //层次遍历(非递归)
    void LevelOrder(BinTreeNode<T>* p) const;

    //从结点subTree开始，搜索结点current的父节点,找到返回父节点的地址，找不到返回NULL
    BinTreeNode<T>* Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current) const;

    //二叉树的销毁
    void Destroy(BinTreeNode<T>*& subTree);

    //复制二叉树函数，返回一个指针，给出一个以originNode为根复制的二叉树的副本
    BinTreeNode<T>* Copy(BinTreeNode<T>* originNode) const;

    //判断两颗二叉树是否相等
    bool equal(BinTreeNode<T>* a, BinTreeNode<T>* b) const;

    //计算二叉树以subTree为根的结点的个数
    int Size(BinTreeNode<T>* subTree) const;

    //计算二叉数以subTree为根的高度
    int Height(BinTreeNode<T>* subTree) const;

    //以广义表的形式输出二叉树
    void PrintBinTree(BinTreeNode<T>* BT) const;

private:
    BinTreeNode<T> *root; //根节点
    T RefValue;           //数据输入停止的标志，需要一个构造函数
};

//线索二叉树类
template <typename T>
class ThreadBinaryTree {
public:
    ThreadBinaryTree() :root(nullptr), flag(0) {}

    //利用二叉树来构造线索二叉树
    ThreadBinaryTree(const BinTreeNode<T>*& node) {
        CreateTree(root);
    }

    //先序线索化二叉树
    void PreorderThread(ThreadBTNode<T>*& root) const {
        if (root) {
            ThreadBTNode<T>* pre = nullptr;
            visit(root, pre);
            InorderThread(root->leftChild, pre);
            InorderThread(root->rightChild, pre);
            if (!pre->rightChild) {
                pre->rtag = 1;
            }
        }
    }

    //中序线索化二叉树
    void InorderThread(ThreadBTNode<T>*& root) const {
        if (root) {
            ThreadBTNode<T>* pre = nullptr;
            InorderThread(root->leftChild, pre);
            visit(root, pre);
            InorderThread(root->rightChild, pre);
            if (!pre->rightChild) {
                pre->rtag = 1;
            }
        }
    }

    //后序线索化二叉树
    void PostorderThread(ThreadBTNode<T>*& root) const {
        if (root) {
            ThreadBTNode<T>* pre = nullptr;
            InorderThread(root->leftChild, pre);
            InorderThread(root->rightChild, pre);
            visit(root, pre);
            if (!pre->rightChild) {
                pre->rtag = 1;
            }
        }
    }

private:
    //访问节点并线索化
    void Visit(ThreadBTNode<T>*& root, ThreadBTNode<T>*& pre) const;

    //先序线索化二叉树(传递前驱)
    void PreorderThread(ThreadBTNode<T>*& root, ThreadBTNode<T>*& pre);

    //中序线索化二叉树(传递前驱)
    void InorderThread(ThreadBTNode<T>*& root, ThreadBTNode<T>*& pre);

    //后序线索化二叉树(传递前驱)
    void PostorderThread(ThreadBTNode<T>*& root, ThreadBTNode<T>*& pre);

    //复制节点
    void CreateTree(ThreadBTNode<T>*& root, const BinTreeNode<T>*& node);

    //根节点
    ThreadBTNode<T>* root;
    //标记线索类型 0--未线索化  1--先序  2--中序  3--后序 
    int flag;
};
