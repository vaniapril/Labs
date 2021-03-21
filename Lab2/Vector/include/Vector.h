#ifdef VECTOR_EXPORTS
#define VECTOR_API __attribute__((visibility("default")))
#else
#define VECTOR_API 
#endif

#include "Number.h"

class VECTOR_API Vector {
	Number _x;
	Number _y;
public:
	Vector(Number x, Number y);

	Number r();
	Number fi();

	Vector sum(Vector v);
};
