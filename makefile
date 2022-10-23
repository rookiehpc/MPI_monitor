SRC_DIRECTORY=src
OBJ_DIRECTORY=obj
LIB_DIRECTORY=lib
APP_DIRECTORY=apps
BIN_DIRECTORY=bin

CFLAGS=-Wall -Wextra -pthread -L$(LIB_DIRECTORY) -lmpi_monitor -I$(SRC_DIRECTORY)

default: all

all: all_states \
	 all_deadlocks

all_deadlocks: deadlock_mutual_ssend \
			   deadlock_mutual_recv \
			   deserter

all_states: make_library
	mpicc -o $(BIN_DIRECTORY)/all_states $(APP_DIRECTORY)/all_states.c $(CFLAGS);

deadlock_mutual_ssend: make_library
	mpicc -o $(BIN_DIRECTORY)/deadlock_mutual_ssend $(APP_DIRECTORY)/deadlock_mutual_ssend.c $(CFLAGS);

deadlock_mutual_recv: make_library
	mpicc -o $(BIN_DIRECTORY)/deadlock_mutual_recv $(APP_DIRECTORY)/deadlock_mutual_recv.c $(CFLAGS);

deserter: make_library
	mpicc -o $(BIN_DIRECTORY)/deserter $(APP_DIRECTORY)/deserter.c $(CFLAGS);

make_library: compile
	ar rcs $(LIB_DIRECTORY)/libmpi_monitor.a $(OBJ_DIRECTORY)/mpi_monitor.o

compile: create_directories $(SRC_DIRECTORY)/mpi_monitor.c $(SRC_DIRECTORY)/mpi_monitor.h
	mpicc -o $(OBJ_DIRECTORY)/mpi_monitor.o -c $(SRC_DIRECTORY)/mpi_monitor.c -Wall -Wextra -pthread

create_directories:
	@for i in $(OBJ_DIRECTORY) $(LIB_DIRECTORY) $(BIN_DIRECTORY); do if [ ! -d $${i} ]; then mkdir $${i}; fi; done

clean:
	rm -rf $(OBJ_DIRECTORY) $(LIB_DIRECTORY) $(BIN_DIRECTORY);