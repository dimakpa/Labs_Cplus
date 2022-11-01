#include <iostream>
#include <exception>
//++() - следу.щий по размеру ключ ()++ - вернуть текущий
// ()--, --()
using namespace std;

template<class IND, class INF>
struct Pair {
    IND first;
    INF second;

    Pair() : first(IND()), second(INF()) {}
    Pair(const IND &key) : first(key), second(INF()) {}
    Pair(const IND &key, const INF &info) : first(key), second(info) {}
};

template<class value>
struct Node {
    Node *left = nullptr;
    Node *right = nullptr;
    value pair;
    Node *parent = nullptr;
    Node(){};
    Node(value &val) : pair(val){};
};

template<class IND, class INF>
class MaapIt;

template<class IND, class INF>
class Map {
    friend class MaapIt<IND, INF>;

private:
    void copy(Node<Pair<IND, INF>> *);
    Node<Pair<IND, INF>> *root = nullptr;
    void deleter(Node<Pair<IND, INF>> *&node);
    void AddNodeToSubtree(Node<Pair<IND, INF>> *parent_root, IND key, INF info);
    void PrintTreeNode(Node<Pair<IND, INF>> *roott);
    void DelNodeImpl(Node<Pair<IND, INF>>*, IND);
    Node<Pair<IND, INF>> * Leftmost(Node<Pair<IND, INF>> * node);
    Node<Pair<IND, INF>> * Rightmost(Node<Pair<IND, INF>> * node);


public:
    Map() { root = nullptr; };
    Map(Pair<IND, INF> &);
    Map(const Map &);
    Map(Map &&) noexcept;
    ~Map();
    Map operator = (const Map &);
    Map &operator = (Map &&);
    Node<Pair<IND, INF>> *getRoot(){return root;};
    void AddNode(IND a, INF b){ AddNodeToSubtree(root, a, b); };
    void PrintTree(){ PrintTreeNode(root); }
    void DelNode(IND key){ DelNodeImpl(root, key);}
    //MaapIt<IND, INF> findNode(Node<Pair<IND, INF>>*, const IND &) const;


    typedef MaapIt<IND, INF> Iterator;
    Iterator begin();
    Iterator end();
    //Iterator find(const IND &) { return MaapIt<IND, INF>(findNode(root, root->pair.first));};
};


template<class IND, class INF>
class MaapIt {
private:
    Node<Pair<IND, INF>> *node;
public:
    MaapIt(Node<Pair<IND, INF>> *a) : node(a) {}
    MaapIt(const MaapIt &maapit): node(maapit.node){}
    MaapIt(MaapIt &&) noexcept;
    MaapIt &operator=(MaapIt &&);

    int operator!=(const MaapIt<IND, INF> &) const;
    int operator==(const MaapIt<IND, INF> &) const;
    Node<Pair<IND, INF>> &operator*();
    Node<Pair<IND, INF>> *operator->();
    MaapIt<IND, INF> &operator++();//возвращает следующий по размеру ключ
    MaapIt<IND, INF> operator++(int);//возвращает текущий ключ и перемещает указатель на следующий
    MaapIt<IND, INF> &operator--();//возвращает предыдущий элемент
    MaapIt<IND, INF> operator--(int);//возвращает текущий элемент и сдвигает указатель на предыдущий
};


template<class IND, class INF>
Map<IND, INF>::Map(Map<IND, INF> &&table) noexcept {
    root = table.root;
    table.root = nullptr;
}

template<class IND, class INF>
Map<IND, INF>::Map(Pair<IND, INF> &r){
     root = new Node (r);
}

template<class IND, class INF>
Map<IND, INF>::~Map() {
    if (root) {
        //deleter(root);
    }
}

template<class IND, class INF>
void Map<IND, INF>::deleter(Node<Pair<IND, INF>>*&node) {
    if (node->left != nullptr) {
        deleter(node->left);
    }
    if (node->right != nullptr) {
        deleter(node->right);
    }
    Node<Pair<IND, INF>> *node1 = node;
    node = nullptr;
    delete node1;

}


