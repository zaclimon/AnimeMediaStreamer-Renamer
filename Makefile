# Basic Makefile to compile the renamer since it is a bit easier
# and faster than always calling gcc to compile the different
# parts of the tool.

renamer_file.o: renamer_file.c renamer_file.h renamer_fansubs.h
	gcc -c renamer_file.c
renamer_directory.o: renamer_directory.c renamer_file.h
	gcc -c renamer_directory.c
renamer.o: renamer.c renamer_directory.h renamer_file.h
	gcc -c renamer.c
renamer_fansubs.o: renamer_fansubs.c renamer_fansubs.h
	gcc -c renamer_fansubs.c
hsrenamer: renamer.o renamer_directory.o renamer_file.o renamer_fansubs.o
	gcc renamer.o renamer_directory.o renamer_file.o renamer_fansubs.o -o hsrenamer
clean:
	rm -f renamer.o renamer_directory.o renamer_file.o renamer_fansubs.o hsrenamer