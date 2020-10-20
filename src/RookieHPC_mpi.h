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
int RookieHPC_MPI_Accumulate(const void* origin_address, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_displacement, int target_count, MPI_Datatype target_datatype, MPI_Op operation, MPI_Win window, char* file, int line, const char* args);
int RookieHPC_MPI_Allgather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Allgatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Allreduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Alltoall(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Alltoallv(void* buffer_send, const int* counts_send, const int* displacements_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Barrier(MPI_Comm comm, char* file, int line, const char* args);
int RookieHPC_MPI_Bcast(void* buffer, int count, MPI_Datatype datatype, int emitter_rank, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Bsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int RookieHPC_MPI_Bsend_init(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Cart_coords(MPI_Comm communicator, int rank, int dimension_number, int* coords, char* file, int line, const char* args);
int RookieHPC_MPI_Cart_create(MPI_Comm old_communicator, int dimension_number, const int* dimensions, const int* periods, int reorder, MPI_Comm* new_communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Cart_get(MPI_Comm communicator, int dimension_number, int* dimensions, int* periods, int* coords, char* file, int line, const char* args);
int RookieHPC_MPI_Cart_shift(MPI_Comm communicator, int direction, int displacement, int* source, int* destination, char* file, int line, const char* args);
int RookieHPC_MPI_Comm_create(MPI_Comm old_communicator, MPI_Group group, MPI_Comm* new_communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Comm_get_name(MPI_Comm communicator, char* name, int* length, char* file, int line, const char* args);
int RookieHPC_MPI_Comm_get_parent(MPI_Comm* parent, char* file, int line, const char* args);
int RookieHPC_MPI_Comm_group(MPI_Comm communicator, MPI_Group* group, char* file, int line, const char* args);
int RookieHPC_MPI_Comm_rank(MPI_Comm communicator, int* rank, char* file, int line, const char* args);
int RookieHPC_MPI_Comm_set_name(MPI_Comm communicator, const char* name, char* file, int line, const char* args);
int RookieHPC_MPI_Comm_size(MPI_Comm communicator, int* size, char* file, int line, const char* args);
int RookieHPC_MPI_Comm_spawn(const char* command, char** arguments, int max_process_number, MPI_Info info, int root, MPI_Comm intracommunicator, MPI_Comm* intercommunicator, int* error_codes, char* file, int line, const char* args);
int RookieHPC_MPI_Comm_split(MPI_Comm old_communicator, int colour, int key, MPI_Comm* new_communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Dims_create(int process_number, int dimension_number, int* dimensions, char* file, int line, const char* args);
int RookieHPC_MPI_Exscan(void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Finalize(char* file, int line);
int RookieHPC_MPI_Gather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Gatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Get(void* origin_address, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_displacement, int target_count, MPI_Datatype target_datatype, MPI_Win window, char* file, int line, const char* args);
int RookieHPC_MPI_Get_address(const void* location, MPI_Aint* address, char* file, int line, const char* args);
int RookieHPC_MPI_Get_count(const MPI_Status* status, MPI_Datatype datatype, int* count, char* file, int line, const char* args);
int RookieHPC_MPI_Group_difference(MPI_Group group_a, MPI_Group group_b, MPI_Group* difference_group, char* file, int line, const char* args);
int RookieHPC_MPI_Group_incl(MPI_Group old_group, int rank_count, const int ranks[], MPI_Group* new_group, char* file, int line, const char* args);
int RookieHPC_MPI_Group_intersection(MPI_Group group_a, MPI_Group group_b, MPI_Group* intersection_group, char* file, int line, const char* args);
int RookieHPC_MPI_Group_rank(MPI_Group group, int* rank, char* file, int line, const char* args);
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
int RookieHPC_MPI_Op_create(MPI_User_function* user_function, int commutativity, MPI_Op* handle, char* file, int line, const char* args);
int RookieHPC_MPI_Op_free(MPI_Op* handle, char* file, int line, const char* args);
int RookieHPC_MPI_Probe(int source, int tag, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Put(const void* origin_address, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_displacement, int target_count, MPI_Datatype target_datatype, MPI_Win window, char* file, int line, const char* args);
int RookieHPC_MPI_Recv(void* buffer, int count, MPI_Datatype type, int source, int tag, MPI_Comm comm, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Recv_init(void* buffer, int count, MPI_Datatype datatype, int sender, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Reduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, int root, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Reduce_scatter(const void* send_buffer, void* receive_buffer, int* counts, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Reduce_scatter_block(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Rsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int RookieHPC_MPI_Rsend_init(const void* buffer, int count, MPI_Datatype datatype, int recipient, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Scan(void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Scatter(const void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Scatterv(const void* buffer_send, const int counts_send[], const int displacements[], MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int RookieHPC_MPI_Send(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int RookieHPC_MPI_Send_init(const void* buffer, int count, MPI_Datatype datatype, int recipient, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Sendrecv(const void* buffer_send, int count_send, MPI_Datatype datatype_send, int recipient, int tag_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int sender, int tag_recv, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Sendrecv_replace(void* buffer, int count_send, MPI_Datatype datatype_send, int recipient, int tag_send, int sender, int tag_recv, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Ssend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int RookieHPC_MPI_Ssend_init(const void* buffer, int count, MPI_Datatype datatype, int recipient, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Start(MPI_Request* request, char* file, int line, const char* args);
int RookieHPC_MPI_Startall(int count, MPI_Request requests[], char* file, int line, const char* args);
int RookieHPC_MPI_Test(MPI_Request* request, int* flag, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Testall(int count, MPI_Request* requests, int* flag, MPI_Status* statuses, char* file, int line, const char* args);
int RookieHPC_MPI_Testany(int count, MPI_Request* requests, int* index, int* flag, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Testsome(int count, MPI_Request* requests, int* index_count, int* indexes, MPI_Status* statuses, char* file, int line, const char* args);
int RookieHPC_MPI_Wait(MPI_Request* request, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Waitall(int count, MPI_Request requests[], MPI_Status statuses[], char* file, int line, const char* args);
int RookieHPC_MPI_Waitany(int count, MPI_Request requests[], int* index, MPI_Status* status, char* file, int line, const char* args);
int RookieHPC_MPI_Waitsome(int request_count, MPI_Request requests[], int* index_count, int indices[], MPI_Status statuses[], char* file, int line, const char* args);
int RookieHPC_MPI_Win_allocate(MPI_Aint size, int displacement_unit, MPI_Info info, MPI_Comm communicator, void* base, MPI_Win* window, char* file, int line, const char* args);
int RookieHPC_MPI_Win_attach(MPI_Win window, void* base, MPI_Aint size, char* file, int line, const char* args);
int RookieHPC_MPI_Win_create(void* base, MPI_Aint size, int displacement_unit, MPI_Info info, MPI_Comm communicator, MPI_Win* window, char* file, int line, const char* args);
int RookieHPC_MPI_Win_create_dynamic(MPI_Info info, MPI_Comm communicator, MPI_Win* window, char* file, int line, const char* args);
int RookieHPC_MPI_Win_detach(MPI_Win window, const void* base, char* file, int line, const char* args);
int RookieHPC_MPI_Win_free(MPI_Win* window, char* file, int line, const char* args);
double RookieHPC_MPI_Wtime(char* file, int line, const char* args);

//////////////////////////////////////////////
// DEFINES TO BYPASS ORIGINAL MPI ROUTINES //
////////////////////////////////////////////

#ifndef ROOKIEHPC_MPI_NO_SUBSTITUTION
/// Redirects calls from MPI_Abort to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Abort(...) RookieHPC_MPI_Abort(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Accumulate to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Accumulate(...) RookieHPC_MPI_Accumulate(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
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
/// Redirects calls from MPI_Bsend_init to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Bsend_init(...) RookieHPC_MPI_Bsend_init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Card_coords to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Card_coords(...) RookieHPC_MPI_Cart_coords(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Card_create to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Card_create(...) RookieHPC_MPI_Cart_create(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Card_get to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Card_get(...) RookieHPC_MPI_Cart_get(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Card_shift to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Card_shift(...) RookieHPC_MPI_Cart_shift(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_create to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_create(...) RookieHPC_MPI_Comm_create(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_get_name to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_get_name(...) RookieHPC_MPI_Comm_get_name(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_get_parent to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_get_parent(...) RookieHPC_MPI_Comm_get_parent(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_group to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_group(...) RookieHPC_MPI_Comm_group(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_rank to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_rank(...) RookieHPC_MPI_Comm_rank(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_set_name to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_set_name(...) RookieHPC_MPI_Comm_set_name(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_size to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_size(...) RookieHPC_MPI_Comm_size(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_spawn to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_spawn(...) RookieHPC_MPI_Comm_spawn(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_split to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_split(...) RookieHPC_MPI_Comm_split(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Dims_create to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Dims_create(...) RookieHPC_MPI_Dims_create(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Exscan to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Exscan(...) RookieHPC_MPI_Exscan(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Finalize to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Finalize() RookieHPC_MPI_Finalize(__FILE__, __LINE__)
/// Redirects calls from MPI_Gather to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Gather(...) RookieHPC_MPI_Gather(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Gatherv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Gatherv(...) RookieHPC_MPI_Gatherv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Get to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Get(...) RookieHPC_MPI_Get(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Get_address to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Get_address(...) RookieHPC_MPI_Get_address(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Get_count to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Get_count(...) RookieHPC_MPI_Get_count(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Group_difference to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Group_difference(...) RookieHPC_MPI_Group_difference(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Group_incl to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Group_incl(...) RookieHPC_MPI_Group_incl(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Group_intersection to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Group_intersection(...) RookieHPC_MPI_Group_intersection(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Group_rank to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Group_rank(...) RookieHPC_MPI_Group_rank(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
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
/// Redirects calls from MPI_Op_create to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Op_create(...) RookieHPC_MPI_Op_create(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Op_free to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Op_free(...) RookieHPC_MPI_Op_free(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Probe to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Probe(...) RookieHPC_MPI_Probe(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Put to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Put(...) RookieHPC_MPI_Put(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Recv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Recv(...) RookieHPC_MPI_Recv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Recv_init to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Recv_init(...) RookieHPC_MPI_Recv_init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Reduce to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Reduce(...) RookieHPC_MPI_Reduce(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Reduce_scatter to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Reduce_scatter(...) RookieHPC_MPI_Reduce_scatter(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Reduce_scatter_block to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Reduce_scatter_block(...) RookieHPC_MPI_Reduce_scatter_block(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Rsend to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Rsend(...) RookieHPC_MPI_Rsend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Rsend_init to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Rsend_init(...) RookieHPC_MPI_Rsend_init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Scan to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Scan(...) RookieHPC_MPI_Scan(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Scatter to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Scatter(...) RookieHPC_MPI_Scatter(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Scatterv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Scatterv(...) RookieHPC_MPI_Scatterv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Send to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Send(...) RookieHPC_MPI_Send(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Send_init to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Send_init(...) RookieHPC_MPI_Send_init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Sendrecv to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Sendrecv(...) RookieHPC_MPI_Sendrecv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Sendrecv_replace to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Sendrecv_replace(...) RookieHPC_MPI_Sendrecv_replace(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ssend to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ssend(...) RookieHPC_MPI_Ssend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ssend_init to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ssend_init(...) RookieHPC_MPI_Ssend_init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Start to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Start(...) RookieHPC_MPI_Start(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Startall to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Startall(...) RookieHPC_MPI_Startall(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Test to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Test(...) RookieHPC_MPI_Test(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Testall to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Testall(...) RookieHPC_MPI_Testall(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Testany to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Testany(...) RookieHPC_MPI_Testany(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Testsome to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Testsome(...) RookieHPC_MPI_Testsome(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Wait to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Wait(...) RookieHPC_MPI_Wait(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Waitall to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Waitall(...) RookieHPC_MPI_Waitall(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Waitany to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Waitany(...) RookieHPC_MPI_Waitany(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Waitsome to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Waitsome(...) RookieHPC_MPI_Waitsome(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_allocate to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_allocate(...) RookieHPC_MPI_Win_allocate(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_attach to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_attach(...) RookieHPC_MPI_Win_attach(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_create to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_create(...) RookieHPC_MPI_Win_create(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_create_dynamic to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_create_dynamic(...) RookieHPC_MPI_Win_create_dynamic(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_detach to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_detach(...) RookieHPC_MPI_Win_detach(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_free to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_free(...) RookieHPC_MPI_Win_free(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Wtime to the RookieHPC version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Wtime(...) RookieHPC_MPI_Wtime(__FILE__, __LINE__, #__VA_ARGS__)
#endif // ROOKIEHPC_MPI_NO_SUBSTITUTION

#endif // ROOKIEHPC_MPI_H_INCLUDED