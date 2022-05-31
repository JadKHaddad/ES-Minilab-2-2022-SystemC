#ifndef DRONE
#define DRONE

#include "helpers.hpp"

SC_MODULE( Drone )
{
  const char* name;
  sc_in<bool> clk;
  sc_in <sc_uint<16>> travel_dist_in;
  
  sc_out<bool> ready_out;
  sc_out<bool> vld_out;

  sc_out<sc_uint<16>> current_pos_row_out;
  sc_out<sc_uint<16>> current_pos_col_out;

  sc_in<sc_uint<16>> current_dest_row_in;
  sc_in<sc_uint<16>> current_dest_col_in;
  void main();

  SC_CTOR( Drone )
  {
    name = sc_core::sc_get_current_process_b()->get_parent_object()->basename();
    current_pos_row_out.initialize(0);
    current_pos_col_out.initialize(0);
    ready_out.initialize(true);
    SC_THREAD(main);
    sensitive << travel_dist_in;
  }
};


#endif