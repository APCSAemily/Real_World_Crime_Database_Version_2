# Real World Crime Version 2

QUICK START
powershell
cd src
g++ -std=c++17 -O2 *.cpp -o main.exe

HOW TO USE
powershell
.\main.exe <DISTRICT> [NUMBER]


Command
What it does
.\main.exe B2
Shows up to 50 crimes in B2
.\main.exe B2 10
Shows top 10 crimes from each heap
.\main.exe B2 0
Shows ALL crimes in B2
.\main.exe C11 5
Top 5 in C11



WHAT YOU SEE
District B2 (1247 total crimes)
Showing top 10 from each heap.
------------------------------------------------------------

Binary heap (sorted by TIME):
  00:01 - INVESTIGATE PERSON
  00:03 - VERBAL DISPUTE
  ...

Ternary heap (sorted by OFFENSE_CODE severity):
  [01102] MURDER
  [01301] ASSAULT - AGGRAVATED
  ...

FEATURES
Binary Heap = sorts by time (earliest first)
Ternary Heap = sorts by severity code (lowest number = most severe)
Fast filtering = only reads crimes from your district
No scrolling = control how many lines with the number!
FILES YOU NEED
src/
├── main.cpp
├── Crime.h
├── BinaryHeap.h/.cpp
├── TernaryHeap.h/.cpp
└── crime.csv

JUST COPY-PASTE THIS in VS CODE TERMINAL
cd src
g++ -std=c++17 -O2 *.cpp -o main.exe
.\main.exe B2 10


GitHub:
https://github.com/APCSAemily/Real_World_Crime_Database_Version_2

