my_grep: main.o flags_collection.o input_processing.o match_line.o print.o
	gcc -Wall -Wextra -g -O1 -o my_grep main.o flags_collection.o input_processing.o match_line.o print.o

main.o: main.c input_processing.h flags_collection.h
	gcc -Wall -Wextra -c main.c 

input_processing.o: input_processing.c flags_collection.h common_defines.h print.h match_line.h
	gcc -Wall -Wextra -c input_processing.c

match_line.o: match_line.c match_line.h common_defines.h flags_collection.h
	gcc -Wall -Wextra -c match_line.c
	
flags_collection.o: flags_collection.c flags_collection.h common_defines.h
	gcc -Wall -Wextra -c flags_collection.c
	
print.o: print.c print.h flags_collection.h
	gcc -Wall -Wextra -c print.c

.PHONY: all clean test
clean: 
	-rm main.o flags_collection.o input_processing.o match_line.o print.o my_grep
all: my_grep
