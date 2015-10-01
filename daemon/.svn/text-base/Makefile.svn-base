CPP=g++
OBJ=manager.o session.o rtmp.o daemon.o
LINKOBJ=manager.o session.o rtmp.o daemon.o
LIBS=-lpthread
CXXINCS=-pthread -D_DEBUG
BIN=OurDaemon
CXXFLAGS=$(CXXINCS) -Wall -Wno-long-long -pedantic
RM=rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

manager.o: SessionManager.cpp SessionManager.h Session.h Debug.h
	$(CPP) -c SessionManager.cpp -o manager.o $(CXXFLAGS)

session.o: Session.cpp Session.h Rtmp.h Debug.h
	$(CPP) -c Session.cpp -o session.o $(CXXFLAGS)

rtmp.o: Rtmp.cpp Rtmp.h Debug.h
	$(CPP) -c Rtmp.cpp -o rtmp.o $(CXXFLAGS)

daemon.o: main.cpp SessionManager.h Debug.h
	$(CPP) -c main.cpp -o daemon.o $(CXXFLAGS)

