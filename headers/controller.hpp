#ifndef CONTROLLER
#define CONTROLLER

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
  sc_uint<16> index = 0;
  sc_uint<16> free_positions_limit = 1;
  Pos free_positions[N*N];

  sc_out <sc_uint<16>> travel_dist_out[DRONE_COUNT];

  sc_in<bool> ready_in[DRONE_COUNT];
  sc_in<bool> vld_in[DRONE_COUNT];

  sc_out<bool> ready_out[DRONE_COUNT];
  sc_out<bool> vld_out[DRONE_COUNT];

  sc_in<sc_uint<16>> drone_rows_in[DRONE_COUNT];
  sc_in<sc_uint<16>> drone_cols_in[DRONE_COUNT];

  sc_out<sc_uint<16>> dest_rows_out[DRONE_COUNT];
  sc_out<sc_uint<16>> dest_cols_out[DRONE_COUNT];

  sc_uint<16> k = 1;

  //methods
  void source();
  void sink();
  IndexDist get_index_and_dist_of_a_free_drone(Pos dest);
  void print_maps();
  SC_CTOR( Controller )
  {
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
    // print_maps();
    SC_CTHREAD(source, clk.pos());
    SC_CTHREAD(sink, clk.pos());
  }
};

#endif