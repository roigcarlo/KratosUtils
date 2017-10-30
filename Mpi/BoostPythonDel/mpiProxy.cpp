#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

#include "mpiProxy.hpp"

MpiProxy::MpiProxy() {
  std::cout << "Creating mpi proxy" << std::endl;
  MPI_Init(nullptr, nullptr);
  
  MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
  std::cout << "Correctly initialized cpp module :)" << std::endl;
}

MpiProxy::~MpiProxy() {
  // Making the code sleep here should prevent 
  // MPI_Finalize from being called when the 
  // module is unloaded if the __del__ function
  // does not wait for this function to end
  sleep(SLEEP_TIME / 1000.0);
  MPI_Finalize();
  std::cout << "Correctly exiting cpp module :)" << std::endl;
}

void MpiProxy::ImportantFunction() {
  std::cout << "I'm vegan... I mean, process " << mpiRank << std::endl;
}