#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]) {
    const char * service_name = "test_service";
    
    MPI_Init(&argc, &argv);

    char port_name[MPI_MAX_PORT_NAME];

    MPI_Lookup_name(service_name, MPI_INFO_NULL, port_name);

    // Create a intercommunicator with the client (1-1)
    MPI_Comm intercomm;
    MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &intercomm);

    // Test Communication
    int send_data[] = {90, 91};
    int recv_data[] = {0, 0};

    MPI_Sendrecv(&send_data, 2, MPI_INT, 0, 0, &recv_data, 2, MPI_INT, 0, 0, intercomm, MPI_STATUS_IGNORE);
    std::cout << "Received from Server: " << recv_data[0] << ", " << recv_data[1] << std::endl;

    // Close port and finalize
    MPI_Close_port(port_name);
    MPI_Finalize();

    return 0;
}