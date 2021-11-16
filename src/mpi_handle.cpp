#include "mpi_task_data.h"

namespace namespace_mpi_rsa{

/*

int HANDLE_CRT_MOD_EXP(char *a, char *result, CRT_N crt_N, int data_length ){

}


int HANDLE_CRT_MOD_EXP(char *a, char *result, char *key, int key_length, int data_length ){

    std::string str_a_full;
    std::string str_a;
    std::string str_result;
    std::string str_k;
    std::string str_e;
    std::string str_n;

    namespace_rsa_final::BN_WORD bn_result;
    namespace_rsa_final::BN_WORD bn_a, bn_e, bn_n;

    str_a_full=(std::string)a;
    str_a=str_a_full.substr(0,data_length);
    str_k=(std::string)key;
    str_e=str_k.substr(0,key_length/2);
    str_n=str_k.substr(key_length/2,key_length/2);

    bn_a.Str_2_BN_WORD(str_a);
    bn_e.Str_2_BN_WORD(str_e);
    bn_n.Str_2_BN_WORD(str_n);

    namespace_rsa_final::BN_mod_exp_cuda(bn_result, bn_a, bn_e , bn_n);

    bn_result.BN_WORD_2_Str(str_result);

    memcpy(result,str_result.c_str(),data_length);
    
    return 1;
}
*/

}
