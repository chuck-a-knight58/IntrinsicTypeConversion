#include <mpi.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include "mpi_wrappers.h"

int MASTER = 0;
int TAG = 1;

int main(int argc, char **argv)
{
	int rank;
	int numtasks;
	int rc;
	char hostname[256];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	gethostname(hostname, 255);

	// Make a buffer with our rank in it
	std::vector<int> buffer(1);
	buffer[0] = rank;

	if (rank == 0)
	{
		printf(
			"Hello world!  I am process number: %02d on host %s\n",
			buffer[0], hostname);

		for (int i = 1; i < numtasks; i++)
		{
			Receive<int>(buffer, i, TAG);
			printf(
				"\tProc %02d reports: %02d\n",
				i, buffer[0]);
		}
	}
	else {

		Send<int>(buffer, MASTER, TAG);
		printf(
			"Hello world!  I am process number: %02d on host %s\n",
			buffer[0], hostname);
	}

	MPI_Finalize();

	return 0;
}
