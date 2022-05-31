#include <systemc.h>
#include "drone.hpp"

void Drone::main()
{   

    while(true)
    {   
        //init handshake
        ready_out.write(0);
        vld_out.write(0);
        current_pos_row_out.write(0);
        current_pos_col_out.write(0);
        wait();

        
        int travel_dist = travel_dist_in.read();

        cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "):" << "travel is: " << travel_dist << endl;

        if (travel_dist > 0)
        {
            cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "):" << "travelling" << endl;
            //travelling
            ready_out.write(false);
            int i = 0;
            while (i < travel_dist * 1000 * 2) { // distance * 2 seconds
                wait(clk.posedge_event());
                i++;
            }
            //arrived, discovering
            int j = 0;
            while (i < 5 * 1000) { // 5 seconds
                wait(clk.posedge_event());
                j++;
            }
            current_pos_row_out.write(current_dest_row_in.read());
            current_pos_col_out.write(current_pos_col_out.read());
            ready_out.write(true);
        }
    }
    
    

}