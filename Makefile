output: main.c motorcontroller.c
	gcc main.c echosensor.c motorcontroller.c irSensor.c lineSensor.c -lwiringPi -lpthread -o driver
	./driver
