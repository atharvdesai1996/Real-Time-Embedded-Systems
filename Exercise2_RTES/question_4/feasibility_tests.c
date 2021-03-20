#include <math.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define U32_T unsigned int

// U=0.7333
U32_T ex0_period[] = {2, 10, 15};
U32_T ex0_wcet[] = {1, 1, 2};

// U=0.9857
U32_T ex1_period[] = {2, 5, 7};
U32_T ex1_wcet[] = {1, 1, 2};

// U=0.9967
U32_T ex2_period[] = {2, 5, 7, 13};
U32_T ex2_wcet[] = {1, 1, 1, 2};

// U=0.93
U32_T ex3_period[] = {3, 5, 15};
U32_T ex3_wcet[] = {1, 2, 3};

// U=1.0
U32_T ex4_period[] = {2, 4, 16};
U32_T ex4_wcet[] = {1, 1, 4};

// U=1.0
U32_T ex5_period[] = {2, 5, 10};
U32_T ex5_wcet[] = {1, 2, 1};

// U=0.9967
U32_T ex6_period[] = {2, 5, 7, 13};
U32_T ex6_wcet[] = {1, 1, 1, 2};
U32_T ex6_deadline[]= {2, 3, 7, 15};

// U=1.0
U32_T ex7_period[] = {3, 5, 15};
U32_T ex7_wcet[] = {1, 2, 4};

// U=0.9967
U32_T ex8_period[] = {2, 5, 7, 13};
U32_T ex8_wcet[] = {1, 1, 1, 2};


int completion_time_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);
int scheduling_point_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[]);
int edf_llf_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[], int edf);


