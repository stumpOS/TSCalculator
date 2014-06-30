#pragma once
#ifndef Iterator_H_
#define Iterator_H_

/*! Base class for iterators.
 */
template<class T> class Iterator
{
public:
    virtual ~Iterator() {}
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() = 0;
    virtual T Current() = 0;
};

/*! Iterator smart pointer
 */
template <class T> class IteratorPtr
{
public:
    IteratorPtr(Iterator<T> * i) : _iter(i) {}
    ~IteratorPtr() {delete _iter;}
    Iterator<T> *operator->() {return _iter;}
    Iterator<T> &operator*() {return *_iter;}

private:
    IteratorPtr();
    IteratorPtr(const IteratorPtr *);
    IteratorPtr &operator=(IteratorPtr &);

    //! The pointer to the actual iterator
    Iterator<T> *_iter;
};

//! General purpose null iterator
template <class T> class CNullIterator : public Iterator<T>
{
public:
    virtual void First() {}
    virtual void Next() {}
    virtual bool IsDone() {return true;}
    virtual T Current() {return NULL;}
};


#endif /* Iterator_H_ */