#include <stdio.h>
#include <RookieHPC_mpi.h>

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	int rank;
	int img = 0;
	int buffer;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Ssend(&buffer, 1, MPI_INT, (rank <img>0) ? 1 : 0, 0, MPI_COMM_WORLD);
	MPI_Finalize();
}