int main(void)
{ 
    int i;
	U32_T numServices;
    
    printf("******** Completion Test Feasibility Example\n");
   
    printf("Ex-0 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=10, T3=15; T=D): ",
		   ((1.0/2.0) + (1.0/10.0) + (2.0/15.0)));
	numServices = sizeof(ex0_period)/sizeof(U32_T);
    if(completion_time_feasibility(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-1 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=5, T3=7; T=D): ", 
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0)));
	numServices = sizeof(ex1_period)/sizeof(U32_T);
    if(completion_time_feasibility(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-2 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex2_period)/sizeof(U32_T);
    if(completion_time_feasibility(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-3 U=%4.2f (C1=1, C2=2, C3=3; T1=3, T2=5, T3=15; T=D): ",
		   ((1.0/3.0) + (2.0/5.0) + (3.0/15.0)));
	numServices = sizeof(ex3_period)/sizeof(U32_T);
    if(completion_time_feasibility(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-4 U=%4.2f (C1=1, C2=1, C3=4; T1=2, T2=4, T3=16; T=D): ",
		   ((1.0/2.0) + (1.0/4.0) + (4.0/16.0)));
	numServices = sizeof(ex4_period)/sizeof(U32_T);
    if(completion_time_feasibility(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-5 U=%4.2f (C1=1, C2=1, C3=1; T1=2, T2=5, T3=10; T=D): ",
		   ((1.0/2.0) + (2.0/5.0) + (1.0/10.0)));
	numServices = sizeof(ex5_period)/sizeof(U32_T);
    if(completion_time_feasibility(numServices, ex5_period, ex5_wcet, ex5_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-6 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; D1=2, D2=3, D3=7, D4=15): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex6_period)/sizeof(U32_T);
    if(completion_time_feasibility(numServices, ex6_period, ex6_wcet, ex6_deadline) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-7 U=%4.2f (C1=1, C2=2, C3=4; T1=3, T2=5, T3=15; T=D): ",
		   ((1.0/3.0) + (2.0/5.0) + (4.0/15.0)));
	numServices = sizeof(ex7_period)/sizeof(U32_T);
    if(completion_time_feasibility(numServices, ex7_period, ex7_wcet, ex7_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-8 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex8_period)/sizeof(U32_T);
    if(completion_time_feasibility(numServices, ex8_period, ex8_wcet, ex8_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");


	printf("\n\n");
    printf("******** Scheduling Point Feasibility Example\n");

    printf("Ex-0 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=10, T3=15; T=D): ",
		   ((1.0/2.0) + (1.0/10.0) + (2.0/15.0)));
	numServices = sizeof(ex0_period)/sizeof(U32_T);
    if(scheduling_point_feasibility(numServices, ex0_period, ex0_wcet, ex0_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-1 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=5, T3=7; T=D): ", 
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0)));
	numServices = sizeof(ex1_period)/sizeof(U32_T);
    if(scheduling_point_feasibility(numServices, ex1_period, ex1_wcet, ex1_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-2 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex2_period)/sizeof(U32_T);
    if(scheduling_point_feasibility(numServices, ex2_period, ex2_wcet, ex2_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-3 U=%4.2f (C1=1, C2=2, C3=3; T1=3, T2=5, T3=15; T=D): ",
		   ((1.0/3.0) + (2.0/5.0) + (3.0/15.0)));
	numServices = sizeof(ex3_period)/sizeof(U32_T);
    if(scheduling_point_feasibility(numServices, ex3_period, ex3_wcet, ex3_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-4 U=%4.2f (C1=1, C2=1, C3=4; T1=2, T2=4, T3=16; T=D): ",
		   ((1.0/2.0) + (1.0/4.0) + (4.0/16.0)));
	numServices = sizeof(ex4_period)/sizeof(U32_T);
    if(scheduling_point_feasibility(numServices, ex4_period, ex4_wcet, ex4_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-5 U=%4.2f (C1=1, C2=1, C3=1; T1=2, T2=5, T3=10; T=D): ",
		   ((1.0/2.0) + (2.0/5.0) + (1.0/10.0)));
	numServices = sizeof(ex5_period)/sizeof(U32_T);
    if(scheduling_point_feasibility(numServices, ex5_period, ex5_wcet, ex5_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-6 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; D1=2, D2=3, D3=7, D4=15): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex6_period)/sizeof(U32_T);
    if(scheduling_point_feasibility(numServices, ex6_period, ex6_wcet, ex6_deadline) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-7 U=%4.2f (C1=1, C2=2, C3=4; T1=3, T2=5, T3=15; T=D): ",
		   ((1.0/3.0) + (2.0/5.0) + (4.0/15.0)));
	numServices = sizeof(ex7_period)/sizeof(U32_T);
    if(scheduling_point_feasibility(numServices, ex7_period, ex7_wcet, ex7_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-8 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex8_period)/sizeof(U32_T);
    if(scheduling_point_feasibility(numServices, ex8_period, ex8_wcet, ex8_period) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
    printf("\n\n");




    printf("******** EDF Completion Feasibility\n");
    printf("Ex-0 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=10, T3=15; T=D): ",
		   ((1.0/2.0) + (1.0/10.0) + (2.0/15.0)));
	numServices = sizeof(ex0_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex0_period, ex0_wcet, ex0_period, TRUE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-1 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=5, T3=7; T=D): ", 
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0)));
	numServices = sizeof(ex1_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex1_period, ex1_wcet, ex1_period, TRUE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-2 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex2_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex2_period, ex2_wcet, ex2_period, TRUE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-3 U=%4.2f (C1=1, C2=2, C3=3; T1=3, T2=5, T3=15; T=D): ",
		   ((1.0/3.0) + (2.0/5.0) + (3.0/15.0)));
	numServices = sizeof(ex3_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex3_period, ex3_wcet, ex3_period, TRUE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-4 U=%4.2f (C1=1, C2=1, C3=4; T1=2, T2=4, T3=16; T=D): ",
		   ((1.0/2.0) + (1.0/4.0) + (4.0/16.0)));
	numServices = sizeof(ex4_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex4_period, ex4_wcet, ex4_period, TRUE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-5 U=%4.2f (C1=1, C2=1, C3=1; T1=2, T2=5, T3=10; T=D): ",
		   ((1.0/2.0) + (2.0/5.0) + (1.0/10.0)));
	numServices = sizeof(ex5_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex5_period, ex5_wcet, ex5_period, TRUE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-6 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; D1=2, D2=3, D3=7, D4=15): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex6_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex6_period, ex6_wcet, ex6_deadline, TRUE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-7 U=%4.2f (C1=1, C2=2, C3=4; T1=3, T2=5, T3=15; T=D): ",
		   ((1.0/3.0) + (2.0/5.0) + (4.0/15.0)));
	numServices = sizeof(ex7_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex7_period, ex7_wcet, ex7_period, TRUE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-8 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex8_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex8_period, ex8_wcet, ex8_period, TRUE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("\n\n");




    printf("******** LLF Completion Feasibility\n");

    printf("Ex-0 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=10, T3=15; T=D): ",
		   ((1.0/2.0) + (1.0/10.0) + (2.0/15.0)));
	numServices = sizeof(ex0_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex0_period, ex0_wcet, ex0_period, FALSE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-1 U=%4.2f (C1=1, C2=1, C3=2; T1=2, T2=5, T3=7; T=D): ", 
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0)));
	numServices = sizeof(ex1_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex1_period, ex1_wcet, ex1_period, FALSE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-2 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex2_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex2_period, ex2_wcet, ex2_period, FALSE) == TRUE)
        printf("FEASIBLE\n");
    else

        printf("INFEASIBLE\n");



    printf("Ex-3 U=%4.2f (C1=1, C2=2, C3=3; T1=3, T2=5, T3=15; T=D): ",

		   ((1.0/3.0) + (2.0/5.0) + (3.0/15.0)));

	numServices = sizeof(ex3_period)/sizeof(U32_T);

    if(edf_llf_feasibility(numServices, ex3_period, ex3_wcet, ex3_period, FALSE) == TRUE)

        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");
	
    printf("Ex-4 U=%4.2f (C1=1, C2=1, C3=4; T1=2, T2=4, T3=16; T=D): ",
		   ((1.0/2.0) + (1.0/4.0) + (4.0/16.0)));
	numServices = sizeof(ex4_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex4_period, ex4_wcet, ex4_period, FALSE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-5 U=%4.2f (C1=1, C2=1, C3=1; T1=2, T2=5, T3=10; T=D): ",
		   ((1.0/2.0) + (2.0/5.0) + (1.0/10.0)));
	numServices = sizeof(ex5_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex5_period, ex5_wcet, ex5_period, FALSE) == TRUE)
        printf("FEASIBLE\n");

    else
        printf("INFEASIBLE\n");

    printf("Ex-6 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; D1=2, D2=3, D3=7, D4=15): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex6_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex6_period, ex6_wcet, ex6_deadline, FALSE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-7 U=%4.2f (C1=1, C2=2, C3=4; T1=3, T2=5, T3=15; T=D): ",
		   ((1.0/3.0) + (2.0/5.0) + (4.0/15.0)));
	numServices = sizeof(ex7_period)/sizeof(U32_T);

    if(edf_llf_feasibility(numServices, ex7_period, ex7_wcet, ex7_period, FALSE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");

    printf("Ex-8 U=%4.2f (C1=1, C2=1, C3=1, C4=2; T1=2, T2=5, T3=7, T4=13; T=D): ",
		   ((1.0/2.0) + (1.0/5.0) + (1.0/7.0) + (2.0/13.0)));
	numServices = sizeof(ex8_period)/sizeof(U32_T);
    if(edf_llf_feasibility(numServices, ex8_period, ex8_wcet, ex8_period, FALSE) == TRUE)
        printf("FEASIBLE\n");
    else
        printf("INFEASIBLE\n");


}


int completion_time_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[])
{
  int i, j;
  U32_T an, anext;
  
  // assume feasible until we find otherwise
  int set_feasible=TRUE;
   
  //printf("numServices=%d\n", numServices);
  
  for (i=0; i < numServices; i++)
  {
       an=0; anext=0;
       
       for (j=0; j <= i; j++)
       {
           an+=wcet[j];
       }
       
	   //printf("i=%d, an=%d\n", i, an);

       while(1)
       {
             anext=wcet[i];
	     
             for (j=0; j < i; j++)
                 anext += ceil(((double)an)/((double)period[j]))*wcet[j];
		 
             if (anext == an)
                break;
             else
                an=anext;

			 //printf("an=%d, anext=%d\n", an, anext);
       }
       
	   //printf("an=%d, deadline[%d]=%d\n", an, i, deadline[i]);

       if (an > deadline[i])
       {
          set_feasible=FALSE;
       }
  }
  
  return set_feasible;
}


int scheduling_point_feasibility(U32_T numServices, U32_T period[], 
								 U32_T wcet[], U32_T deadline[])
{
   int rc = TRUE, i, j, k, l, status, temp;

   for (i=0; i < numServices; i++) // iterate from highest to lowest priority
   {
      status=0;

      for (k=0; k<=i; k++) 
      {
          for (l=1; l <= (floor((double)period[i]/(double)period[k])); l++)
          {
               temp=0;

               for (j=0; j<=i; j++) temp += wcet[j] * ceil((double)l*(double)period[k]/(double)period[j]);

               if (temp <= (l*period[k]))
			   {
				   status=1;
				   break;
			   }
           }
           if (status) break;
      }
      if (!status) rc=FALSE;
   }
   return rc;
}

// Recursive function to return gcd of a and b
// this function was copied from: https://www.geeksforgeeks.org/program-to-find-lcm-of-two-numbers/
int gcd(int a, int b)  
{  
    if (a == 0) 
        return b;  
    return gcd(b % a, a);  
}  
  
// Function to return LCM of two numbers  
// this function was copied from: https://www.geeksforgeeks.org/program-to-find-lcm-of-two-numbers/
int calculate_lcm(int a, int b)  
{  
    return (a*b)/gcd(a, b);  
}

typedef struct
{
	int completed;
	int execution_left;
	int time_to_deadline;
	int queued;
	int execution_left_2;
	int time_to_deadline_2;
} task_t;

task_t tasks[10]; // allocate memory for up to 10 tasks

/**
 * This function runs either an EDF or LLF feasibility test, depending on the
 * parameter edf. If edf is true, an EDF test will be run. If it is false, an
 * LLF test will be run. All the other parameters are the same as the functions
 * above.
 */
int edf_llf_feasibility(U32_T numServices, U32_T period[], U32_T wcet[], U32_T deadline[], int edf)
{
	// calculate LCM
	int lcm = period[0];
	
	// start at 1 because we already initialized the lcm to period[0]
	for (int i = 1; i < numServices; i++)  
	{
		lcm = calculate_lcm(lcm, period[i]);
	}

	// initialize tasks
	for (int i = 0; i < numServices; i++)
	{
		tasks[i].completed = TRUE;
		tasks[i].queued = FALSE;
	}

	// for each step up to LCM
	for (int i = 0; i < lcm; i++)
	{

		// update each task
		for (int j = 0; j < numServices; j++)
		{
			// check if the period is up, meaning it's time to run again.
			if (i % period[j] == 0)
			{
				// check if the task has already completed. If not, add it
				// to a queue (this is only used for a task that has a 
				// deadline longer than its period)
				if (tasks[j].completed)
				{
					tasks[j].completed = FALSE;
					tasks[j].execution_left = wcet[j];
					tasks[j].time_to_deadline = deadline[j];
				}
				else
				{
					tasks[j].queued = TRUE;
					tasks[j].execution_left_2 = wcet[j];
					tasks[j].time_to_deadline_2 = deadline[j];
				}
			}
		}

		// determine which task has the highest priority
		int highest_priority_task = -1;
		for (int j = 0; j < numServices; j++)
		{
			if (!tasks[j].completed) // only consider tasks that have not yet completed
			{
				if (highest_priority_task == -1)
				{
					highest_priority_task = j;
				}
				// if we're using EDF and the task's deadline is less than the current minimum
				else if (edf && tasks[j].time_to_deadline < tasks[highest_priority_task].time_to_deadline)
				{
					highest_priority_task = j;
				}
				// if we're using LLF and the task's laxity is less than the current minimum
				else if (!edf && (tasks[j].time_to_deadline - tasks[j].execution_left) < (tasks[highest_priority_task].time_to_deadline - tasks[highest_priority_task].execution_left))
				{
					highest_priority_task = j;
				}
			}
		}

		// Check the task with the highest priority.
		// if there's not enough time to complete before deadline, fail!
		if (tasks[highest_priority_task].execution_left > tasks[highest_priority_task].time_to_deadline)
		{
			printf("task %d failed at i: %d. execution left: %d, time to deadline: %d\n", highest_priority_task, i, tasks[highest_priority_task].execution_left, tasks[highest_priority_task].time_to_deadline);
			return FALSE;
		}
		
		// run one step by decrementing execution_left on highest task and decrementing time_to_deadline on every task
		if (highest_priority_task >= 0)
		{
			tasks[highest_priority_task].execution_left--;
		}
		for (int j = 0; j < numServices; j++)
		{
			if (!tasks[j].completed) // only decrement tasks that have not yet completed
			{
				tasks[j].time_to_deadline--;
				if (tasks[j].queued) // decrement queued deadline, if necessary
				{
					tasks[j].time_to_deadline_2--;
				}

				if (tasks[j].execution_left == 0) // if a task has completed
				{
					tasks[j].completed = TRUE;
					if (tasks[j].queued) // if there was a queued task, set it as the main task now
					{
						tasks[j].completed = FALSE;
						tasks[j].time_to_deadline = tasks[j].time_to_deadline_2;
						tasks[j].execution_left = tasks[j].execution_left_2;
						tasks[j].queued = FALSE;
					}
				}
			}
		}
		
	}
	
	// if we make it all the way here, we have sucessfully scheduled everything! return true
	return TRUE;
}
