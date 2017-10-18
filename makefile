.PHONY: all lib clean test

MPI_LIBS := -lmpi
CXX = icpc
LIBS += -L$(MPI_DIR)/lib $(MPI_LIBS)
INCLUDES += -I./ -I$(MPI_DIR)/include
LDFLAGS += -g

example: example.cpp mpi_wrappers.cpp
	$(CXX) $(LDFLAGS) $(INCLUDES) -c mpi_wrappers.cpp 
	$(CXX) $(LDFLAGS) $(INCLUDES) -c example.cpp 
	$(CXX) $(LDFLAGS) $(INCLUDES) $(LIBS) -o $@ example.o mpi_wrappers.o 

clean:
	rm -f *.o example *.out
