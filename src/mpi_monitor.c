/**
 * @file mpi_monitor.c
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool
#include <math.h> // fabs
#include <pthread.h> // pthread_t
#include <string.h> // memcpy
#include <unistd.h> // sleep, usleep
#include <sys/time.h> // gettimeofday
/// Allows to include the mpi_monitor header without MPI substitions so that MPI calls are issued as is.
#define MPI_MONITOR_NO_SUBSTITUTION
#include "mpi_monitor.h"

/// Maximum length of names used in this library.
#define MPIM_MAX_FILENAME_LENGTH 256
/// Maximum length of arguments used in this library.
#define MPIM_MAX_ARGUMENTS_LENGTH 256

/**
 * @brief Moves the cursor to the given coordinate in the console screen.
 * @param[in] col The column index (starting at 1).
 * @param[in] row The row index (starting at 1).
 **/
void MPIM_console_move_cursor_to(unsigned short int col, unsigned short int row)
{
    printf("\033[%d;%dH", row, col);
}

/**
 * @brief Clears the console screen.
 **/
void MPIM_console_clear_screen()
{
    printf("\033[2J");
}

//////////////////////////////
// STRUCTURES DECLARATIONS //
////////////////////////////

enum MPIM_message_temporality_t { MPIM_TEMPORALITY_BEFORE,
                                  MPIM_TEMPORALITY_AFTER };

