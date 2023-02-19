#pragma once

class Class;
class SafePtrBase
{

protected:
	SafePtrBase* prev;
	SafePtrBase* next;
	Class* ptr;

public:
	virtual		~SafePtrBase()
	{
		throw "Shouldn't execute nightfall's SafePtrBaSE Destructor.";
	}
};
template<class T>
class SafePtr : public SafePtrBase
{
public:
	template< class U > friend bool operator==(SafePtr<U> a, U* b);
	template< class U > friend bool operator!=(SafePtr<U> a, U* b);
	template< class U > friend bool operator==(U* a, SafePtr<U> b);
	template< class U > friend bool operator!=(U* a, SafePtr<U> b);
	template< class U > friend bool operator==(SafePtr<U> a, SafePtr<U> b);
	template< class U > friend bool operator!=(SafePtr<U> a, SafePtr<U> b);

	bool operator !() const;
	operator T* () const;
	T* operator->() const;
	T& operator*() const;
};


template<class T>
inline bool operator==(SafePtr<T> a, T* b)
{
	return a.ptr == b;
}

template<class T>
inline bool operator!=(SafePtr<T> a, T* b)
{
	return a.ptr != b;
}

template<class T>
inline bool operator==(T* a, SafePtr<T> b)
{
	return a == b.ptr;
}

template<class T>
inline bool operator!=(T* a, SafePtr<T> b)
{
	return a != b.ptr;
}

template<class T>
inline bool operator==(SafePtr<T> a, SafePtr<T> b)
{
	return a.ptr == b.ptr;
}

template<class T>
inline bool operator!=(SafePtr<T> a, SafePtr<T> b)
{
	return a.ptr != b.ptr;
}

template<class T>
inline bool SafePtr<T>::operator !() const
{
	return ptr == NULL;
}

template<class T>
inline SafePtr<T>::operator T* () const
{
	return (T*)ptr;
}

template<class T>
inline T* SafePtr<T>::operator->() const
{
	return (T*)ptr;
}

template<class T>
inline T& SafePtr<T>::operator*() const
{
	return *(T*)ptr;
}
