/**
 * @file RookieHPC_mpi.h
 * @author RookieHPC
 * @brief This tool can be downloaded from https://www.rookiehpc.com/mpi/tools/.
 **/

#ifndef ROOKIEHPC_MPI_H_INCLUDED
#define ROOKIEHPC_MPI_H_INCLUDED

////////////////////
// CUSTOMISATION //
//////////////////

// Uncomment this define so that an MPI_Send will always result in an MPI_Ssend (same for non-blocking)
// #define ROOKIEHPC_ENFORCE_SYNCHRONOUS_SENDS

//////////////
// WARNING //
////////////

// Please do not modify the code below.

#include <mpi.h>

/////////////////////////////////////////
// ROOKIEHPC VERSIONS OF MPI ROUTINES //
///////////////////////////////////////

void RookieHPC_MPI_Allgather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
void RookieHPC_MPI_Allgatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
void RookieHPC_MPI_Allreduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
void RookieHPC_MPI_Alltoall(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
void RookieHPC_MPI_Alltoallv(void* buffer_send, const int* counts_send, const int* displacements_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
void RookieHPC_MPI_Barrier(MPI_Comm comm, char* file, int line, const char* args);
void RookieHPC_MPI_Bcast(void* buffer, int count, MPI_Datatype datatype, int emitter_rank, MPI_Comm communicator, char* file, int line, const char* args);
void RookieHPC_MPI_Bsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
void RookieHPC_MPI_Comm_split(MPI_Comm old_communicator, int colour, int key, MPI_Comm* new_communicator, char* file, int line, const char* args);
void RookieHPC_MPI_Finalize(char* file, int line);
void RookieHPC_MPI_Gather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
void RookieHPC_MPI_Gatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
void RookieHPC_MPI_Get_address(const void* location, MPI_Aint* address, char* file, int line, const char* args);
void RookieHPC_MPI_Init(int* argc, char*** argv, char* file, int line, const char* args);
void RookieHPC_MPI_Recv(void* buffer, int count, MPI_Datatype type, int source, int tag, MPI_Comm comm, MPI_Status* status, char* file, int line, const char* args);
void RookieHPC_MPI_Send(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
void RookieHPC_MPI_Ssend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);

//////////////////////////////////////////////
// DEFINES TO BYPASS ORIGINAL MPI ROUTINES //
////////////////////////////////////////////

#ifndef ROOKIEHPC_MPI_NO_SUBSTITUTION
/// Redirects calls from MPI_Allgather to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Allgather(...) RookieHPC_MPI_Allgather(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Allgatherv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Allgatherv(...) RookieHPC_MPI_Allgatherv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Allreduce to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Allreduce(...) RookieHPC_MPI_Allreduce(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Alltoall to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Alltoall(...) RookieHPC_MPI_Alltoall(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Alltoallv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Alltoallv(...) RookieHPC_MPI_Alltoallv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Barrier to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Barrier(...) RookieHPC_MPI_Barrier(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Bsend to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Bcast(...) RookieHPC_MPI_Bcast(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Bsend to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Bsend(...) RookieHPC_MPI_Bsend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_split to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_split(...) RookieHPC_MPI_Comm_split(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Finalize to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Finalize() RookieHPC_MPI_Finalize(__FILE__, __LINE__)
/// Redirects calls from MPI_Gather to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Gather(...) RookieHPC_MPI_Gather(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Gatherv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Gatherv(...) RookieHPC_MPI_Gatherv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Get_address to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Get_address(...) RookieHPC_MPI_Get_address(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Init to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Init(...) RookieHPC_MPI_Init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Recv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Recv(...) RookieHPC_MPI_Recv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Send to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Send(...) RookieHPC_MPI_Send(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ssend to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ssend(...) RookieHPC_MPI_Ssend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
#endif

#endif // ROOKIEHPC_MPI_H_INCLUDED