/// Indicates from which MPI call the message was issued
enum MPIM_message_type_t { /// The message is sent about MPI_Abort
                           MPIM_MESSAGE_ABORT,
                           /// The message is sent about MPI_Accumulate
                           MPIM_MESSAGE_ACCUMULATE,
                           /// The message is sent about MPI_Allgather
                           MPIM_MESSAGE_ALLGATHER,
                           /// The message is sent about MPI_Allgatherv
                           MPIM_MESSAGE_ALLGATHERV,
                           /// The message is sent about MPI_Allreduce
                           MPIM_MESSAGE_ALLREDUCE,
                           /// The message is sent about MPI_Alltoall
                           MPIM_MESSAGE_ALLTOALL,
                           /// The message is sent about MPI_Alltoallv
                           MPIM_MESSAGE_ALLTOALLV,
                           /// The message is sent about MPI_Barrier
                           MPIM_MESSAGE_BARRIER,
                           /// The message is sent about MPI_Bsend
                           MPIM_MESSAGE_BCAST,
                           /// The message is sent about MPI_Bsend
                           MPIM_MESSAGE_BSEND,
                           /// The message is sent about MPI_Bsend_init
                           MPIM_MESSAGE_BSEND_INIT,
                           /// The message is sent about MPI_Cancel
                           MPIM_MESSAGE_CANCEL,
                           /// The message is sent about MPI_Cart_coords
                           MPIM_MESSAGE_CART_COORDS,
                           /// The message is sent about MPI_Cart_create
                           MPIM_MESSAGE_CART_CREATE,
                           /// The message is sent about MPI_Cart_get
                           MPIM_MESSAGE_CART_GET,
                           /// The message is sent about MPI_Cart_shift
                           MPIM_MESSAGE_CART_SHIFT,
                           /// The message is sent about MPI_Comm_create
                           MPIM_MESSAGE_COMM_CREATE,
                           /// The message is sent about MPI_Comm_get_name
                           MPIM_MESSAGE_COMM_GET_NAME,
                           /// The message is sent about MPI_Comm_get_parent
                           MPIM_MESSAGE_COMM_GET_PARENT,
                           /// The message is sent about MPI_Comm_group
                           MPIM_MESSAGE_COMM_GROUP,
                           /// The message is sent about MPI_Comm_rank
                           MPIM_MESSAGE_COMM_RANK,
                           /// The message is sent about MPI_Comm_set_name
                           MPIM_MESSAGE_COMM_SET_NAME,
                           /// The message is sent about MPI_Comm_size
                           MPIM_MESSAGE_COMM_SIZE,
                           /// The message is sent about MPI_Comm_spawn
                           MPIM_MESSAGE_COMM_SPAWN,
                           /// The message is sent about MPI_Comm_split
                           MPIM_MESSAGE_COMM_SPLIT,
                           /// The message is sent about MPI_Dims_create
                           MPIM_MESSAGE_DIMS_CREATE,
                           /// The message is sent about MPI_Exscan
                           MPIM_MESSAGE_EXSCAN,
                           /// The message is sent about MPI_Finalize
                           MPIM_MESSAGE_FINALISED,
                           /// The message is sent about MPI_Gather
                           MPIM_MESSAGE_GATHER,
                           /// The message is sent about MPI_Gatherv
                           MPIM_MESSAGE_GATHERV,
                           /// The message is sent about MPI_Get
                           MPIM_MESSAGE_GET,
                           /// The message is sent about MPI_Get_address
                           MPIM_MESSAGE_GET_ADDRESS,
                           /// The message is sent about MPI_Get_count
                           MPIM_MESSAGE_GET_COUNT,
                           /// The message is sent about MPI_Group_difference
                           MPIM_MESSAGE_GROUP_DIFFERENCE,
                           /// The message is sent about MPI_Group_incl
                           MPIM_MESSAGE_GROUP_INCL,
                           /// The message is sent about MPI_Group_intersection
                           MPIM_MESSAGE_GROUP_INTERSECTION,
                           /// The message is sent about MPI_Group_rank
                           MPIM_MESSAGE_GROUP_RANK,
                           /// The message is sent about MPI_Group_size
                           MPIM_MESSAGE_GROUP_SIZE,
                           /// The message is sent about MPI_Group_union
                           MPIM_MESSAGE_GROUP_UNION,
                           /// The message is sent about MPI_Iallgather
                           MPIM_MESSAGE_IALLGATHER,
                           /// The message is sent about MPI_Iallgatherv
                           MPIM_MESSAGE_IALLGATHERV,
                           /// The message is sent about MPI_Iallreduce
                           MPIM_MESSAGE_IALLREDUCE,
                           /// The message is sent about MPI_Ialltoall
                           MPIM_MESSAGE_IALLTOALL,
                           /// The message is sent about MPI_Ialltoallv
                           MPIM_MESSAGE_IALLTOALLV,
                           /// The message is sent about MPI_Ibarrier
                           MPIM_MESSAGE_IBARRIER,
                           /// The message is sent about MPI_Ibsend
                           MPIM_MESSAGE_IBSEND,
                           /// The message is sent about MPI_Igather
                           MPIM_MESSAGE_IGATHER,
                           /// The message is sent about MPI_Igatherv
                           MPIM_MESSAGE_IGATHERV,
                           /// The message is sent about MPI_Init
                           MPIM_MESSAGE_INITIALISED,
                           /// The message is sent about MPI_Iprobe
                           MPIM_MESSAGE_IPROBE,
                           /// The message is sent about MPI_Irecv
                           MPIM_MESSAGE_IRECV,
                           /// The message is sent about MPI_Ireduce
                           MPIM_MESSAGE_IREDUCE,
                           /// The message is sent about MPI_Ireduce_scatter
                           MPIM_MESSAGE_IREDUCE_SCATTER,
                           /// The message is sent about MPI_Ireduce_scatter_block
                           MPIM_MESSAGE_IREDUCE_SCATTER_BLOCK,
                           /// The message is sent about MPI_Irsend
                           MPIM_MESSAGE_IRSEND,
                           /// The message is sent about MPI_Iscatter
                           MPIM_MESSAGE_ISCATTER,
                           /// The message is sent about MPI_Iscatterv
                           MPIM_MESSAGE_ISCATTERV,
                           /// The message is sent about MPI_Isend
                           MPIM_MESSAGE_ISEND,
                           /// The message is sent about MPI_Issend
                           MPIM_MESSAGE_ISSEND,
                           /// The message is sent about MPI_Op_create
                           MPIM_MESSAGE_OP_CREATE,
                           /// The message is sent about MPI_Op_free
                           MPIM_MESSAGE_OP_FREE,
                           /// The message is sent about MPI_Probe
                           MPIM_MESSAGE_PROBE,
                           /// The message is sent about MPI_Put
                           MPIM_MESSAGE_PUT,
                           /// The message is sent about MPI_Recv
                           MPIM_MESSAGE_RECV,
                           /// The message is sent about MPI_Recv_init
                           MPIM_MESSAGE_RECV_INIT,
                           /// The message is sent about MPI_Reduce
                           MPIM_MESSAGE_REDUCE,
                           /// The message is sent about MPI_Reduce_scatter
                           MPIM_MESSAGE_REDUCE_SCATTER,
                           /// The message is sent about MPI_Reduce_scatter_block
                           MPIM_MESSAGE_REDUCE_SCATTER_BLOCK,
                           /// The message is sent about MPI_Rsend
                           MPIM_MESSAGE_RSEND,
                           /// The message is sent about MPI_Rsend_init
                           MPIM_MESSAGE_RSEND_INIT,
                           /// The message is sent about MPI_Scan
                           MPIM_MESSAGE_SCAN,
                           /// The message is sent about MPI_Scatter
                           MPIM_MESSAGE_SCATTER,
                           /// The message is sent about MPI_Scatterv
                           MPIM_MESSAGE_SCATTERV,
                           /// The message is sent about MPI_Send
                           MPIM_MESSAGE_SEND,
                           /// The message is sent about MPI_Send_init
                           MPIM_MESSAGE_SEND_INIT,
                           /// The message is sent about MPI_Sendrecv
                           MPIM_MESSAGE_SENDRECV,
                           /// The message is sent about MPI_Sendrecv_replace
                           MPIM_MESSAGE_SENDRECV_REPLACE,
                           /// The message is sent about MPI_Ssend
                           MPIM_MESSAGE_SSEND,
                           /// The message is sent about MPI_Ssend_init
                           MPIM_MESSAGE_SSEND_INIT,
                           /// The message is sent about MPI_Start
                           MPIM_MESSAGE_START,
                           /// The message is sent about MPI_Startall
                           MPIM_MESSAGE_STARTALL,
                           /// The message is sent about MPI_Test
                           MPIM_MESSAGE_TEST,
                           /// The message is sent about MPI_Test_cancelled
                           MPIM_MESSAGE_TEST_CANCELLED,
                           /// The message is sent about MPI_Testall
                           MPIM_MESSAGE_TESTALL,
                           /// The message is sent about MPI_Testany
                           MPIM_MESSAGE_TESTANY,
                           /// The message is sent about MPI_Testsome
                           MPIM_MESSAGE_TESTSOME,
                           /// The message is sent about MPI_Type_commit
                           MPIM_MESSAGE_TYPE_COMMIT,
                           /// The message is sent about MPI_Type_contiguous
                           MPIM_MESSAGE_TYPE_CONTIGUOUS,
                           /// The message is sent about MPI_Type_create_hindexed
                           MPIM_MESSAGE_TYPE_CREATE_HINDEXED,
                           /// The message is sent about MPI_Type_create_hindexed_block
                           MPIM_MESSAGE_TYPE_CREATE_HINDEXED_BLOCK,
                           /// The message is sent about MPI_Type_create_hvector
                           MPIM_MESSAGE_TYPE_CREATE_HVECTOR,
                           /// The message is sent about MPI_Type_create_indexed_block
                           MPIM_MESSAGE_TYPE_CREATE_INDEXED_BLOCK,
                           /// The message is sent about MPI_Type_create_struct
                           MPIM_MESSAGE_TYPE_CREATE_STRUCT,
                           /// The message is sent about MPI_Type_create_subarray
                           MPIM_MESSAGE_TYPE_CREATE_SUBARRAY,
                           /// The message is sent about MPI_Type_free
                           MPIM_MESSAGE_TYPE_FREE,
                           /// The message is sent about MPI_Type_get_extent
                           MPIM_MESSAGE_TYPE_GET_EXTENT,
                           /// The message is sent about MPI_Type_indexed
                           MPIM_MESSAGE_TYPE_INDEXED,
                           /// The message is sent about MPI_Type_vector
                           MPIM_MESSAGE_TYPE_VECTOR,
                           /// The process has not even called MPI_Init so far
                           MPIM_MESSAGE_UNINITIALISED,
                           /// The message is sent about MPI_Wait
                           MPIM_MESSAGE_WAIT,
                           /// The message is sent about MPI_Waitall
                           MPIM_MESSAGE_WAITALL,
                           /// The message is sent about MPI_Waitany
                           MPIM_MESSAGE_WAITANY,
                           /// The message is sent about MPI_Waitsome
                           MPIM_MESSAGE_WAITSOME,
                           /// The message is sent about MPI_Win_allocate
                           MPIM_MESSAGE_WIN_ALLOCATE,
                           /// The message is sent about MPI_Win_attach
                           MPIM_MESSAGE_WIN_ATTACH,
                           /// The message is sent about MPI_Win_create
                           MPIM_MESSAGE_WIN_CREATE,
                           /// The message is sent about MPI_Win_create_dynamic
                           MPIM_MESSAGE_WIN_CREATE_DYNAMIC,
                           /// The message is sent about MPI_Win_detach
                           MPIM_MESSAGE_WIN_DETACH,
                           /// The message is sent about MPI_Win_free
                           MPIM_MESSAGE_WIN_FREE,
                           /// The message is sent about MPI_Wtime
                           MPIM_MESSAGE_WTIME };

