#ifndef MPI_LOG_H
#define MPI_LOG_H

#include "mpi_config.h"
#include "mpi_rsa_time_stamp.h"
#include "stdio.h"

namespace namespace_mpi_rsa{

int LOG_INFO( FILE *file, Time_Stamp time_stamp, char *log_info);

//int LOG_INFO_INIT (char *log_info, int processor_id, int processor_num, int distribute_id, int gather_id);

int LOG_INFO_DIST (char *log_info_data, int dest_id, DATA_TYPE data_type, char *send_data, int loop_num);

int LOG_INFO_GATH (char *log_info_data, int from_id, DATA_TYPE data_type, char *recv_data, int loop_num);

int LOG_INFO_HAND (char *log_info_data, DATA_TYPE data_type, char *recv_data, char *send_data, int loop_num);

}

#endif
