TARGET = Hello_world
CC = gcc

PREF_SRC = ./
PREF_OBJ = ./

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lpthread

$(PREF_OBJ)%.o : $(PREF_SRC)%.c
	$(CC) -c $< -o $@ 

clean : 
	rm $(TARGET) $(PREF_OBJ)*.o
