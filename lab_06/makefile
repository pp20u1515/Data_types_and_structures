CC := gcc
SRC := ./src/
INC := ./inc/
OBJ := ./obj/
CFLAGS := -std=gnu99 -I../inc/ -lm -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -Wpedantic -Wvla -I../inc/

.PHONY: clean

SRCS = $(wildcard $(SRC)*.c)
OBJS = $(patsubst $(SRC)%.c, $(OBJ)%.o, $(SRCS))

app.exe: $(OBJS)
	$(CC) $^ -o $@

$(OBJ)%.o: $(SRC)%.c
	mkdir -p obj && cd obj && $(CC) $(CFLAGS) -c ../$<

clean:
	rm -fr .vscode
	rm *.exe
	rm -fr ./obj/
