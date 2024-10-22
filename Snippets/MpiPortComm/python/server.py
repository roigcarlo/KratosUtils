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

send_data = [None for _ in range(size)]; 
send_data[rize] = 1337

recv_data = intercomm.sendrecv(sendobj=[send_data], dest=0, sendtag=0, source=0, recvtag=0)

print(f"Client has data:", recv_data)

MPI.Finalize()