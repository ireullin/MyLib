#ifndef __UITOXTHREADBIND__
#define __UITOXTHREADBIND__

namespace Uitox{
namespace Threading{

class ThreadBind : public Thread
{
private:
	typedef Thread super;
	ThreadBind(const ThreadBind&);
	ThreadBind& operator= (const ThreadBind&);

	Uitox::IRunable* m_pRunable;


protected:
	virtual void run(void* param=NULL)
	{
		if(m_pRunable==NULL)
		{
			throw UITOX_EXPCEPTION_1("Runable can't be empty.");
		}


		m_pRunable->run(this);
	}

public:
	ThreadBind()
		:m_pRunable(NULL)
	{}


	virtual ~ThreadBind()
	{
		SAFE_DELETE(m_pRunable);
	}


	virtual void start(void* param=NULL)
	{
		throw UITOX_EXPCEPTION_1("This method has been denied, please call another method void start(Uitox::IRunable* pRunable)");
	}


	void start(Uitox::IRunable* pRunable)
	{
		SAFE_DELETE(m_pRunable);
		m_pRunable = pRunable;
		super::start(NULL);
	}
};

}
}


#endif
