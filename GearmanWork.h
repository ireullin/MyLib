#ifndef __GEARMANWORK__
#define __GEARMANWORK__

class GearmanWork
{
private:
	GearmanWork(const GearmanWork&);
	GearmanWork& operator= (const GearmanWork&);
	
	gearman_worker_st* m_pWorkerSt;

public:
	GearmanWork()
		:m_pWorkerSt(NULL)
	{
	}


	virtual ~GearmanWork()
	{
		printf("~GearmanWork\n");
		if(m_pWorkerSt==NULL)
			return;

		gearman_worker_free(m_pWorkerSt);
		delete(m_pWorkerSt);
	}


	void create()
	{
		m_pWorkerSt = new gearman_worker_st();
		if(gearman_worker_create(m_pWorkerSt)==NULL)
			throw UITOX_EXPCEPTION_1("create failed");
	}


	void addServer(const std::string& host, int port)
	{
		// gearman_return_t's value is in return.h
		gearman_return_t _rc = gearman_worker_add_server(m_pWorkerSt, host.c_str(), port);
		if (_rc == GEARMAN_SUCCESS)
			return;
		
		std::stringstream _ss;
		_ss << "addServer failed gearman_return_t=" << _rc;
		throw UITOX_EXPCEPTION_1(_ss.str());
	}


	void addFunction(const std::string& fuctionName, gearman_worker_fn *function)
	{
	 	// gearman_return_t's value is in return.h
		gearman_return_t _rc = gearman_worker_add_function(
			m_pWorkerSt,
			fuctionName.c_str(),/* const char *function_name */
            10,					/* uint32_t timeout */
            function,			/* gearman_worker_fn *function */
            NULL				/* void *context */
            );

		if (_rc == GEARMAN_SUCCESS)
			return;
		
		std::stringstream _ss;
		_ss << "addFunction failed gearman_return_t=" << _rc;
		throw UITOX_EXPCEPTION_1(_ss.str());
	}


	void echo(const void* content, size_t size)
	{
		gearman_return_t _rc = gearman_worker_echo(m_pWorkerSt, content, size);
		if (_rc == GEARMAN_SUCCESS)
			return;
		
		std::stringstream _ss;
		_ss << "echo failed gearman_return_t=" << _rc;
		throw UITOX_EXPCEPTION_1(_ss.str());
	}


	gearman_return_t work()
	{
		return gearman_worker_work(m_pWorkerSt);
	}

};

#endif
