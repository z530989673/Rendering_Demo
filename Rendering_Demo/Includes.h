#include <vector>
#include <assert.h>
#include "Objects/GameObject.h"
#include "Modules/Module.h"


#ifdef DEBUG
#include "Debugging/Debug.h"
#endif // DEBUG


#define SafeDelete(x)	\
{						\
	if (x)				\
		delete (x);		\
	x = 0;				\
}

#define SafeDeleteArray(x)	\
{							\
	if (x)					\
		delete[] (x);		\
	x = 0;					\
}

#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }

#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x) assert(SUCCEEDED(x))
#endif
#endif
