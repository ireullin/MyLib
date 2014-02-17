#ifndef __UITOXTHREAD__
#define __UITOXTHREAD__

namespace Uitox{
namespace Threading{

extern void			sleep(double second);
extern unsigned int currentThreadID();

// an abstract class, you shall override method run before use.
class Thread
{
private:
	Thread(const Thread&);
	Thread& operator= (const Thread&);

	pthread_t		m_handle;
	void*			m_param;
	unsigned int	m_id;


	void exception(int error_no)
	{
		switch(error_no)
		{
		case EAGAIN:	throw UITOX_EXPCEPTION_2(error_no ,"The system lacked the necessary resources to create another thread, or the system-imposed limit on the total number of threads in a process PTHREAD_THREADS_MAX would be exceeded.");
		case EINVAL:	throw UITOX_EXPCEPTION_2(error_no ,"The value specified by attr is invalid.");
		case EPERM:		throw UITOX_EXPCEPTION_2(error_no ,"The caller does not have appropriate permission to set the required scheduling parameters or scheduling policy.");
		default:		throw UITOX_EXPCEPTION_2(error_no ,"Unknown thread error.");
		}
	}


	void release()
	{
		if(m_handle!=0)
		{
			int _rc = pthread_detach(m_handle);
			if(_rc!=0 && _rc!=ESRCH) this->exception(_rc);
			m_handle = 0;
		}
	}


	/*static void signal()
	{
		struct sigaction _act;  
		_act.sa_handler = signal_event;
		_act.sa_flags = 0;  
		sigemptyset(&_act.sa_mask);
		sigaction(SIGUSR1, &_act, NULL);
		raise(SIGUSR1);
	}*/
	

	static void* threadCallback(void* sender)
	{
		Thread* _thread = reinterpret_cast<Thread*>(sender);

		try
		{
			_thread->m_id = Uitox::Threading::currentThreadID();
			_thread->run(_thread->m_param);
		}
		catch(std::exception& exp)
		{
			std::cout << "Thread " << Uitox::Threading::currentThreadID() << " threw an exception \"" << exp.what() << "\"" << std::endl;
			//signal();
			assert(false);
		}
		catch(const char* errMsg)
		{
			std::cout << "Thread " << Uitox::Threading::currentThreadID() << " threw an exception \"" << errMsg << "\"" << std::endl;
			//signal();
			assert(false);
		}
		catch(const std::string& errMsg)
		{
			std::cout << "Thread " << Uitox::Threading::currentThreadID() << " threw an exception \"" << errMsg << "\"" << std::endl;
			//signal();
			assert(false);
		}
		catch(...)
		{
			std::cout << "Thread " << Uitox::Threading::currentThreadID() << " threw an unknown exception." << std::endl;
			//signal();
			assert(false);
		}

		_thread->m_id = 0;
		return NULL;
	}


protected:
	virtual void run(void* param)=0;


public:
	Thread()
		:m_handle(0),m_param(NULL),m_id(0)
	{
	}
	

	virtual ~Thread()
	{
		if(this->isRunning())
		{
			throw UITOX_EXPCEPTION_1("Memory was be deleted before the thread finished.");
		}

		this->release();
	}


	virtual void start(void* param=NULL)
	{
		m_param = param;

		int _rc = pthread_create( &m_handle, NULL, Thread::threadCallback, this );
		if(_rc!=0)
			this->exception(_rc);
	}


	void join()
	{
		if(m_id==Uitox::Threading::currentThreadID())
		{
			throw UITOX_EXPCEPTION_1("Can not be joined by self.");
		}
		
		int _rc = pthread_join(m_handle, NULL );
		if(_rc!=0 && _rc!=ESRCH)
			this->exception(_rc);

		this->release();
	}
	

	pthread_t handle()
	{return m_handle;}


	unsigned int ID()
	{return m_id;}


	bool isRunning()
	{return m_id!=0;}

	void sleep(double second)
	{Uitox::Threading::sleep(second);}
};


void sleep(double second)
{
	usleep(second*1000*1000);
}


unsigned int currentThreadID()
{
	return (unsigned int)pthread_self();
}

}//namespace Threading
}//namespace Uitox

#endif
