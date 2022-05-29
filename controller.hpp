#ifndef CONTROLLER
#define CONTROLLER

#include "helpers.hpp"

SC_MODULE( Controller )
{
  sc_in<bool> clk;
  sc_out <sc_uint<16>> travel;
  sc_in<bool> ready;
  
  sc_uint<16> i = 1;
  void main();

  SC_CTOR( Controller )
  {
    SC_CTHREAD(main, clk.pos());
  }
};

#endif