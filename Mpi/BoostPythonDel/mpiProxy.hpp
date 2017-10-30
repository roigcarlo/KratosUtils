#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

constexpr int SLEEP_TIME = 2500;

class MpiProxy {
public:
  int mpiSize;
  int mpiRank;

  MpiProxy();
  ~MpiProxy();

  void ImportantFunction();
};