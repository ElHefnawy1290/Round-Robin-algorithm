# Round Robin CPU Scheduling Implementation

## Overview
A C++ implementation of the Round Robin CPU scheduling algorithm that calculates key performance metrics and generates a Gantt chart visualization. Processes are read from an input file and results are written to an output file.

## Features
- Round Robin scheduling with fixed quantum time (2 units)
- Gantt chart visualization
- Performance metrics calculation:
  - Turnaround Time
  - Waiting Time
  - Response Time
  - Averages for all metrics
- File-based input/output
- Process management with arrival time support

## Installation
1. Ensure you have a C++ compiler (g++ recommended)
2. Compile the source file:
```bash
g++ round_robin.cpp -o scheduler
```
## Usage
1. Create input file `Example.txt` with process data
2. Run the executable:
```
./scheduler
```
3. Results will be saved in `Solution.txt`
### Input File Format (`Example.txt`)
```
[number_of_processes]
[name1] [burst_time1] [arrival_time1]
[name2] [burst_time2] [arrival_time2]
...
```
Example:
```
3
P1 5 0
P2 3 1
P3 6 2
```
## Functions
- `roundRobin()`: Implements scheduling algorithm
- `drawGanttChart()`: Generates ASCII Gantt chart
- `calculateTurnAroundTime()`: Computes turnaround times
- `calculateWaitingTime()`: Computes waiting times
- `printSolutionReport()`: Displays performance metrics

## Example Output
### Gantt Chart:
```
|---|---|---|
|P1 |P2 |P3 |
|---|---|---|
```
### Performance Report:
```
name            wt              trt             rt
P1               7               12              0
P2               9               11              1
P3               10              14              2
AVG              8.66667         12.3333         1
```
## Notes
- Fixed quantum time of 2 time units
- Process names should follow PX format (e.g., P1, P2)
- Input file must be named `Example.txt`
- Output is written to `Solution.txt`
- No error handling for invalid inputs
- Processes with same arrival time are added in file order
