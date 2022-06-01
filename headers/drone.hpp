#ifndef DRONE
#define DRONE

#include "helpers.hpp"

SC_MODULE( Drone )
{
  sc_in<bool> clk;
  sc_in <sc_int<16>> travel_dist_in;

  sc_out<bool> ready_out;
  sc_out<bool> vld_out;

  sc_in<bool> ready_in;
  sc_in<bool> vld_in;

  void main();

  SC_CTOR( Drone )
  {
    SC_THREAD(main);
    sensitive << clk.pos();
  }
};

#endif