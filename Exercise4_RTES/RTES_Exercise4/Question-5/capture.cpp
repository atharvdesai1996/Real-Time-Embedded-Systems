#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include  <sys/time.h>
#include <sys/sysinfo.h>
#include <fstream> 
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

#define HRES 1280
#define VRES 960
#define NUM_THREADS (1) 
#define CANNY 0
#define HOUGH 0
#define HOUGH_ELLIPTICAL 1 
#define TOTAL_FRAMES 98
#define JITTER_FRAMES 50
#define NSEC_PER_SEC (1000000000)
#define NSEC_PER_MSEC (1000000)
#define NSEC_PER_MICROSEC (1000)



CvCapture* capture;

pthread_t threads[NUM_THREADS]; //Thread descriptors
pthread_attr_t rt_sched_attr[NUM_THREADS]; //Thread attributes object
struct sched_param rt_param[NUM_THREADS];
struct sched_param main_param;
float C[100], jitter[100], missed_deadline[100];

int delta_t(struct timespec *stop, struct timespec *start, struct timespec *delta_t)
{
  int dt_sec=stop->tv_sec - start->tv_sec;
  int dt_nsec=stop->tv_nsec - start->tv_nsec;

  if(dt_sec >= 0)
  {
    if(dt_nsec >= 0)
    {
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }
    else
    {
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }
  else
  {
    if(dt_nsec >= 0)
    {
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }
    else
    {
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }

  return(1);
}

void *canny_task(void* threadid)
{
	IplImage* frame;
	Mat canny_frame, timg_gray, gray, timg_grad, cdst;
	int lowThreshold=0;
	int ratio = 3;
	double  fps, avg_fps;
	int i=TOTAL_FRAMES+1, n=1, j=0,k=0, v=0; 
	float deadline=0, max_C, avg_jitter;
	vector<Vec3f> circles;
	vector<Vec4i> lines;
	
	struct timespec start_time, end_time, time_diff;
	while(i!=-1)
	{
		
		clock_gettime(CLOCK_REALTIME, &start_time);
		#if (CANNY)
		
		frame=cvQueryFrame(capture);
		Mat mat_frame(cvarrToMat(frame));
		cvtColor(mat_frame, timg_gray, CV_RGB2GRAY);
		/// Reduce noise with a kernel 3x3
		blur( timg_gray, canny_frame, Size(3,3) );
		/// Canny detector
		Canny( canny_frame, canny_frame, lowThreshold, lowThreshold*ratio, 3);
		/// Using Canny's output as a mask, we display our result
		timg_grad = Scalar::all(0);
        	mat_frame.copyTo( timg_grad, canny_frame);
		imshow("Canny Edge Detection", timg_grad);
		
		#endif

		#if (HOUGH_ELLIPTICAL)
		frame=cvQueryFrame(capture);
		Mat mat_frame(cvarrToMat(frame));
		cvtColor(mat_frame, gray, CV_RGB2GRAY);
		GaussianBlur(gray, gray, Size(9,9), 2, 2);
		HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, gray.rows/8, 100, 50, 0, 0);		
		printf("circles.size = %ld\n", circles.size());
		for( size_t count = 0; count < circles.size(); count++ )
        	{
          		Point center(cvRound(circles[count][0]), cvRound(circles[count][1]));
          		int radius = cvRound(circles[count][2]);
          		// circle center
          		circle( mat_frame, center, 3, Scalar(0,255,0), -1, 8, 0 );
          		// circle outline
          		circle( mat_frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
        	}
		imshow("Hough Elliptical", mat_frame);		
		#endif
		#if (HOUGH)
		frame=cvQueryFrame(capture);
		Mat mat_frame(cvarrToMat(frame));
		Canny(mat_frame, canny_frame, 50, 200, 3);
		cvtColor(canny_frame, cdst, CV_GRAY2BGR);
        	cvtColor(mat_frame, gray, CV_BGR2GRAY);

        	HoughLinesP(canny_frame, lines, 1, CV_PI/180, 50, 50, 10);

        	for( size_t i = 0; i < lines.size(); i++ )
        	{
          		Vec4i l = lines[i];
          		line(mat_frame, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
        	}
		imshow("Hough", mat_frame);
		#endif

		
		clock_gettime(CLOCK_REALTIME, &end_time);
		delta_t(&end_time, &start_time, &time_diff);
		C[i] = ((float)time_diff.tv_nsec/NSEC_PER_MSEC);
		fps =  (NSEC_PER_SEC /time_diff.tv_nsec);
		avg_fps = ((avg_fps*n) + fps)/(n+1);
		n++;
		printf("\n fps = %lf, C[%d]=%f", fps, i, C[i]);
		if(i<=TOTAL_FRAMES&&i>=JITTER_FRAMES)
		{

			if(C[i]>deadline)
	        	{   
				max_C = C[i];
			}
			
		}	
		else if	(i<JITTER_FRAMES)
		{	
			deadline = max_C*1.2;			
			jitter[j] =deadline -  C[i];
			avg_jitter = ((avg_jitter*j)+jitter[j])/(j+1);
			printf("\njitter[%d] = %f, C[%d]=%f",j, jitter[j],i, C[i]);
			if(C[i]>deadline)
			{
				missed_deadline[k] = C[i];
				k++;			
			}			
				
			j++;
 	
		}
		i--;
		char c = cvWaitKey(10);
		if( c == 27 )
		{
			
			printf("\nQuit");		
			break;
		}
	}
	printf("\nMaximum Deadline = %f \nAverage Frame Rate = %lf \nNumber of missed deadlines = %d \nAverage Jitter = %f", deadline, avg_fps,k, avg_jitter);
	ofstream file;
	file.open("jitterfile.csv");
	for(v =0; v<JITTER_FRAMES; v++)
		file<<jitter[v]<<endl;
	file.close();
	

}

void print_scheduler(void)
{
   int schedType;

   schedType = sched_getscheduler(getpid());

   switch(schedType)
   {
     case SCHED_FIFO:
           printf("Pthread Policy is SCHED_FIFO\n");
           break;
     case SCHED_OTHER:
           printf("Pthread Policy is SCHED_OTHER\n");
       break;
     case SCHED_RR:
           printf("Pthread Policy is SCHED_OTHER\n");
           break;
     default:
       printf("Pthread Policy is UNKNOWN\n");
   }

}

int numberOfProcessors;

int main()
{	
	int rt_max_prio;
	int rc;
	int dev = 0;
	int i, coreid, idx;
	
	cpu_set_t allcpuset;
        cpu_set_t threadcpu;

	printf("This system has %d processors configured and %d processors available.\n", get_nprocs_conf(), get_nprocs());

	numberOfProcessors = get_nprocs_conf(); 
        printf("number of CPU cores=%d\n", numberOfProcessors);

        CPU_ZERO(&allcpuset);
	for(i=0; i < numberOfProcessors; i++)
       		CPU_SET(i, &allcpuset);

	if (rc)
		perror("\n sem init failed for sem[0]");
	
	rt_max_prio = sched_get_priority_max(SCHED_OTHER);
	main_param.sched_priority=rt_max_prio; //Scheduler priority is 99 
   	sched_setscheduler(getpid(), SCHED_OTHER, &main_param); // scheduling policy is SCHED_FIFO
	
	
	print_scheduler();
	capture = (CvCapture *)cvCreateCameraCapture(dev);
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, HRES);
        cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, VRES);
	for(i=0;i<NUM_THREADS;i++)
	{
		CPU_ZERO(&threadcpu);
       		coreid=i%numberOfProcessors;
	        printf("Setting thread %d to core %d\n", i, coreid);
 
       		CPU_SET(coreid, &threadcpu);
       		for(idx=0; idx<numberOfProcessors; idx++)
           		if(CPU_ISSET(idx, &threadcpu))  printf(" CPU-%d ", idx);
       			printf("\nLaunching thread %d\n", i);
		
		pthread_attr_init(&rt_sched_attr[i]);
		rc=pthread_attr_setinheritsched(&rt_sched_attr[i], PTHREAD_EXPLICIT_SCHED);
		rc=pthread_attr_setschedpolicy(&rt_sched_attr[i], SCHED_OTHER); //Set SCHED_FIFO
		rc=pthread_attr_setaffinity_np(&rt_sched_attr[i], sizeof(cpu_set_t), &threadcpu);

       		rt_param[i].sched_priority=rt_max_prio-i-1;
       		pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);
        	pthread_attr_setschedparam(&rt_sched_attr[i], &rt_param[i]);
	
		rc = pthread_create(&threads[i],   
                      &rt_sched_attr[i],                          
                      canny_task, 
                      (void *)i 
                     );
	 if (rc) 
	 	perror("pthread create failed for 0");
	pthread_join(threads[0], NULL);
	}	
	cvReleaseCapture(&capture);

}
