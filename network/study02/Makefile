CC = gcc
TARGETS = udp_echocli udp_echoserv
all : $(TARGETS)
udp_echocli : udp_echocli.c netproh.h
	$(CC) -o udp_echocli udp_echocli.c
udp_echoserv: udp_echoserv.c netprog.h
	$(CC) -o udp_echoserv udp_echoserv.c
clean:
	rm -f $(TARGETS)

