#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;
const int size_of_cylinders = 5000;
int get_disk_init_pos(int disk_init_pos)
{
    bool input_flag = false;
    //ask user for input for initial position of disk-head to start servicing requests
    cerr << "Enter a starting disk-head placement " << endl;
    cin >> disk_init_pos;
    while (input_flag)
    {
        //questionable input validation, kind of buggy at the moment
        if (!isdigit(disk_init_pos))
        {
            cerr << "Input was not a number. Please try again" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            //exit(1);
        }
        else
            input_flag = false;
        cin >> disk_init_pos;
    }
    return disk_init_pos;
}

int main(int argc, char *argv[])
{
    array<int, size_of_cylinders> service_requests;
    service_requests.fill(0);
    int disk_init_pos, disk_pos, overhead_work, tmp_seek_time, sr_loc = 0;
    int min_seek_time = size_of_cylinders+1;
    int number_of_requests = 50;

    //function to get user input on disk head initial position
    disk_pos = get_disk_init_pos(disk_init_pos);

    //populate queue with 50 randomly generated requests (use random number generator to get
    //service request numbers)
    //initialize service requests on array to value 1 to denote a service being requested
    srand(time(NULL));
    for (int i = 0; i < number_of_requests; i++)
    {
        service_requests[(rand() % size_of_cylinders)] = 1;
    }
    
    //check all service requests in the array (not efficient)
    //and mark down the value in a tmp variable and compare it to minimum
    //only work with minimum seek time each iteration for a service request fulfillment
    for (int y=0; y < number_of_requests; y++ ) {
        for (int p = 0; p < service_requests.size(); p++)
        {
            if (service_requests[p] == 1)
            {
                cout << "Service Request Number " << p << endl;
                tmp_seek_time = abs(disk_pos - p);
                //cout << "tmp_seek_time is " << tmp_seek_time << endl;
                if (tmp_seek_time < min_seek_time)
                {
                    min_seek_time = tmp_seek_time;
                    //cout << "min seek time is " << min_seek_time << endl;
                    sr_loc = p;
                }
            }
        }
        overhead_work += min_seek_time;
        cout << "overhead work is currently " << overhead_work << endl << endl;
        //mark down service request index and reset it to 0 to denote finished service
        disk_pos = sr_loc;
        service_requests[sr_loc] = 0;
        //reset min_seek_time otherwise it will be unlikely to change if its already
        //the smallest value
        min_seek_time = size_of_cylinders+1;
    }
    
    //print out the amount of work done seeking the track
    cout << "Total amount of overhead work is " << overhead_work << endl;

    return 0;
}
