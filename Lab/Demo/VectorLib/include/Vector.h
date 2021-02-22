#pragma once

#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
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