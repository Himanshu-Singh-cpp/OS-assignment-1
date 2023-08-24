#invoke make inside following directories and in this order: loader, launch, fib
#move the lib_simpleloader.so and launch binaries inside bin directory
all:
	cd loader && $(MAKE)
	mv ./loader/lib_simpleloader.so ./bin
	cd launcher && $(MAKE)
	mv ./launcher/launch ./bin
	cd test && $(MAKE)

#Provide the command for cleanup
clean:
	cd loader && $(MAKE) clean
	cd launcher && $(MAKE) clean
	cd test && $(MAKE) clean

