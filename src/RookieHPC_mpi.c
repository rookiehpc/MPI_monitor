/**
 * @file RookieHPC_mpi.c
 * @author RookieHPC
 * @brief This tool can be downloaded from https://www.rookiehpc.com/mpi/tools/.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool
#include <math.h> // fabs
#include <pthread.h> // pthread_t
#include <string.h> // memcpy
#include <unistd.h> // sleep, usleep
#include <sys/time.h> // gettimeofday
/// Allows to include the RookieHPC_mpi header without MPI substitions so that MPI calls are issued as is.
#define ROOKIEHPC_MPI_NO_SUBSTITUTION
#include "RookieHPC_mpi.h"

/// Maximum length of names used in this library.
#define ROOKIEHPC_MAX_FILENAME_LENGTH 256
/// Maximum length of arguments used in this library.
#define ROOKIEHPC_MAX_ARGUMENTS_LENGTH 256

/**
 * @brief Moves the cursor to the given coordinate in the console screen.
 * @param[in] col The column index (starting at 1).
 * @param[in] row The row index (starting at 1).
 **/
void RookieHPC_console_move_cursor_to(unsigned short int col, unsigned short int row)
{
    printf("\033[%d;%dH", row, col);
}

/**
 * @brief Clears the console screen.
 **/
void RookieHPC_console_clear_screen()
{
    printf("\033[2J");
}

//////////////////////////////
// STRUCTURES DECLARATIONS //
////////////////////////////

enum RookieHPC_monitoring_message_temporality_t { ROOKIEHPC_TEMPORALITY_BEFORE,
                                                  ROOKIEHPC_TEMPORALITY_AFTER };

