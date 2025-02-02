#ifndef SEA_BASE_HPP
#define SEA_BASE_HPP

#include "vmodule_api.h"
#include "Sd2_h/CannonTrace.h"

class SEA_BASE : public CANNON_TRACE_BASE {
public:
  virtual float WaveXZ(float x, float z, CVECTOR* vNormal = nullptr) = 0;
};

#endif
