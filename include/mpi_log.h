#ifndef MPI_LOG_H
#define MPI_LOG_H

#define MPI_RSA_LOG "/home/nx2/mpi_rsa/log/" 

#include "time_stamp.h"
#include "stdio.h"

#define LOG_INFO_LENGTH_MAX 1000000

typedef enum log_type{
    DIST_LOG=1, //distribution log
    GATH_LOG,   //gather       log
    HAND_LOG,   //handle       log
    INIT_LOG,   //init         log

}LOG_TYPE;

int LOG_INFO( FILE *file, Time_Stamp time_stamp, char *log_info, int log_info_length );

#endif
