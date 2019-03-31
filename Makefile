# EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
# Projet Dodgeball
# Auteurs: Rafael RIBER - SCIPER: 296142
#          Valentin RIAT - SCIPER: 289121

CXXFILES = tools.cc player.cc ball.cc map.cc simulation.cc projet.cc
EXECUTABLE = projet

CXX     = g++
CXXFLAGS = -Wall -std=c++11
OFILES = $(CXXFILES:.cc=.o)

$(EXECUTABLE): $(OFILES)
	$(CXX) $(OFILES) -o $(EXECUTABLE)

depend:
	@echo " *** UPDATING DEPENDENCIES ***"
	@(sed '/^# AUTOMATIC RULES:/q' Makefile && \
	  $(CXX) -MM $(CXXFLAGS) $(CXXFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile
	@echo " *** DONE ! ***"

clean:
	@echo " *** CLEANUP IN PROGRESS ***"
	@/bin/rm -f *.o *.x *.c~ *.h~ $(EXECUTABLE)
	@echo " *** DONE ! ***"

# -------- Do not delete next line --------
# AUTOMATIC RULES:
tools.o: tools.cc tools.h
player.o: player.cc player.h tools.h define.h
ball.o: ball.cc ball.h tools.h
map.o: map.cc map.h tools.h define.h error.h
simulation.o: simulation.cc error.h define.h simulation.h player.h \
  tools.h ball.h map.h
projet.o: projet.cc simulation.h player.h tools.h ball.h map.h error.h \
  define.h