/// Contains the name of the MPI function matching to a message type
const char* MPIM_routine_name_t[] = {
                                    "MPI_Abort",
                                    "MPI_Accumulate",
                                    "MPI_Allgather",
                                    "MPI_Allgatherv",
                                    "MPI_Allreduce",
                                    "MPI_Alltoall",
                                    "MPI_Alltoallv",
                                    "MPI_Barrier",
                                    "MPI_Bcast",
                                    "MPI_Bsend",
                                    "MPI_Bsend_init",
                                    "MPI_Cancel",
                                    "MPI_Cart_coords",
                                    "MPI_Cart_create",
                                    "MPI_Cart_get",
                                    "MPI_Cart_shift",
                                    "MPI_Comm_create",
                                    "MPI_Comm_get_name",
                                    "MPI_Comm_get_parent",
                                    "MPI_Comm_group",
                                    "MPI_Comm_rank",
                                    "MPI_Comm_set_name",
                                    "MPI_Comm_size",
                                    "MPI_Comm_spawn",
                                    "MPI_Comm_split",
                                    "MPI_Dims_create",
                                    "MPI_Exscan",
                                    "MPI_Finalize",
                                    "MPI_Gather",
                                    "MPI_Gatherv",
                                    "MPI_Get",
                                    "MPI_Get_address",
                                    "MPI_Get_count",
                                    "MPI_Group_difference",
                                    "MPI_Group_incl",
                                    "MPI_Group_intersection",
                                    "MPI_Group_rank",
                                    "MPI_Group_size",
                                    "MPI_Group_union",
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
                                    "MPI_Iprobe",
                                    "MPI_Irecv",
                                    "MPI_Ireduce",
                                    "MPI_Ireduce_scatter",
                                    "MPI_Ireduce_scatter_block",
                                    "MPI_Irsend",
                                    "MPI_Iscatter",
                                    "MPI_Iscatterv",
                                    "MPI_Isend",
                                    "MPI_Issend",
                                    "MPI_Op_create",
                                    "MPI_Op_free",
                                    "MPI_Probe",
                                    "MPI_Put",
                                    "MPI_Recv",
                                    "MPI_Recv_init",
                                    "MPI_Reduce",
                                    "MPI_Reduce_scatter",
                                    "MPI_Reduce_scatter_block",
                                    "MPI_Rsend",
                                    "MPI_Rsend_init",
                                    "MPI_Scan",
                                    "MPI_Scatter",
                                    "MPI_Scatterv",
                                    "MPI_Send",
                                    "MPI_Send_init",
                                    "MPI_Sendrecv",
                                    "MPI_Sendrecv_replace",
                                    "MPI_Ssend",
                                    "MPI_Ssend_init",
                                    "MPI_Start",
                                    "MPI_Startall",
                                    "MPI_Test",
                                    "MPI_Test_cancelled",
                                    "MPI_Testall",
                                    "MPI_Testany",
                                    "MPI_Testsome",
                                    "MPI_Type_commit",
                                    "MPI_Type_contiguous",
                                    "MPI_Type_create_hindexed",
                                    "MPI_Type_create_hindexed_block",
                                    "MPI_Type_create_hvector",
                                    "MPI_Type_create_indexed_block",
                                    "MPI_Type_create_struct",
                                    "MPI_Type_create_subarray",
                                    "MPI_Type_free",
                                    "MPI_Type_get_extent",
                                    "MPI_Type_indexed",
                                    "MPI_Type_vector",
                                    "-",
                                    "MPI_Wait",
                                    "MPI_Waitall",
                                    "MPI_Waitany",
                                    "MPI_Waitsome",
                                    "MPI_Win_allocate",
                                    "MPI_Win_attach",
                                    "MPI_Win_create",
                                    "MPI_Win_create_dynamic",
                                    "MPI_Win_detach",
                                    "MPI_Win_free",
                                    "MPI_Wtime" };

/// Contains the message representing an update to the debugger
struct MPIM_message_t
{
    /// The type of the message, indicating the MPI routine to which it corresponds
    enum MPIM_message_type_t type;
    /// Indicates if the message is built right before or right after the MPI routine is called
    bool before;
    /// Name of the file from which the MPI routine represented was issued
    char file[MPIM_MAX_FILENAME_LENGTH];
    /// The line corresponding to the MPI routine about which the message was sent
    int line;
    /// The time at which the message was created
    double walltime;
    /// The arguments passed to the MPI routine
    char args[MPIM_MAX_ARGUMENTS_LENGTH];
    /// Total size, in bytes, of data sent by this process
    size_t total_data_sent;
    /// Total size, in bytes, of data received by this process
    size_t total_data_received;
};

///////////////////////
// VARIABLES NEEDED //
/////////////////////

/// Rank of the MPI process handled
int MPIM_my_rank;
/// Number of processes in the global communicator
int MPIM_my_comm_size;
/// The thread that will run the monitoring on the master process
pthread_t MPIM_manager_thread;
/// MPI window in which the updates will be sent
MPI_Win MPIM_my_window;
/// The actual buffer behind the window
struct MPIM_message_t* MPIM_my_window_buffer_original = NULL;
/// A copy of the buffer in which information is sent; that allows to make sure that reproducible reads can be performed on it
struct MPIM_message_t* MPIM_my_window_buffer_copy = NULL;
/// The termination condition for the monitoring thread
volatile bool MPIM_manager_end = false;

///////////////////////
// FUNCTIONS NEEDED //
/////////////////////

/**
 * @brief Returns walltime in seconds.
 * @details This function is used as a substitute to MPI_Wtime when MPI_Init is not called yet.
 * @return The walltime, in seconds.
 **/
static double MPIM_get_time()
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
static void MPIM_sleep(unsigned int milliseconds)
{
    usleep(milliseconds * 1000);
}

/**
 * @brief Fills the filename field in the MPI monitoring message.
 * @param[inout] message The MPI monitoring message.
 * @param[in] file The name of the file from which the MPI call is issued.
 **/
static void MPIM_message_set_name(struct MPIM_message_t* message, const char* file)
{
    strncpy(message->file, file, MPIM_MAX_FILENAME_LENGTH);
    message->file[MPIM_MAX_FILENAME_LENGTH-1] = '\0';
}

/**
 * @brief Fills the arguments field in the MPI monitoring message.
 * @param[inout] message The MPI monitoring message.
 * @param[in] args The arguments passed to the MPI call issued.
 **/
static void MPIM_message_set_args(struct MPIM_message_t* message, const char* args)
{
    strncpy(message->args, args, MPIM_MAX_ARGUMENTS_LENGTH);
    message->args[MPIM_MAX_ARGUMENTS_LENGTH-1] = '\0';
}

/**
 * @brief Propagates an update to the coordinator process
 * @param[in] message The message containing the update.
 **/
static void MPIM_send_update(struct MPIM_message_t* message, const char* file, int line, const char* args)
{
    MPIM_message_set_name(message, file);
    message->line = line;
    message->walltime = MPIM_get_time();
    MPIM_message_set_args(message, args);
    MPI_Put(message, sizeof(struct MPIM_message_t), MPI_CHAR, 0, MPIM_my_rank, sizeof(struct MPIM_message_t), MPI_CHAR, MPIM_my_window);
}

