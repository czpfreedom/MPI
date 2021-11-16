#include "mpi_task_data.h"
#include "stdlib.h"
#include "string.h"

namespace namespace_mpi_rsa {

MPI_Task_Data :: MPI_Task_Data(){

    struct timeval tv;
    gettimeofday(&tv,NULL);    
    Time_Stamp time_stamp = * new Time_Stamp(tv);
    m_task_id=time_stamp.m_data;
    m_dis_alg_type= Alg_No_Distribute;
    m_handle_alg_type= Handle_Alg_No;
    m_block_length=FCFS_2048;

    MPI_Comm_rank(MPI_COMM_WORLD, &m_processor_id);
    MPI_Comm_size(MPI_COMM_WORLD, &m_processor_num);
    m_distribute_id = 0;
    m_gather_id = 1;
    m_dest_id = -1;
    m_loop_num = 0;

    memset(m_key,0,KEY_LENGTH_MAX);
    memset(m_text_data,0,TEXT_LENGTH_MAX);
    memset(m_mpi_data_send,0,SEND_LENGTH_MAX);
    memset(m_mpi_data_recv,0,RECV_LENGTH_MAX);
    memset(m_log_file_name,0,LOG_FILE_NAME_LENGTH);
    
    if(m_processor_id==m_distribute_id){
        log_info(CREATE_LOG);
    }
}


MPI_Task_Data :: MPI_Task_Data(MPI_Task_Data& mpi_task_data){
    m_task_id = mpi_task_data.m_task_id;
    m_handle_alg_type = mpi_task_data.m_handle_alg_type;
    m_dis_alg_type = mpi_task_data.m_dis_alg_type;
    m_block_length = mpi_task_data.m_block_length;
    m_time_stamp = mpi_task_data.m_time_stamp;
    
    m_processor_id = mpi_task_data.m_processor_id;
    m_processor_num = mpi_task_data.m_processor_num;
    m_distribute_id = mpi_task_data.m_distribute_id;
    m_gather_id = mpi_task_data.m_gather_id;
    m_dest_id = mpi_task_data.m_dest_id;
    m_loop_num = mpi_task_data.m_loop_num;

    m_mpi_status = mpi_task_data.m_mpi_status;
    m_mpi_request = mpi_task_data.m_mpi_request;
    
    m_text_data_length = mpi_task_data.m_text_data_length;
    memcpy(m_key,mpi_task_data.m_key,KEY_LENGTH_MAX);
    memcpy(m_text_data,mpi_task_data.m_text_data,TEXT_LENGTH_MAX);
    memcpy(m_mpi_data_send,mpi_task_data.m_mpi_data_send,SEND_LENGTH_MAX);
    memcpy(m_mpi_data_recv,mpi_task_data.m_mpi_data_recv,RECV_LENGTH_MAX);
    memcpy(m_log_file_name,mpi_task_data.m_log_file_name,LOG_FILE_NAME_LENGTH);

    m_crt_n=mpi_task_data.m_crt_n;
    m_bn_e=mpi_task_data.m_bn_e;
}

MPI_Task_Data& MPI_Task_Data :: operator=(MPI_Task_Data& mpi_task_data){
    m_task_id = mpi_task_data.m_task_id;
    m_handle_alg_type = mpi_task_data.m_handle_alg_type;
    m_dis_alg_type = mpi_task_data.m_dis_alg_type;
    m_block_length = mpi_task_data.m_block_length;
    m_time_stamp = mpi_task_data.m_time_stamp;

    m_processor_id = mpi_task_data.m_processor_id;
    m_processor_num = mpi_task_data.m_processor_num;
    m_distribute_id = mpi_task_data.m_distribute_id;
    m_gather_id = mpi_task_data.m_gather_id;
    m_dest_id = mpi_task_data.m_dest_id;
    m_loop_num = mpi_task_data.m_loop_num;

    m_mpi_status = mpi_task_data.m_mpi_status;
    m_mpi_request = mpi_task_data.m_mpi_request;
    
    m_text_data_length = mpi_task_data.m_text_data_length;
    memcpy(m_key,mpi_task_data.m_key,KEY_LENGTH_MAX);
    memcpy(m_text_data,mpi_task_data.m_text_data,TEXT_LENGTH_MAX);
    memcpy(m_mpi_data_send,mpi_task_data.m_mpi_data_send,SEND_LENGTH_MAX);
    memcpy(m_mpi_data_recv,mpi_task_data.m_mpi_data_recv,RECV_LENGTH_MAX);
    memcpy(m_log_file_name,mpi_task_data.m_log_file_name,LOG_FILE_NAME_LENGTH);

    m_crt_n=mpi_task_data.m_crt_n;
    m_bn_e=mpi_task_data.m_bn_e;
    return *this;
}

MPI_Task_Data :: ~MPI_Task_Data(){
    log_info(QUIT_LOG);
}

//the following functions are all for test

int MPI_Task_Data :: init_random(Handle_Alg_Type handle_alg_type, Dis_Alg_Type dis_alg_type, int block_length){
    
    int rand_num;

    if(m_processor_id==m_distribute_id){
	m_dis_alg_type=dis_alg_type;
	m_handle_alg_type=handle_alg_type;
    	m_block_length=block_length;

// E_random    	
	for(int i=E_TOP;i<E_TOP+CRYPT_LENGTH;i++){
	    rand_num=rand()%16;
    	    if(rand_num<10){
	        m_key[i]='0'+rand_num;
    	    }
    	    else {
		m_key[i]='A'+rand_num-10;
    	    }
    	}
// make sure e is not odd
	m_key[E_TOP+CRYPT_LENGTH-1]='F';

	for(int i=N_TOP;i<N_TOP+CRYPT_LENGTH;i++){
	    rand_num=rand()%16;
            if(rand_num<10){
                m_key[i]='0'+rand_num;
            }
            else {
                m_key[i]='A'+rand_num-10;
            } 	
	}
// make sure n is not odd
        m_key[N_TOP+CRYPT_LENGTH-1]='F';

    	m_text_data_length = 20480;
    	for(int i=0;i<m_text_data_length;i++){
	    rand_num=rand()%16;
    	    if(rand_num<10){
		m_text_data[i]='0'+rand_num;
    	    }
    	    else {
		m_text_data[i]='A'+rand_num-10;
    	    }
    	}
	log_info(INIT_LOG);
    }

}

int MPI_Task_Data :: crypt(){
    if(m_processor_id==m_distribute_id){
	distribute();
    }

    if(m_processor_id==m_gather_id){
	gather();
    }

    if((m_processor_id!=m_distribute_id)&&(m_processor_id!=m_gather_id)){
	recv_send_task_data();
    }
}

}
