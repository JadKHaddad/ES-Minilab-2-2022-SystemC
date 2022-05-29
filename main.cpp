#include <systemc.h>
#include "controller.hpp"
#include "drone.hpp"
#include "helpers.hpp"
#include "const.hpp"


int sc_main(int argc, char* argv[])
{
  Controller controller("Controller");
  Drone drone_1("Drone_1");

  sc_clock clksig("clk", 1, SC_SEC);

  sc_signal <sc_uint<16>> travel_sig;
  sc_signal <bool> ready_sig;
  controller.clk(clksig);
  drone_1.clk(clksig);

  controller.travel(travel_sig);
  drone_1.travel(travel_sig);

  drone_1.ready(ready_sig);
  controller.ready(ready_sig);
  
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