static void MPIM_message(enum MPIM_message_temporality_t temporality, enum MPIM_message_type_t type, const char* file, int line, const char* args)
{
    struct MPIM_message_t message;
    message.type = type;
    message.before = (temporality == MPIM_TEMPORALITY_BEFORE);
    MPIM_send_update(&message, file, line, args);
}

/////////////////////////////////////////
// MPIM_ VERSIONS OF MPI ROUTINES //
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
static void* MPIM_manager()
{
    // Every second, send updates
    static double beginning = 0.0;
    if(beginning == 0.0)
    {
        beginning = MPIM_get_time();
    }
    double past = MPIM_get_time();
    double now = MPIM_get_time();
    const double FPS = 4;
    double refresh_time = 1.0 / FPS;
    while(!MPIM_manager_end)
    {
        memcpy(MPIM_my_window_buffer_copy, MPIM_my_window_buffer_original, sizeof(struct MPIM_message_t) * MPIM_my_comm_size);

        MPIM_manager_end = true;
        for(int i = 0; i < MPIM_my_comm_size; i++)
        {
            if(MPIM_my_window_buffer_copy[i].type != MPIM_MESSAGE_FINALISED)
            {
                MPIM_manager_end = false;
            }
        }

        // Clear the screen
        MPIM_console_clear_screen();
        MPIM_console_move_cursor_to(1, 1);

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
        for(int i = 0; i < MPIM_my_comm_size; i++)
        {
            temp_max_routine_name_length = strlen(MPIM_routine_name_t[MPIM_my_window_buffer_copy[i].type]);
            if(temp_max_routine_name_length > current_max_routine_name_length)
            {
                current_max_routine_name_length = temp_max_routine_name_length;
            }

            snprintf(where, WHERE_LENGTH, "%s:%d", MPIM_my_window_buffer_copy[i].file, MPIM_my_window_buffer_copy[i].line);
            temp_max_where_length = strlen(where);
            if(temp_max_where_length > current_max_where_length)
            {
                current_max_where_length = temp_max_where_length;
            }

            elapsed = fabs(now - MPIM_my_window_buffer_copy[i].walltime);
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
        for(int i = 0; i < MPIM_my_comm_size; i++)
        {
            elapsed = fabs(now - MPIM_my_window_buffer_copy[i].walltime);
            if(elapsed > 0.01)
            {
                snprintf(when, WHEN_LENGTH, "%.2f%s", elapsed, "s ago");
            }
            else
            {
                snprintf(when, WHEN_LENGTH, "%s", "just now");
            }
            snprintf(where, WHERE_LENGTH, "%s:%d", MPIM_my_window_buffer_copy[i].file, MPIM_my_window_buffer_copy[i].line);
            printf("| %3d | %*s | %*s | %9s %*s |\n", i,
                                            current_max_routine_name_length,
                                            MPIM_routine_name_t[MPIM_my_window_buffer_copy[i].type],
                                            current_max_where_length,
                                            where,
                                            (MPIM_my_window_buffer_copy[i].before) ? "started" : "completed",
                                            current_max_when_length,
                                            when);
        }

        // Print footer
        print_horizontal_separator(current_max_routine_name_length, current_max_where_length, current_max_when_length);

        // Wait for 1 sec before next round
        now = MPIM_get_time();
        if((now - past) < refresh_time)
        {
            MPIM_sleep((refresh_time - (now - past)) * 1000);
        }
        past = now;
    }

    return NULL;
}

int MPIM_Abort(MPI_Comm communicator, int error_code, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_ABORT, file, line, args);
    int result = MPI_Abort(communicator, error_code);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_ABORT, file, line, args);
    return result;
}

int MPIM_Accumulate(const void* origin_address, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_displacement, int target_count, MPI_Datatype target_datatype, MPI_Op operation, MPI_Win window, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_ACCUMULATE, file, line, args);
    int result = MPI_Accumulate(origin_address, origin_count, origin_datatype, target_rank, target_displacement, target_count, target_datatype, operation, window);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_ACCUMULATE, file, line, args);
    return result;
}

int MPIM_Allgather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_ALLGATHER, file, line, args);
    int result = MPI_Allgather(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_ALLGATHER, file, line, args);
    return result;
}

int MPIM_Allgatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_ALLGATHERV, file, line, args);
    int result = MPI_Allgatherv(buffer_send, count_send, datatype_send, buffer_recv, counts_recv, displacements, datatype_recv, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_ALLGATHERV, file, line, args);
    return result;
}

int MPIM_Allreduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_ALLREDUCE, file, line, args);
    int result = MPI_Allreduce(send_buffer, receive_buffer, count, datatype, operation, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_ALLREDUCE, file, line, args);
    return result;
}

int MPIM_Alltoall(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_ALLTOALL, file, line, args);
    int result = MPI_Alltoall(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_ALLTOALL, file, line, args);
    return result;
}

int MPIM_Alltoallv(void* buffer_send, const int* counts_send, const int* displacements_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_ALLTOALLV, file, line, args);
    int result = MPI_Alltoallv(buffer_send, counts_send, displacements_send, datatype_send, buffer_recv, counts_recv, displacements_recv, datatype_recv, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_ALLTOALLV, file, line, args);
    return result;
}

int MPIM_Barrier(MPI_Comm comm, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_BARRIER, file, line, args);
    int result = MPI_Barrier(comm);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_BARRIER, file, line, args);
    return result;
}

int MPIM_Bcast(void* buffer, int count, MPI_Datatype datatype, int emitter_rank, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_BCAST, file, line, args);
    int result = MPI_Bcast(buffer, count, datatype, emitter_rank, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_BCAST, file, line, args);
    return result;
}

int MPIM_Bsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_BSEND, file, line, args);
    int result = MPI_Bsend(buffer, count, type, dst, tag, comm);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_BSEND, file, line, args);
    return result;
}

int MPIM_Bsend_init(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_BSEND_INIT, file, line, args);
    int result = MPI_Bsend_init(buffer, count, type, dst, tag, comm, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_BSEND_INIT, file, line, args);
    return result;
}

int MPIM_Cancel(MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_CANCEL, file, line, args);
    int result = MPI_Cancel(request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_CANCEL, file, line, args);
    return result; 
}

int MPIM_Cart_coords(MPI_Comm communicator, int rank, int dimension_number, int* coords, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_CART_COORDS, file, line, args);
    int result = MPI_Cart_coords(communicator, rank, dimension_number, coords);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_CART_COORDS, file, line, args);
    return result;
}

int MPIM_Cart_create(MPI_Comm old_communicator, int dimension_number, const int* dimensions, const int* periods, int reorder, MPI_Comm* new_communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_CART_CREATE, file, line, args);
    int result = MPI_Cart_create(old_communicator, dimension_number, dimensions, periods, reorder, new_communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_CART_CREATE, file, line, args);
    return result;
}

