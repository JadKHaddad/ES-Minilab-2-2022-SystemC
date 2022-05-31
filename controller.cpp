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

IndexDist Controller::get_index_and_dist_of_a_free_drone(Pos dest)
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
    return IndexDist(drone_index, min_dist);
}


void Controller::source()
{
    while(true)
    {
        wait();
        Pos dest = free_positions[index];
        IndexDist index_dist = get_index_and_dist_of_a_free_drone(dest);
        int drone_index = index_dist.index;
        int dist = index_dist.dist;
        //cout << "drone index: " << drone_index << " dist: " << dist << endl;
        if (drone_index > -1)
        {   
            vld_out[drone_index].write(true);
            travel_dist_out[drone_index].write(dist);
            dest_rows_out[drone_index].write(dest.row);
            dest_cols_out[drone_index].write(dest.col);
            //mark dest "to be discovered"
            map[dest.row][dest.col] = 2;

            do {
                wait();
            } while (!ready_in[drone_index].read());
            vld_out[drone_index].write(false);

            cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << "Controller" << "):" << "Dest (" << dest.row << ", " << dest.col << ") to drone: " << drone_index << " with dist: " << dist << endl;
            k++;
            if (k > 10){
                sc_stop();
            } 
        }      
    }
}

void Controller::sink()
{

}