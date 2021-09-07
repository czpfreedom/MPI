
#include "mpi_log.h"


int LOG_INFO( FILE *file, Time_Stamp time_stamp, char *log_info, int log_info_length ){
    fprintf(file,"TimeStamp:%lu\n%s", time_stamp.m_data, log_info);
    return 0;
}
