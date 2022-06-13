#include <systemc.h>
#include "controller.hpp"
#include "drone.hpp"
#include "helpers.hpp"
#include "const.hpp"

int sc_main(int argc, char* argv[])
{
  //create modules, clock, ports and signals
  sc_clock clksig("clk", 1, SC_MS);
  Controller controller("Controller");

  controller.clk(clksig);

  sc_signal<bool> ready_signals[DRONE_COUNT];
  sc_signal<bool> vld_signals[DRONE_COUNT];
  sc_signal<bool> ready_signals_o[DRONE_COUNT];
  sc_signal<bool> vld_signals_o[DRONE_COUNT];
  sc_signal<sc_int<16>> travel_dist_signals[DRONE_COUNT];
  Drone *drones[DRONE_COUNT];

  //connect drones to the controller
  for(int i = 0; i < DRONE_COUNT; ++i){
    auto name = "drone_" + std::to_string( i );
    const char *cname = name.c_str();
    drones[i] = new Drone(cname);
    drones[i]->clk(clksig);
    
    controller.travel_dist_out[i](travel_dist_signals[i]);
    drones[i]->travel_dist_in(travel_dist_signals[i]);

    controller.ready_in[i](ready_signals[i]);
    drones[i]->ready_out(ready_signals[i]);

    controller.vld_in[i](vld_signals[i]);
    drones[i]->vld_out(vld_signals[i]);

    controller.ready_out[i](ready_signals_o[i]);
    drones[i]->ready_in(ready_signals_o[i]);

    controller.vld_out[i](vld_signals_o[i]);
    drones[i]->vld_in(vld_signals_o[i]);
  }
  sc_start();

  cout << "Freeing Memory" << endl;
  //free memory
  for(int i = 0; i < DRONE_COUNT; ++i){
    delete(drones[i]);
  }
  
  return 0;
}