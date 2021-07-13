# build mqtt_sub executable when user executes "make"
mqtt_sub: mqtt_sub.o
	$(CC) $(LDFLAGS) mqtt_sub.o -o mqtt_sub -lmosquitto
mqtt_sub.o: mqtt_sub.c
	$(CC) $(CFLAGS) -c mqtt_sub.c

# remove object files and executable when user executes "make clean"
clean:
	rm *.o mqtt_sub
