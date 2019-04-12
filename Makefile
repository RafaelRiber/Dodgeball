# EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
# Projet Dodgeball
# Auteurs: Rafael RIBER - SCIPER: 296142
#          Valentin RIAT - SCIPER: 289121

CXXFILES = tools.cc player.cc ball.cc map.cc simulation.cc projet.cc gui.cc
OUT = projet

CXX     = g++
CXXFLAGS = -Wall -std=c++11
LINKING = `pkg-config --cflags gtkmm-3.0`
LDLIBS = `pkg-config --libs gtkmm-3.0`
OFILES = $(CXXFILES:.cc=.o)

all: $(OUT)

tools.o: tools.cc tools.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

player.o: player.cc player.h tools.h define.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

ball.o: ball.cc ball.h tools.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

map.o: map.cc map.h tools.h define.h error.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

gui.o: gui.cc gui.h simulation.h tools.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

simulation.o: simulation.cc error.h define.h simulation.h player.h \
  tools.h ball.h map.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

projet.o: projet.cc simulation.h player.h tools.h ball.h map.h error.h \
  define.h
	$(CXX) $(CXXFLAGS) $(LINKING) -c $< -o $@ $(LINKING)

$(OUT): $(OFILES)
	$(CXX) $(CXXFLAGS) $(LINKING) $(OFILES) -o $@ $(LDLIBS)

clean:
	@echo " *** CLEANUP IN PROGRESS ***"
	@/bin/rm -f *.o *.x *.c~ *.h~ $(OUT)
	@echo " *** DONE ! ***"
