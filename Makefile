output: main.c motorcontroller.c
	gcc main.c motorcontroller.c -lwiringPi -lpthread -o assigment3
	./assignment3
