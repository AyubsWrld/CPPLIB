#pragma once

#include "A.h"

// BoardManager.h

struct B 
{
  void Invoke(A* a)
  {
    a->HandleRequest(this);
  }
};

