#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <stdio.h>
#include <time.h>       // for time()
#include <unistd.h>     // for sleep()

void get_elapsed_time(int start_time, int *elapsed_time, char str_time[])
{
	int end_time= time(NULL);
	
	int hours,minutes,seconds;
	
	
	*elapsed_time=end_time-start_time;
	
	hours = *elapsed_time/3600; 
	minutes = (*elapsed_time-hours*3600)/60;
	seconds = *elapsed_time-hours*3600-minutes*60;
	sprintf(str_time, "%02d:%02d:%02d ", hours, minutes, seconds);
}

void restart_chronometer(int *start_time, int elapsed_time)
{
	*start_time=time(NULL)-elapsed_time;
}


#endif
