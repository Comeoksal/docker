CC = gcc
TARGETS = udp_calccli udp_calcserv
all : $(TARGETS)
udp_calccli: udp_calccli.c netprog.h
	$(CC) -o udp_calccli udp_calccli.c
udp_calcserv: udp_calcserv.c netprog.h
	$(CC) -o udp_calcserv udp_calcserv.c
clean:
	rm -f $(TARGETS)
