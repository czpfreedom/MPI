include ../../Makefile

test_mpi_task_data : test_mpi_task_data.o $(MPI_RSA_LIB) /home/nx2/rsa_final_new/lib/rsa_final.a
	$(MPICXX)  $^ -o $@ $(INC)   $(LIB) $(MPI_RSA_LIB)

test_mpi_task_data.o : test_mpi_task_data.cpp
	$(MPICXX) -c  $< $(INC) -o $@
