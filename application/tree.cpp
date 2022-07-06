#include "tree.h"
#include <queue>
#include <stack>
#include <vector>
#include<iostream>
using namespace std;


//==============================二叉树==================================//


//使用广义表创建二叉树函数,这里以“字符”创建二叉树,以'#'字符代表结束
//A（B（D，E（G，）），C（，F））#
template<typename T>
void BinaryTree<T>::CreateBinTree(BinTreeNode<T>*& BT){
    stack<BinTreeNode<T>*> s;
    BT = nullptr;
    BinTreeNode<T>* cur = nullptr, * data = nullptr; //cur用来记住当前创建的节点，data用来记住栈顶的元素
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


//==============================二叉线索树==================================//

//该树第一个被访问的节点
template<typename T>
ThreadBTNode<T>* ThreadBinaryTree<T>::FindFirst(ThreadBTNode<T>*& root) const {
    ThreadBTNode<T>* p = root;
    if (p) {
        switch (flag) {
        case 1:
            //第一个访问的是根节点
            break;
        case 2:
            //第一个访问的是最左边的节点
            while (p->leftChild) {
                p = p->leftChild;
            }
            break;
        case 3:
            //第一个访问的是最左边的节点
            while (p->leftChild) {
                p = p->leftChild;
            }
            break;
        default:
            std::cout << "数据异常" << std::endl;
        }
    }
    return p;
}

//该树最后一个被访问的节点
template<typename T>
ThreadBTNode<T>* ThreadBinaryTree<T>::FindLast(ThreadBTNode<T>*& root) const {
    ThreadBTNode<T>* p = root;
    if (p) {
        switch (flag) {
        case 1:
            //最后一个访问的是最右边的节点
            while (p->rightChild) {
                p = p->rightChild;
            }
            break;
        case 2:
            //最后一个访问的是最右边的节点
            while (p->rightChild) {
                p = p->rightChild;
            }
            break;
        case 3:
            //最后一个访问的是根节点
            break;
        default:
            std::cout << "数据异常" << std::endl;
        }
    }
    return p;
}


//找到该节点的后继
template<typename T>
ThreadBTNode<T>* ThreadBinaryTree<T>::FindNext(ThreadBTNode<T>*& root) const {
    ThreadBTNode<T>* p = root;
    if (p) {
        switch (flag) {
            //先序的后继
        case 1:
            if (!p->rtag && p->leftChild) {
                return p->leftChild;
            }
            return p->rightChild;
            break;
            //中序的后继
        case 2:
            if (!p->rtag) {
                return FindFirst(p->rightChild);
            }
            return p->rightChild;
            break;
            //后序的后继
        case 3:
            //同========先序的前驱
            // 找到父节点
            // 1.可再次重新遍历(dfs bfs)找到父节点
            // 2.改变节点构造,新加一个父节点
            // 比较复杂,暂未实现
            break;
        default:
            std::cout << "数据异常" << std::endl;
        }
    }
}

//找到该节点的前驱
template<typename T>
ThreadBTNode<T>* ThreadBinaryTree<T>::FindPre(ThreadBTNode<T>*& root) const {
    ThreadBTNode<T>* p = root;
    if (p) {
        switch (flag) {
            //先序的前驱
        case 1:
            // 找到父节点
            // 1.可再次重新遍历(dfs bfs)找到父节点
            // 2.改变节点构造,新加一个父节点
            // 比较复杂,暂未实现
            break;
            //中序的前驱
        case 2:
            if (!p->ltag) {
                return FindLast(p->leftChild);
            }
            return p->leftChild;
            break;
            //后序的前驱
        case 3:
            if (!p->ltag && p->rightChild) {
                return p->rightChild;
            }
            return p->leftChild;
            break;
        default:
            std::cout << "数据异常" << std::endl;
        }
    }
}

//访问节点
template<typename T>
void ThreadBinaryTree<T>::Visit(ThreadBTNode<T>*& root) const {
    std::cout << root->data << " ";
}


//先序线索化二叉树(传递前驱)
template<typename T>
void ThreadBinaryTree<T>::PreorderThread(ThreadBTNode<T>*& root, ThreadBTNode<T>*& pre) {
    if (root) {
        Thread(root, pre);
        InorderThread(root->leftChild, pre);
        InorderThread(root->rightChild, pre);
    }
}

//中序线索化二叉树(传递前驱)
template<typename T>
void ThreadBinaryTree<T>::InorderThread(ThreadBTNode<T>*& root, ThreadBTNode<T>*& pre){
    if (root) {
        InorderThread(root->leftChild, pre);
        Thread(root, pre);
        InorderThread(root->rightChild, pre);
    }
}

//hou序线索化二叉树(传递前驱)
template<typename T>
void ThreadBinaryTree<T>::PostorderThread(ThreadBTNode<T>*& root, ThreadBTNode<T>*& pre) {
    if (root) {
        InorderThread(root->leftChild, pre);
        InorderThread(root->rightChild, pre);
        Thread(root, pre);
    }
}

//访问节点并线索化
template<typename T>
void ThreadBinaryTree<T>::Thread(ThreadBTNode<T>*& root, ThreadBTNode<T>*& pre) const {
    if (!root->leftChild) {
        root->leftChild = pre;
        root->ltag = 1;
    }
    if (pre && pre->rightChild == nullptr) {
        pre->rightChild = root;
        pre->rtag = 1;
    }
    pre = root;
}

//复制节点
template<typename T>
void ThreadBinaryTree<T>::CreateTree(ThreadBTNode<T>*& root, const BinTreeNode<T>*& node) {
    if (node) {
        root = new ThreadBTNode<T>(node);
        if (node->leftChild) {
            CreateTree(root->leftChild, node->leftChild);
        }
        else {
            root->ltag = 1;
        }
        if (node->rightChild) {
            CreateTree(root->rightChild, node->rightChild);
        }
        else {
            root->rtag = 1;
        }
    }
}
