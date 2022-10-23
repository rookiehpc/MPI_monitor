/**
 * @file mpi_monitor.h
 **/

#ifndef MPI_MONITOR_H_INCLUDED
#define MPI_MONITOR_H_INCLUDED

#include <mpi.h>

/////////////////////////////////////////
// MPIM versionS OF MPI ROUTINES //
///////////////////////////////////////

int MPIM_Abort(MPI_Comm communicator, int error_code, char* file, int line, const char* args);
int MPIM_Accumulate(const void* origin_address, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_displacement, int target_count, MPI_Datatype target_datatype, MPI_Op operation, MPI_Win window, char* file, int line, const char* args);
int MPIM_Allgather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Allgatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Allreduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Alltoall(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Alltoallv(void* buffer_send, const int* counts_send, const int* displacements_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Barrier(MPI_Comm comm, char* file, int line, const char* args);
int MPIM_Bcast(void* buffer, int count, MPI_Datatype datatype, int emitter_rank, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Bsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int MPIM_Bsend_init(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Cancel(MPI_Request* request, char* file, int line, const char* args);
int MPIM_Cart_coords(MPI_Comm communicator, int rank, int dimension_number, int* coords, char* file, int line, const char* args);
int MPIM_Cart_create(MPI_Comm old_communicator, int dimension_number, const int* dimensions, const int* periods, int reorder, MPI_Comm* new_communicator, char* file, int line, const char* args);
int MPIM_Cart_get(MPI_Comm communicator, int dimension_number, int* dimensions, int* periods, int* coords, char* file, int line, const char* args);
int MPIM_Cart_shift(MPI_Comm communicator, int direction, int displacement, int* source, int* destination, char* file, int line, const char* args);
int MPIM_Comm_create(MPI_Comm old_communicator, MPI_Group group, MPI_Comm* new_communicator, char* file, int line, const char* args);
int MPIM_Comm_get_name(MPI_Comm communicator, char* name, int* length, char* file, int line, const char* args);
int MPIM_Comm_get_parent(MPI_Comm* parent, char* file, int line, const char* args);
int MPIM_Comm_group(MPI_Comm communicator, MPI_Group* group, char* file, int line, const char* args);
int MPIM_Comm_rank(MPI_Comm communicator, int* rank, char* file, int line, const char* args);
int MPIM_Comm_set_name(MPI_Comm communicator, const char* name, char* file, int line, const char* args);
int MPIM_Comm_size(MPI_Comm communicator, int* size, char* file, int line, const char* args);
int MPIM_Comm_spawn(const char* command, char** arguments, int max_process_number, MPI_Info info, int root, MPI_Comm intracommunicator, MPI_Comm* intercommunicator, int* error_codes, char* file, int line, const char* args);
int MPIM_Comm_split(MPI_Comm old_communicator, int colour, int key, MPI_Comm* new_communicator, char* file, int line, const char* args);
int MPIM_Dims_create(int process_number, int dimension_number, int* dimensions, char* file, int line, const char* args);
int MPIM_Exscan(void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Finalize(char* file, int line);
int MPIM_Gather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Gatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Get(void* origin_address, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_displacement, int target_count, MPI_Datatype target_datatype, MPI_Win window, char* file, int line, const char* args);
int MPIM_Get_address(const void* location, MPI_Aint* address, char* file, int line, const char* args);
int MPIM_Get_count(const MPI_Status* status, MPI_Datatype datatype, int* count, char* file, int line, const char* args);
int MPIM_Group_difference(MPI_Group group_a, MPI_Group group_b, MPI_Group* difference_group, char* file, int line, const char* args);
int MPIM_Group_incl(MPI_Group old_group, int rank_count, const int ranks[], MPI_Group* new_group, char* file, int line, const char* args);
int MPIM_Group_intersection(MPI_Group group_a, MPI_Group group_b, MPI_Group* intersection_group, char* file, int line, const char* args);
int MPIM_Group_rank(MPI_Group group, int* rank, char* file, int line, const char* args);
int MPIM_Group_size(MPI_Group group, int* size, char* file, int line, const char* args);
int MPIM_Group_union(MPI_Group group_a, MPI_Group group_b, MPI_Group* union_group, char* file, int line, const char* args);
int MPIM_Iallgather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Iallgatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Iallreduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Ialltoall(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Ialltoallv(void* buffer_send, const int* counts_send, const int* displacements_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Ibarrier(MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Ibsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Igather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Igatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Init(int* argc, char*** argv, char* file, int line, const char* args);
int MPIM_Iprobe(int source, int tag, MPI_Comm communicator, int* flag, MPI_Status* status, char* file, int line, const char* args);
int MPIM_Irecv(void* buffer, int count, MPI_Datatype datatype, int sender, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Ireduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Ireduce_scatter(const void* send_buffer, void* receive_buffer, int* counts, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Ireduce_scatter_block(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Irsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Iscatter(const void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Iscatterv(const void* buffer_send, const int counts_send[], const int displacements[], MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Isend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Issend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Op_create(MPI_User_function* user_function, int commutativity, MPI_Op* handle, char* file, int line, const char* args);
int MPIM_Op_free(MPI_Op* handle, char* file, int line, const char* args);
int MPIM_Probe(int source, int tag, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args);
int MPIM_Put(const void* origin_address, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_displacement, int target_count, MPI_Datatype target_datatype, MPI_Win window, char* file, int line, const char* args);
int MPIM_Recv(void* buffer, int count, MPI_Datatype type, int source, int tag, MPI_Comm comm, MPI_Status* status, char* file, int line, const char* args);
int MPIM_Recv_init(void* buffer, int count, MPI_Datatype datatype, int sender, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Reduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, int root, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Reduce_scatter(const void* send_buffer, void* receive_buffer, int* counts, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Reduce_scatter_block(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Rsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int MPIM_Rsend_init(const void* buffer, int count, MPI_Datatype datatype, int recipient, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Scan(void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Scatter(const void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Scatterv(const void* buffer_send, const int counts_send[], const int displacements[], MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args);
int MPIM_Send(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int MPIM_Send_init(const void* buffer, int count, MPI_Datatype datatype, int recipient, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Sendrecv(const void* buffer_send, int count_send, MPI_Datatype datatype_send, int recipient, int tag_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int sender, int tag_recv, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args);
int MPIM_Sendrecv_replace(void* buffer, int count_send, MPI_Datatype datatype_send, int recipient, int tag_send, int sender, int tag_recv, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args);
int MPIM_Ssend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args);
int MPIM_Ssend_init(const void* buffer, int count, MPI_Datatype datatype, int recipient, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args);
int MPIM_Start(MPI_Request* request, char* file, int line, const char* args);
int MPIM_Startall(int count, MPI_Request requests[], char* file, int line, const char* args);
int MPIM_Test(MPI_Request* request, int* flag, MPI_Status* status, char* file, int line, const char* args);
int MPIM_Test_cancelled(const MPI_Status* status, int* flag, char* file, int line, const char* args);
int MPIM_Testall(int count, MPI_Request* requests, int* flag, MPI_Status* statuses, char* file, int line, const char* args);
int MPIM_Testany(int count, MPI_Request* requests, int* index, int* flag, MPI_Status* status, char* file, int line, const char* args);
int MPIM_Testsome(int count, MPI_Request* requests, int* index_count, int* indexes, MPI_Status* statuses, char* file, int line, const char* args);
int MPIM_Type_commit(MPI_Datatype* datatype, char* file, int line, const char* args);
int MPIM_Type_contiguous(int count, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args);
int MPIM_Type_create_hindexed(int block_count, int* block_lengths, MPI_Aint* displacements, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args);
int MPIM_Type_create_hindexed_block(int block_count, int block_length, MPI_Aint* displacements, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args);
int MPIM_Type_create_hvector(int block_count, int block_length, MPI_Aint stride, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args);
int MPIM_Type_create_indexed_block(int block_count, int block_length, int* displacements, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args);
int MPIM_Type_create_struct(int block_count, const int block_lengths[], const MPI_Aint displacements[], MPI_Datatype block_types[], MPI_Datatype* new_datatype, char* file, int line, const char* args);
int MPIM_Type_create_subarray(int dim_count, const int array_element_counts[], const int subarray_element_counts[], const int subarray_coordinates[], int order, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args);
int MPIM_Type_free(MPI_Datatype* datatype, char* file, int line, const char* args);
int MPIM_Type_get_extent(MPI_Datatype datatype, MPI_Aint* lower_bound, MPI_Aint* extent, char* file, int line, const char* args);
int MPIM_Type_indexed(int block_count, int* block_lengths, const int displacements[], MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args);
int MPIM_Type_vector(int block_count, int block_length, int stride, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args);
int MPIM_Wait(MPI_Request* request, MPI_Status* status, char* file, int line, const char* args);
int MPIM_Waitall(int count, MPI_Request requests[], MPI_Status statuses[], char* file, int line, const char* args);
int MPIM_Waitany(int count, MPI_Request requests[], int* index, MPI_Status* status, char* file, int line, const char* args);
int MPIM_Waitsome(int request_count, MPI_Request requests[], int* index_count, int indices[], MPI_Status statuses[], char* file, int line, const char* args);
int MPIM_Win_allocate(MPI_Aint size, int displacement_unit, MPI_Info info, MPI_Comm communicator, void* base, MPI_Win* window, char* file, int line, const char* args);
int MPIM_Win_attach(MPI_Win window, void* base, MPI_Aint size, char* file, int line, const char* args);
int MPIM_Win_create(void* base, MPI_Aint size, int displacement_unit, MPI_Info info, MPI_Comm communicator, MPI_Win* window, char* file, int line, const char* args);
int MPIM_Win_create_dynamic(MPI_Info info, MPI_Comm communicator, MPI_Win* window, char* file, int line, const char* args);
int MPIM_Win_detach(MPI_Win window, const void* base, char* file, int line, const char* args);
int MPIM_Win_free(MPI_Win* window, char* file, int line, const char* args);
double MPIM_Wtime(char* file, int line, const char* args);

//////////////////////////////////////////////
// DEFINES TO BYPASS ORIGINAL MPI ROUTINES //
////////////////////////////////////////////

#ifndef MPI_MONITOR_NO_SUBSTITUTION
/// Redirects calls from MPI_Abort to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Abort(...) MPIM_Abort(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Accumulate to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Accumulate(...) MPIM_Accumulate(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Allgather to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Allgather(...) MPIM_Allgather(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Allgatherv to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Allgatherv(...) MPIM_Allgatherv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Allreduce to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Allreduce(...) MPIM_Allreduce(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Alltoall to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Alltoall(...) MPIM_Alltoall(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Alltoallv to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Alltoallv(...) MPIM_Alltoallv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Barrier to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Barrier(...) MPIM_Barrier(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Bsend to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Bcast(...) MPIM_Bcast(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Bsend to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Bsend(...) MPIM_Bsend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Bsend_init to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Bsend_init(...) MPIM_Bsend_init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Cancel to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Cancel(...) MPIM_Cancel(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Card_coords to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Card_coords(...) MPIM_Cart_coords(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Card_create to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Card_create(...) MPIM_Cart_create(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Card_get to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Card_get(...) MPIM_Cart_get(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Card_shift to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Card_shift(...) MPIM_Cart_shift(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_create to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_create(...) MPIM_Comm_create(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_get_name to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_get_name(...) MPIM_Comm_get_name(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_get_parent to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_get_parent(...) MPIM_Comm_get_parent(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_group to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_group(...) MPIM_Comm_group(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_rank to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_rank(...) MPIM_Comm_rank(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_set_name to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_set_name(...) MPIM_Comm_set_name(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_size to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_size(...) MPIM_Comm_size(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_spawn to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_spawn(...) MPIM_Comm_spawn(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Comm_split to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Comm_split(...) MPIM_Comm_split(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Dims_create to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Dims_create(...) MPIM_Dims_create(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Exscan to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Exscan(...) MPIM_Exscan(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Finalize to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Finalize() MPIM_Finalize(__FILE__, __LINE__)
/// Redirects calls from MPI_Gather to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Gather(...) MPIM_Gather(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Gatherv to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Gatherv(...) MPIM_Gatherv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Get to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Get(...) MPIM_Get(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Get_address to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Get_address(...) MPIM_Get_address(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Get_count to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Get_count(...) MPIM_Get_count(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Group_difference to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Group_difference(...) MPIM_Group_difference(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Group_incl to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Group_incl(...) MPIM_Group_incl(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Group_intersection to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Group_intersection(...) MPIM_Group_intersection(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Group_rank to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Group_rank(...) MPIM_Group_rank(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Group_size to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Group_size(...) MPIM_Group_size(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Group_union to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Group_union(...) MPIM_Group_union(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iallgather to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iallgather(...) MPIM_Iallgather(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iallgatherv to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iallgatherv(...) MPIM_Iallgatherv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iallreduce to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iallreduce(...) MPIM_Iallreduce(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ialltoall to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ialltoall(...) MPIM_Ialltoall(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ialltoallv to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ialltoallv(...) MPIM_Ialltoallv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ibarrier to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ibarrier(...) MPIM_Ibarrier(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ibsend to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ibsend(...) MPIM_Ibsend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Igather to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Igather(...) MPIM_Igather(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Igatherv to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Igatherv(...) MPIM_Igatherv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Init to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Init(...) MPIM_Init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iprobe to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iprobe(...) MPIM_Iprobe(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Irecv to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Irecv(...) MPIM_Irecv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ireduce to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ireduce(...) MPIM_Ireduce(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ireduce_scatter to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ireduce_scatter(...) MPIM_Ireduce_scatter(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ireduce_scatter_block to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ireduce_scatter_block(...) MPIM_Ireduce_scatter_block(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Irsend to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Irsend(...) MPIM_Irsend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iscatter to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iscatter(...) MPIM_Iscatter(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Iscatterv to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Iscatterv(...) MPIM_Iscatterv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Isend to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Isend(...) MPIM_Isend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Issend to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Issend(...) MPIM_Issend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Op_create to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Op_create(...) MPIM_Op_create(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Op_free to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Op_free(...) MPIM_Op_free(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Probe to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Probe(...) MPIM_Probe(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Put to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Put(...) MPIM_Put(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Recv to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Recv(...) MPIM_Recv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Recv_init to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Recv_init(...) MPIM_Recv_init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Reduce to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Reduce(...) MPIM_Reduce(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Reduce_scatter to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Reduce_scatter(...) MPIM_Reduce_scatter(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Reduce_scatter_block to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Reduce_scatter_block(...) MPIM_Reduce_scatter_block(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Rsend to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Rsend(...) MPIM_Rsend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Rsend_init to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Rsend_init(...) MPIM_Rsend_init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Scan to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Scan(...) MPIM_Scan(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Scatter to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Scatter(...) MPIM_Scatter(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Scatterv to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Scatterv(...) MPIM_Scatterv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Send to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Send(...) MPIM_Send(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Send_init to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Send_init(...) MPIM_Send_init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Sendrecv to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Sendrecv(...) MPIM_Sendrecv(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Sendrecv_replace to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Sendrecv_replace(...) MPIM_Sendrecv_replace(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ssend to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ssend(...) MPIM_Ssend(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Ssend_init to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Ssend_init(...) MPIM_Ssend_init(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Start to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Start(...) MPIM_Start(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Startall to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Startall(...) MPIM_Startall(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Test to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Test(...) MPIM_Test(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Test_cancelled to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Test_cancelled(...) MPIM_Test_cancelled(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Testall to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Testall(...) MPIM_Testall(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Testany to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Testany(...) MPIM_Testany(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Testsome to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Testsome(...) MPIM_Testsome(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_commit to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_commit(...) MPIM_Type_commit(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_contiguous to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_contiguous(...) MPIM_Type_contiguous(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_create_hindexed to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_create_hindexed(...) MPIM_Type_create_hindexed(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_create_hindexed_block to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_create_hindexed_block(...) MPIM_Type_create_hindexed_block(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_create_hvector to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_create_hvector(...) MPIM_Type_create_hvector(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_create_indexed_block to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_create_indexed_block(...) MPIM_Type_create_indexed_block(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_create_struct to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_create_struct(...) MPIM_Type_create_struct(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_create_subarray to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_create_subarray(...) MPIM_Type_create_subarray(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_free to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_free(...) MPIM_Type_free(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_get_extent to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_get_extent(...) MPIM_Type_get_extent(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_indexed to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_indexed(...) MPIM_Type_indexed(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Type_vector to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Type_vector(...) MPIM_Type_vector(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Wait to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Wait(...) MPIM_Wait(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Waitall to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Waitall(...) MPIM_Waitall(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Waitany to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Waitany(...) MPIM_Waitany(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Waitsome to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Waitsome(...) MPIM_Waitsome(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_allocate to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_allocate(...) MPIM_Win_allocate(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_attach to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_attach(...) MPIM_Win_attach(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_create to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_create(...) MPIM_Win_create(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_create_dynamic to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_create_dynamic(...) MPIM_Win_create_dynamic(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_detach to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_detach(...) MPIM_Win_detach(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Win_free to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Win_free(...) MPIM_Win_free(__VA_ARGS__, __FILE__, __LINE__, #__VA_ARGS__)
/// Redirects calls from MPI_Wtime to the MPIM version and collects the file name as well as the line at which the MPI call is issued
#define MPI_Wtime(...) MPIM_Wtime(__FILE__, __LINE__, #__VA_ARGS__)
#endif // MPI_MONITOR_NO_SUBSTITUTION

#endif // MPI_MONITOR_H_INCLUDED