/// Indicates from which MPI call the message was issued
enum RookieHPC_MPI_message_type_t { /// The message is sent about MPI_Allgather
                                    ROOKIEHPC_MESSAGE_ALLGATHER,
                                    /// The message is sent about MPI_Allgatherv
                                    ROOKIEHPC_MESSAGE_ALLGATHERV,
                                    /// The message is sent about MPI_Allreduce
                                    ROOKIEHPC_MESSAGE_ALLREDUCE,
                                    /// The message is sent about MPI_Alltoall
                                    ROOKIEHPC_MESSAGE_ALLTOALL,
                                    /// The message is sent about MPI_Alltoallv
                                    ROOKIEHPC_MESSAGE_ALLTOALLV,
                                    /// The message is sent about MPI_Barrier
                                    ROOKIEHPC_MESSAGE_BARRIER,
                                    /// The message is sent about MPI_Bsend
                                    ROOKIEHPC_MESSAGE_BCAST,
                                    /// The message is sent about MPI_Bsend
                                    ROOKIEHPC_MESSAGE_BSEND,
                                    /// The message is sent about MPI_Comm_split
                                    ROOKIEHPC_MESSAGE_COMM_SPLIT,
                                    /// The message is sent about MPI_Exscan
                                    ROOKIEHPC_MESSAGE_EXSCAN,
                                    /// The message is sent about MPI_Finalize
                                    ROOKIEHPC_MESSAGE_FINALISED,
                                    /// The message is sent about MPI_Gather
                                    ROOKIEHPC_MESSAGE_GATHER,
                                    /// The message is sent about MPI_Gatherv
                                    ROOKIEHPC_MESSAGE_GATHERV,
                                    /// The message is sent about MPI_Get_address
                                    ROOKIEHPC_MESSAGE_GET_ADDRESS,
                                    /// The message is sent about MPI_Iallgather
                                    ROOKIEHPC_MESSAGE_IALLGATHER,
                                    /// The message is sent about MPI_Iallgatherv
                                    ROOKIEHPC_MESSAGE_IALLGATHERV,
                                    /// The message is sent about MPI_Iallreduce
                                    ROOKIEHPC_MESSAGE_IALLREDUCE,
                                    /// The message is sent about MPI_Ialltoall
                                    ROOKIEHPC_MESSAGE_IALLTOALL,
                                    /// The message is sent about MPI_Ialltoallv
                                    ROOKIEHPC_MESSAGE_IALLTOALLV,
                                    /// The message is sent about MPI_Ibarrier
                                    ROOKIEHPC_MESSAGE_IBARRIER,
                                    /// The message is sent about MPI_Ibsend
                                    ROOKIEHPC_MESSAGE_IBSEND,
                                    /// The message is sent about MPI_Igather
                                    ROOKIEHPC_MESSAGE_IGATHER,
                                    /// The message is sent about MPI_Igatherv
                                    ROOKIEHPC_MESSAGE_IGATHERV,
                                    /// The message is sent about MPI_Init
                                    ROOKIEHPC_MESSAGE_INITIALISED,
                                    /// The message is sent about MPI_Ireduce
                                    ROOKIEHPC_MESSAGE_IREDUCE,
                                    /// The message is sent about MPI_Ireduce_scatter
                                    ROOKIEHPC_MESSAGE_IREDUCE_SCATTER,
                                    /// The message is sent about MPI_Ireduce_scatter_block
                                    ROOKIEHPC_MESSAGE_IREDUCE_SCATTER_BLOCK,
                                    /// The message is sent about MPI_Irsend
                                    ROOKIEHPC_MESSAGE_IRSEND,
                                    /// The message is sent about MPI_Iscatter
                                    ROOKIEHPC_MESSAGE_ISCATTER,
                                    /// The message is sent about MPI_Iscatterv
                                    ROOKIEHPC_MESSAGE_ISCATTERV,
                                    /// The message is sent about MPI_Isend
                                    ROOKIEHPC_MESSAGE_ISEND,
                                    /// The message is sent about MPI_Issend
                                    ROOKIEHPC_MESSAGE_ISSEND,
                                    /// The message is sent about MPI_Recv
                                    ROOKIEHPC_MESSAGE_RECV,
                                    /// The message is sent about MPI_Reduce
                                    ROOKIEHPC_MESSAGE_REDUCE,
                                    /// The message is sent about MPI_Reduce_scatter
                                    ROOKIEHPC_MESSAGE_REDUCE_SCATTER,
                                    /// The message is sent about MPI_Reduce_scatter_block
                                    ROOKIEHPC_MESSAGE_REDUCE_SCATTER_BLOCK,
                                    /// The message is sent about MPI_Rsend
                                    ROOKIEHPC_MESSAGE_RSEND,
                                    /// The message is sent about MPI_Scan
                                    ROOKIEHPC_MESSAGE_SCAN,
                                    /// The message is sent about MPI_Scatter
                                    ROOKIEHPC_MESSAGE_SCATTER,
                                    /// The message is sent about MPI_Send
                                    ROOKIEHPC_MESSAGE_SEND,
                                    /// The message is sent about MPI_Sendrecv
                                    ROOKIEHPC_MESSAGE_SENDRECV,
                                    /// The message is sent about MPI_Sendrecv_replace
                                    ROOKIEHPC_MESSAGE_SENDRECV_REPLACE,
                                    /// The message is sent about MPI_Ssend
                                    ROOKIEHPC_MESSAGE_SSEND,
                                    /// The process has not even called MPI_Init so far
                                    ROOKIEHPC_MESSAGE_UNINITIALISED,
                                    /// The message is sent about MPI_Wait
                                    ROOKIEHPC_MESSAGE_WAIT,
                                    /// The message is sent about MPI_Waitall
                                    ROOKIEHPC_MESSAGE_WAITALL,
                                    /// The message is sent about MPI_Waitany
                                    ROOKIEHPC_MESSAGE_WAITANY,
                                    /// The message is sent about MPI_Waitsome
                                    ROOKIEHPC_MESSAGE_WAITSOME };

