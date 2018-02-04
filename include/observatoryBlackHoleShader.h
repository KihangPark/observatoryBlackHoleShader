#ifndef OBSERVATORY_BLACKHOLE_H
#define OBSERVATORY_BLACKHOLE_H

#include "shader.h"

struct observatoryBlackHoleShader {
	miScalar transparency;
	miScalar radius;
	miBoolean debug;
};

miC_LINKAGE DLLEXPORT void observatoryBlackHoleShader_init(miState*, struct observatoryBlackHoleShader*, miBoolean*);
miC_LINKAGE DLLEXPORT miBoolean observatoryBlackHoleShader(miColor*, miState*, struct observatoryBlackHoleShader*);
miC_LINKAGE DLLEXPORT miInteger observatoryBlackHoleShader_version();
miC_LINKAGE DLLEXPORT void observatoryBlackHoleShader_exit(miState*, struct observatoryBlackHoleShader*);

#endif