int MPIM_Cart_get(MPI_Comm communicator, int dimension_number, int* dimensions, int* periods, int* coords, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_CART_GET, file, line, args);
    int result = MPI_Cart_get(communicator, dimension_number, dimensions, periods, coords);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_CART_GET, file, line, args);
    return result;
}

int MPIM_Cart_shift(MPI_Comm communicator, int direction, int displacement, int* source, int* destination, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_CART_SHIFT, file, line, args);
    int result = MPI_Cart_shift(communicator, direction, displacement, source, destination);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_CART_SHIFT, file, line, args);
    return result;
}

int MPIM_Comm_create(MPI_Comm old_communicator, MPI_Group group, MPI_Comm* new_communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_COMM_CREATE, file, line, args);
    int result = MPI_Comm_create(old_communicator, group, new_communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_COMM_CREATE, file, line, args);
    return result;
}

int MPIM_Comm_get_name(MPI_Comm communicator, char* name, int* length, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_COMM_GET_NAME, file, line, args);
    int result = MPI_Comm_get_name(communicator, name, length);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_COMM_GET_NAME, file, line, args);
    return result;
}

int MPIM_Comm_get_parent(MPI_Comm* parent, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_COMM_GET_PARENT, file, line, args);
    int result = MPI_Comm_get_parent(parent);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_COMM_GET_PARENT, file, line, args);
    return result;
}

int MPIM_Comm_group(MPI_Comm communicator, MPI_Group* group, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_COMM_GROUP, file, line, args);
    int result = MPI_Comm_group(communicator, group);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_COMM_GROUP, file, line, args);
    return result;
}

int MPIM_Comm_rank(MPI_Comm communicator, int* rank, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_COMM_RANK, file, line, args);
    int result = MPI_Comm_rank(communicator, rank);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_COMM_RANK, file, line, args);
    return result;
}

int MPIM_Comm_set_name(MPI_Comm communicator, const char* name, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_COMM_SET_NAME, file, line, args);
    int result = MPI_Comm_set_name(communicator, name);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_COMM_SET_NAME, file, line, args);
    return result;
}

int MPIM_Comm_size(MPI_Comm communicator, int* size, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_COMM_SIZE, file, line, args);
    int result = MPI_Comm_size(communicator, size);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_COMM_SIZE, file, line, args);
    return result;
}

int MPIM_Comm_spawn(const char* command, char** arguments, int max_process_number, MPI_Info info, int root, MPI_Comm intracommunicator, MPI_Comm* intercommunicator, int* error_codes, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_COMM_SPAWN, file, line, args);
    int result = MPI_Comm_spawn(command, arguments, max_process_number, info, root, intracommunicator, intercommunicator, error_codes);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_COMM_SPAWN, file, line, args);
    return result;
}

int MPIM_Comm_split(MPI_Comm old_communicator, int colour, int key, MPI_Comm* new_communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_COMM_SPLIT, file, line, args);
    int result = MPI_Comm_split(old_communicator, colour, key, new_communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_COMM_SPLIT, file, line, args);
    return result;
}

int MPIM_Dims_create(int process_number, int dimension_number, int* dimensions, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_DIMS_CREATE, file, line, args);
    int result = MPI_Dims_create(process_number, dimension_number, dimensions);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_DIMS_CREATE, file, line, args);
    return result;
}

int MPIM_Exscan(void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_EXSCAN, file, line, args);
    int result = MPI_Exscan(send_buffer, receive_buffer, count, datatype, operation, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_EXSCAN, file, line, args);
    return result;
}

int MPIM_Finalize(char* file, int line)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_FINALISED, file, line, "");
    MPI_Win_unlock(0, MPIM_my_window);
    MPI_Barrier(MPI_COMM_WORLD);
    if(MPIM_my_rank == 0)
    {
        pthread_join(MPIM_manager_thread, NULL);
    }
    MPI_Win_free(&MPIM_my_window);
    return MPI_Finalize();
}

int MPIM_Gather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_GATHER, file, line, args);
    int result = MPI_Gather(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, root, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_GATHER, file, line, args);
    return result;
}

int MPIM_Gatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_GATHERV, file, line, args);
    int result = MPI_Gatherv(buffer_send, count_send, datatype_send, buffer_recv, counts_recv, displacements, datatype_recv, root, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_GATHERV, file, line, args);
    return result;
}

int MPIM_Get(void* origin_address, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_displacement, int target_count, MPI_Datatype target_datatype, MPI_Win window, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_GET, file, line, args);
    int result = MPI_Get(origin_address, origin_count, origin_datatype, target_rank, target_displacement, target_count, target_datatype, window);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_GET, file, line, args);
    return result;
}

int MPIM_Get_address(const void* location, MPI_Aint* address, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_GET_ADDRESS, file, line, args);
    int result = MPI_Get_address(location, address);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_GET_ADDRESS, file, line, args);
    return result;
}

int MPIM_Get_count(const MPI_Status* status, MPI_Datatype datatype, int* count, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_GET_COUNT, file, line, args);
    int result = MPI_Get_count(status, datatype, count);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_GET_COUNT, file, line, args);
    return result;
}

int MPIM_Group_difference(MPI_Group group_a, MPI_Group group_b, MPI_Group* difference_group, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_GROUP_DIFFERENCE, file, line, args);
    int result = MPI_Group_difference(group_a, group_b, difference_group);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_GROUP_DIFFERENCE, file, line, args);
    return result;
}

int MPIM_Group_incl(MPI_Group old_group, int rank_count, const int ranks[], MPI_Group* new_group, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_GROUP_INCL, file, line, args);
    int result = MPI_Group_incl(old_group, rank_count, ranks, new_group);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_GROUP_INCL, file, line, args);
    return result;
}

int MPIM_Group_intersection(MPI_Group group_a, MPI_Group group_b, MPI_Group* intersection_group, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_GROUP_INTERSECTION, file, line, args);
    int result = MPI_Group_intersection(group_a, group_b, intersection_group);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_GROUP_INTERSECTION, file, line, args);
    return result;
}

int MPIM_Group_rank(MPI_Group group, int* rank, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_GROUP_RANK, file, line, args);
    int result = MPI_Group_rank(group, rank);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_GROUP_RANK, file, line, args);
    return result;
}

int MPIM_Group_size(MPI_Group group, int* size, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_GROUP_SIZE, file, line, args);
    int result = MPI_Group_size(group, size);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_GROUP_SIZE, file, line, args);
    return result;
}

int MPIM_Group_union(MPI_Group group_a, MPI_Group group_b, MPI_Group* union_group, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_GROUP_UNION, file, line, args);
    int result = MPI_Group_union(group_a, group_b, union_group);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_GROUP_UNION, file, line, args);
    return result;
}