template<class IND, class INF>
void Map<IND, INF>::AddNodeToSubtree(Node<Pair<IND, INF>> *parent_root, IND key, INF info) {

    if (key != parent_root->pair.first) {
        Pair<IND, INF> newpair = Pair<IND, INF>(key, info);
        auto *newnode = new Node<Pair<IND, INF>>();
        if (key < parent_root->pair.first) {
            if (parent_root->left == nullptr) {
                parent_root->left = newnode;
                parent_root->left->parent = parent_root;
                newnode->pair = newpair;
                newnode->parent = parent_root;
//            newnode->left = nullptr;
//            newnode->right = nullptr;
            } else {
                AddNodeToSubtree(parent_root->left, key, info); /*(1)*/
            }

        }
        if (parent_root->pair.first < key) {
            if (parent_root->right == NULL) {
                parent_root->right = newnode;
                parent_root->right->parent = parent_root;
                newnode->pair = newpair;
            } else AddNodeToSubtree(parent_root->right, key, info);/*(2)*/
        }
    }
}
template<class IND, class INF>
void Map<IND, INF>::PrintTreeNode(Node<Pair<IND, INF>> *roott) {
    if (roott != nullptr) {
        PrintTreeNode(roott->left);
        cout << "First: " << roott->pair.first << " Second: " << roott->pair.second << endl;
        PrintTreeNode(roott->right);
    }
}

template<class IND, class INF>
void Map<IND, INF>::DelNodeImpl(Node<Pair<IND, INF>> *node, IND value) {

    if (node == nullptr)
        throw exception();
    if (value < node->pair.first)
        return DelNodeImpl(node->left, value);
    if (value > node->pair.first)
        return DelNodeImpl(node->right, value);
    else {
        if(node->left == nullptr && node->right == nullptr && node->parent != nullptr){
            if(node->parent->left == node)
                node->parent->left = nullptr;
            else
                node->parent->right = nullptr;
            delete node;
        } else if (node->parent != nullptr){
            Node<Pair<IND, INF>> * newnode = nullptr;
            if(node->left != nullptr)
                newnode = Rightmost(node->left);
            else
                newnode = Leftmost(node->right);

            if(node->parent->left == node)
                node->parent->left = newnode;
            else
                node->parent->right = newnode;

            newnode->parent = node->parent;
            newnode->right = node->right;
            newnode->left = node->left;

            delete node;
        } else {
            if (node->left != nullptr){
                Node<Pair<IND, INF>> *newnode = node;
                Node<Pair<IND, INF>> *newnode2 = root;
                root = node->left;
                Node<Pair<IND, INF>> *par = root;
                while ( par->right != nullptr)
                    par = par->right;
                par->right = newnode->right;
                deleter(newnode);

            } else if (node->right == nullptr )
                deleter( root);
            else {
                Node<Pair<IND, INF>> *newnode = node;
                root = node->right;
                deleter(newnode);
            }
        }
    }
}


template<class IND, class INF>
Node<Pair<IND, INF>> *Map<IND, INF>::Leftmost(Node<Pair<IND, INF>> * node) {
    if (node == nullptr)
        return nullptr;
    if (node->left != nullptr) {
        return Leftmost(node->left);
    }
    return node;
}

template<class IND, class INF>
Node<Pair<IND, INF>> * Map<IND, INF>::Rightmost(Node<Pair<IND, INF>> * node) {
    if (node == nullptr)
        return nullptr;
    if (node->right != nullptr) {
        return Rightmost(node->right);
    }
    return node;
}

template<class IND, class INF>
Node<Pair<IND, INF>> &MaapIt<IND, INF>::operator*() {
    return *node;
}

template<class IND, class INF>
Node<Pair<IND, INF>> *MaapIt<IND, INF>::operator->() {
    return node;
}
//template<class IND, class INF>
//Pair<IND, INF> *MaapIt<IND, INF>::operator->() {
//    return node->pair;
//}


template<class IND, class INF>
MaapIt<IND, INF> Map<IND, INF>::begin() {
    Node<Pair<IND, INF>> *node = this->root;
    while (node->left != nullptr){
        node = node->left;
    }
    return MaapIt<IND, INF>(node);
}

template<class IND, class INF>
MaapIt<IND, INF> Map<IND, INF>::end() {
    Node<Pair<IND, INF>> *node = this->root;
    while (node->right != nullptr)
        node = node->right;
    return MaapIt<IND, INF>(node);
}

