#include "mpi_task_data.h"
#include "stdio.h"
#include "string.h"
#include "iostream"

using namespace namespace_mpi_rsa;

int main(int argc,char* argv[]){
    MPI_Init(&argc, &argv);

    
    MPI_Task_Data mpi_task_data;
    mpi_task_data.init_random();
    
    mpi_task_data.crypt();
    
    MPI_Finalize();

}
