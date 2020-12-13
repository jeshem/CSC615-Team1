output: main.c motorcontroller.c
	gcc main.c motorcontroller.c irSensor.c lineSensor.c -lwiringPi -lpthread -o driver
	./driver