/// Contains the name of the MPI function matching to a message type
const char* RookieHPC_MPI_routine_name_t[] = { "MPI_Allgather",
                                               "MPI_Allgatherv",
                                               "MPI_Allreduce",
                                               "MPI_Alltoall",
                                               "MPI_Alltoallv",
                                               "MPI_Barrier",
                                               "MPI_Bcast",
                                               "MPI_Bsend",
                                               "MPI_Comm_split",
                                               "MPI_Exscan",
                                               "MPI_Finalize",
                                               "MPI_Gather",
                                               "MPI_Gatherv",
                                               "MPI_Get_address",
                                               "MPI_Iallgather",
                                               "MPI_Iallgatherv",
                                               "MPI_Iallreduce",
                                               "MPI_Ialltoall",
                                               "MPI_Ialltoallv",
                                               "MPI_Ibarrier",
                                               "MPI_Ibsend",
                                               "MPI_Igather",
                                               "MPI_Igatherv",
                                               "MPI_Init",
                                               "MPI_Ireduce",
                                               "MPI_Ireduce_scatter",
                                               "MPI_Ireduce_scatter_block",
                                               "MPI_Irsend",
                                               "MPI_Iscatter",
                                               "MPI_Iscatterv",
                                               "MPI_Isend",
                                               "MPI_Issend",
                                               "MPI_Recv",
                                               "MPI_Reduce",
                                               "MPI_Reduce_scatter",
                                               "MPI_Reduce_scatter_block",
                                               "MPI_Rsend",
                                               "MPI_Scan",
                                               "MPI_Scatter",
                                               "MPI_Send",
                                               "MPI_Sendrecv",
                                               "MPI_Sendrecv_replace",
                                               "MPI_Ssend",
                                               "-",
                                               "MPI_Wait",
                                               "MPI_Waitall",
                                               "MPI_Waitany",
                                               "MPI_Waitsome" };

/// Contains the message representing an update to the debugger
struct RookieHPC_MPI_message_t
{
    /// The type of the message, indicating the MPI routine to which it corresponds
    enum RookieHPC_MPI_message_type_t type;
    /// Indicates if the message is built right before or right after the MPI routine is called
    bool before;
    /// Name of the file from which the MPI routine represented was issued
    char file[ROOKIEHPC_MAX_FILENAME_LENGTH];
    /// The line corresponding to the MPI routine about which the message was sent
    int line;
    /// The time at which the message was created
    double walltime;
    /// The arguments passed to the MPI routine
    char args[ROOKIEHPC_MAX_ARGUMENTS_LENGTH];
    /// Total size, in bytes, of data sent by this process
    size_t total_data_sent;
    /// Total size, in bytes, of data received by this process
    size_t total_data_received;
};

///////////////////////
// VARIABLES NEEDED //
/////////////////////

/// Rank of the MPI process handled
int RookieHPC_my_rank;
/// Number of processes in the global communicator
int RookieHPC_comm_size;
/// The thread that will run the monitoring on the master process
pthread_t RookieHPC_manager_thread;
/// MPI window in which the updates will be sent
MPI_Win RookieHPC_window;
/// The actual buffer behind the window
struct RookieHPC_MPI_message_t* RookieHPC_window_buffer_original = NULL;
/// A copy of the buffer in which information is sent; that allows to make sure that reproducible reads can be performed on it
struct RookieHPC_MPI_message_t* RookieHPC_window_buffer_copy = NULL;
/// The termination condition for the monitoring thread
volatile bool RookieHPC_manager_end = false;

///////////////////////
// FUNCTIONS NEEDED //
/////////////////////

/**
 * @brief Returns walltime in seconds.
 * @details This function is used as a substitute to MPI_Wtime when MPI_Init is not called yet.
 * @return The walltime, in seconds.
 **/
static double RookieHPC_Wtime()
{
    struct timeval wtime;
    gettimeofday(&wtime, NULL);
    double wtime_second = wtime.tv_sec;
    wtime_second += (wtime.tv_usec / 1000000.0);
    return wtime_second;
}

/**
 * @brief Sleeps for a given duration.
 * @param[in] milliseconds The duration to sleep for, in milliseconds.
 **/
static void RookieHPC_sleep(unsigned int milliseconds)
{
    usleep(milliseconds * 1000);
}

/**
 * @brief Fills the filename field in the MPI monitoring message.
 * @param[inout] message The MPI monitoring message.
 * @param[in] file The name of the file from which the MPI call is issued.
 **/
static void RookieHPC_MPI_message_set_name(struct RookieHPC_MPI_message_t* message, const char* file)
{
    strncpy(message->file, file, ROOKIEHPC_MAX_FILENAME_LENGTH);
    message->file[ROOKIEHPC_MAX_FILENAME_LENGTH-1] = '\0';
}

/**
 * @brief Fills the arguments field in the MPI monitoring message.
 * @param[inout] message The MPI monitoring message.
 * @param[in] args The arguments passed to the MPI call issued.
 **/
