#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;
const int size_of_cylinders = 5000;
int get_disk_init_pos(int disk_init_pos, bool input_flag)
{
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
    queue<int> service_requests;
    int number_of_requests = 50; 
    int disk_init_pos, disk_pos, overhead_work = 0;
    bool input_flag = false;
    //function to get user input on disk head initial position
    disk_pos = get_disk_init_pos(disk_init_pos, input_flag);

    //populate queue with 50 randomly generated requests (use random number generator to get
    //service request numbers)
    //push the values into queue
    srand(time(NULL));
    for (int i = 0; i < number_of_requests; i++)
    {
        service_requests.push((rand() % size_of_cylinders));
        //cout << "Generating random service request " << endl;
    }
    //service all the requests in FCFS order. Tally up the overhead work seeking the disk
    //make the new disk position the last service request serviced
    //pop the front service request off the queue to get the next one
    while (!service_requests.empty())
    {
        overhead_work += abs(disk_pos - service_requests.front());
        cout << "Current overhead work is " << overhead_work << endl;
        disk_pos = service_requests.front();
        service_requests.pop();
    }
    //print out the amount of work done traversing
    cout << "Total amount of overhead work is " << overhead_work << endl;
    return 0;
}
