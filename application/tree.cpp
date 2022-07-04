#include "tree.h"
#include <queue>
#include <stack>
#include <vector>
#include<iostream>
using namespace std;

//使用广义表创建二叉树函数,这里以“字符”创建二叉树,以'#'字符代表结束
//A（B（D，E（G，）），C（，F））#
template<typename T>
void BinaryTree<T>::CreateBinTree(BinTreeNode<T>*& BT){
    stack<BinTreeNode<T>*> s;
    BT = nullptr;
    BinTreeNode<T>* cur, * data; //cur用来记住当前创建的节点，data用来记住栈顶的元素
    int key;                 //key是处理左、右子树的标记
    T ch;
    cin >> ch;

    while (ch != RefValue){
        switch (ch){
        case '(': //对(做处理
            s.emplace(cur);
            key = 1;
            break;

        case ')': //对)做处理
            s.pop();
            break;

        case ',': //对,做处理
            key = 2;
            break;

        default:
            cur = new BinTreeNode<T>(ch); //构造一个结点
            if (BT == nullptr) {           //如果头节点是空
                BT = cur;
            }
            else if (key == 1) { //链入*t的左孩子
                data = s.top();
                data->leftChild = cur;
            }
            else {//链入*t的右孩子
                data = s.top();
                data->rightChild = cur;
            }
        }
        cin >> ch;
    }
}

//创建二叉树(利用已知的二叉树的前序遍历创建)用#表示空结点
//ABC##DE#G##F###   #表示空节点
template<typename T>
void BinaryTree<T>::CreateBinTree_PreOrder(BinTreeNode<T>*& subTree){
    T item;
    if (cin >> item){
        if (item != RefValue){
            subTree = new BinTreeNode<T>(item);             //构造结点
            CreateBinTree_PreOrder(subTree->leftChild);     //递归创建左子树
            CreateBinTree_PreOrder(subTree->rightChild);    //递归创建右子树
        }
        else{
            subTree == nullptr;
        }
    }
}

//使用先序遍历和中序遍历创建二叉树
template<typename T>
void BinaryTree<T>::CreateBinTreeBy_Pre_In(BinTreeNode<T>*& cur, const char* pre, const char* in, int len){
    if (len <= 0){
        cur = nullptr;
        return;
    }
    int k = 0;
    while (pre[0] != in[k]) { //在中序中找到pre[0]的值
        if (++k > len) {
            cerr << "datas is wrong!" << endl;
            exit(1);
        }
    }
    cur = new BinTreeNode<T>(in[k]);            //创建结点
    CreateBinTreeBy_Pre_In(cur->leftChild, pre + 1, in, k);                         //递归创建左子树
    CreateBinTreeBy_Pre_In(cur->rightChild, pre + k + 1, in + k + 1, len - k - 1);  //递归创建右子树
}

//使用后序遍历和中序遍历创建二叉树
template<typename T>
void BinaryTree<T>::CreateBinTreeBy_Post_In(BinTreeNode<T>*& cur, const char* post, const char* in, int len){
    if (len == 0) {
        cur = nullptr;
        return;
    }

    char cur = *(post + len - 1);    //根结点值
    cur = new BinTreeNode<T>(cur); //构造当前结点

    int key = 0;
    const char* temp = in;
    while (*temp != cur){
        ++key;
        ++temp;
    }
    CreateBinTreeBy_Post_In(cur->leftChild, post, in, key);                              //递归创建左子树
    CreateBinTreeBy_Post_In(cur->rightChild, post + key, temp + 1, len - key - 1);   //递归创建右子树
}

//访问元素
template<typename T>
void BinaryTree<T>::visit(BinTreeNode<T>*& node) const {
    cout << node->data << " ";
}


//先序遍历(递归)
template<typename T>
void BinaryTree<T>::PreOrder(BinTreeNode<T>*& subTree) const {
    if (subTree != nullptr) {
        visit(subTree);
        PreOrder(subTree->leftChild);
        PreOrder(subTree->rightChild);
    }
}

//中序遍历(递归)
template<typename T>
void BinaryTree<T>::InOrder(BinTreeNode<T>*& subTree) const {
    if (subTree != nullptr) {
        InOrder(subTree->leftChild);
        visit(subTree);
        InOrder(subTree->rightChild);
    }
}

//后序遍历(递归)
template<typename T>
void BinaryTree<T>::PostOrder(BinTreeNode<T>*& subTree) const {
    if (subTree != nullptr){
        PostOrder(subTree->leftChild);
        PostOrder(subTree->rightChild);
        visit(subTree);
    }
}

//先序遍历（非递归）
template<typename T>
void BinaryTree<T>::PreOrder_NoRecurve(BinTreeNode<T>* node) const {
    if (node == nullptr)
        return;
    stack<BinTreeNode<T>*> S;
    BinTreeNode<T>* t;
    S.emplace(node);           //根节点进栈
    while (!S.empty()) {    //当栈不为空
        t = S.top();        //p先记住栈顶元素，然后栈顶出栈
        S.pop();
        cout << t->data << " ";         //访问元素
        if (t->rightChild != nullptr) {    //右孩子不为空，右孩子进栈
            S.emplace(t->rightChild);
        }
        if (t->leftChild != nullptr) {     //左孩子不为空，左孩子进栈
            S.emplace(t->leftChild);
        }
    }
}