static void RookieHPC_MPI_message_set_args(struct RookieHPC_MPI_message_t* message, const char* args)
{
    strncpy(message->args, args, ROOKIEHPC_MAX_ARGUMENTS_LENGTH);
    message->args[ROOKIEHPC_MAX_ARGUMENTS_LENGTH-1] = '\0';
}

/**
 * @brief Propagates an update to the coordinator process
 * @param[in] message The message containing the update.
 **/
static void RookieHPC_send_update(struct RookieHPC_MPI_message_t* message, const char* file, int line, const char* args)
{
    RookieHPC_MPI_message_set_name(message, file);
    message->line = line;
    message->walltime = RookieHPC_Wtime();
    RookieHPC_MPI_message_set_args(message, args);
    MPI_Put(message, sizeof(struct RookieHPC_MPI_message_t), MPI_CHAR, 0, RookieHPC_my_rank, sizeof(struct RookieHPC_MPI_message_t), MPI_CHAR, RookieHPC_window);
}

static void RookieHPC_monitoring_message(enum RookieHPC_monitoring_message_temporality_t temporality, enum RookieHPC_MPI_message_type_t type, const char* file, int line, const char* args)
{
    struct RookieHPC_MPI_message_t message;
    message.type = type;
    message.before = (temporality == ROOKIEHPC_TEMPORALITY_BEFORE);
    RookieHPC_send_update(&message, file, line, args);
}

/////////////////////////////////////////
// ROOKIEHPC VERSIONS OF MPI ROUTINES //
///////////////////////////////////////

/**
 * @brief Prints an horizontal seperator, used in tables.
 * @param[in] routine_name_length The maximum length of the strings contained in the 'routine name' column.
 * @param[in] where_length The maximum length of the strings contained in the 'where' column.
 * @param[in] when_length The maximum length of the strings contained in the 'when' column.
 **/
static void print_horizontal_separator(int routine_name_length, int where_length, int when_length)
{
    printf("+-----+-");
    for(int i = 0; i < routine_name_length; i++)
    {
        printf("-");
    }
    printf("-+-");
    for(int i = 0; i < where_length; i++)
    {
        printf("-");
    }
    printf("-+-");
    for(int i = 0; i < when_length; i++)
    {
        printf("-");
    }
    printf("-----------+\n");
}

/**
 * @brief Updates the monitoring report.
 * @return This is a placeholder to fit the fork task prototype.
 **/
