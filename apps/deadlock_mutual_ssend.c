#include <stdio.h>
#include "../src/mpi_monitor.h"

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank == 0)
	{
		MPI_Ssend(&rank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else if(rank == 1)
	{
		MPI_Ssend(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
