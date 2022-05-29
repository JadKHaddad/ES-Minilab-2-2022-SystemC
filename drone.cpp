#include <systemc.h>
#include "drone.hpp"

void Drone::main()
{   

    while(true)
    {   
        wait();
        
        int data = travel.read();
        cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << "Drone" << "):" << "travel is: " << data << endl;

        if (data > 0)
        {
            cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << "Drone" << "):" << "travelling" << endl;
            ready.write(false);
            int i = 0;
            while (i < data) {
                wait(clk.posedge_event());
                i++;
            }
            ready.write(true);
        }
    }
    
    

}