static void* RookieHPC_manager()
{
    // Every second, send updates
    static double beginning = 0.0;
    if(beginning == 0.0)
    {
        beginning = RookieHPC_Wtime();
    }
    double past = RookieHPC_Wtime();
    double now = RookieHPC_Wtime();
    const double FPS = 4;
    double refresh_time = 1.0 / FPS;
    while(!RookieHPC_manager_end)
    {
        memcpy(RookieHPC_window_buffer_copy, RookieHPC_window_buffer_original, sizeof(struct RookieHPC_MPI_message_t) * RookieHPC_comm_size);

        RookieHPC_manager_end = true;
        for(int i = 0; i < RookieHPC_comm_size; i++)
        {
            if(RookieHPC_window_buffer_copy[i].type != ROOKIEHPC_MESSAGE_FINALISED)
            {
                RookieHPC_manager_end = false;
            }
        }

        // Clear the screen
        RookieHPC_console_clear_screen();
        RookieHPC_console_move_cursor_to(1, 1);

        int current_max_routine_name_length = 0;
        int temp_max_routine_name_length;
        int current_max_where_length = 0;
        int temp_max_where_length;
        const int WHERE_LENGTH = 64;
        char where[WHERE_LENGTH];
        const int WHEN_LENGTH = 32;
        char when[WHEN_LENGTH];
        double elapsed;
        int current_max_when_length = 0;
        int temp_max_when_length;
        for(int i = 0; i < RookieHPC_comm_size; i++)
        {
            temp_max_routine_name_length = strlen(RookieHPC_MPI_routine_name_t[RookieHPC_window_buffer_copy[i].type]);
            if(temp_max_routine_name_length > current_max_routine_name_length)
            {
                current_max_routine_name_length = temp_max_routine_name_length;
            }

            snprintf(where, WHERE_LENGTH, "%s:%d", RookieHPC_window_buffer_copy[i].file, RookieHPC_window_buffer_copy[i].line);
            temp_max_where_length = strlen(where);
            if(temp_max_where_length > current_max_where_length)
            {
                current_max_where_length = temp_max_where_length;
            }

            elapsed = fabs(now - RookieHPC_window_buffer_copy[i].walltime);
            if(elapsed > 0.01)
            {
                snprintf(when, WHEN_LENGTH, "%.2f%s", elapsed, "s ago");
            }
            else
            {
                snprintf(when, WHEN_LENGTH, "%s", "just now");
            }
            temp_max_when_length = strlen(when);
            if(temp_max_when_length > current_max_when_length)
            {
                current_max_when_length = temp_max_when_length;
            }
        }

        // Print header
        printf("Runtime: %s%.2f seconds\n", (now - beginning) < 0.01 ? "<" : "", now - beginning);
        print_horizontal_separator(current_max_routine_name_length, current_max_where_length, current_max_when_length);
        printf("| %3s | %*s | %*s | %*s |\n", "Who", current_max_routine_name_length, "What", current_max_where_length, "Where", current_max_when_length + 10, "When");
        print_horizontal_separator(current_max_routine_name_length, current_max_where_length, current_max_when_length);

        // Print body
        for(int i = 0; i < RookieHPC_comm_size; i++)
        {
            elapsed = fabs(now - RookieHPC_window_buffer_copy[i].walltime);
            if(elapsed > 0.01)
            {
                snprintf(when, WHEN_LENGTH, "%.2f%s", elapsed, "s ago");
            }
            else
            {
                snprintf(when, WHEN_LENGTH, "%s", "just now");
            }
            snprintf(where, WHERE_LENGTH, "%s:%d", RookieHPC_window_buffer_copy[i].file, RookieHPC_window_buffer_copy[i].line);
            printf("| %3d | %*s | %*s | %9s %*s |\n", i,
                                            current_max_routine_name_length,
                                            RookieHPC_MPI_routine_name_t[RookieHPC_window_buffer_copy[i].type],
                                            current_max_where_length,
                                            where,
                                            (RookieHPC_window_buffer_copy[i].before) ? "started" : "completed",
                                            current_max_when_length,
                                            when);
        }

        // Print footer
        print_horizontal_separator(current_max_routine_name_length, current_max_where_length, current_max_when_length);

        // Wait for 1 sec before next round
        now = RookieHPC_Wtime();
        if((now - past) < refresh_time)
        {
            RookieHPC_sleep((refresh_time - (now - past)) * 1000);
        }
        past = now;
    }

    return NULL;
}

int RookieHPC_MPI_Allgather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_ALLGATHER, file, line, args);
    int result = MPI_Allgather(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_ALLGATHER, file, line, args);
    return result;
}

int RookieHPC_MPI_Allgatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_ALLGATHERV, file, line, args);
    int result = MPI_Allgatherv(buffer_send, count_send, datatype_send, buffer_recv, counts_recv, displacements, datatype_recv, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_ALLGATHERV, file, line, args);
    return result;
}

int RookieHPC_MPI_Allreduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_ALLREDUCE, file, line, args);
    int result = MPI_Allreduce(send_buffer, receive_buffer, count, datatype, operation, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_ALLREDUCE, file, line, args);
    return result;
}

int RookieHPC_MPI_Alltoall(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_ALLTOALL, file, line, args);
    int result = MPI_Alltoall(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_ALLTOALL, file, line, args);
    return result;
}

int RookieHPC_MPI_Alltoallv(void* buffer_send, const int* counts_send, const int* displacements_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_ALLTOALLV, file, line, args);
    int result = MPI_Alltoallv(buffer_send, counts_send, displacements_send, datatype_send, buffer_recv, counts_recv, displacements_recv, datatype_recv, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_ALLTOALLV, file, line, args);
    return result;
}

int RookieHPC_MPI_Barrier(MPI_Comm comm, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_BARRIER, file, line, args);
    int result = MPI_Barrier(comm);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_BARRIER, file, line, args);
    return result;
}

