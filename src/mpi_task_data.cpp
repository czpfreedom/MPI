#include "mpi_task_data.h"
#include "stdlib.h"
#include "string.h"

using namespace std;

MPI_Task_Data :: MPI_Task_Data(int argc,char* argv[]){

    MPI_Init(&argc, &argv); 
    struct timeval tv;
    gettimeofday(&tv,NULL);
    m_data_id = Time_Stamp(tv);

    m_mpi_data_send = (char*)malloc(sizeof(char)*SEND_LENGTH_MAX);
    m_mpi_data_recv = (char*)malloc(sizeof(char)*RECV_LENGTH_MAX);
    m_key = (char*)malloc(sizeof(char)*KEY_LENGTH_MAX);
    m_text_data = (char*)malloc(sizeof(char)*TEXT_LENGTH_MAX);

    MPI_Comm_rank(MPI_COMM_WORLD, &m_processor_id);
    MPI_Comm_size(MPI_COMM_WORLD, &m_processor_num);
    m_distribute_id = 0;
    m_gather_id = 1;


    log_create();

}


MPI_Task_Data :: MPI_Task_Data(MPI_Task_Data& mpi_task_data){
    m_dis_alg_type = mpi_task_data.m_dis_alg_type;
    
    m_processor_id = mpi_task_data.m_processor_id;
    m_processor_num = mpi_task_data.m_processor_num;
    m_distribute_id = mpi_task_data.m_distribute_id;
    m_gather_id = mpi_task_data.m_gather_id;

    m_dest_id = mpi_task_data.m_dest_id;

    m_mpi_status = mpi_task_data.m_mpi_status;

    m_mpi_status = mpi_task_data.m_mpi_status;
    m_key_length = mpi_task_data.m_key_length;
    m_text_data_length = mpi_task_data.m_text_data_length;
    m_mpi_data_send_length = mpi_task_data.m_mpi_data_send_length;
    m_mpi_data_recv_length = mpi_task_data.m_mpi_data_recv_length;
    memcpy(m_key,mpi_task_data.m_key,KEY_LENGTH_MAX);
    memcpy(m_text_data,mpi_task_data.m_text_data,TEXT_LENGTH_MAX);
    memcpy(m_mpi_data_send,mpi_task_data.m_mpi_data_send,SEND_LENGTH_MAX);
    memcpy(m_mpi_data_recv,mpi_task_data.m_mpi_data_recv,RECV_LENGTH_MAX);

}

MPI_Task_Data& MPI_Task_Data :: operator=(MPI_Task_Data& mpi_task_data){

    m_dis_alg_type = mpi_task_data.m_dis_alg_type;

    m_processor_id = mpi_task_data.m_processor_id;
    m_processor_num = mpi_task_data.m_processor_num;
    m_distribute_id = mpi_task_data.m_distribute_id;
    m_gather_id = mpi_task_data.m_gather_id;

    m_dest_id = mpi_task_data.m_dest_id;

    m_mpi_status = mpi_task_data.m_mpi_status;

    m_mpi_status = mpi_task_data.m_mpi_status;
    m_key_length = mpi_task_data.m_key_length;
    m_text_data_length = mpi_task_data.m_text_data_length;
    m_mpi_data_send_length = mpi_task_data.m_mpi_data_send_length;
    m_mpi_data_recv_length = mpi_task_data.m_mpi_data_recv_length;
    memcpy(m_key,mpi_task_data.m_key,KEY_LENGTH_MAX);
    memcpy(m_text_data,mpi_task_data.m_text_data,TEXT_LENGTH_MAX);
    memcpy(m_mpi_data_send,mpi_task_data.m_mpi_data_send,SEND_LENGTH_MAX);
    memcpy(m_mpi_data_recv,mpi_task_data.m_mpi_data_recv,RECV_LENGTH_MAX);

    return *this;
}

MPI_Task_Data :: ~MPI_Task_Data(){
    free(m_key);
    free(m_text_data);
    free(m_mpi_data_send);
    free(m_mpi_data_recv);
    MPI_Finalize(); 
    log_quit();
    
}

