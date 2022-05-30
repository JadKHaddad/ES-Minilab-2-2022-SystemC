#ifndef CONTROLLER
#define CONTROLLER

#include "const.hpp"
#include "helpers.hpp"

using namespace std;

SC_MODULE( Controller )
{
  sc_in<bool> clk;
  sc_uint<16> index = 0;
  Pos free_positions[N*N];

  sc_out <sc_uint<16>> travel_out[DRONE_COUNT];
  sc_in<bool> ready_in[DRONE_COUNT];
  //sc_in<sc_uint<16>> drone_rows_in[DRONE_COUNT];
  //sc_in<sc_uint<16>> drone_cols_in[DRONE_COUNT];

  sc_uint<16> j = 1;
  void main();

  SC_CTOR( Controller )
  {
    SC_CTHREAD(main, clk.pos());
  }
};

#endif