#ifndef _MEM_LEAK_H
#define _MEM_LEAK_H


#ifdef __WINDOWS__

	#define __MEM_LEAKS

	#ifdef __MEM_LEAKS
		#define _CRTDBG_MAP_ALLOC
		#ifndef _DEBUG
			#define _DEBUG
		#endif
		#include <stdlib.h>
		#include <crtdbg.h>
	#endif

	#ifdef 	__MEM_LEAKS
		#define _SHOW_MEM_LEAK() _CrtDumpMemoryLeaks()
	#else
		#define _SHOW_MEM_LEAK()
	#endif

#else
	#define _SHOW_MEM_LEAK()
#endif

#endif
