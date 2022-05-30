#include <systemc.h>
#include "controller.hpp"
#include "drone.hpp"
#include "helpers.hpp"
#include "const.hpp"

int sc_main(int argc, char* argv[])
{
  sc_clock clksig("clk", 1, SC_MS);
  Controller controller("Controller");

  controller.clk(clksig);

  // sc_vector<Drone> drones;
  sc_signal<bool> ready_signals[DRONE_COUNT];
  sc_signal<sc_uint<16>> travel_dist_signals[DRONE_COUNT];
  sc_signal<sc_uint<16>> drone_rows_signals[DRONE_COUNT];
  sc_signal<sc_uint<16>> drone_cols_signals[DRONE_COUNT];
  sc_signal<sc_uint<16>> dest_rows_signals[DRONE_COUNT];
  sc_signal<sc_uint<16>> dest_cols_signals[DRONE_COUNT];
  Drone *drones[DRONE_COUNT];

  for(int i = 0; i < DRONE_COUNT; ++i){
    auto name = "drone_" + std::to_string( i );
    const char *cname = name.c_str();
    drones[i] = new Drone(cname);
    drones[i]->clk(clksig);
    
    controller.travel_dist_out[i](travel_dist_signals[i]);
    drones[i]->travel_dist_in(travel_dist_signals[i]);

    controller.ready_in[i](ready_signals[i]);
    drones[i]->ready_out(ready_signals[i]);

    controller.drone_rows_in[i](drone_rows_signals[i]);
    drones[i]->current_pos_row_out(drone_rows_signals[i]);

    controller.drone_cols_in[i](drone_cols_signals[i]);
    drones[i]->current_pos_col_out(drone_cols_signals[i]);

    controller.dest_rows_out[i](dest_rows_signals[i]);
    drones[i]->current_dest_row_in(dest_rows_signals[i]);

    controller.dest_cols_out[i](dest_cols_signals[i]);
    drones[i]->current_dest_col_in(dest_cols_signals[i]);
  }

  sc_start();

  // int grid[N][N] = {
  // {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  // {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  // {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  // {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  // {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  // {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  // {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  // {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  // {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  },
  // {   00,	00,	00,	00,	00,	00,	00,	00,	00,	00  }
  // };

  //int i = min_distance(grid, Pos(0,0), Pos(0,9));
	//cout << i << endl;

  cout << "Freeing Memory" << endl;
  for(int i = 0; i < DRONE_COUNT; ++i){
    delete(drones[i]);
  }
  return 0;
}