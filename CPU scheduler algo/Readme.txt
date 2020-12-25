Reference:

1)For using float and displaying correct average time i used:
  //https://www.geeksforgeeks.org/g-fact-41-setting-decimal-precision-in-c/

To compile and run program use:
gcc -o A4 A4.c

In timberlea the file Output.txt already exists so if you want
to generate that file again please delete the existing file and then run
command: ./A4

This will execute the executable file generated after compiling.

I only did two schedules, FCFS and NPSJF.
Only dipslay problem with NPSJF is that waiting time for T4 is shown before T3
that is because i implemented tasks as an array and sorted them according
to their CPU burst. Hence I could not go back and display T4 before T3.

I know the Round Robin does not work and The sorting before process starts
should be able to run PSFJ. Unfortunately i did not have time for doing that.

Hope my code commnets and code indentations are easy to read