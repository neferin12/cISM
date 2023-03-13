//
// Created by julian on 13.03.23.
//

#include "headers/cismMPI.h"
#include "mpi.h"
GArray *mpiRun(int runsPerProcess, const GArray *students, const GArray *w_seminars, const GArray *p_seminars){
    int process_Rank, size_Of_Comm;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size_Of_Comm);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_Rank);

    MPI_Finalize();
    return NULL;
}
