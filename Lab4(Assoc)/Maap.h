#include <exception>
//перемещаюзий конструктор
//оператор равно
template <class IND, class INF>
struct Pair{
    IND first;
    INF second;
    Pair* left;
    Pair* right;
    Pair():first(IND( )),second(0){ }
    Pair(const IND &name):first(name), second(0){ }
};

template <class IND, class INF>
        class MaapIt;


template <class IND, class INF>
class Maap{
    friend class MaapIt<IND, INF>;
private:
    static const int QUOTA = 10;
    int cnt, cur;
    Pair<IND, INF> *arr;//указатель на первый элемент
    int getPos(const IND &) const;
public:
    Maap():cnt(QUOTA), cur(0), arr(new Pair<IND, INF>){ }
    Maap(const Maap<IND, INF> &);
    ~Maap(){delete [ ] arr;}//переделать
    Maap<IND, INF>& operator = (const Maap<IND, INF> &);

    INF & operator[](const IND &); // l-value
    const INF & operator[](const IND &) const; // r-value
    typedef MaapIt<IND, INF> Iterator;
    Iterator begin( );
    Iterator end( );
    Iterator find(const IND &) const;


//    int size();
//    bool empty();
//    Maap<class Key, class MyType>::iterator find(Key);
//    Maap::MyType& insert(Key, Maap::MyType);
//    void erase(Key);
//    void erase(Maap<class Key, class MyType>::iterator);
//    Maap<class Key, class MyType>::iterator begin();
//    Maap<class Key, class MyType>::iterator end();

};

template <class IND, class INF>
class MaapIt{
private:
    Pair<IND, INF> *cur;
public:
    MaapIt( ):cur(0){ }
    MaapIt(Pair<IND, INF> *a):cur(a){ }
    int operator !=(const MaapIt<IND, INF> &) const;
    int operator ==(const MaapIt<IND, INF> &) const;
    Pair<IND, INF>& operator *( );
    Pair<IND, INF>* operator ->( );
    MaapIt<IND, INF>& operator ++( );
    MaapIt<IND, INF> operator ++(int);

};

template <class IND, class INF>
Maap<IND, INF>::Maap( const Maap<IND, INF> &a) :cnt(a.cnt), cur(a.cur), arr(new Pair[a.cnt])
{
    for(int i = 0; i < cnt; ++i)
        arr[i] = a.arr[i];

}

template <class IND, class INF>
Maap<IND, INF>& Maap<IND, INF>::operator = (
        const Maap<IND, INF> &a) {
    if(this != &a) {
        delete [ ] arr;
        arr = new Pair<IND, INF> [cnt = a.cnt];
        cur = a.cur;
        for(int i = 0; i < cnt; ++i)
            arr[i] = a.arr[i];

    }
    return *this;
}

template <class IND, class INF>
int Maap<IND, INF>::getPos(const IND &s) const
{
    for(int i = 0; i < cur; ++i)
        if(arr[i].first == s)
            return i;

    return -1;
}

template <class IND, class INF>
INF & Maap<IND, INF>::operator[](const IND &s)
{
    int i = getPos(s);
    if (i < 0){
        i = cur;
        if (cur >= cnt){
            Pair<IND, INF> *old = arr;
            arr = new Pair<IND, INF>[cnt += QUOTA];
            for (i = 0; i < cur; ++i)
                arr[i] = old[i];
            delete[] old;
        }
        arr[cur].first = s;
        ++cur;
    }
    return arr[i].second;
}

template <class IND, class INF>
const INF & Maap<IND, INF>::operator[ ](const IND &s)
const
{
    int i = getPos(s);
    if (i < 0)
        throw std::runtime_error("Illegal index");
    return arr[i].second;
}

template <class IND, class INF>
MaapIt<IND, INF> Maap<IND, INF>::begin( )
{
    return AssocIt<IND, INF>(this->arr);
}

template <class IND, class INF>
MaapIt<IND, INF> Maap<IND, INF>::end( )
{
    return AssocIt<IND, INF>(this->arr + cur);
}

template <class IND, class INF>
MaapIt<IND, INF> Maap<IND, INF>::find(const IND &s)
const
{
    int i = getPos(s);
    if(i < 0)
        i = cur;
    return AssocIt<IND, INF>(this->arr + i);
}


template <class IND, class INF>
int MaapIt<IND, INF>::operator !=(
        const MaapIt<IND, INF> &it) const
{
    return cur != it.cur;
}

template <class IND, class INF>
int MaapIt<IND, INF>::operator ==(
        const MaapIt<IND, INF> &it) const
{
    return cur == it.cur;
}

template <class IND, class INF>
Pair<IND, INF>& MaapIt<IND, INF>::operator *( )
{
    return *cur;
}

template <class IND, class INF>
Pair<IND, INF>* MaapIt<IND, INF>::operator ->( )
{
    return cur;
}

template <class IND, class INF>
MaapIt<IND, INF>& MaapIt<IND, INF>::operator ++( )
{
    ++cur;
    return *this;
}

template <class IND, class INF>
MaapIt<IND, INF> MaapIt<IND, INF>::operator ++(int)
{

    MaapIt<IND, INF> res(*this);
    ++cur;
    return res;

}