int MPIM_Iallgather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IALLGATHER, file, line, args);
    int result = MPI_Iallgather(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IALLGATHER, file, line, args);
    return result;
}

int MPIM_Iallgatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IALLGATHERV, file, line, args);
    int result = MPI_Iallgatherv(buffer_send, count_send, datatype_send, buffer_recv, counts_recv, displacements, datatype_recv, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IALLGATHERV, file, line, args);
    return result;
}

int MPIM_Iallreduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IALLREDUCE, file, line, args);
    int result = MPI_Iallreduce(send_buffer, receive_buffer, count, datatype, operation, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IALLREDUCE, file, line, args);
    return result;
}

int MPIM_Ialltoall(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IALLTOALL, file, line, args);
    int result = MPI_Ialltoall(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IALLTOALL, file, line, args);
    return result;
}

int MPIM_Ialltoallv(void* buffer_send, const int* counts_send, const int* displacements_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements_recv, MPI_Datatype datatype_recv, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IALLTOALLV, file, line, args);
    int result = MPI_Ialltoallv(buffer_send, counts_send, displacements_send, datatype_send, buffer_recv, counts_recv, displacements_recv, datatype_recv, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IALLTOALLV, file, line, args);
    return result;
}

int MPIM_Ibarrier(MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IBARRIER, file, line, args);
    int result = MPI_Ibarrier(communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IBARRIER, file, line, args);
    return result;
}

int MPIM_Ibsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IBSEND, file, line, args);
    int result = MPI_Ibsend(buffer, count, type, dst, tag, comm, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IBSEND, file, line, args);
    return result;
}

int MPIM_Igather(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IGATHER, file, line, args);
    int result = MPI_Igather(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, root, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IGATHER, file, line, args);
    return result;
}

int MPIM_Igatherv(void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, const int* counts_recv, const int* displacements, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IGATHERV, file, line, args);
    int result = MPI_Igatherv(buffer_send, count_send, datatype_send, buffer_recv, counts_recv, displacements, datatype_recv, root, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IGATHERV, file, line, args);
    return result;
}

int MPIM_Init(int* argc, char*** argv, char* file, int line, const char* args)
{
    int result = MPI_Init(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &MPIM_my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &MPIM_my_comm_size);

    MPI_Aint size;
    if(MPIM_my_rank == 0)
    {
        size = sizeof(struct MPIM_message_t) * MPIM_my_comm_size;
        MPIM_my_window_buffer_original = (struct MPIM_message_t*)malloc(size);
        if(MPIM_my_window_buffer_original == NULL)
        {
            printf("Failure in allocating MPIM_my_window_buffer_original.\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
        MPIM_my_window_buffer_copy = (struct MPIM_message_t*)malloc(size);
        if(MPIM_my_window_buffer_copy == NULL)
        {
            printf("Failure in allocating MPIM_my_window_buffer_original copy.\n");
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
        for(int i = 0; i < MPIM_my_comm_size; i++)
        {
            MPIM_my_window_buffer_original[i].type = MPIM_MESSAGE_UNINITIALISED;
            MPIM_my_window_buffer_original[i].before = false;
            MPIM_my_window_buffer_original[i].walltime = MPIM_get_time();
            MPIM_message_set_name(&MPIM_my_window_buffer_original[i], "-");
            MPIM_my_window_buffer_original[i].line = 0;
        }
    }
    else
    {
        size = 0;
    }

    MPI_Win_create(MPIM_my_window_buffer_original, size, sizeof(struct MPIM_message_t), MPI_INFO_NULL, MPI_COMM_WORLD, &MPIM_my_window);
    MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, MPIM_my_window);

    if(MPIM_my_rank == 0)
    {
        pthread_create(&MPIM_manager_thread, NULL, (void* (*)(void*))MPIM_manager, NULL);
    }

    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_INITIALISED, file, line, args);

    // All wait for the process 0 to tell us the initialisation is complete and successful
    MPI_Barrier(MPI_COMM_WORLD);

    return result;
}

int MPIM_Iprobe(int source, int tag, MPI_Comm communicator, int* flag, MPI_Status* status, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IPROBE, file, line, args);
    int result = MPI_Iprobe(source, tag, communicator, flag, status);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IPROBE, file, line, args);
    return result;
}

int MPIM_Irecv(void* buffer, int count, MPI_Datatype datatype, int sender, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IRECV, file, line, args);
    int result = MPI_Irecv(buffer, count, datatype, sender, tag, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IRECV, file, line, args);
    return result;
}

int MPIM_Ireduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IREDUCE, file, line, args);
    int result = MPI_Ireduce(send_buffer, receive_buffer, count, datatype, operation, root, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IREDUCE, file, line, args);
    return result;
}

int MPIM_Ireduce_scatter(const void* send_buffer, void* receive_buffer, int* counts, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IREDUCE_SCATTER, file, line, args);
    int result = MPI_Ireduce_scatter(send_buffer, receive_buffer, counts, datatype, operation, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IREDUCE_SCATTER, file, line, args);
    return result;
}

int MPIM_Ireduce_scatter_block(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IREDUCE_SCATTER_BLOCK, file, line, args);
    int result = MPI_Ireduce_scatter_block(send_buffer, receive_buffer, count, datatype, operation, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IREDUCE_SCATTER_BLOCK, file, line, args);
    return result;
}

int MPIM_Irsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_IRSEND, file, line, args);
    int result = MPI_Irsend(buffer, count, type, dst, tag, comm, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_IRSEND, file, line, args);
    return result;
}

int MPIM_Iscatter(const void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_ISCATTER, file, line, args);
    int result = MPI_Iscatter(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, root, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_ISCATTER, file, line, args);
    return result;
}

int MPIM_Iscatterv(const void* buffer_send, const int counts_send[], const int displacements[], MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_ISCATTERV, file, line, args);
    int result = MPI_Iscatterv(buffer_send, counts_send, displacements, datatype_send, buffer_recv, count_recv, datatype_recv, root, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_ISCATTERV, file, line, args);
    return result;
}

int MPIM_Isend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_ISEND, file, line, args);
    int result = MPI_Isend(buffer, count, type, dst, tag, comm, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_ISEND, file, line, args);
    return result;
}

int MPIM_Issend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_ISSEND, file, line, args);
    int result = MPI_Issend(buffer, count, type, dst, tag, comm, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_ISSEND, file, line, args);
    return result;
}

int MPIM_Op_create(MPI_User_function* user_function, int commutativity, MPI_Op* handle, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_OP_CREATE, file, line, args);
    int result = MPI_Op_create(user_function, commutativity, handle);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_OP_CREATE, file, line, args);
    return result;
}

int MPIM_Op_free(MPI_Op* handle, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_OP_FREE, file, line, args);
    int result = MPI_Op_free(handle);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_OP_FREE, file, line, args);
    return result;
}

