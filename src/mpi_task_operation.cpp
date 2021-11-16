#include "mpi_task_data.h"
#include "stdlib.h"
#include "string.h"

namespace namespace_mpi_rsa {

int MPI_Task_Data :: distribute(){
    int data_length;
    int tag;
    int end_sign_num;

    if(m_dis_alg_type==Alg_FCFS){
        m_dest_id=1;
        m_loop_num=1;
        data_length=0;
        end_sign_num=0;

	log_info(TASK_LOG);
//send crypt_message
        unsigned long crypt_message[4];
	crypt_message[0]=m_task_id;
	crypt_message[1]=(unsigned long)m_handle_alg_type;
	crypt_message[2]=(unsigned long)m_dis_alg_type;
	crypt_message[3]=(unsigned long)m_block_length;
        
	//send gather	
	tag=m_loop_num*TAG_MATRIX+m_dest_id;
	MPI_Send(crypt_message,4, MPI_UNSIGNED_LONG, m_dest_id, tag, MPI_COMM_WORLD);
	m_dest_id=2;
	
	while(m_loop_num==1){
	   tag=m_loop_num*TAG_MATRIX+m_dest_id;
 	   MPI_Send(crypt_message,4, MPI_UNSIGNED_LONG, m_dest_id, tag, MPI_COMM_WORLD); 
           dest_calculate();
	}

// send key
        while(m_loop_num==2){
            memset(m_mpi_data_send, 0, SEND_LENGTH_MAX);
            memcpy(m_mpi_data_send, m_key,KEY_LENGTH_MAX);
            tag=m_loop_num*TAG_MATRIX+m_dest_id;

            MPI_Send(m_mpi_data_send, KEY_LENGTH_MAX, MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD);
//          MPI_Isend(m_mpi_data_send, SEND_LENGTH_MAX, MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD,m_mpi_request);
//          MPI_Wait(m_mpi_request,&m_mpi_status);

	    log_info(DIST_LOG,KEY_DATA);
            dest_calculate();
        }

        // send data
        while((data_length<m_text_data_length)&&(m_loop_num>=3)){
            memset(m_mpi_data_send, 0, SEND_LENGTH_MAX);
            memcpy(m_mpi_data_send, m_text_data+data_length,m_block_length);

            tag=m_loop_num*TAG_MATRIX+m_dest_id;

            MPI_Send(m_mpi_data_send, m_block_length, MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD);
//          MPI_Isend(m_mpi_data_send, SEND_LENGTH_MAX, MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD,m_mpi_request);
//          MPI_Wait(m_mpi_request,&m_mpi_status);

            data_length=data_length+m_block_length;
	    log_info(DIST_LOG,CONTENT_DATA);
            dest_calculate();
        }

        // send end_sign
        while(end_sign_num<m_processor_num-2){
            memset(m_mpi_data_send, 0, SEND_LENGTH_MAX);

            tag=m_loop_num*TAG_MATRIX+m_dest_id;
            MPI_Send(m_mpi_data_send, SEND_LENGTH_MAX, MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD);
//          MPI_Isend(m_mpi_data_send, SEND_LENGTH_MAX, MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD,m_mpi_request);
//          MPI_Wait(m_mpi_request,&m_mpi_status);
	    log_info(DIST_LOG,END_DATA);
            dest_calculate();
            end_sign_num++;
        }
    }
}

int MPI_Task_Data :: gather(){
    int tag;
    int data_length=0;
    m_dest_id=1;
    m_loop_num=1;

    //recv task_message
    unsigned long crypt_message[4];
    tag=m_loop_num*TAG_MATRIX+m_dest_id;
    MPI_Recv(crypt_message,4, MPI_UNSIGNED_LONG, m_distribute_id, tag, MPI_COMM_WORLD, &m_mpi_status);

    m_task_id=crypt_message[0];
    m_handle_alg_type=(Handle_Alg_Type)crypt_message[1];
    m_dis_alg_type=(Dis_Alg_Type)crypt_message[2];
    m_block_length=(int)crypt_message[3];
    
    log_info(CREATE_LOG);

    if(m_dis_alg_type==Alg_FCFS){
	m_dest_id=2;
	m_loop_num=3;

//recv data
        while(1){
            tag=m_loop_num*TAG_MATRIX+m_dest_id;

            MPI_Recv(m_mpi_data_recv,RECV_LENGTH_MAX , MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD, &m_mpi_status);
//          MPI_Irecv(m_mpi_data_recv,RECV_LENGTH_MAX , MPI_CHAR, m_dest_id, tag, MPI_COMM_WORLD, m_mpi_request);
//          MPI_Wait(m_mpi_request,&m_mpi_status);

            if(m_mpi_data_recv[0]==0){
	        log_info(GATH_LOG,END_DATA);
                break;
            }
            memcpy(m_text_data+data_length, m_mpi_data_recv, m_block_length);
            data_length=data_length+m_block_length;
	    log_info(GATH_LOG,CONTENT_DATA);
            dest_calculate();
        }
    }
    log_info(RESULT_LOG);
}

int MPI_Task_Data :: recv_send_task_data(){
    int tag;
    int recv_length;
    m_loop_num=1;

//recv crypt_message
    unsigned long crypt_message[4];
    tag=m_loop_num*TAG_MATRIX+m_processor_id;
    MPI_Recv(crypt_message,4, MPI_UNSIGNED_LONG, m_distribute_id, tag, MPI_COMM_WORLD, &m_mpi_status);

    m_task_id=crypt_message[0];
    m_handle_alg_type=(Handle_Alg_Type)crypt_message[1];
    m_dis_alg_type=(Dis_Alg_Type)crypt_message[2];
    m_block_length=(int)crypt_message[3];

    log_info(CREATE_LOG);

    if(m_dis_alg_type==Alg_FCFS){
//recv key
        m_loop_num++;
        tag=m_loop_num*TAG_MATRIX+m_processor_id;
        MPI_Recv(m_mpi_data_recv,KEY_LENGTH_MAX, MPI_CHAR, m_distribute_id, tag, MPI_COMM_WORLD, &m_mpi_status);
//      MPI_Irecv(m_mpi_data_recv,RECV_LENGTH_MAX , MPI_CHAR, m_distribute_id, tag, MPI_COMM_WORLD, m_mpi_request); 
//      MPI_Wait(m_mpi_request,&m_mpi_status);

        memcpy(m_key,m_mpi_data_recv,KEY_LENGTH_MAX);
	key_handle();
	log_info(HAND_LOG,KEY_DATA);
        m_loop_num++;
// recv data

        while(1){
            tag=m_loop_num*TAG_MATRIX+m_processor_id;
            MPI_Recv(m_mpi_data_recv,RECV_LENGTH_MAX , MPI_CHAR, m_distribute_id, tag, MPI_COMM_WORLD, &m_mpi_status);
//          MPI_Irecv(m_mpi_data_recv,RECV_LENGTH_MAX , MPI_CHAR, m_distribute_id, tag, MPI_COMM_WORLD, m_mpi_request);
//          MPI_Wait(m_mpi_request,&m_mpi_status);

            if(m_mpi_data_recv[0]==0){ // not right
                memset(m_mpi_data_send, 0, SEND_LENGTH_MAX);
                MPI_Send(m_mpi_data_send,m_block_length, MPI_CHAR, m_gather_id, tag, MPI_COMM_WORLD);
		log_info(HAND_LOG,END_DATA);
                break; // data_end
            }
	    else{
		data_handle();
    		MPI_Send(m_mpi_data_send,m_block_length, MPI_CHAR, m_gather_id, tag, MPI_COMM_WORLD);
//          MPI_Isend(m_mpi_data_send, SEND_LENGTH_MAX, MPI_CHAR, m_gather_id, tag, MPI_COMM_WORLD,m_mpi_request);
//          MPI_Wait(m_mpi_request,&m_mpi_status);
		log_info(HAND_LOG,CONTENT_DATA);
                m_loop_num++;	    
	    }
        }
    }
}

int MPI_Task_Data :: key_handle(){

    char char_e[CRYPT_LENGTH];
    char char_n[CRYPT_LENGTH];
    std:: string str_e, str_n;
    namespace_rsa_final :: BN_WORD bn_n;

    memcpy(char_e,m_key+E_TOP,CRYPT_LENGTH);
    memcpy(char_n,m_key+N_TOP,CRYPT_LENGTH);
    str_e=(std::string)char_e;
    str_n=(std::string)char_n;

    m_bn_e.Str_2_BN_WORD(str_e);
    bn_n.Str_2_BN_WORD(str_n);
    if(m_handle_alg_type==Handle_Alg_CRT){
	namespace_rsa_final ::RSA_N rsa_n;
	rsa_n.m_n=bn_n;
	m_crt_n=*new namespace_rsa_final ::CRT_N(rsa_n);
    }
    return 1;
}

int MPI_Task_Data :: data_handle(){
    int block_num=m_block_length/CRYPT_LENGTH;
    for(int i=0;i<block_num;i++){
        char char_a[CRYPT_LENGTH];
	char char_r[CRYPT_LENGTH];
	std:: string str_a, str_r;
	namespace_rsa_final ::BN_WORD bn_a, bn_r;
	memcpy(char_a,m_mpi_data_recv+i*CRYPT_LENGTH,CRYPT_LENGTH);
	str_a=(std::string)char_a;
	bn_a.Str_2_BN_WORD(str_a);
	if(m_handle_alg_type==Handle_Alg_CRT){
	    m_crt_n.CRT_MOD_EXP(bn_a,m_bn_e,bn_r);
	}
	bn_r.BN_WORD_2_Str(str_r);
	strcpy(char_r,str_r.c_str());
	memcpy(m_mpi_data_send+i*CRYPT_LENGTH,char_r,CRYPT_LENGTH);
    }
    return 1;

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

}
