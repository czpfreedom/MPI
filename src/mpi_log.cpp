
#include "mpi_log.h"

namespace namespace_mpi_rsa{

int LOG_INFO( FILE *file, Time_Stamp time_stamp, char *log_info, int log_info_length ){
    fprintf(file,"TimeStamp:%s\n%s", time_stamp.m_full, log_info);
    return 0;
}

}
