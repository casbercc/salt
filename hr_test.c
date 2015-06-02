#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define AP_NAME "hr_test"
#define EMPTY_STRUCTURE(S,X) memset((X),0,sizeof(S))

int timer_start(struct timespec *start_time)
{
	EMPTY_STRUCTURE(struct timespec,start_time);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID,start_time);	
	printf("start: %ld\n",start_time->tv_nsec);

	return 0;
}

long timer_end(struct timespec start_time)
{
	struct timespec end_time;
	long diffInNanos=0;
	
	EMPTY_STRUCTURE(struct timespec,&end_time);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID,&end_time);
	printf("end: %ld\n",end_time.tv_nsec);
	diffInNanos=end_time.tv_nsec-start_time.tv_nsec;
	
	return diffInNanos;			
}

int do_task(int max, FILE *record_fp)
{
	int idx;

    if (!record_fp) {
        printf("NULL record_fp!\n");
        return -1;
    }
	
	for (idx=0; idx<max; idx++)
		fprintf(record_fp,"(%d)",idx+1);

    fclose(record_fp);

    return 0;
}

int main(int argc, char *argv[])
{
	struct timespec vartime;
	long timeElapsed=0;
	float *result=NULL,total;
	int maxCnt=0,repeatCnt=0,doCnt=0;
    FILE *record_fp=NULL;

    if (argv[1])
	    maxCnt=atoi(argv[1]);
	else {
        printf("lack of do count!\n");
        return -1;
	}

    if (argv[2])
	    repeatCnt=atoi(argv[2]);
	else {
        printf("lack of repeat count!\n");
        return -1;
	}

    if (!(result = (float *)calloc(repeatCnt,sizeof(float)))) {
        printf("No memory!\n");
        return -1;
    }

    for (doCnt=0; doCnt<repeatCnt; doCnt++) {
    	record_fp = fopen(AP_NAME".txt","w");
    	timer_start(&vartime);
    	do_task(maxCnt,record_fp);
    	timeElapsed=timer_end(vartime);
    	result[doCnt]=(float)((float)timeElapsed/1000000L);
    	printf("(%d) Time taken in nano grade = %.3f ms\n",doCnt+1,result[doCnt]);
    }

    for (doCnt=0; doCnt<repeatCnt; doCnt++)
        total+=result[doCnt];

    total/=repeatCnt;

    printf("-> Average: %.3f ms\n",total);
		
	return 0;	
}
