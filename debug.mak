project_debug: user_interface_debug.o llist_debug.o
	g++ -o project_debug user_interface_debug.o llist_debug.o

user_interface_debug.o: user_interface.cpp record.h llist.h
	g++ -DDEBUGMODE -ansi -pedantic-errors -Wall -c -o user_interface_debug.o user_interface.cpp

llist_debug.o: llist.cpp llist.h record.h
	g++ -DDEBUGMODE -ansi -pedantic-errors -Wall -c -o llist_debug.o llist.cpp

clean:
	rm user_interface.o llist.o
