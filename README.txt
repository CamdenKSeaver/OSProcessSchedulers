To compile:
-cd into the directory containing the extracted files (schedMain.cpp, schedulers.h, schedulers.cpp)
-enter: make
    or: g++ schedMain.cpp schedulers.cpp -o program

To run:
-enter: program <input file> <millisecond waiting>
-if an input file is not specified, the program will try to read in from "./procList.txt". Otherwise
 it will attempt to read the file specified
-if millisecond waiting isn't specified, the program will wait for 500ms. Otherwise it will attempt
to parse input as unsigned long.
