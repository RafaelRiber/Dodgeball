CC     = g++
CFLAGS = -Wall -std=c++11
CFILES =
OFILES = $(CFILES:.cc=.o)
EXECUTABLE =

$(EXECUTABLE): $(OFILES)
	$(CC) $(OFILES) -o $(EXECUTABLE)

depend:
	@echo " *** UPDATING DEPENDENCIES ***"
	@(sed '/^# AUTOMATIC RULES:/q' Makefile && \
	  $(CC) -MM $(CFLAGS) $(CFILES) | \
	  egrep -v "/usr/include" \
	 ) >Makefile.new
	@mv Makefile.new Makefile

clean:
	@echo " *** CLEANUP IN PROGRESS ***"
	@/bin/rm -f *.o *.x *.c~ *.h~ $(EXECUTABLE)

# -------- Do not delete next line --------
# AUTOMATIC RULES:
