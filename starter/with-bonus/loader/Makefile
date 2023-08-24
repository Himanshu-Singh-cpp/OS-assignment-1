#Create lib_simpleloader.so from loader.c

#Provide the command for cleanup
lib_simpleloader.so: loader.o
	gcc -m32 -shared loader.o -o lib_simpleloader.so

loader.o: loader.c loader.h
	gcc -w -m32 -c -fpic loader.c

clean:
	-@rm -f loader.o
	-@rm -f ../bin/lib_simpleloader.so
