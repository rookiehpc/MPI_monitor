SRC_DIRECTORY=src
OBJ_DIRECTORY=obj
LIB_DIRECTORY=lib
APP_DIRECTORY=apps
BIN_DIRECTORY=bin

CFLAGS=-Wall -Wextra -pthread -L$(LIB_DIRECTORY) -lRookieHPC_mpi -I$(SRC_DIRECTORY)

default: all

all: all_states all_deadlocks all_hacks

all_deadlocks: deadlock_mutual_ssend deadlock_mutual_recv deserter broadcast

all_states: make_library
	mpicc -o $(BIN_DIRECTORY)/all_states $(APP_DIRECTORY)/all_states.c $(CFLAGS);

deadlock_mutual_ssend: make_library
	mpicc -o $(BIN_DIRECTORY)/deadlock_mutual_ssend $(APP_DIRECTORY)/deadlock_mutual_ssend.c $(CFLAGS);

deadlock_mutual_recv: make_library
	mpicc -o $(BIN_DIRECTORY)/deadlock_mutual_recv $(APP_DIRECTORY)/deadlock_mutual_recv.c $(CFLAGS);

all_hacks: hack_sql_injection hack_html_injection

hack_sql_injection: make_library
	mpicc -o $(BIN_DIRECTORY)/hack_sql_injection $(APP_DIRECTORY)/hack_sql_injection.c $(CFLAGS);

hack_html_injection: make_library
	mpicc -o $(BIN_DIRECTORY)/hack_html_injection $(APP_DIRECTORY)/hack_html_injection.c $(CFLAGS);

deserter: make_library
	mpicc -o $(BIN_DIRECTORY)/deserter $(APP_DIRECTORY)/deserter.c $(CFLAGS);

broadcast: make_library
	mpicc -o $(BIN_DIRECTORY)/broadcast $(APP_DIRECTORY)/broadcast.c $(CFLAGS);

make_library: compile
	ar rcs $(LIB_DIRECTORY)/libRookieHPC_mpi.a $(OBJ_DIRECTORY)/RookieHPC_mpi.o

compile: create_directories $(SRC_DIRECTORY)/RookieHPC_mpi.c $(SRC_DIRECTORY)/RookieHPC_mpi.h
	mpicc -o $(OBJ_DIRECTORY)/RookieHPC_mpi.o -c $(SRC_DIRECTORY)/RookieHPC_mpi.c -Wall -Wextra -pthread -DROOKIEHPC_MPI_LIB

create_directories:
	@for i in $(OBJ_DIRECTORY) $(LIB_DIRECTORY) $(BIN_DIRECTORY); do if [ ! -d $${i} ]; then mkdir $${i}; fi; done

clean:
	@rm -rf $(OBJ_DIRECTORY) $(LIB_DIRECTORY) $(BIN_DIRECTORY);