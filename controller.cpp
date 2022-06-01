#include "controller.hpp"

void Controller::print_maps()
{
    cout << endl << "Map" << endl;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            int num =  map[i][j];
            std::string spacing= "\t\t";
            if (num == 99 || num == -1)
            {
                spacing = "\t";
            }
            cout << "[" << num << "]" << spacing;
        }
        cout << endl;
    }
    cout << endl;
    cout << "Real world Map" << endl;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            int num = real_world_map[i][j];
            std::string spacing= "\t\t";
            if (num == 99 || num == -1)
            {
                spacing = "\t";
            }
            cout << "[" << num << "]" << spacing;
        }
        cout << endl;
    }
}

void Controller::print_free_positions()
{   
    cout << endl << "Next free positions: ";
    int i = index;
    while(i < index_limit)
    {
        cout << "[(" << free_positions[i].row << ", " << free_positions[i].col << ")] ";
        i++; 
    }
    cout << endl << endl;
}

IndexDist Controller::get_index_and_dist_of_a_free_drone(Pos dest)
{
    int drone_index = -1;
    int min_dist = -1;
    for(int i = 0; i < DRONE_COUNT; ++i)
        {
            if(ready_in[i].read())
            {
                Pos source = drones_positions[i];
                int dist = min_distance(map, source, dest);
                if(dist > -1)
                {
                    if(min_dist == -1 || dist < min_dist)
                    {
                        min_dist = dist;
                        drone_index = i;
                    }
                }
            }
        }
    return IndexDist(drone_index, min_dist);
}

void Controller::expand_path(Pos new_pos)
{
    int counter = index_limit;
    int i = new_pos.row;
    int j = new_pos.col;
    if (i - 1 >= 0 && map[i - 1][j] == 0)
    {
        if (real_world_map[i - 1][j] == 0)
        {
            Pos p = Pos(i - 1, j);
            free_positions[counter] = p;
            counter++;
            index_limit++;
            map[i - 1][j] = -1;
        }
        else
        {
            map[i - 1][j] = 99;
        }
    }

    if (i + 1 < N && map[i + 1][j] == 0)
    {
        if (real_world_map[i + 1][j] == 0)
        {
            Pos p = Pos(i + 1, j);
            free_positions[counter] = p;
            counter++;
            index_limit++;
            map[i + 1][j] = -1;
        }
        else
        {
            map[i + 1][j] = 99;
        }
    }

    if (j - 1 >= 0 && map[i][j - 1] == 0)
    {
        if (real_world_map[i][j - 1] == 0)
        {
            Pos p = Pos(i, j - 1);
            free_positions[counter] = p;
            counter++;
            index_limit++;
            map[i][j - 1] = -1;
        }
        else
        {
            map[i][j - 1] = 99;
        }
    }

    if (j + 1 < N && map[i][j + 1] == 0)
    {
        if (real_world_map[i][j + 1] == 0)
        {
            Pos p = Pos(i, j + 1);
            free_positions[counter] = p;
            counter++;
            index_limit++;
            map[i][j + 1] = -1;
        }
        else
        {
            map[i][j + 1] = 99;
        }
    }
}

void Controller::source()
{
    while(true)
    {
        wait();
        if(index >= index_limit)
        {
            if(working_drones_count == 0)
            {   
                cout << "Mission complete" << endl;
                print_maps();
                sc_stop();
            }
            continue;
        }
        Pos dest = free_positions[index];
        IndexDist index_dist = get_index_and_dist_of_a_free_drone(dest);
        int drone_index = index_dist.index;
        int dist = index_dist.dist;
        //cout << "drone index: " << drone_index << " dist: " << dist << endl;
        if (drone_index > -1)
        {   
            
            vld_out[drone_index].write(true);
            travel_dist_out[drone_index].write(dist);
            //mark dest "to be discovered"
            working_drones_count++;
            Pos drone_current_pos = drones_positions[drone_index];
            if(map[drone_current_pos.row][drone_current_pos.col] == 3)
            {
                map[drone_current_pos.row][drone_current_pos.col] = 1;
            }
            map[dest.row][dest.col] = 2;
            drones_positions[drone_index] = dest;
            do {
                wait();
            } while (!ready_in[drone_index].read());
            vld_out[drone_index].write(false);
            index++;
            cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << "Controller" << "): " << "Destination [(" << dest.row << ", " << dest.col << ")] was sent to [drone_" << drone_index << "] with distance: [" << dist << "]" << endl;
        }      
    }
}

void Controller::sink()
{
    for(int i = 0; i< DRONE_COUNT; ++i){
        ready_out[i].write(false);
    }
    while(true)
    {      
        wait();
        for(int i = 0; i< DRONE_COUNT; ++i){
            if(vld_in[i].read())
            {
                ready_out[i].write(true);
                do {
                    wait();
                } while(!vld_in[i].read());
                ready_out[i].write(false);
                working_drones_count--;
                Pos new_pos = drones_positions[i];
                expand_path(new_pos);
                map[new_pos.row][new_pos.col] = 3;
                cout << "[" << sc_time_stamp() << "/" << sc_delta_count() << "](" << "Controller" << "): " << "Destination [(" << new_pos.row << ", " << new_pos.col << ")] was discovered by [drone_" << i << "]" << endl;
                print_maps();
                print_free_positions();
            }
        }    
    }
}
