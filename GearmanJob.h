#ifndef __GEARMANJOB__
#define __GEARMANJOB__

class GearmanJob
{
private:
	gearman_job_st* m_jobSt;


public:
	GearmanJob(gearman_job_st* job)
		:m_jobSt(job)
	{}

	virtual ~GearmanJob()
	{}

	std::string workload()
	{
		char* _buff = (char*)gearman_job_workload(m_jobSt);
		int _size = gearman_job_workload_size(m_jobSt);
		return std::string(_buff, _size);
	}

	void sendComplate(const std::string& data)
	{
		gearman_return_t _rc = gearman_job_send_complete(
			m_jobSt,
			(void*)data.c_str(),
            data.size()
            );

		if (_rc == GEARMAN_SUCCESS)
			return;
		
		std::stringstream _ss;
		_ss << "addFunction failed gearman_return_t=" << _rc;
		throw UITOX_EXPCEPTION_1(_ss.str());
	}

};

#endif