int RookieHPC_MPI_Bcast(void* buffer, int count, MPI_Datatype datatype, int emitter_rank, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_BCAST, file, line, args);
    int result = MPI_Bcast(buffer, count, datatype, emitter_rank, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_BCAST, file, line, args);
    return result;
}

int RookieHPC_MPI_Bsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_BSEND, file, line, args);
    int result = MPI_Bsend(buffer, count, type, dst, tag, comm);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_BSEND, file, line, args);
    return result;
}

int RookieHPC_MPI_Comm_split(MPI_Comm old_communicator, int colour, int key, MPI_Comm* new_communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_COMM_SPLIT, file, line, args);
    int result = MPI_Comm_split(old_communicator, colour, key, new_communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_COMM_SPLIT, file, line, args);
    return result;
}

int RookieHPC_MPI_Exscan(void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_EXSCAN, file, line, args);
    int result = MPI_Exscan(send_buffer, receive_buffer, count, datatype, operation, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_EXSCAN, file, line, args);
    return result;
}

int RookieHPC_MPI_Finalize(char* file, int line)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_FINALISED, file, line, "");
    MPI_Win_unlock(0, RookieHPC_window);
    MPI_Barrier(MPI_COMM_WORLD);
    if(RookieHPC_my_rank == 0)
    {
        pthread_join(RookieHPC_manager_thread, NULL);
    }
    MPI_Win_free(&RookieHPC_window);
    return MPI_Finalize();
}

int RookieHPC_MPI_Gather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_GATHER, file, line, args);
    int result = MPI_Gather(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, root, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_GATHER, file, line, args);
    return result;
}

int RookieHPC_MPI_Gatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_GATHERV, file, line, args);
    int result = MPI_Gatherv(buffer_send, count_send, datatype_send, buffer_recv, counts_recv, displacements, datatype_recv, root, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_GATHERV, file, line, args);
    return result;
}

int RookieHPC_MPI_Get_address(const void* location, MPI_Aint* address, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_GET_ADDRESS, file, line, args);
    int result = MPI_Get_address(location, address);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_GET_ADDRESS, file, line, args);
    return result;
}

int RookieHPC_MPI_Iallgather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IALLGATHER, file, line, args);
    int result = MPI_Iallgather(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IALLGATHER, file, line, args);
    return result;
}

int RookieHPC_MPI_Iallgatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IALLGATHERV, file, line, args);
    int result = MPI_Iallgatherv(buffer_send, count_send, datatype_send, buffer_recv, counts_recv, displacements, datatype_recv, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IALLGATHERV, file, line, args);
    return result;
}

int RookieHPC_MPI_Iallreduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IALLREDUCE, file, line, args);
    int result = MPI_Iallreduce(send_buffer, receive_buffer, count, datatype, operation, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IALLREDUCE, file, line, args);
    return result;
}

int RookieHPC_MPI_Ialltoall(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IALLTOALL, file, line, args);
    int result = MPI_Ialltoall(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IALLTOALL, file, line, args);
    return result;
}

int RookieHPC_MPI_Ialltoallv(void* buffer_send, const int* counts_send, const int* displacements_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IALLTOALLV, file, line, args);
    int result = MPI_Ialltoallv(buffer_send, counts_send, displacements_send, datatype_send, buffer_recv, counts_recv, displacements_recv, datatype_recv, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IALLTOALLV, file, line, args);
    return result;
}

int RookieHPC_MPI_Ibarrier(MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IBARRIER, file, line, args);
    int result = MPI_Ibarrier(communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IBARRIER, file, line, args);
    return result;
}

int RookieHPC_MPI_Ibsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IBSEND, file, line, args);
    int result = MPI_Ibsend(buffer, count, type, dst, tag, comm, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IBSEND, file, line, args);
    return result;
}

int RookieHPC_MPI_Igather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IGATHER, file, line, args);
    int result = MPI_Igather(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, root, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IGATHER, file, line, args);
    return result;
}

int RookieHPC_MPI_Igatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IGATHERV, file, line, args);
    int result = MPI_Igatherv(buffer_send, count_send, datatype_send, buffer_recv, counts_recv, displacements, datatype_recv, root, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IGATHERV, file, line, args);
    return result;
}

