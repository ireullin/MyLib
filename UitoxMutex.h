#ifndef __UITOXMUTEX__
#define __UITOXMUTEX__

namespace Uitox{
namespace Threading{

class Mutex
{
private:
	Mutex(const Mutex&);
	Mutex& operator= (const Mutex&);

	pthread_mutex_t	m_handle;

	void exception(int error_no)
	{
		switch(error_no)
		{
		case EAGAIN:	throw UITOX_EXPCEPTION_2(error_no ,"The system lacked the necessary resources (other than memory) to initialise another mutex.");
		case ENOMEM:	throw UITOX_EXPCEPTION_2(error_no ,"Insufficient memory exists to initialise the mutex.");
		case EPERM:		throw UITOX_EXPCEPTION_2(error_no ,"The caller does not have the privilege to perform the operation."); 
		case EBUSY:		throw UITOX_EXPCEPTION_2(error_no ,"The implementation has detected an attempt to re-initialise the object referenced by mutex, a previously initialised, but not yet destroyed, mutex.");
		//case EBUSY:		throw UITOX_EXPCEPTION_2(error_no ,"The implementation has detected an attempt to destroy the object referenced by mutex while it is locked or referenced (for example, while being used in a pthread_cond_wait() or pthread_cond_timedwait()) by another thread."); 
		case EINVAL:	throw UITOX_EXPCEPTION_2(error_no ,"The value specified by mutex is invalid.");
		default:		throw UITOX_EXPCEPTION_2(error_no ,"Unknown mutex error");
		}
	}


public:
	Mutex()
	{
		int _rc = pthread_mutex_init(&m_handle, NULL);
		if(_rc!=0)exception(_rc);
	}


	virtual ~Mutex()
	{
		int _rc = pthread_mutex_destroy(&m_handle);
		if(_rc!=0)exception(_rc);
	}


	/// Return false if timeout.
	bool lock(double waitSecond)
	{
		struct timespec _now;
		clock_gettime(CLOCK_REALTIME, &_now);
		double _deadLine = waitSecond + ((double)_now.tv_nsec / NANO);
		int _deadSec = floor(_deadLine);
		double _deadNsec = _deadLine - _deadSec;
		_now.tv_sec = _now.tv_sec + _deadSec;
		_now.tv_nsec = _deadNsec*NANO;

		int _rc1 = pthread_mutex_timedlock(&m_handle, &_now);
		if ( _rc1 == ETIMEDOUT )
			return false;

		if( _rc1 != 0 )
			exception(_rc1);
		
		return true;
	}
	

	void lock()
	{
		int _rc = pthread_mutex_lock(&m_handle); 
		if(_rc!=0)exception(_rc);
	}
	
	
	void unlock()
	{
		int _rc = pthread_mutex_unlock(&m_handle); 
		if(_rc!=0)exception(_rc);
	}
	

	bool locked()
	{
		int _rc = pthread_mutex_trylock(&m_handle);
		if(_rc==EBUSY)
			return true;

		if(_rc!=0)
			exception(_rc);

		this->unlock();
		return false;
	}


	pthread_mutex_t handle()
	{return m_handle;}
}; // class Mutex


class AutoLock
{
private:
	AutoLock(const AutoLock&);
	AutoLock& operator= (const AutoLock&);
	Mutex& m_mutex;
	
public:
	AutoLock(Mutex& mutex)
		:m_mutex(mutex)
	{m_mutex.lock();}

	virtual ~AutoLock()
	{m_mutex.unlock();}
};


} // namespace Threading
} // namespace Uitox
#endif
