CXX=g++
LD=g++ -lpthread -losip2 -losipparser2
CFLAGS=-Wall -pedantic -Wno-long-long

all: program

program: md5.o Packet.o Socket.o TCPClientSocket.o TCPServerSocket.o UDPClientSocket.o UDPServerSocket.o SIPClient.o SIPPacket.o SIPRequest.o SIPResponse.o main.o
	$(LD) -o sip md5.o Packet.o Socket.o TCPClientSocket.o TCPServerSocket.o UDPClientSocket.o UDPServerSocket.o SIPClient.o SIPPacket.o SIPRequest.o SIPResponse.o main.o

md5.o: ../md5/md5.cpp ../md5/md5.h
	$(CXX) $(CFLAGS) -c -o md5.o ../md5/md5.cpp

Packet.o: ../Socket/Packet.cpp ../Socket/Socket.h
	$(CXX) $(CFLAGS) -c -o Packet.o ../Socket/Packet.cpp

Socket.o: ../Socket/Socket.cpp ../Socket/Socket.h
	$(CXX) $(CFLAGS) -c -o Socket.o ../Socket/Socket.cpp

TCPClientSocket.o: ../Socket/TCPClientSocket.cpp ../Socket/Socket.h
	$(CXX) $(CFLAGS) -c -o TCPClientSocket.o ../Socket/TCPClientSocket.cpp

TCPServerSocket.o: ../Socket/TCPServerSocket.cpp ../Socket/Socket.h
	$(CXX) $(CFLAGS) -c -o TCPServerSocket.o ../Socket/TCPServerSocket.cpp

UDPClientSocket.o: ../Socket/UDPClientSocket.cpp ../Socket/Socket.h
	$(CXX) $(CFLAGS) -c -o UDPClientSocket.o ../Socket/UDPClientSocket.cpp

UDPServerSocket.o: ../Socket/UDPServerSocket.cpp ../Socket/Socket.h
	$(CXX) $(CFLAGS) -c -o UDPServerSocket.o ../Socket/UDPServerSocket.cpp

SIPClient.o: SIPClient.cpp SIPClient.h SIPConstants.h SIPRequest.h \
 SIPPacket.h ../Socket/Socket.h ../md5/md5.h SIPResponse.h
	$(CXX) $(CFLAGS) -c -o SIPClient.o SIPClient.cpp

SIPPacket.o: SIPPacket.cpp SIPPacket.h ../Socket/Socket.h
	$(CXX) $(CFLAGS) -c -o SIPPacket.o SIPPacket.cpp

SIPRequest.o: SIPRequest.cpp SIPConstants.h SIPRequest.h SIPPacket.h \
 ../Socket/Socket.h ../md5/md5.h
	$(CXX) $(CFLAGS) -c -o SIPRequest.o SIPRequest.cpp

SIPResponse.o: SIPResponse.cpp SIPConstants.h SIPResponse.h SIPPacket.h \
 ../Socket/Socket.h
	$(CXX) $(CFLAGS) -c -o SIPResponse.o SIPResponse.cpp

main.o: main.cpp SIPClient.h SIPConstants.h SIPRequest.h SIPPacket.h \
 ../Socket/Socket.h ../md5/md5.h SIPResponse.h
	$(CXX) $(CFLAGS) -c -o main.o main.cpp

clean:
	rm -f *.o

