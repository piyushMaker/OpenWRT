# build mqtt executable when user executes "make"
mqtt: mqtt.o
	$(CC) $(LDFLAGS) mqtt.o -o mqtt -lmosquitto
mqtt.o: mqtt.c
	$(CC) $(CFLAGS) -c mqtt.c

# remove object files and executable when user executes "make clean"
clean:
	rm *.o mqtt
