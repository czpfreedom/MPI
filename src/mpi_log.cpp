#include "mpi_task_data.h"
#include "stdlib.h"
#include "string.h"
#include "mpi_log.h"

namespace namespace_mpi_rsa{

int MPI_Task_Data :: log_info(LOG_TYPE log_type){
    char log_info_data[LOG_INFO_LENGTH_MAX];
    memset(log_info_data, 0, LOG_INFO_LENGTH_MAX);
    struct timeval tv;
    gettimeofday(&tv,NULL);
    Time_Stamp time_stamp(tv);
    FILE *log_file;

    if(log_type==CREATE_LOG){
	snprintf(m_log_file_name,LOG_FILE_NAME_LENGTH, "%s%d:%lu.log",MPI_RSA_LOG , m_processor_id,m_task_id);

	log_file = fopen(m_log_file_name, "a+");
	snprintf(log_info_data, LOG_INFO_LENGTH_MAX, "  Operation:CREATE \n  ProcessorId: %d  \n  ProcessorNum: %d  \n  DistributeId: %d\n  GatherId: %d\n\n-----------------------------------------\n\n", m_processor_id, m_processor_num, m_distribute_id, m_gather_id);
	LOG_INFO( log_file, time_stamp, log_info_data );
	fclose(log_file);
        return 1;
    }

    if(log_type==QUIT_LOG){
	log_file = fopen(m_log_file_name, "a+");
	snprintf(log_info_data, LOG_INFO_LENGTH_MAX, "  Operation:QUIT\n\n-----------------------------------------\n\n");
	LOG_INFO( log_file, time_stamp, log_info_data );
	fclose(log_file);
        return 1;
    }

    if(log_type==INIT_LOG){
	log_file = fopen(m_log_file_name, "a+");
	snprintf(log_info_data, LOG_INFO_LENGTH_MAX, "  Operation:INIT \n  Key:%s\n  Data:%s\n\n-----------------------------------------\n\n", m_key, m_text_data);
	LOG_INFO( log_file, time_stamp, log_info_data );
	fclose(log_file);
        return 1;
    } 
    
    if(log_type==TASK_LOG){
	log_file = fopen(m_log_file_name, "a+");
	snprintf(log_info_data, LOG_INFO_LENGTH_MAX, "  Operation:TASK  \n  Key:%s\n  Data:%s\n\n-----------------------------------------\n\n", m_key, m_text_data);
	LOG_INFO( log_file, time_stamp, log_info_data );
	fclose(log_file);
        return 1;
    }

    if(log_type==RESULT_LOG){
	log_file = fopen(m_log_file_name, "a+");
	snprintf(log_info_data, LOG_INFO_LENGTH_MAX, "  Operation:RESULT \n  Data:%s\n\n-----------------------------------------\n\n", m_text_data);
	LOG_INFO( log_file, time_stamp, log_info_data );
	fclose(log_file);
        return 1;
    }
    return 0;
}

int MPI_Task_Data :: log_info(LOG_TYPE log_type, DATA_TYPE data_type){
    char log_info_data[LOG_INFO_LENGTH_MAX];
    memset(log_info_data, 0, LOG_INFO_LENGTH_MAX);
    struct timeval tv;
    gettimeofday(&tv,NULL);
    Time_Stamp time_stamp(tv);
    FILE *log_file;

    if(log_type==DIST_LOG){
	log_file = fopen(m_log_file_name, "a+");
	LOG_INFO_DIST (log_info_data, m_dest_id, data_type, m_mpi_data_send, m_loop_num);
	LOG_INFO( log_file, time_stamp, log_info_data );
	fclose(log_file);
	return 1;
    }

    if(log_type==GATH_LOG){
	log_file = fopen(m_log_file_name, "a+");
	LOG_INFO_GATH (log_info_data, m_dest_id, data_type, m_mpi_data_recv, m_loop_num);
	LOG_INFO( log_file, time_stamp, log_info_data );
	fclose(log_file);
	return 1;
    }

    if(log_type==HAND_LOG){
	log_file = fopen(m_log_file_name, "a+");
	LOG_INFO_HAND (log_info_data, data_type, m_mpi_data_recv, m_mpi_data_send, m_loop_num);
	LOG_INFO( log_file, time_stamp, log_info_data );
	fclose(log_file);
	return 1;
    }

//error
    return 0;

}

int LOG_INFO( FILE *file, Time_Stamp time_stamp, char *log_info ){
    fprintf(file,"TimeStamp:%s\n%s", time_stamp.m_full, log_info);
    return 0;
}

int LOG_INFO_DIST (char *log_info_data, int dest_id , DATA_TYPE data_type, char *send_data, int loop_num){
    if(data_type== KEY_DATA){
    snprintf(log_info_data,LOG_INFO_LENGTH_MAX, "  Operation: DISTRIBUTE \n  DestId:%d\n  DATA_TYPE: KEY_DATA \n  DATA: %s\n  Loop_num:%d\n --------------------------------------------------\n\n", dest_id, send_data, loop_num);    
    }
    if(data_type== CONTENT_DATA){
    snprintf(log_info_data,LOG_INFO_LENGTH_MAX, "  Operation: DISTRIBUTE \n  DestId:%d\n  DATA_TYPE: CONTENT_DATA \n  DATA: %s\n  Loop_num:%d\n --------------------------------------------------\n\n", dest_id, send_data, loop_num);
    }
    if(data_type== END_DATA){
    snprintf(log_info_data,LOG_INFO_LENGTH_MAX, "  Operation: DISTRIBUTE \n  DestId:%d\n  DATA_TYPE: END_DATA \n  DATA: %s\n  Loop_num:%d\n --------------------------------------------------\n\n", dest_id, send_data, loop_num);
    }
    return 1;
}

int LOG_INFO_GATH (char *log_info_data, int from_id, DATA_TYPE data_type, char *recv_data, int loop_num){
    if(data_type== CONTENT_DATA){
    snprintf(log_info_data,LOG_INFO_LENGTH_MAX, "  Operation: GATHER \n  FromId:%d\n  DATA_TYPE: CONTENT_DATA \n  DATA: %s\n  Loop_num:%d\n --------------------------------------------------\n\n", from_id, recv_data, loop_num);
    }
    if(data_type== END_DATA){
    snprintf(log_info_data,LOG_INFO_LENGTH_MAX, "  Operation: Gather \n  FromId:%d\n  DATA_TYPE: END_DATA \n  DATA: %s\n  Loop_num:%d\n --------------------------------------------------\n\n", from_id, recv_data, loop_num);
    }
    return 1;
}

int LOG_INFO_HAND (char *log_info_data, DATA_TYPE data_type, char *recv_data, char *send_data, int loop_num){
    if(data_type== KEY_DATA){
    snprintf(log_info_data,LOG_INFO_LENGTH_MAX, "  Operation: HANDLE \n  DATA_TYPE: KEY_DATA \n  RECV_DATA:%s \n  SEND_DATA: NULL \n  Loop_num:%d\n --------------------------------------------------\n\n", recv_data, loop_num);    
    }
    if(data_type== CONTENT_DATA){
    snprintf(log_info_data,LOG_INFO_LENGTH_MAX, "  Operation: HANDLE \n  DATA_TYPE: CONTENT_DATA \n  RECV_DATA:%s \n  SEND_DATA: %s \n  Loop_num:%d\n --------------------------------------------------\n\n", recv_data, send_data, loop_num);    
    }
    if(data_type== END_DATA){
    snprintf(log_info_data,LOG_INFO_LENGTH_MAX, "  Operation: HANDLE \n  DATA_TYPE: END_DATA \n  RECV_DATA:%s \n  SEND_DATA: %s \n  Loop_num:%d\n --------------------------------------------------\n\n", recv_data, send_data, loop_num);    
    }
    return 1;
}



}
