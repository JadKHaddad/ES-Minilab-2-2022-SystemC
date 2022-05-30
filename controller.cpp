#include <systemc.h>
#include "controller.hpp"

void Controller::main()
{
    while(true)
    {
        wait();
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