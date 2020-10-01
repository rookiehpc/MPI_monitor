/**
 * @file RookieHPC_mpi.h
 * @author RookieHPC
 * @brief This tool can be downloaded from https://www.rookiehpc.com/mpi/tools/.
 **/

#ifndef ROOKIEHPC_MPI_H_INCLUDED
#define ROOKIEHPC_MPI_H_INCLUDED

#include <mpi.h>

/////////////////////////////////////////
// ROOKIEHPC VERSIONS OF MPI ROUTINES //
///////////////////////////////////////

int RookieHPC_MPI_Abort(MPI_Comm communicator, int error_code, char* file, int line, const char* args);
int RookieHPC_MPI_Allgather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Allgatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Allreduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Alltoall(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Alltoallv(void* buffer_send, const int* counts_send, const int* displacements_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Barrier(MPI_Comm comm, char* file, int line, const char* args);
int RookieHPC_MPI_Bcast(void* buffer, int count, MPI_Datatype datatype, int emitter_rank, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Bsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int RookieHPC_MPI_Comm_split(MPI_Comm old_communicator, int colour, int key, MPI_Comm* new_communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Exscan(void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Finalize(char* file, int line);
int RookieHPC_MPI_Gather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Gatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Get_address(const void* location, MPI_Aint* address, char* file, int line, const char* args);
int RookieHPC_MPI_Iallgather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Iallgatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Iallreduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Ialltoall(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Ialltoallv(void* buffer_send, const int* counts_send, const int* displacements_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Ibarrier(MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Ibsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Igather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Igatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Init(int* argc, char*** argv, char* file, int line, const char* args);
int RookieHPC_MPI_Iprobe(int source, int tag, MPI_Comm communicator, int* flag, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Irecv(void* buffer, int count, MPI_Datatype datatype, int sender, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Ireduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Ireduce_scatter(const void* send_buffer, void* receive_buffer, int* counts, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Ireduce_scatter_block(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Irsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Iscatter(const void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Iscatterv(const void* buffer_send, const int counts_send[], const int displacements[], MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Isend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Issend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Recv(void* buffer, int count, MPI_Datatype type, int source, int tag, MPI_Comm comm, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Reduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, int root, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Reduce_scatter(const void* send_buffer, void* receive_buffer, int* counts, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Reduce_scatter_block(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Rsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int RookieHPC_MPI_Scan(void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Scatter(const void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Scatterv(const void* buffer_send, const int counts_send[], const int displacements[], MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Send(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int RookieHPC_MPI_Sendrecv(const void* buffer_send, int count_send, MPI_Datatype datatype_send, int recipient, int tag_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int sender, int tag_recv, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Sendrecv_replace(void* buffer, int count_send, MPI_Datatype datatype_send, int recipient, int tag_send, int sender, int tag_recv, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Ssend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int RookieHPC_MPI_Wait(MPI_Request* request, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Waitall(int count, MPI_Request requests[], MPI_Status statuses[], char* file, int line, const char* args);
int RookieHPC_MPI_Waitany(int count, MPI_Request requests[], int* index, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Waitsome(int request_count, MPI_Request requests[], int* index_count, int indices[], MPI_Status statuses[], char* file, int line, const char* args);
double RookieHPC_MPI_Wtime(char* file, int line, const char* args);

//////////////////////////////////////////////
// DEFINES TO BYPASS ORIGINAL MPI ROUTINES //
////////////////////////////////////////////

#ifndef ROOKIEHPC_MPI_NO_SUBSTITUTION
/// Redirects calls from MPI_Abort to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Abort(...) RookieHPC_MPI_Abort(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
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
/// Redirects calls from MPI_Exscan to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Exscan(...) RookieHPC_MPI_Exscan(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Finalize to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Finalize() RookieHPC_MPI_Finalize(__FILE__, __LINE__)
/// Redirects calls from MPI_Gather to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Gather(...) RookieHPC_MPI_Gather(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Gatherv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Gatherv(...) RookieHPC_MPI_Gatherv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Get_address to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Get_address(...) RookieHPC_MPI_Get_address(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iallgather to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iallgather(...) RookieHPC_MPI_Iallgather(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iallgatherv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iallgatherv(...) RookieHPC_MPI_Iallgatherv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iallreduce to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iallreduce(...) RookieHPC_MPI_Iallreduce(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ialltoall to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ialltoall(...) RookieHPC_MPI_Ialltoall(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ialltoallv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ialltoallv(...) RookieHPC_MPI_Ialltoallv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ibarrier to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ibarrier(...) RookieHPC_MPI_Ibarrier(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ibsend to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ibsend(...) RookieHPC_MPI_Ibsend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Igather to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Igather(...) RookieHPC_MPI_Igather(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Igatherv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Igatherv(...) RookieHPC_MPI_Igatherv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Init to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Init(...) RookieHPC_MPI_Init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iprobe to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iprobe(...) RookieHPC_MPI_Iprobe(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Irecv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Irecv(...) RookieHPC_MPI_Irecv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ireduce to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ireduce(...) RookieHPC_MPI_Ireduce(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ireduce_scatter to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ireduce_scatter(...) RookieHPC_MPI_Ireduce_scatter(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ireduce_scatter_block to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ireduce_scatter_block(...) RookieHPC_MPI_Ireduce_scatter_block(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Irsend to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Irsend(...) RookieHPC_MPI_Irsend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iscatter to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iscatter(...) RookieHPC_MPI_Iscatter(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iscatterv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iscatterv(...) RookieHPC_MPI_Iscatterv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Isend to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Isend(...) RookieHPC_MPI_Isend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Issend to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Issend(...) RookieHPC_MPI_Issend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Recv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Recv(...) RookieHPC_MPI_Recv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Reduce to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Reduce(...) RookieHPC_MPI_Reduce(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Reduce_scatter to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Reduce_scatter(...) RookieHPC_MPI_Reduce_scatter(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Reduce_scatter_block to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Reduce_scatter_block(...) RookieHPC_MPI_Reduce_scatter_block(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Rsend to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Rsend(...) RookieHPC_MPI_Rsend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Scan to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Scan(...) RookieHPC_MPI_Scan(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Scatter to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Scatter(...) RookieHPC_MPI_Scatter(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Scatterv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Scatterv(...) RookieHPC_MPI_Scatterv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Send to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Send(...) RookieHPC_MPI_Send(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Sendrecv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Sendrecv(...) RookieHPC_MPI_Sendrecv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Sendrecv_replace to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Sendrecv_replace(...) RookieHPC_MPI_Sendrecv_replace(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ssend to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ssend(...) RookieHPC_MPI_Ssend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Wait to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Wait(...) RookieHPC_MPI_Wait(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Waitall to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Waitall(...) RookieHPC_MPI_Waitall(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Waitany to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Waitany(...) RookieHPC_MPI_Waitany(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Waitsome to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Waitsome(...) RookieHPC_MPI_Waitsome(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Wtime to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Wtime(...) RookieHPC_MPI_Wtime(__FILE__, __LINE__, #__VA_ARGS__)
#endif // ROOKIEHPC_MPI_NO_SUBSTITUTION

#endif // ROOKIEHPC_MPI_H_INCLUDED