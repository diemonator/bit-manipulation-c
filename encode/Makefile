#give PN the name of your c file wihich contains main
PN=encode

CFLAGS=-Wall -Werror -Iproduct -I../Unity -Itest

#add your own other c files here
SHARED=\
	                         
TEST=$(SHARED) \
             ../Unity/unity.c \

all: 
	gcc $(CFLAGS) product/$(PN).c $(SHARED) -o $(PN) 

EncodeTest: 
	gcc $(CFLAGS) test/encode_test.c $(TEST) -o EncodeTest 
	./EncodeTest
    
clean:
	rm -rf $(PN)Test $(PN) EncodeTest

valgrind: 
	valgrind ./$(PN)



.PHONY: clean test valgrind
