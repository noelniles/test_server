CC=g++ -ansi -Wall -Wextra
SRC=src
BLDS=blds

all :
	make server
	make client
	make clean

server : srvr.o
	$(CC) -o server srvr.o

client : clnt.o
	$(CC) -o client clnt.o

srvr.o :
	if [ -f $(BLDS)/srvr.o ]; then \
	    cp $(BLDS)/srvr.o . ; \
	else \
	    $(CC) -c $(SRC)/srvr.cc ; \
	    mv srvr.o $(BLDS); \
	fi

clnt.o :
	$(CC) -c $(SRC)/clnt.cc

clean : 
	if [ `ls *.o|wc -l` ]; then \
	    mv *.o $(BLDS); \
	fi
