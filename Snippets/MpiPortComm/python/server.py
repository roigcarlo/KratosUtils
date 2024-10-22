import numpy as np

from mpi4py import MPI 

comm = MPI.COMM_WORLD

service_name="test_service"

port_name=MPI.Open_port()
MPI.Publish_name(service_name, port_name)

print("ServiceName Published")

# Create a intercommunicator with the client (1-1)
intercomm = comm.Accept(port_name)

rank = comm.Get_rank()
size = comm.Get_size()
rize = intercomm.remote_size

print(f"Server initialized ({rank},{size},{rize})")

send_data = np.array([1337, 2661], dtype=np.int32); 
recv_data = np.array([0,    0   ], dtype=np.int32); 

# Test Communication
intercomm.Sendrecv(
    sendbuf=[send_data, 2, 0, MPI.INT], dest=0, sendtag=0, 
    recvbuf=[recv_data, 2, 0, MPI.INT], source=0, recvtag=0
)

print(f"Client has data:", recv_data)

MPI.Close_port(port_name)
MPI.Finalize()