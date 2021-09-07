include ../../Makefile

test_mpi_task_data : test_mpi_task_data.o
	$(MPICXX)  $^ -o $@ $(INC)   $(LIB)

test_mpi_task_data.o : test_mpi_task_data.cpp
	$(MPICXX) -c  $< $(INC) -o $@