int RookieHPC_MPI_Init(int* argc, char*** argv, char* file, int line, const char* args)
{
    int result = MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &RookieHPC_my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &RookieHPC_comm_size);

    MPI_Aint size;
    if(RookieHPC_my_rank == 0)
    {
        size = sizeof(struct RookieHPC_MPI_message_t) * RookieHPC_comm_size;
        RookieHPC_window_buffer_original = (struct RookieHPC_MPI_message_t*)malloc(size);
        if(RookieHPC_window_buffer_original == NULL)
        {
            printf("Failure in allocating RookieHPC_window_buffer_original.\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
        RookieHPC_window_buffer_copy = (struct RookieHPC_MPI_message_t*)malloc(size);
        if(RookieHPC_window_buffer_copy == NULL)
        {
            printf("Failure in allocating RookieHPC_window_buffer_original copy.\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
        for(int i = 0; i < RookieHPC_comm_size; i++)
        {
            RookieHPC_window_buffer_original[i].type = ROOKIEHPC_MESSAGE_UNINITIALISED;
            RookieHPC_window_buffer_original[i].before = false;
            RookieHPC_window_buffer_original[i].walltime = RookieHPC_Wtime();
            RookieHPC_MPI_message_set_name(&RookieHPC_window_buffer_original[i], "-");
            RookieHPC_window_buffer_original[i].line = 0;
        }
    }
    else
    {
        size = 0;
    }

    MPI_Win_create(RookieHPC_window_buffer_original, size, sizeof(struct RookieHPC_MPI_message_t), MPI_INFO_NULL, MPI_COMM_WORLD, &RookieHPC_window);
    MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, RookieHPC_window);

    if(RookieHPC_my_rank == 0)
    {
        pthread_create(&RookieHPC_manager_thread, NULL, (void* (*)(void*))RookieHPC_manager, NULL);
    }

    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_INITIALISED, file, line, args);

    // All wait for the process 0 to tell us the initialisation is complete and successful
    MPI_Barrier(MPI_COMM_WORLD);

    return result;
}

int RookieHPC_MPI_Ireduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IREDUCE, file, line, args);
    int result = MPI_Ireduce(send_buffer, receive_buffer, count, datatype, operation, root, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IREDUCE, file, line, args);
    return result;
}

int RookieHPC_MPI_Ireduce_scatter(const void* send_buffer, void* receive_buffer, int* counts, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IREDUCE_SCATTER, file, line, args);
    int result = MPI_Ireduce_scatter(send_buffer, receive_buffer, counts, datatype, operation, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IREDUCE_SCATTER, file, line, args);
    return result;
}

int RookieHPC_MPI_Ireduce_scatter_block(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IREDUCE_SCATTER_BLOCK, file, line, args);
    int result = MPI_Ireduce_scatter_block(send_buffer, receive_buffer, count, datatype, operation, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IREDUCE_SCATTER_BLOCK, file, line, args);
    return result;
}

int RookieHPC_MPI_Irsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_IRSEND, file, line, args);
    int result = MPI_Irsend(buffer, count, type, dst, tag, comm, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_IRSEND, file, line, args);
    return result;
}

int RookieHPC_MPI_Iscatter(const void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_ISCATTER, file, line, args);
    int result = MPI_Iscatter(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, root, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_ISCATTER, file, line, args);
    return result;
}

int RookieHPC_MPI_Iscatterv(const void* buffer_send, const int counts_send[], const int displacements[], MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_ISCATTERV, file, line, args);
    int result = MPI_Iscatterv(buffer_send, counts_send, displacements, datatype_send, buffer_recv, count_recv, datatype_recv, root, communicator, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_ISCATTERV, file, line, args);
    return result;
}

int RookieHPC_MPI_Isend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_ISEND, file, line, args);
    int result = MPI_Isend(buffer, count, type, dst, tag, comm, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_ISEND, file, line, args);
    return result;
}

int RookieHPC_MPI_Issend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_ISSEND, file, line, args);
    int result = MPI_Issend(buffer, count, type, dst, tag, comm, request);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_ISSEND, file, line, args);
    return result;
}

int RookieHPC_MPI_Recv(void* buffer, int count, MPI_Datatype type, int source, int tag, MPI_Comm comm, MPI_Status* status, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_RECV, file, line, args);
    int result = MPI_Recv(buffer, count, type, source, tag, comm, status);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_RECV, file, line, args);
    return result;
}

