#ifndef DRONE
#define DRONE

#include "helpers.hpp"

SC_MODULE( Drone )
{
  sc_in<bool> clk;
  sc_in <sc_uint<16>> travel;
  sc_out<bool> ready;
  void main();

  SC_CTOR( Drone )
  {
    ready.initialize(true);
    SC_THREAD(main);
    sensitive << travel;
  }
};


#endif