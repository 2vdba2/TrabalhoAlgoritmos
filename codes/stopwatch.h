#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdio.h>
#include <time.h>       // for time()
#include <unistd.h>     // for sleep()

//void get_elapsed_time(int start_time, int *elapsed_time, char str_time[])
void get_elapsed_time(struct Stopwatch *stopwatch)
{
	int end_time= time(NULL);
	
	int hours,minutes,seconds;
	
	
	stopwatch->elapsed_time=end_time-stopwatch->start_time;
	
	hours = stopwatch->elapsed_time/3600; 
	minutes = (stopwatch->elapsed_time-hours*3600)/60;
	seconds = stopwatch->elapsed_time-hours*3600-minutes*60;
	sprintf(stopwatch->str_time, "%02d:%02d:%02d ", hours, minutes, seconds);
}

void restart_chronometer(struct Stopwatch *stopwatch)
{
	stopwatch->start_time=time(NULL)-stopwatch->elapsed_time;
}


#endif
