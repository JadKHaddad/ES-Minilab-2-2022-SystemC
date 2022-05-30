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
  
  // for(int i = 0; i < DRONE_COUNT; ++i){

  // }

    Drone drone("drone_0");
    drone.clk(clksig);
    sc_signal <sc_uint<16>> travel_sig;
    sc_signal <bool> ready_sig;
    controller.travel_out[0](travel_sig);
    drone.travel_in(travel_sig);
    controller.ready_in[0](ready_sig);
    drone.ready_out(ready_sig);
  
    Drone drone_1("drone_1");
    drone_1.clk(clksig);
    sc_signal <sc_uint<16>> travel_sig_1;
    sc_signal <bool> ready_sig_1;
    controller.travel_out[1](travel_sig_1);
    drone_1.travel_in(travel_sig_1);
    controller.ready_in[1](ready_sig_1);
    drone_1.ready_out(ready_sig_1);

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