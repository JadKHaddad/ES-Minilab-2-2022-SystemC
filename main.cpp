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
  sc_signal<sc_uint<16>> travel_signals[DRONE_COUNT];
  Drone *drones[DRONE_COUNT];

  for(int i = 0; i < DRONE_COUNT; ++i){
    drones[i] = new Drone("drone_" + i);
    drones[i]->clk(clksig);
    controller.travel_out[i](travel_signals[i]);
    drones[i]->travel_in(travel_signals[i]);
    controller.ready_in[i](ready_signals[i]);
    drones[i]->ready_out(ready_signals[i]);
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

  cout << "Freeing Memory" << endl;
  for(int i = 0; i < DRONE_COUNT; ++i){
    delete(drones[i]);
  }
  return 0;
}