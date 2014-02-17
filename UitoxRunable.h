/***************************************************************************************************************
Classes of Runable and RunableEx both derived from IRunable.


Author: Ireul Lin
Last update: 2014/02/02
Copyright is owned by UITOX.
***************************************************************************************************************/
#ifndef __UITOXRUNABLE__
#define __UITOXRUNABLE__

namespace Uitox
{

// an interface
class IRunable
{
public:
	IRunable(){}
	virtual ~IRunable(){}
	virtual void* run(void*)=0;
};


/// for global method and static method.
class Runable1 : public IRunable
{
private:
	Runable1(const Runable1& r);
	Runable1& operator=(const Runable1& r);

	typedef void* (*MethodName)(void*, void*);
	MethodName	m_pMethod;
	void*		m_param;

public:
	Runable1(MethodName pfn , void* param=NULL)
	{
		m_pMethod = pfn;
		m_param = param;
	}

	virtual ~Runable1()
	{}

	virtual void* run(void* sender=NULL)
	{return (m_pMethod)(sender,m_param);}
};


/// for member method
template<typename T>
class Runable2 : public IRunable
{
private:
	Runable2(const Runable2& r);	
	Runable2& operator=(const Runable2& r);

	typedef void* (T::*MethodName)(void*, void*);
	MethodName	m_pMethod;
	T*			m_instance;
	void*		m_param;

public:
	Runable2(T* instance, MethodName pfn, void* param=NULL)
	{
		m_pMethod = pfn;
		m_instance = instance;
		m_param = param;
	}

	virtual ~Runable2()
	{}

	virtual void* run(void* sender=NULL)
	{return (m_instance->*m_pMethod)(sender,m_param);}
};


/// for funtor
template<typename T>
class Runable3 : public IRunable
{
private:
	Runable3(const Runable3& r);	
	Runable3& operator=(const Runable3& r);

	typedef void* (T::*MethodName)(void*, void*);
	MethodName	m_pMethod;
	T*			m_instance;
	void*		m_param;

public:
	Runable3(T* instance, void* param=NULL)
	{
		m_instance = instance;
		m_param = param;
	}

	virtual ~Runable3()
	{}

	virtual void* run(void* sender=NULL)
	{return m_instance->operator()(sender,m_param);}
};

}

#endif
