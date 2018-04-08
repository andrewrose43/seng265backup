SENG 256 Assignment 3 -Testing Data README

This zip file contains 3 separate test input files (to read from stdin) and corresponding expected output.  The input files in*.txt mimic various sets of input a user may enter to the application.  Their corresponding output*.txt files have the expected output for that set of commands.  

To run the tests use the following command with in1.txt:
python3 ferry_delays.py test1.csv < in1.txt | sed -n -e '/RESULTS/,/END/p'

Change the in1.txt with in2.txt and in3.txt in the command above to run it with the other two test files. 