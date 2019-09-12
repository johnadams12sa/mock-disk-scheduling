#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

const int size_of_cylinders = 5000;
const int midpoint = size_of_cylinders/2;

int get_disk_init_pos(int disk_init_pos){
    bool input_flag = false;
    //ask user for input for initial position of disk-head to start servicing requests
    cerr << "Enter a starting disk-head placement " << endl;
    cin >> disk_init_pos;
    while (input_flag){
        //questionable input validation, kind of buggy at the moment
        if (!isdigit(disk_init_pos)){
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
int main(){
    array<int, size_of_cylinders> service_requests;
    service_requests.fill(0);
    int disk_init_pos, disk_pos, overhead_work = 0;
    int number_of_requests = 50;

    //function to get user input on initial disk head
    disk_pos = get_disk_init_pos(disk_init_pos);

    //populate queue with 50 randomly generated requests (use random number generator to get
    //service request numbers)
    //initialize service requests on array to value 1 to denote a service being requested
    srand(time(NULL));
    for (int i = 0; i < number_of_requests; i++)
    {
        service_requests[(rand() % size_of_cylinders)] = 1;
    }

    for (int u = 0; u < size_of_cylinders; u++){
        if (service_requests[u] == 1){
            cout << "Service Request number " << u << endl;
        }
    }

    //determine which end the initial seek position is in and traverse towards that end
    //first, then the traversal is reversed in the other direction to finish any other requests
    if (disk_pos > midpoint){
        for (int i= disk_pos; i < size_of_cylinders; i++){
            if(service_requests[i] == 1){
                cout << "Service Request " << i << " is fulfilled first round " << endl;
                overhead_work += abs(disk_pos - i);
                disk_pos = i;
            }
        }
        for (int j = size_of_cylinders; j > 0; j--){
            if(service_requests[j] == 1){
                cout << "Service Request " << j << " is fulfilled second round " << endl;
                overhead_work += abs(disk_pos - j);
                disk_pos = j;
            }
        }
    }
    else if (disk_pos < midpoint) {
        for (int i = disk_pos; i > 0; i--)
        {
            if (service_requests[i] == 1)
            {
                cout << "Service Request " << i << " is fulfilled first round " << endl;
                overhead_work += abs(disk_pos - i);
                disk_pos = i;
            }
        }
        for (int j = 0; j < size_of_cylinders; j++)
        {
            if (service_requests[j] == 1)
            {
                cout << "Service Request " << j << " is fulfilled second round " << endl;
                overhead_work += abs(disk_pos - j);
                disk_pos = j;
            }
        }
    }
    else {
        for (int i = disk_pos; i < size_of_cylinders; i++)
        {
            if (service_requests[i] == 1)
            {
                cout << "Service Request " << i << " is fulfilled first round " << endl;
                overhead_work += abs(disk_pos - i);
                disk_pos = i;
            }
        }
        for (int j = size_of_cylinders; j > 0; j--)
        {
            if (service_requests[j] == 1)
            {
                cout << "Service Request " << j << " is fulfilled second round " << endl;
                overhead_work += abs(disk_pos - j);
                disk_pos = j;
            }
        }
    }

    //print out the amount of work done seeking the track
    cout << "Total overhead work is " << overhead_work << endl;
    return 0;
}