int MPI_Task_Data :: distribute(){
    int data_length;
    int tag;
    int end_sign_num;
    if(m_dis_alg_type==Alg_FCFS){
        if(m_processor_id==m_distribute_id){
	    m_dest_id=2;
	    m_loop_num=1;
	    data_length=0;
	    end_sign_num=0;
	// send key
	    while(m_loop_num!=2){
                memset(m_mpi_data_send, 0, SEND_LENGTH_MAX);
		memcpy(m_mpi_data_send, m_key, m_key_length);

		tag=m_loop_num*TAG_MATRIX+m_dest_id;

		MPI_Send(m_mpi_data_send, SEND_LENGTH_MAX, MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD);

	        dest_calculate();
	    }
	// send data
	    while(data_length<m_text_data_length){
	        memset(m_mpi_data_send, 0, SEND_LENGTH_MAX);
		memcpy(m_mpi_data_send, m_text_data+data_length, FCFS_4096);

		tag=m_loop_num*TAG_MATRIX+m_dest_id;

		MPI_Send(m_mpi_data_send, SEND_LENGTH_MAX, MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD);
 
		data_length=data_length+FCFS_4096;
		dest_calculate();
	    }

	// send end_sign
	    while(end_sign_num<m_processor_num-2){
	        memset(m_mpi_data_send, 0, SEND_LENGTH_MAX);
		
		tag=m_loop_num*TAG_MATRIX+m_dest_id;
		MPI_Send(m_mpi_data_send, SEND_LENGTH_MAX, MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD);
		dest_calculate();
	    }
	    log_info(DIST_LOG);
	}
        
        if(m_processor_id==m_gather_id){
	    ;	
	}
	
	if((m_processor_id!=m_distribute_id)&&(m_processor_id!=m_gather_id)){
	    ;
	}

    }

}

int MPI_Task_Data :: gather(){
    if(m_dis_alg_type==Alg_FCFS){
	int tag;
	int data_length;
	m_dest_id=2;
	m_loop_num=1;
       	if(m_processor_id==m_distribute_id){
		;
	}
        
	if(m_processor_id==m_gather_id){
    	    while(1){
	        tag=m_loop_num*TAG_MATRIX+m_dest_id;
		MPI_Recv(m_mpi_data_recv,RECV_LENGTH_MAX , MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD, &m_mpi_status);
		if(m_mpi_data_recv[0]==0){
		    break;
		}
		memcpy(m_text_data+data_length, m_mpi_data_recv, FCFS_4096);
		data_length=data_length+FCFS_4096;
		dest_calculate();
	    }
	    log_info(GATH_LOG);
    	}
	
	if((m_processor_id!=m_distribute_id)&&(m_processor_id!=m_gather_id)){
		;
	}
    }


}


int MPI_Task_Data :: recv_send_task_data(){
    if(m_dis_alg_type==Alg_FCFS){
	int tag;
	m_loop_num=1;
        if(m_processor_id==m_distribute_id){
	    ;	
	} 

	if(m_processor_id==m_gather_id){
	    ;
	}

	if((m_processor_id!=m_distribute_id)&&(m_processor_id!=m_gather_id)){
	// recv key
	    tag=m_loop_num*TAG_MATRIX+m_processor_id;
	    MPI_Recv(m_mpi_data_recv,RECV_LENGTH_MAX , MPI_CHAR, m_distribute_id, tag, MPI_COMM_WORLD, &m_mpi_status);    
	    memcpy(m_key,m_mpi_data_recv,m_key_length);
	    m_loop_num++;
	// recv data
	    while(1){
	        tag=m_loop_num*TAG_MATRIX+m_processor_id;
		MPI_Recv(m_mpi_data_recv,RECV_LENGTH_MAX , MPI_CHAR, m_distribute_id, tag, MPI_COMM_WORLD, &m_mpi_status);
		if(m_mpi_data_recv[0]==0){
	            memset(m_mpi_data_send, 0, SEND_LENGTH_MAX);
		    MPI_Send(m_mpi_data_send, SEND_LENGTH_MAX, MPI_CHAR, m_distribute_id, tag, MPI_COMM_WORLD);
		    break; // data_end
		}
		handle();
		MPI_Send(m_mpi_data_send, SEND_LENGTH_MAX, MPI_CHAR, m_gather_id, tag, MPI_COMM_WORLD);
		m_loop_num++;
	    }
	}
    
    }

}

