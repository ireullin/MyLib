#ifndef __UITOXCONDITION__
#define __UITOXCONDITION__


namespace Uitox{
namespace Threading{


class Condition
{
private:
	Condition(const Condition&);
	Condition& operator= (const Condition&);

	pthread_mutex_t	m_mu;
	pthread_cond_t  m_cn;

	void exception(int error_no)
	{
		switch(error_no)
		{
		case EAGAIN:	throw UITOX_EXPCEPTION_2(error_no, "The system lacked the necessary resources (other than memory) to initialise another mutex.");
		case ENOMEM:	throw UITOX_EXPCEPTION_2(error_no, "Insufficient memory exists to initialise the mutex.");
		case EPERM:		throw UITOX_EXPCEPTION_2(error_no, "The caller does not have the privilege to perform the operation."); 
		case EBUSY:		throw UITOX_EXPCEPTION_2(error_no, "The implementation has detected an attempt to re-initialise the object referenced by mutex, a previously initialised, but not yet destroyed, mutex.");
		//case EBUSY:	throw UITOX_EXPCEPTION_2(error_no, "The implementation has detected an attempt to destroy the object referenced by mutex while it is locked or referenced (for example, while being used in a pthread_cond_wait() or pthread_cond_timedwait()) by another thread."); 
		case EINVAL:	throw UITOX_EXPCEPTION_2(error_no, "The value specified by mutex is invalid.");
		default:		throw UITOX_EXPCEPTION_2(error_no, "Unknown returned value.");
		}
	}

public:
	Condition()
	{
		int _rc1 = pthread_cond_init(&m_cn, NULL );
		if(_rc1!=0)	exception(_rc1);

		int _rc2 = pthread_mutex_init(&m_mu, NULL );
		if(_rc2!=0)	exception(_rc2);
	}


	virtual ~Condition()
	{
		int _rc1=pthread_mutex_destroy(&m_mu );
		if(_rc1!=0)	exception(_rc1);

		int _rc2 = pthread_cond_destroy(&m_cn );
		if(_rc2!=0)	exception(_rc2);
	}


	/// Return false if timeout.
	bool wait(double waitSecond)
	{
		int _rc1 = pthread_mutex_lock(&m_mu);
		if(_rc1!=0)	
			exception(_rc1);

		struct timespec _now;
		clock_gettime(CLOCK_REALTIME, &_now);
		double _deadLine = waitSecond + ((double)_now.tv_nsec / NANO);
		int _deadSec = floor(_deadLine);
		double _deadNsec = _deadLine - _deadSec;
		_now.tv_sec = _now.tv_sec + _deadSec;
		_now.tv_nsec = _deadNsec*NANO;

		int _rcCond = pthread_cond_timedwait(&m_cn, &m_mu, &_now);

		int _rc2 = pthread_mutex_unlock(&m_mu);
		if(_rc2!=0)	
			exception(_rc2);

		if ( _rcCond == ETIMEDOUT )
			return false;

		if( _rcCond != 0 )
			exception(_rcCond);
		
		return true;
	}


	void wait()
	{
		int _rc1 = pthread_mutex_lock(&m_mu);
		if(_rc1!=0)	exception(_rc1);

		int _rc2 = pthread_cond_wait(&m_cn, &m_mu);
		if(_rc2!=0)	exception(_rc2);

		int _rc3 = pthread_mutex_unlock(&m_mu);
		if(_rc3!=0)	exception(_rc3);
	}


	void signal()
	{
		int _rc1 = pthread_mutex_lock(&m_mu);
		if(_rc1!=0)	exception(_rc1);

		int _rc2 = pthread_cond_signal(&m_cn);
		if(_rc2!=0)	exception(_rc2);

		int _rc3 = pthread_mutex_unlock(&m_mu);
		if(_rc3!=0)	exception(_rc3);
	}


	void broadcast()
	{
		int _rc1 = pthread_mutex_lock(&m_mu);
		if(_rc1!=0)	exception(_rc1);

		int _rc2 = pthread_cond_broadcast(&m_cn);
		if(_rc2!=0)	exception(_rc2);

		int _rc3 = pthread_mutex_unlock(&m_mu);
		if(_rc3!=0)	exception(_rc3);
	}

};


} // namespace Threading
} // namespace Uitox

#endif
