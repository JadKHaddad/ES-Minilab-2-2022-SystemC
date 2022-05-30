#include <systemc.h>
#include "controller.hpp"

using namespace std;

void Controller::print_maps()
{
    
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            cout << map[i][j] << ", ";
        }
        cout << "\t\t";
        for(int j = 0; j < N; ++j)
        {
            cout << real_world_map[i][j] << ", ";
        }
        cout << endl;
    }
}

tuple<int, int> Controller::get_index_and_dist_of_a_free_drone(Pos dest)
{
    int drone_index = -1;
    int min_dist = -1;

    for(int i = 0; i < DRONE_COUNT; ++i)
        {
            if(ready_in[i].read())
            {
                int row = drone_rows_in[i].read();
                int col = drone_cols_in[i].read();
                Pos source = Pos(row, col);
                int dist = min_distance(map, source, dest);
                if(dist > -1)
                {
                    if(min_dist == -1 || dist <= min_dist)
                    {
                        min_dist = dist;
                        drone_index = i;
                    }
                }
            }
        }
    return std::make_tuple(drone_index, min_dist);
}

void Controller::main()
{
    while(true)
    {
        wait();
        Pos dest = free_positions[index];
        auto tuple_index_dist = get_index_and_dist_of_a_free_drone(dest);
        int drone_index = get<0>(tuple_index_dist);
        int dist = get<1>(tuple_index_dist);

        cout << "index: " << drone_index << " dist: " << dist << endl;
        if (drone_index > -1)
        {
            travel_dist_out[drone_index].write(k);
            dest_rows_out[drone_index].write(dest.row);
            dest_cols_out[drone_index].write(dest.col);


            cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << "Controller" << "):" << "Dest (" << dest.row << ", " << dest.col << ") to drone: " << drone_index << " with dist: " << dist << endl;
            k++;
            if (k > 10){
                sc_stop();
            } 
        }

        // wait();
        // int free_drone_index = get_index_of_free_drone();
        // if (free_drone_index > -1)
        // {
        //     travel_out[free_drone_index].write(k);
        //     cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << "Controller" << "):" << "travel sent: " << k << " to: " << free_drone_index << endl;
        //     k++;
        //     if (k > 10){
        //         sc_stop();
        //     } 
        // }
        
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