//中序遍历(非递归)
template<typename T>
void BinaryTree<T>::InOrder_NoRecurve(BinTreeNode<T>* node) const {
    if (node == nullptr)
        return;
    stack<BinTreeNode<T>*> s;
    s.emplace(node);
    while (!s.empty()){
        while (s.top()->leftChild != nullptr) {     //将左结点依次入栈
            s.emplace(s.top()->leftChild);
        }
        while (!s.empty()){
            BinTreeNode<T>* cur = s.top();
            cout << cur->data << " ";
            s.pop();
            if (cur->rightChild != nullptr){
                s.emplace(cur->rightChild);
                break;
            }
        }
    }
}

//后序遍历(非递归)
template<typename T>
void BinaryTree<T>::PostOrder_NoRecurve(BinTreeNode<T>* node) const {
    if (root == nullptr)
        return;
    stack<BinTreeNode<T>*> s;
    s.emplace(node);
    BinTreeNode<T>* lastPop = nullptr;
    while (!s.empty()){
        while (s.top()->leftChild != nullptr) {
            s.emplace(s.top()->leftChild);
        }
        while (!s.empty()){
            //右叶子结点 || 没有右结点
            if (lastPop == s.top()->rightChild || s.top()->rightChild == nullptr) {
                cout << s.top()->data << " ";
                lastPop = s.top();
                s.pop();
            }
            else if (s.top()->rightChild != nullptr){
                s.emplace(s.top()->rightChild);
                break;
            }
        }
    }
}

//层次遍历(非递归)
template<typename T>
void BinaryTree<T>::LevelOrder(BinTreeNode<T>* p) const {
    queue<BinTreeNode<T>*> que;
    que.emplace(p); //根节点进队
    BinTreeNode<T>* t;
    while (!que.empty()){
        t = que.front(); //t先记住队头,再将队头出队
        que.pop();
        cout << t->data << " "; //访问队头元素的数据

        if (t->leftChild != nullptr){
            que.emplace(t->leftChild);
        }
        if (t->rightChild != nullptr){
            que.emplace(t->rightChild);
        }
    }
}

//从结点subTree开始，搜索结点current的父节点,找到返回父节点的地址，找不到返回NULL
template<typename T>
BinTreeNode<T>* BinaryTree<T>::Parent(BinTreeNode<T>* subTree, BinTreeNode<T>* current)const {
    if (subTree == nullptr){
        return nullptr;
    }
    if (subTree->leftChild == current || subTree->rightChild == current) { //如果找到，返回父节点subTree
        return subTree;
    }
    BinTreeNode<T>* p;
    if (p = Parent(subTree->leftChild, current) != nullptr){ //递归在左子树中搜索
        return p;
    }
    else{
        return Parent(subTree->rightChild, current); //递归右子树中搜索
    }
}

//二叉树的销毁
template<typename T>
void BinaryTree<T>::Destroy(BinTreeNode<T>*& subTree){
    if (subTree != nullptr){
        Destroy(subTree->leftChild);
        Destroy(subTree->rightChild);
        delete subTree;
        subTree = nullptr;
    }
}

//复制二叉树函数，返回一个指针，给出一个以originNode为根复制的二叉树的副本
template<typename T>
BinTreeNode<T>* BinaryTree<T>::Copy(BinTreeNode<T>* originNode) const {
    if (originNode == nullptr){
        return nullptr;
    }
    BinTreeNode<T>* temp = new BinTreeNode<T>; //创建根结点
    temp->data = originNode->data;
    temp->leftChild = Copy(originNode->leftChild);
    temp->rightChild = Copy(originNode->rightChild);
    return temp;
}

//判断两颗二叉树是否相等
template<typename T>
bool BinaryTree<T>::equal(BinTreeNode<T>* a, BinTreeNode<T>* b) const {
    if (a == nullptr && b == nullptr) { //两者都为空
        return true;
    }
    if (a != nullptr && b != nullptr && a->data == b->data &&
        equal(a->leftChild, b->leftChild) && 
        equal(a->rightChild, b->rightChild)) {//两者都不为空，且两者的结点数据相等，且两者的左右子树的结点都相等
        return true;
    }
    return false;
}

//计算二叉树以subTree为根的结点的个数
template<typename T>
int BinaryTree<T>::Size(BinTreeNode<T>* subTree) const{
    if (subTree == nullptr) {//递归结束，空树结点个数为0
        return 0;
    }
    return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
}

//计算二叉数以subTree为根的高度
template<typename T>
int BinaryTree<T>::Height(BinTreeNode<T>* subTree)const {
    if (subTree == nullptr) {//递归结束，空树高度为0
        return 0;
    }
    int i = Height(subTree->leftChild);
    int j = Height(subTree->rightChild);
    return i < j ? j + 1 : i + 1;
}

//以广义表的形式输出二叉树
template<typename T>
void BinaryTree<T>::PrintBinTree(BinTreeNode<T>* BT)const {
    if (BT != nullptr) {//树为空时结束递归
        cout << BT->data;
        if (BT->leftChild != nullptr || BT->rightChild != nullptr){
            cout << '(';
            if (BT->leftChild != nullptr){
                PrintBinTree(BT->leftChild);
            }
            cout << ',';
            if (BT->rightChild != nullptr){
                PrintBinTree(BT->rightChild);
            }
            cout << ')';
        }
    }
}