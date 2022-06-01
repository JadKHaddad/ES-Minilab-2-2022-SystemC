#include <systemc.h>
#include "drone.hpp"


void Drone::main()
{   
    const char* name = sc_core::sc_get_current_process_b()->get_parent_object()->basename();
    //init handshake
    ready_out.write(false);
    vld_out.write(false);
    wait();

    while(true)
    {   
        ready_out.write(true);
        do {
            wait();
        } while(!vld_in.read());
        bool come_back = false;
        int travel_dist = travel_dist_in.read();
        if (travel_dist < 0)
        {
            come_back = true;
            travel_dist = -1 * travel_dist; 
        }
        ready_out.write(false);

        cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "): " << "Travelling" << endl;
        //travelling
        int i = 0;
        while (i < travel_dist * 1000 * 2) { // distance * 2 seconds
            wait(clk.posedge_event());
            i++;
        }
        if(!come_back)
        {
            cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "): " << "Discovering" << endl;
            //arrived, discovering
            int j = 0;
            while (j < 5 * 1000) { // 5 seconds
                wait(clk.posedge_event());
                j++;
            }
            cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "): " << "Finished discovering" << endl;
        }
        vld_out.write(true);
        cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "): " << "Waiting for controller" << endl;
        do {
            wait();
        } while (!ready_in.read());
        vld_out.write(false);
    }
}