//template<class IND, class INF>
//MaapIt<IND, INF> Map<IND, INF>::findNode(Node<Pair<IND, INF>> *node,const IND &s)const {
//    if (this->root->pair.first == s)
//        return MaapIt<IND, INF>(this->root);
//    if (node->pair.first < s)
//        if (node->right != nullptr)
//            return findNode(node->right, s);
//    if (node->pair.first > s)
//        if (node->left != nullptr)
//            return findNode(node->left, s);
//}

template<class IND, class INF>
Map<IND, INF> &Map<IND, INF>::operator=(Map &&tree) {

    if (this != &tree) {
        Pair<IND, INF> tmp = root;
        root = tree.root;
        tree.root = tmp;
    }
    return *this;
}

template<class IND, class INF>
Map<IND, INF>::Map(const Map &map) {
    this->root = map.root;
    copy(map.root);
}

template<class IND, class INF>
void Map<IND, INF>::copy(Node<Pair<IND,INF>> *node1) {
    if (node1 != nullptr){
        AddNode(node1->pair.first, node1->pair.second);
        copy(node1->left);
        copy(node1->right);
    }

}

template<class IND, class INF>
Map<IND, INF> Map<IND, INF>::operator=(const Map<IND, INF> &map) {
    return Map(map);
}


template<class IND, class INF>
MaapIt<IND, INF>::MaapIt(MaapIt<IND, INF> &&it) noexcept {
   node = it.node;
   it.node = nullptr;
}

template<class IND, class INF>
MaapIt<IND, INF> &MaapIt<IND, INF>::operator =(MaapIt<IND, INF> &&it) {
    if (this != &it) {
        Node<Pair<IND, INF>> tmp = node;
        node = it.root;
        it.node = tmp;
    }
    return *this;
}

template<class IND, class INF>
int MaapIt<IND, INF>::operator!=(const MaapIt<IND, INF> &it) const {
    return node->pair != it.node->pair;
}

template<class IND, class INF>
int MaapIt<IND, INF>::operator==(const MaapIt<IND, INF> &it) const {
    return node->pair == it.node->pair;
}

template<class IND, class INF>
MaapIt<IND, INF> &MaapIt<IND, INF>::operator++() {

    if (node->right != nullptr){
        if (node->right->left == nullptr) {
            node = node->right;
            return *this;
        }
        else{
            Node<Pair<IND, INF>> *par = node->right;
            while (par->left != nullptr)
                par = par->left;
            node = par;
            return *this;
        }
    } else if(node->parent == nullptr) {
        std::cout << "It's max element";
        throw exception();
    }

    else{
            Node<Pair<IND, INF>> *par = node->parent;
            while (par->parent != nullptr && par->pair.first < node->pair.first){
                par = par->parent;
            }
            if(par->pair.first > node->pair.first){
                node = par;
                return *this;
            }
            else{
                std::cout << "It's max element";
                throw exception();

            }
    }
}

template<class IND, class INF>
MaapIt<IND, INF> MaapIt<IND, INF>::operator++(int) {
    MaapIt maapIt(node);//временный объект
    ++(*this);
    return maapIt;
}

template<class IND, class INF>
MaapIt<IND, INF> &MaapIt<IND, INF>::operator--() {
    //1)
    if (node->left != nullptr){
        if (node->left->right == nullptr){
            node = node->left;
            return *this;
        }
        else{
            Node<Pair<IND, INF>> *par = node->left;
            while (par->right != nullptr)
                par = par->right;
            node = par;
            return *this;
        }
    } else if(node->parent == nullptr) {
        std::cout << "It's min element";
        throw exception();
    }
        //2)
    else{
        Node<Pair<IND, INF>> *par = node->parent;
        while (par->parent != nullptr && par->pair.first > node->pair.first){
            par = par->parent;
        }
        if(par->pair.first < node->pair.first) {
            node = par;
            return *this;
        }
        else{
            std::cout << "It's min element";
            throw exception();
        }
    }
}

template<class IND, class INF>
MaapIt<IND, INF> MaapIt<IND, INF>::operator--(int) {
    MaapIt maapIt(node);//временный объект
    --(*this);
    return maapIt;
}
