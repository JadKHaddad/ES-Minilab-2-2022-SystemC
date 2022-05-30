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

  //sc_vector<Drone> drones;
  for(int i = 0; i < DRONE_COUNT; ++i){
    Drone drone("drone_" + i);
    drone.clk(clksig);
    sc_signal <sc_uint<16>> travel_sig;
    sc_signal <bool> ready_sig;
    controller.travel_out[i](travel_sig);
    drone.travel_in(travel_sig);
    controller.ready_in[i](ready_sig);
    drone.ready_out(ready_sig);
  }

  sc_start();
  // char grid[N][N] = 
  // { { '0', '*', '0', '*' },
	// 	{ '*', '0', '*', '*' },
	// 	{ '0', '*', '*', '*' },
	// 	{ '*', '*', '*', '*' } 
  // };
  // int i = min_distance(grid, Pos(0,3), Pos(3,0));
	// cout << i << endl;

  return 0;
}