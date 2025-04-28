CC = gcc
TARGETS = udp_chatserv udp_chatcli
OBJS = netprog2.o udp_chatserv.o udp_chatcli.o
all: $(TARGETS)
udp_chatserv: udp_chatserv.o netprog2.o
	$(CC) -o udp_chatserv udp_chatserv.o netprog2.o
udp_chatserv.o: udp_chatserv.c netprog2.h
	$(CC) -c udp_chatserv.c
udp_chatcli: udp_chatcli.o netprog2.o
	$(CC) -o udp_chatcli udp_chatcli.o netprog2.o
udp_chatcli.o: udp_chatcli.c netprog2.h
	$(CC) -c udp_chatcli.c
netprog2.o: netprog2.c netprog2.h
	$(CC) -c netprog2.c
clean:
	rm -f $(TARGETS) $(OBJS)
