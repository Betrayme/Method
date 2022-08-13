#ifndef _bsl_
#define _bsl_
#include <iostream>

#ifndef _USENAMESPACES_
#define _USENAMESPACES_
using namespace std;
#endif

template<typename comparable>
class Binarysearchtree {
public:
    Binarysearchtree();
    Binarysearchtree(const comparable&);//拷贝构造
    ~Binarysearchtree();                //析构

    const Binarysearchtree<comparable>& operator=(Binarysearchtree<comparable>&);  //拷贝赋值
    void insert(const comparable&);           //插入元素
    void remove(const comparable&);           //删除元素
    bool contains(const comparable&) const;         //查找是否存在某元素,前序遍历
    bool isempty() const;                     //判断非空
    void printTree(ostream& out) const;                   //输出树
    void makeEmpty();                   //清空树
private:
    struct node {
        comparable element;
        node* left = nullptr;
        node* right = nullptr;

        node(const comparable& theElement, struct node* theleft, struct node* theright) //节点构造,insert的时候使用
            :element(theElement), left(theleft), right(theright) {}
    };

    node* root;

    void insert(const comparable&, node*&);
    void remove(const comparable&, node*&);
    node* clone(node* t) const;
    node* findMin(node*) const;
    node* findMax(node*) const;
    bool contains(const comparable&, const node*) const;
    void printTree(ostream&, node*) const;   //中序遍历
    void makeEmpty(node*);                   //清空树
};

//public成员函数
template<typename comparable>
inline Binarysearchtree<comparable>::Binarysearchtree() :root(nullptr) {}

template<typename comparable>
inline Binarysearchtree<comparable>::Binarysearchtree(const comparable& theElement) : root(new node(theElement, nullptr, nullptr)) {}

template<typename comparable>
inline Binarysearchtree<comparable>::~Binarysearchtree()
{
    makeEmpty();
}

template<typename comparable>
inline const Binarysearchtree<comparable>& Binarysearchtree<comparable>::operator=(Binarysearchtree<comparable>& rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
        return *this;
    }
    return *this;
}

template<typename comparable> inline void Binarysearchtree<comparable>::insert(const comparable& theElement)
{
    insert(theElement, root);
}

template<typename comparable> inline void Binarysearchtree<comparable>::remove(const comparable& theElement)
{
    remove(theElement, root);
}

template<typename comparable> inline bool Binarysearchtree<comparable>::contains(const comparable& theElement) const
{
    return contains(theElement, root);
}

template<typename comparable> inline bool Binarysearchtree<comparable>::isempty() const
{
    if (root == nullptr)
        return true;
    else
        return false;
}

template<typename comparable> inline void Binarysearchtree<comparable>::printTree(ostream& out) const
{
    if (isempty())
        out << "the tree is empty!" << endl;
    else
        printTree(out, root);
}

template<typename comparable> inline void Binarysearchtree<comparable>::makeEmpty()
{
    makeEmpty(root);
}

//private成员函数
template<typename comparable> inline void Binarysearchtree<comparable>::insert(const comparable& theElement, node* &nod)
{
    if (nod == nullptr)
        nod = new node(theElement, nullptr, nullptr);
    else if (theElement < nod->element)
        insert(theElement, nod->left);
    else if (theElement > nod->element)
        insert(theElement, nod->right);
    else
        ;//找到元素,do nothing
}

template<typename comparable> inline void Binarysearchtree<comparable>::remove(const comparable& theElement, node* &nod)
{
    if (nod == nullptr)
        return;
    else if (theElement < nod->element)
        remove(theElement, nod->left);
    else if (theElement > nod->element)
        remove(theElement, nod->right);
    else if (nod->left == nullptr)
    {
        node* oldptr = nod;
        nod = nod->left;
        delete oldptr;
    }
    else if (nod->right == nullptr)
    {
        node* oldptr = nod;
        nod = nod->right;
        delete oldptr;
    }
    else
    {
        nod->element = findmin(nod->right)->element;
        remove(nod->element, nod->right);
    }
}

template <typename comparable>
inline typename Binarysearchtree<comparable>::node* Binarysearchtree<comparable>::clone(node* t) const
{
    if (t == nullptr)
        return nullptr;
    return new node(t->element, clone(t->left), clone(t->right));
}

template <typename comparable>
inline typename Binarysearchtree<comparable>::node* Binarysearchtree<comparable>::findMin(node* nod) const
{
    if (nod == nullptr)
        return nod;
    else if (nod->left != nullptr)
    {
        findMin(nod->left);
    }
    else
        return nod;
}

template <typename comparable>
inline typename Binarysearchtree<comparable>::node* Binarysearchtree<comparable>::findMax(node* nod) const
{
    if (nod == nullptr)
        return nod;
    else if (nod->right != nullptr)
    {
        findMax(nod->left);
    }
    else
        return nod;
}

template <typename comparable>
inline bool Binarysearchtree<comparable>::contains(const comparable& theElement, const node* nod) const
{
    if (nod == nullptr)
        return false;
    else if (nod->element > theElement)
        contains(theElement, nod->left);
    else if (nod->element < theElement)
        contains(theElement, nod->right);
    else
        return true;
}

template<typename comparable> inline void Binarysearchtree<comparable>::printTree(ostream& out, node* nod) const
{
    if (nod == nullptr)
        return;
    else
    {
        printTree(out, nod->left);
        out << nod->element << " ";
        printTree(out, nod->right);
    }
}

template<typename comparable> inline void Binarysearchtree<comparable>::makeEmpty(node* nod)
{
    if (nod != nullptr)
    {
        makeEmpty(nod->left);
        makeEmpty(nod->right);
        delete(nod);
    }
    else
        ;
}
#endif