int MPIM_Probe(int source, int tag, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_PROBE, file, line, args);
    int result = MPI_Probe(source, tag, communicator, status);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_PROBE, file, line, args);
    return result;
}

int MPIM_Put(const void* origin_address, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_displacement, int target_count, MPI_Datatype target_datatype, MPI_Win window, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_PUT, file, line, args);
    int result = MPI_Put(origin_address, origin_count, origin_datatype, target_rank, target_displacement, target_count, target_datatype, window);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_PUT, file, line, args);
    return result;
}

int MPIM_Recv(void* buffer, int count, MPI_Datatype type, int source, int tag, MPI_Comm comm, MPI_Status* status, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_RECV, file, line, args);
    int result = MPI_Recv(buffer, count, type, source, tag, comm, status);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_RECV, file, line, args);
    return result;
}

int MPIM_Recv_init(void* buffer, int count, MPI_Datatype datatype, int sender, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_RECV_INIT, file, line, args);
    int result = MPI_Recv_init(buffer, count, datatype, sender, tag, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_RECV_INIT, file, line, args);
    return result;
}

int MPIM_Reduce(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, int root, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_REDUCE, file, line, args);
    int result = MPI_Reduce(send_buffer, receive_buffer, count, datatype, operation, root, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_REDUCE, file, line, args);
    return result;
}

int MPIM_Reduce_scatter(const void* send_buffer, void* receive_buffer, int* counts, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_REDUCE_SCATTER, file, line, args);
    int result = MPI_Reduce_scatter(send_buffer, receive_buffer, counts, datatype, operation, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_REDUCE_SCATTER, file, line, args);
    return result;
}

int MPIM_Reduce_scatter_block(const void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_REDUCE_SCATTER_BLOCK, file, line, args);
    int result = MPI_Reduce_scatter_block(send_buffer, receive_buffer, count, datatype, operation, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_REDUCE_SCATTER_BLOCK, file, line, args);
    return result;
}

int MPIM_Rsend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_RSEND, file, line, args);
    int result = MPI_Rsend(buffer, count, type, dst, tag, comm);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_RSEND, file, line, args);
    return result;
}

int MPIM_Rsend_init(const void* buffer, int count, MPI_Datatype datatype, int recipient, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_RSEND_INIT, file, line, args);
    int result = MPI_Rsend_init(buffer, count, datatype, recipient, tag, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_RSEND_INIT, file, line, args);
    return result;
}

int MPIM_Scan(void* send_buffer, void* receive_buffer, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_SCAN, file, line, args);
    int result = MPI_Scan(send_buffer, receive_buffer, count, datatype, operation, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_SCAN, file, line, args);
    return result;
}

int MPIM_Scatter(const void* buffer_send, int count_send, MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_SCATTER, file, line, args);
    int result = MPI_Scatter(buffer_send, count_send, datatype_send, buffer_recv, count_recv, datatype_recv, root, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_SCATTER, file, line, args);
    return result;
}

int MPIM_Scatterv(const void* buffer_send, const int counts_send[], const int displacements[], MPI_Datatype datatype_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int root, MPI_Comm communicator, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_SCATTERV, file, line, args);
    int result = MPI_Scatterv(buffer_send, counts_send, displacements, datatype_send, buffer_recv, count_recv, datatype_recv, root, communicator);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_SCATTERV, file, line, args);
    return result;
}

int MPIM_Send(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_SEND, file, line, args);
    int result = MPI_Send(buffer, count, type, dst, tag, comm);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_SEND, file, line, args);
    return result;
}

int MPIM_Send_init(const void* buffer, int count, MPI_Datatype datatype, int recipient, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_SEND_INIT, file, line, args);
    int result = MPI_Send_init(buffer, count, datatype, recipient, tag, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_SEND_INIT, file, line, args);
    return result;
}

int MPIM_Sendrecv(const void* buffer_send, int count_send, MPI_Datatype datatype_send, int recipient, int tag_send, void* buffer_recv, int count_recv, MPI_Datatype datatype_recv, int sender, int tag_recv, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_SENDRECV, file, line, args);
    int result = MPI_Sendrecv(buffer_send, count_send, datatype_send, recipient, tag_send, buffer_recv, count_recv, datatype_recv, sender, tag_recv, communicator, status);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_SENDRECV, file, line, args);
    return result;
}

int MPIM_Sendrecv_replace(void* buffer, int count_send, MPI_Datatype datatype_send, int recipient, int tag_send, int sender, int tag_recv, MPI_Comm communicator, MPI_Status* status, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_SENDRECV_REPLACE, file, line, args);
    int result = MPI_Sendrecv_replace(buffer, count_send, datatype_send, recipient, tag_send, sender, tag_recv, communicator, status);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_SENDRECV_REPLACE, file, line, args);
    return result;
}

int MPIM_Ssend(void* buffer, int count, MPI_Datatype type, int dst, int tag, MPI_Comm comm, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_SSEND, file, line, args);
    int result = MPI_Ssend(buffer, count, type, dst, tag, comm);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_SSEND, file, line, args);
    return result;
}

int MPIM_Ssend_init(const void* buffer, int count, MPI_Datatype datatype, int recipient, int tag, MPI_Comm communicator, MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_SSEND_INIT, file, line, args);
    int result = MPI_Ssend_init(buffer, count, datatype, recipient, tag, communicator, request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_SSEND_INIT, file, line, args);
    return result;
}

int MPIM_Start(MPI_Request* request, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_START, file, line, args);
    int result = MPI_Start(request);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_START, file, line, args);
    return result;
}

int MPIM_Startall(int count, MPI_Request requests[], char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_STARTALL, file, line, args);
    int result = MPI_Startall(count, requests);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_STARTALL, file, line, args);
    return result;
}

int MPIM_Test(MPI_Request* request, int* flag, MPI_Status* status, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TEST, file, line, args);
    int result = MPI_Test(request, flag, status);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TEST, file, line, args);
    return result;
}

int MPIM_Test_cancelled(const MPI_Status* status, int* flag, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TEST_CANCELLED, file, line, args);
    int result = MPI_Test_cancelled(status, flag);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TEST_CANCELLED, file, line, args);
    return result;
}

int MPIM_Testall(int count, MPI_Request* requests, int* flag, MPI_Status* statuses, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TESTALL, file, line, args);
    int result = MPI_Testall(count, requests, flag, statuses);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TESTALL, file, line, args);
    return result;
}

int MPIM_Testany(int count, MPI_Request* requests, int* index, int* flag, MPI_Status* status, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TESTANY, file, line, args);
    int result = MPI_Testany(count, requests, index, flag, status);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TESTANY, file, line, args);
    return result;
}

int MPIM_Testsome(int count, MPI_Request* requests, int* index_count, int* indexes, MPI_Status* statuses, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TESTSOME, file, line, args);
    int result = MPI_Testsome(count, requests, index_count, indexes, statuses);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TESTSOME, file, line, args);
    return result;
}

