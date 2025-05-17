#ifndef SHOVEL_H
#define SHOVEL_H
#include "Tool.h"

class Shovel : public Tool 
{
private:
public:
  Shovel() : Tool("play/shovel.png") 
  {
    m_type=SHOVEL;
  }
};

#endif // !SHOVEL_H
