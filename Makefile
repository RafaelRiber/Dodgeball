# TO BE DEFINED:
CFILES = tools.cc player.cc ball.cc map.cc simulation.cc projet.cc
EXECUTABLE = projet

# Variables
CC     = g++
CFLAGS = -Wall -std=c++11
OFILES = $(CFILES:.cc=.o)

$(EXECUTABLE): $(OFILES)
	$(CC) $(OFILES) -o $(EXECUTABLE)

depend:
	@echo " *** UPDATING DEPENDENCIES ***"
	@(sed '/^# AUTOMATIC RULES:/q' Makefile && \
	  $(CC) -MM $(CFLAGS) $(CFILES) | \
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
player.o: player.cc player.h tools.h
ball.o: ball.cc ball.h tools.h
map.o: map.cc map.h tools.h
simulation.o: simulation.cc simulation.h player.h tools.h ball.h map.h \
  error.h define.h
projet.o: projet.cc simulation.h player.h tools.h ball.h map.h error.h \
  define.h
