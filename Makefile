COURSE = cs320
SEMESTER = fall2022

# Update the CP_NUMBER if you adapt this makefile for future assignments
CP_NUMBER = 1

# Change the following to your own information
LASTNAME = Cataneo
GITUSERID = Vendiblebee8

# The name of the executable
EXE = predictors

# Name files according to CS240 naming conventions
REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
OBJ = obj

# Store executables in a subdirectory
all: $(EXE)

//$(EXE):$(OBJ)/predictors.o
	$(CC) $(FLAGS)$(OBJ)/predictors.o -o $@

$(OBJ)/predictors.o: predictors.cpp
	$(CC) $(FLAGS) -c predictors.cpp -o $@


tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(EXE) *.tar.gz