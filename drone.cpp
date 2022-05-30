#include <systemc.h>
#include "drone.hpp"

void Drone::main()
{   

    while(true)
    {   
        wait();
        const char* name = sc_core::sc_get_current_process_b()->get_parent_object()->basename();
        int data = travel_dist_in.read();
        cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "):" << "travel is: " << data << endl;

        if (data > 0)
        {
            cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << name << "):" << "travelling" << endl;
            ready_out.write(false);
            int i = 0;
            while (i < data * 1000) {
                wait(clk.posedge_event());
                i++;
            }
            ready_out.write(true);
        }
    }
    
    

}