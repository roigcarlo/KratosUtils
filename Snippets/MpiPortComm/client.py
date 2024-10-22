from mpi4py import MPI 

comm = MPI.COMM_WORLD

service_name="test_service"

port_name = MPI.Lookup_name(service_name)

print("PortName obtained")

intercomm = comm.Connect(port_name)

rank = intercomm.Get_rank()
size = intercomm.Get_size()
rize = intercomm.remote_size

print(f"Client initialized ({rank},{size},{rize})")

send_data = [None for _ in range(size)]; send_data[rank] = 42
recv_data = []

recv_data = intercomm.sendrecv(sendobj=[send_data], dest=0, sendtag=0, source=0, recvtag=0)

print(f"Client has data:", recv_data)

MPI.Finalize()