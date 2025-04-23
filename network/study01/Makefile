CC = gcc
TARGETS = tcp_echocli tcp_echoserv
all : $(TARGETS)
tcp_echocli: tcp_echocli.c netprog.h
	$(CC) -o tcp_echocli tcp_echocli.c
tcp_echoserv: tcp_echoserv.c netprog.h
	$(CC) -o tcp_echoserv tcp_echoserv.c
clean:
	rm -f $(TARGETS)

