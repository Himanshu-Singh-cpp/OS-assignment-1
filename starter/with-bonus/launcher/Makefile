#Compile the launch.c by linking it with the lib_simpleloader.so
launch: launch.c
	gcc -w -m32 -I../loader -o launch launch.c -L ../bin -l_simpleloader -Wl,-rpath=../bin

#Provide the command for cleanup
clean:
	-@rm -f ../bin/launch