int MPI_Task_Data :: handle(){
    memcpy(m_mpi_data_recv,m_mpi_data_send,SEND_LENGTH_MAX);
    log_info(HAND_LOG);
}


int MPI_Task_Data :: dest_calculate(){
    if((m_dest_id<2)||(m_dest_id>=m_processor_num)){
        m_dest_id=2;
	m_loop_num=1;
	return -1;
    }
    if((m_loop_num<1)){
	m_dest_id=2;
	m_loop_num=1;
        return -2;
    }
    m_dest_id=m_dest_id+1;
    if(m_dest_id>=m_processor_num){
        m_dest_id=2;
	m_loop_num=m_loop_num+1;
    }
    return 0;
}

int MPI_Task_Data :: log_info(LOG_TYPE log_type){
    if(log_type==INIT_LOG){
	char log_info_data[LOG_INFO_LENGTH_MAX];
    	memset(log_info_data, 0, LOG_INFO_LENGTH_MAX);

    	snprintf(log_info_data, sizeof(log_info_data), "Operation:INIT \n ProcessorId:%d  \n ProcessorNum:%d  \n DistributeId: %d  \n GatherId: %d  \n -----------------------------------------\n\n", \
	                m_processor_id, m_processor_num, m_distribute_id, m_gather_id); 
    
    	LOG_INFO( m_log_file,  m_data_id, log_info_data , strlen(log_info_data) );
    }

    if(log_type==DIST_LOG){
	char log_info_data[LOG_INFO_LENGTH_MAX];                        
	memset(log_info_data, 0, LOG_INFO_LENGTH_MAX);

	snprintf(log_info_data,sizeof(log_info_data), \
			"Operation: DISTRIBUTE\n KEY:%s\n DATA: %s\n --------------------------------------------------\n\n", \
			m_key, m_text_data);

	struct timeval tv;
	gettimeofday(&tv,NULL);
	Time_Stamp time_stamp(tv);

	LOG_INFO( m_log_file,  time_stamp, log_info_data , strlen(log_info_data) );    
    }

    if(log_type==GATH_LOG){
	char log_info_data[LOG_INFO_LENGTH_MAX];
	memset(log_info_data, 0, LOG_INFO_LENGTH_MAX);

        snprintf(log_info_data,sizeof(log_info_data), \
			"Operation: GATHER\n  DATA:%s\n --------------------------------------------------\n\n", \
			m_text_data);

        struct timeval tv;                      
        gettimeofday(&tv,NULL);                         
        Time_Stamp time_stamp(tv);
                                        
        LOG_INFO( m_log_file,  time_stamp, log_info_data , strlen(log_info_data) );
    }

    if(log_type==HAND_LOG){
	char log_info_data[LOG_INFO_LENGTH_MAX];                    
	memset(log_info_data, 0, LOG_INFO_LENGTH_MAX);

	snprintf(log_info_data,sizeof(log_info_data), \
			"Operation: HANDLE\n RECVDATA:%s\n SENDDATA:%s\n --------------------------------------------------\n\n", \
			m_mpi_data_recv, m_mpi_data_send);
    
	struct timeval tv;
	gettimeofday(&tv,NULL);
	Time_Stamp time_stamp(tv);

	LOG_INFO( m_log_file,  time_stamp, log_info_data , strlen(log_info_data) );
    }
}

int MPI_Task_Data :: log_create(){
    char file_name[100];
    snprintf(file_name,sizeof(file_name), "%s%lu.log", MPI_RSA_LOG , m_data_id.m_data);
    m_log_file = fopen(file_name, "a+");
}

int MPI_Task_Data :: log_quit(){
    fclose(m_log_file);
}

//the following functions are all for test


int MPI_Task_Data :: init_random(){
    int rand_num;

    m_dis_alg_type = Alg_FCFS;

    m_dest_id = -1;
    m_loop_num = 0;

    // key length 2048
    m_key_length = 1024;
    for(int i=0;i<m_key_length;i++){
        rand_num=rand()%16;
	if(rand_num<10){
	    m_key[i]='0'+rand_num;
	}
	else {
	    m_key[i]='A'+rand_num-10;
	}
    }

    m_text_data_length = 40960;
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
