#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../src/mpi_monitor.h"
/**
 * @details Covers the following situations:
 * - Mutual ssend deadlock: 0 vs 1
 * - Collateral deadlock: 2 vs 0
 * - Processing: 3 vs 4
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    if(comm_size < 8)
    {
        printf("This application must be run with at least 8 MPI processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int buffer;
    switch(my_rank)
    {
    	case 0:
    	{
            MPI_Ssend(&buffer, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    		break;
    	}
    	case 1:
    	{
    		MPI_Ssend(&buffer, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    		break;
    	}
    	case 2:
    	{
    		MPI_Ssend(&buffer, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    		break;
    	}
    	case 3:
    	{
    		for(int i = 0; i < 4E6; i++)
    		{
    			MPI_Ssend(&buffer, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
    		}
    		break;
    	}
    	case 4:
    	{
    		for(int i = 0; i < 4E6; i++)
    		{
    			MPI_Recv(&buffer, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    		}
    		break;
    	}
    	case 5:
    	{
    		MPI_Ssend(&buffer, 1, MPI_INT, 6, 0, MPI_COMM_WORLD);
    		break;
    	}
        case 6:
        {
            sleep(5);
            MPI_Recv(&buffer, 1, MPI_INT, 5, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            break;
        }
        case 7:
        {
            sleep(3);
            break;
        }
    }

    MPI_Finalize();
 
    return 0;
}