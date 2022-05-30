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
  Pos free_positions[N*N];

  sc_out <sc_uint<16>> travel_out[DRONE_COUNT];
  sc_in<bool> ready_in[DRONE_COUNT];
  //sc_in<sc_uint<16>> drone_rows_in[DRONE_COUNT];
  //sc_in<sc_uint<16>> drone_cols_in[DRONE_COUNT];

  sc_uint<16> k = 1;
  void main();

  SC_CTOR( Controller )
  {
    for(int i = 0; i < N; ++i)
    {
      for(int j = 0; j < N; ++j)
      {
        map[i][j] = 0;
      }
    }
    SC_CTHREAD(main, clk.pos());
  }
};

#endif