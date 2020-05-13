all:code.c pi_serial.c pi_multi-thread.c
	gcc -pthread -o pi_serial pi_serial.c
	gcc -pthread -o pi_multi-thread pi_multi-thread.c
	gcc -pthread -o code code.c
pi_serial: pi_serial.c
	gcc -pthread -o pi_serial pi_serial.c
pi_multi-thread: pi_multi-thread.c
	gcc -pthread -o pi_multi-thread pi_multi-thread.c
code: code.c
	gcc -pthread -o code code.c 
clean:
	rm -r -f *.o code pi_multi-thread pi_serial