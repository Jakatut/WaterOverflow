#
# This makefile will compile all sources found in the
# current directory.
# =======================================================
#                  WaterOverflow
# =======================================================

CFLAGS=-Iinc
DEBUG=
COMPILER=cc

#
# =====================================================
#               Final binary Target
# =====================================================
./bin/WaterOverflow : ./obj/main.o ./obj/events.o ./obj/controls.o ./obj/gpio.o
	$(COMPILER) ./obj/main.o ./obj/events.o ./obj/controls.o ./obj/gpio.o $(DEBUG) -o ./bin/WaterOverflow

#
# =======================================================
#                  Dependencies
# =======================================================
./obj/main.o : ./main.c
	$(COMPILER) -c ./main.c $(CFLAGS) $(DEBUG) -o ./obj/main.o

./obj/events.o : ./src/events.c
	$(COMPILER) -c ./src/events.c -lpigpio -lrt -lpthread $(CFLAGS) $(DEBUG) -o ./obj/events.o

./obj/controls.o : ./src/controls.c
	$(COMPILER) -c ./src/controls.c $(CFLAGS) $(DEBUG) -o ./obj/controls.o

./obj/gpio.o : ./src/gpio.c
	$(COMPILER) -c ./src/gpio.c -lpigpio -lrt -lpthread $(CFLAGS) $(DEBUG) -o ./obj/gpio.o

#
# =======================================================
#                  Other targets
# =======================================================
all : ./bin/WaterOverflow

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./inc/*.h~
	rm -f ./src/*.c~
	rm -f ./lib/*.a
	rm -f ./bin/*.so
