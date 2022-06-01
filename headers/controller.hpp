#ifndef CONTROLLER
#define CONTROLLER

#include <systemc.h>
#include "const.hpp"
#include "helpers.hpp"

using namespace std;

SC_MODULE( Controller )
{
  int real_world_map[N][N] = {
  {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  {   99,	99,	99,	99,	99,	00,	00,	99,	99,	99  },
  {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  }
  };
  int map[N][N];

  sc_in<bool> clk;
  sc_uint<16> working_drones_count = 0;
  sc_uint<16> came_back_drones_cout = 0;
  sc_uint<16> index = 0;
  sc_uint<16> index_limit = 1;
  
  Pos drones_positions[DRONE_COUNT];
  Pos free_positions[N*N];

  sc_out <sc_int<16>> travel_dist_out[DRONE_COUNT];

  sc_in<bool> ready_in[DRONE_COUNT];
  sc_in<bool> vld_in[DRONE_COUNT];

  sc_out<bool> ready_out[DRONE_COUNT];
  sc_out<bool> vld_out[DRONE_COUNT];

  //methods
  void source();
  void sink();
  void guard();
  void expand_path(Pos new_pos);
  void print_map();
  void print_real_world_map();
  void print_free_positions();
  IndexDist get_index_and_dist_of_a_free_drone(Pos dest);

  SC_CTOR( Controller )
  {
    for(int i = 0; i < DRONE_COUNT; ++i)
    {
      drones_positions[i] = Pos();
    }
    for(int i = 0; i < N; ++i)
    {
      for(int j = 0; j < N; ++j)
      {
        map[i][j] = 0;
      }
    }
    for(int i = 0; i < N*N; ++i)
    {
      free_positions[i] = Pos();
    }
    SC_CTHREAD(source, clk.pos());
    SC_CTHREAD(sink, clk.pos());
    SC_CTHREAD(guard, clk.pos());
  }
};

#endif