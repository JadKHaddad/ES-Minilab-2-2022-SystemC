#include <systemc.h>
#include "controller.hpp"

void Controller::main()
{
    while(true)
    {
        wait();
        for(int i = 0; i < DRONE_COUNT; ++i)
        {
            if(ready_in[i].read())
            {
                travel_out[i].write(k);
                cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << "Controller" << "):" << "travel sent: " << k << " to: " << i << endl;
                k++;
                if (k > 10){
                    sc_stop();
                } 
            }
        }
        // if (ready.read())
        // {
        //     travel.write(i);
        //     cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << "Controller" << "):" << "travel sent: " << i << endl;
        //     i = i + 1;
        //     if (i > 10){
        //         sc_stop();
        //     }
        // }
            
    }

}