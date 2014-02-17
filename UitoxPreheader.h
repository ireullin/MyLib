/***************************************************************************************************************
1. A header file include other header files in common use form STL, ubuntu system, UITOX library and so on....
2. Dedfined some marcos for UITOX library.

Author: Ireul Lin
Last update: 2014/02/04
Copyright is owned by UITOX.
***************************************************************************************************************/
#ifndef __UITOXPREHEADER__
#define __UITOXPREHEADER__


#define UITOX_EXPCEPTION_1(param)		Uitox::Exception(param, __FILE__, __LINE__);
#define UITOX_EXPCEPTION_2(no, msg)		Uitox::Exception(no, msg, __FILE__, __LINE__);

#ifndef AUTO_LOCK
	#define AUTO_LOCK(a)				Uitox::Threading::AutoLock _autolock(a)
#endif

#ifndef DICTIONARY_FOREACH
	#define DICTIONARY_FOREACH(a)		for(a.begin(); !a.end(); ++a)
#endif

#ifndef SAFE_DELETE
	#define SAFE_DELETE(a)				if( (a) != NULL ) {delete (a); (a) = NULL;}
#endif

#ifndef SAFE_DELETE_ARRAY
	#define SAFE_DELETE_ARRAY(a)		if( (a) != NULL ) {delete[] (a); (a) = NULL;}
#endif


#ifndef ON
	#define ON 1
#endif

#ifndef OFF
	#define OFF 2
#endif

#ifndef ONLY_SHOW
	#define ONLY_SHOW 3
#endif

	
#ifdef UITOX_TRACE_ENABLE
	#define TRACE_THIS_FUNCTION(x)	Uitox::UitoxTrace _uitoxtrace_(x, __FILE__,__FUNCTION__);
	#define SHOW_POSITION			_uitoxtrace_.position(__LINE__)
	#define SHOW_VALUES				_uitoxtrace_.line(__LINE__); _uitoxtrace_.show
	#define SHOW_ERRORS				_uitoxtrace_.line(__LINE__); _uitoxtrace_.error
#else
	#define TRACE_THIS_FUNCTION(x)	/* UITOX_TRACE_DISABLE */
	#define SHOW_POSITION			/* UITOX_TRACE_DISABLE */
	#define SHOW_VALUES				//
	#define SHOW_ERRORS				//
#endif


#ifndef NANO
#define NANO 1000000000LL
#endif


// STL pure c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <stddef.h>
#include <ctype.h>

// STL C++
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <exception>
#include <queue>
#include <memory>
#include <tr1/memory>
#include <list>
#include <iomanip>

// unbuntu
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <libgen.h> 
#include <sys/timeb.h>
#include <pthread.h>
#include <errno.h>

// uitox
#include "UitoxException.h"
#include "UitoxTrace.h"
#include "UitoxRunable.h"
#include "UitoxSignal.h"
#include "UitoxThread.h"
#include "UitoxThreadBind.h"
#include "UitoxMutex.h"
#include "UitoxCondition.h"
#include "UitoxDictionary.h"
#include "UitoxSingleton.h"
#include "UitoxSimplePool.h"
#include "UitoxDateTimeFormat.h"
#include "UitoxDateTime.h"
#include "UitoxExtendItem.h"
#include "UitoxStringPlus.h"


#endif
