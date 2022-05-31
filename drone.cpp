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
        int travel_dist = travel_dist_in.read();
        ready_out.write(false);

        cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "):" << "travelling" << endl;
        //travelling
        int i = 0;
        while (i < travel_dist * 1000 * 2) { // distance * 2 seconds
            wait(clk.posedge_event());
            i++;
        }
        cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "):" << "discovering" << endl;
        //arrived, discovering
        int j = 0;
        while (j < 5 * 1000) { // 5 seconds
            wait(clk.posedge_event());
            j++;
        }
        cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "):" << "finished discovering" << endl;

        vld_out.write(true);
        current_pos_row_out.write(current_dest_row_in.read());
        current_pos_col_out.write(current_pos_col_out.read());
        do {
            cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "):" << "waiting for controller" << endl;
            wait();
        } while (!ready_in.read());
        vld_out.write(false);
    }
}