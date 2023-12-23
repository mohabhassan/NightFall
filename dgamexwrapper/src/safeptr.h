#pragma once

//class Class;

#define LL_Add(rootnode, newnode, next, prev) 			\
   {                                              			\
   (newnode)->next = (rootnode);                  			\
   (newnode)->prev = (rootnode)->prev;                	\
   (rootnode)->prev->next = (newnode);                	\
   (rootnode)->prev = (newnode);                      	\
   }

#define LL_Remove(node,next,prev) \
   {                                  \
   node->prev->next = node->next;     \
   node->next->prev = node->prev;     \
   node->next = node;                 \
   node->prev = node;                 \
   }
#define LL_Reset(list,next,prev)    (list)->next = (list)->prev = (list)
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

	void AddReference(Class* ptr);
	void RemoveReference(Class* ptr);
	void InitSafePtr(Class* newptr);

};

inline void SafePtrBase::AddReference(Class* ptr)
{
	if (!ptr->SafePtrList)
	{
		ptr->SafePtrList = this;
		LL_Reset(this, next, prev);
	}
	else
	{
		LL_Add(ptr->SafePtrList, this, next, prev);
	}
}

inline void SafePtrBase::RemoveReference(Class* ptr)
{
	if (ptr->SafePtrList == this)
	{
		if (ptr->SafePtrList->next == this)
		{
			ptr->SafePtrList = nullptr;
		}
		else
		{
			ptr->SafePtrList = next;
			LL_Remove(this, next, prev);
		}
	}
	else
	{
		LL_Remove(this, next, prev);
	}
}

inline void SafePtrBase::InitSafePtr(Class* newptr)
{
	if (ptr != newptr)
	{
		if (ptr)
		{
			RemoveReference(ptr);
		}

		ptr = newptr;
		if (ptr == nullptr)
		{
			return;
		}

		AddReference(ptr);
	}
}

template<class T>
class SafePtr : public SafePtrBase
{
public:
	SafePtr& operator=(T* const obj);
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
inline SafePtr<T>& SafePtr<T>::operator=(T* const obj)
{
	InitSafePtr(obj);
	return *this;
}


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