int RookieHPC_MPI_Reduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, int root, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_REDUCE, file, line, args);
    int result = MPI_Reduce(send_buffer, receive_buffer, count, datatype, operation, root, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_REDUCE, file, line, args);
    return result;
}

int RookieHPC_MPI_Reduce_scatter(const void* send_buffer, void* receive_buffer, int* counts, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_REDUCE_SCATTER, file, line, args);
    int result = MPI_Reduce_scatter(send_buffer, receive_buffer, counts, datatype, operation, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_REDUCE_SCATTER, file, line, args);
    return result;
}

int RookieHPC_MPI_Reduce_scatter_block(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_REDUCE_SCATTER_BLOCK, file, line, args);
    int result = MPI_Reduce_scatter_block(send_buffer, receive_buffer, count, datatype, operation, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_REDUCE_SCATTER_BLOCK, file, line, args);
    return result;
}

int RookieHPC_MPI_Rsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_RSEND, file, line, args);
    int result = MPI_Rsend(buffer, count, type, dst, tag, comm);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_RSEND, file, line, args);
    return result;
}

int RookieHPC_MPI_Scan(void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_SCAN, file, line, args);
    int result = MPI_Scan(send_buffer, receive_buffer, count, datatype, operation, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_SCAN, file, line, args);
    return result;
}

int RookieHPC_MPI_Scatter(const void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_SCATTER, file, line, args);
    int result = MPI_Scatter(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, root, communicator);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_SCATTER, file, line, args);
    return result;
}

int RookieHPC_MPI_Send(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_SEND, file, line, args);
    int result = MPI_Send(buffer, count, type, dst, tag, comm);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_SEND, file, line, args);
    return result;
}

int RookieHPC_MPI_Sendrecv(const void* buffer_send, int count_send, MPI_Datatype datatype_send, int recipient, int tag_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int sender, int tag_recv, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_SENDRECV, file, line, args);
    int result = MPI_Sendrecv(buffer_send, count_send, datatype_send, recipient, tag_send, buffer_recv, count_recv, datatype_recv, sender, tag_recv, communicator, status);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_SENDRECV, file, line, args);
    return result;
}

int RookieHPC_MPI_Sendrecv_replace(void* buffer, int count_send, MPI_Datatype datatype_send, int recipient, int tag_send, int sender, int tag_recv, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_SENDRECV_REPLACE, file, line, args);
    int result = MPI_Sendrecv_replace(buffer, count_send, datatype_send, recipient, tag_send, sender, tag_recv, communicator, status);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_SENDRECV_REPLACE, file, line, args);
    return result;
}

int RookieHPC_MPI_Ssend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_SSEND, file, line, args);
    int result = MPI_Ssend(buffer, count, type, dst, tag, comm);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_SSEND, file, line, args);
    return result;
}

int RookieHPC_MPI_Wait(MPI_Request* request, MPI_Status* status, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_WAIT, file, line, args);
    int result = MPI_Wait(request, status);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_WAIT, file, line, args);
    return result;
}

int RookieHPC_MPI_Waitall(int count, MPI_Request requests[], MPI_Status statuses[], char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_WAITALL, file, line, args);
    int result = MPI_Waitall(count, requests, statuses);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_WAITALL, file, line, args);
    return result;
}

int RookieHPC_MPI_Waitany(int count, MPI_Request requests[], int* index, MPI_Status* status, char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_WAITANY, file, line, args);
    int result = MPI_Waitany(count, requests, index, status);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_WAITANY, file, line, args);
    return result;
}

int RookieHPC_MPI_Waitsome(int request_count, MPI_Request requests[], int* index_count, int indices[], MPI_Status statuses[], char* file, int line, const char* args)
{
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_BEFORE, ROOKIEHPC_MESSAGE_WAITSOME, file, line, args);
    int result = MPI_Waitsome(request_count, requests, index_count, indices, statuses);
    RookieHPC_monitoring_message(ROOKIEHPC_TEMPORALITY_AFTER, ROOKIEHPC_MESSAGE_WAITSOME, file, line, args);
    return result;
}