CXX=g++
LD=g++
CFLAGS=-Wall -pedantic -Wno-long-long

all: program

program: Packet.o Socket.o TCPClientSocket.o TCPServerSocket.o UDPClientSocket.o UDPServerSocket.o TestSuitcase.o Tester.o TesterPacket.o TesterTCPSocket.o TesterUDPSocket.o main.o
	$(LD) -o socklib_test Packet.o Socket.o TCPClientSocket.o TCPServerSocket.o UDPClientSocket.o UDPServerSocket.o TestSuitcase.o Tester.o TesterPacket.o TesterTCPSocket.o TesterUDPSocket.o main.o

Packet.o: ../Packet.cpp ../Socket.h
	$(CXX) $(CFLAGS) -c -o Packet.o ../Packet.cpp

Socket.o: ../Socket.cpp ../Socket.h
	$(CXX) $(CFLAGS) -c -o Socket.o ../Socket.cpp

TCPClientSocket.o: ../TCPClientSocket.cpp ../Socket.h
	$(CXX) $(CFLAGS) -c -o TCPClientSocket.o ../TCPClientSocket.cpp

TCPServerSocket.o: ../TCPServerSocket.cpp ../Socket.h
	$(CXX) $(CFLAGS) -c -o TCPServerSocket.o ../TCPServerSocket.cpp

UDPClientSocket.o: ../UDPClientSocket.cpp ../Socket.h
	$(CXX) $(CFLAGS) -c -o UDPClientSocket.o ../UDPClientSocket.cpp

UDPServerSocket.o: ../UDPServerSocket.cpp ../Socket.h
	$(CXX) $(CFLAGS) -c -o UDPServerSocket.o ../UDPServerSocket.cpp
	
TestSuitcase.o: TestSuitcase.cpp TestSuitcase.h Tester.h
	$(CXX) $(CFLAGS) -c -o TestSuitcase.o TestSuitcase.cpp

Tester.o: Tester.cpp Tester.h
	$(CXX) $(CFLAGS) -c -o Tester.o Tester.cpp

TesterPacket.o: TesterPacket.cpp TesterPacket.h Tester.h ../Socket.h
	$(CXX) $(CFLAGS) -c -o TesterPacket.o TesterPacket.cpp

TesterTCPSocket.o: TesterTCPSocket.cpp TesterTCPSocket.h Tester.h ../Socket.h
	$(CXX) $(CFLAGS) -c -o TesterTCPSocket.o TesterTCPSocket.cpp

TesterUDPSocket.o: TesterUDPSocket.cpp TesterUDPSocket.h Tester.h ../Socket.h
	$(CXX) $(CFLAGS) -c -o TesterUDPSocket.o TesterUDPSocket.cpp
	
main.o: main.cpp TestSuitcase.h Tester.h TesterPacket.h ../Socket.h TesterTCPSocket.h TesterUDPSocket.h
	$(CXX) $(CFLAGS) -c -o main.o main.cpp

clean:
	rm -f *.o
