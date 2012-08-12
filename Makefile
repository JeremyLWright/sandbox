CFLAGS=-Wall -O3
CNOP_FLAGS=-Wall -O0
LDFLAGS=-lrt
TARGETS=switch_state switch_state_nop functions functions_nop jump_table jump_table_nop

all: $(TARGETS) 

.PHONY: all test

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o

functions: functions.c main.o
	gcc $(CFLAGS) -c functions.c -o functions.o
	gcc main.o functions.o -o functions $(LDFLAGS)

functions_nop: functions.c main.o
	gcc $(CNOP_FLAGS) -c functions.c -o functions_nop.o 
	gcc main.o functions_nop.o -o functions_nop $(LDFLAGS)

jump_table: jump_table.c main.o
	gcc $(CFLAGS) -c jump_table.c -o jump_table.o 
	gcc main.o jump_table.o -o jump_table $(LDFLAGS)

jump_table_nop: jump_table.c main.o
	gcc $(CNOP_FLAGS) -c jump_table.c -o jump_table_nop.o 
	gcc main.o jump_table_nop.o -o jump_table_nop $(LDFLAGS)

switch_state: switch_state.c main.o
	gcc $(CFLAGS) -c switch_state.c -o switch_state.o 
	gcc main.o switch_state.o -o switch_state $(LDFLAGS)

switch_state_nop: switch_state.c main.o
	gcc $(CNOP_FLAGS) -c switch_state.c -o switch_state_nop.o 
	gcc main.o switch_state_nop.o -o switch_state_nop $(LDFLAGS)

clean:
	rm -rf $(TARGETS) *.out *.png *.o

test: functions.out functions_nop.out switch_state.out switch_state_nop.out jump_table.out jump_table_nop.out

functions.out: functions
	./run_tests.sh functions functions.out

functions_nop.out: functions_nop
	./run_tests.sh functions_nop functions_nop.out

jump_table.out: jump_table
	./run_tests.sh jump_table jump_table.out

jump_table_nop.out: jump_table_nop
	./run_tests.sh jump_table_nop jump_table_nop.out

switch_state.out: switch_state
	./run_tests.sh switch_state switch_state.out

switch_state_nop.out: switch_state_nop
	./run_tests.sh switch_state_nop switch_state_nop.out

analysis: test
	octave analysis.m