int MPIM_Type_commit(MPI_Datatype* datatype, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_COMMIT, file, line, args);
    int result = MPI_Type_commit(datatype);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_COMMIT, file, line, args);
    return result;
}

int MPIM_Type_contiguous(int count, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_CONTIGUOUS, file, line, args);
    int result = MPI_Type_contiguous(count, old_datatype, new_datatype);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_CONTIGUOUS, file, line, args);
    return result;
}

int MPIM_Type_create_hindexed(int block_count, int* block_lengths, MPI_Aint* displacements, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_CREATE_HINDEXED, file, line, args);
    int result = MPI_Type_create_hindexed(block_count, block_lengths, displacements, old_datatype, new_datatype);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_CREATE_HINDEXED, file, line, args);
    return result;
}

int MPIM_Type_create_hindexed_block(int block_count, int block_length, MPI_Aint* displacements, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_CREATE_HINDEXED_BLOCK, file, line, args);
    int result = MPI_Type_create_hindexed_block(block_count, block_length, displacements, old_datatype, new_datatype);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_CREATE_HINDEXED_BLOCK, file, line, args);
    return result;
}

int MPIM_Type_create_hvector(int block_count, int block_length, MPI_Aint stride, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_CREATE_HVECTOR, file, line, args);
    int result = MPI_Type_create_hvector(block_count, block_length, stride, old_datatype, new_datatype);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_CREATE_HVECTOR, file, line, args);
    return result;
}

int MPIM_Type_create_indexed_block(int block_count, int block_length, int* displacements, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_CREATE_INDEXED_BLOCK, file, line, args);
    int result = MPI_Type_create_indexed_block(block_count, block_length, displacements, old_datatype, new_datatype);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_CREATE_INDEXED_BLOCK, file, line, args);
    return result;
}

int MPIM_Type_create_struct(int block_count, const int block_lengths[], const MPI_Aint displacements[], MPI_Datatype block_types[], MPI_Datatype* new_datatype, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_CREATE_STRUCT, file, line, args);
    int result = MPI_Type_create_struct(block_count, block_lengths, displacements, block_types, new_datatype);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_CREATE_STRUCT, file, line, args);
    return result;
}

int MPIM_Type_create_subarray(int dim_count, const int array_element_counts[], const int subarray_element_counts[], const int subarray_coordinates[], int order, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_CREATE_SUBARRAY, file, line, args);
    int result = MPI_Type_create_subarray(dim_count, array_element_counts, subarray_element_counts, subarray_coordinates, order, old_datatype, new_datatype);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_CREATE_SUBARRAY, file, line, args);
    return result;
}

int MPIM_Type_free(MPI_Datatype* datatype, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_FREE, file, line, args);
    int result = MPI_Type_free(datatype);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_FREE, file, line, args);
    return result;
}

int MPIM_Type_get_extent(MPI_Datatype datatype, MPI_Aint* lower_bound, MPI_Aint* extent, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_GET_EXTENT, file, line, args);
    int result = MPI_Type_get_extent(datatype, lower_bound, extent);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_GET_EXTENT, file, line, args);
    return result;
}

int MPIM_Type_indexed(int block_count, int* block_lengths, const int displacements[], MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_INDEXED, file, line, args);
    int result = MPI_Type_indexed(block_count, block_lengths, displacements, old_datatype, new_datatype);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_INDEXED, file, line, args);
    return result;
}

int MPIM_Type_vector(int block_count, int block_length, int stride, MPI_Datatype old_datatype, MPI_Datatype* new_datatype, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_TYPE_VECTOR, file, line, args);
    int result = MPI_Type_vector(block_count, block_length, stride, old_datatype, new_datatype);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_TYPE_VECTOR, file, line, args);
    return result;
}

int MPIM_Wait(MPI_Request* request, MPI_Status* status, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_WAIT, file, line, args);
    int result = MPI_Wait(request, status);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_WAIT, file, line, args);
    return result;
}

int MPIM_Waitall(int count, MPI_Request requests[], MPI_Status statuses[], char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_WAITALL, file, line, args);
    int result = MPI_Waitall(count, requests, statuses);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_WAITALL, file, line, args);
    return result;
}

int MPIM_Waitany(int count, MPI_Request requests[], int* index, MPI_Status* status, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_WAITANY, file, line, args);
    int result = MPI_Waitany(count, requests, index, status);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_WAITANY, file, line, args);
    return result;
}

int MPIM_Waitsome(int request_count, MPI_Request requests[], int* index_count, int indices[], MPI_Status statuses[], char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_WAITSOME, file, line, args);
    int result = MPI_Waitsome(request_count, requests, index_count, indices, statuses);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_WAITSOME, file, line, args);
    return result;
}

int MPIM_Win_allocate(MPI_Aint size, int displacement_unit, MPI_Info info, MPI_Comm communicator, void* base, MPI_Win* window, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_WIN_ALLOCATE, file, line, args);
    int result = MPI_Win_allocate(size, displacement_unit, info, communicator, base, window);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_WIN_ALLOCATE, file, line, args);
    return result;
}

int MPIM_Win_attach(MPI_Win window, void* base, MPI_Aint size, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_WIN_ATTACH, file, line, args);
    int result = MPI_Win_attach(window, base, size);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_WIN_ATTACH, file, line, args);
    return result;
}

int MPIM_Win_create(void* base, MPI_Aint size, int displacement_unit, MPI_Info info, MPI_Comm communicator, MPI_Win* window, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_WIN_CREATE, file, line, args);
    int result = MPI_Win_create(base, size, displacement_unit, info, communicator, window);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_WIN_CREATE, file, line, args);
    return result;
}

int MPIM_Win_create_dynamic(MPI_Info info, MPI_Comm communicator, MPI_Win* window, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_WIN_CREATE_DYNAMIC, file, line, args);
    int result = MPI_Win_create_dynamic(info, communicator, window);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_WIN_CREATE_DYNAMIC, file, line, args);
    return result;
}

int MPIM_Win_detach(MPI_Win window, const void* base, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_WIN_DETACH, file, line, args);
    int result = MPI_Win_detach(window, base);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_WIN_DETACH, file, line, args);
    return result;
}

int MPIM_Win_free(MPI_Win* window, char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_WIN_FREE, file, line, args);
    int result = MPI_Win_free(window);
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_WIN_FREE, file, line, args);
    return result;
}

double MPIM_Wtime(char* file, int line, const char* args)
{
    MPIM_message(MPIM_TEMPORALITY_BEFORE, MPIM_MESSAGE_WTIME, file, line, args);
    double result = MPI_Wtime();
    MPIM_message(MPIM_TEMPORALITY_AFTER, MPIM_MESSAGE_WTIME, file, line, args);
    return result;
}