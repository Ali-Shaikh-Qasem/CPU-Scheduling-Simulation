
// Ali Shaikh Qasem , 1212171.

#include <stdio.h>
#include <stdlib.h>

#define num_processes 7
#define duration 200

struct node ;
typedef struct node * ptr;
struct node
{
    int pid;
    int arrival_time;
    int burst_time;
    int come_back_time;
    int priority;
    int total_cpu_time; // don't forget to increases this after each burst
    int finish_time; // when the process ends it's work in the 200 time units duration
    int Queue_waiting_time; // to count the instant waiting time of the process (inside the waiting queue)
    int total_waiting_queue_time; // count the total time that the process spent in the waiting queue
    int final_waiting_time; // the total time the process spends in the waiting queue, ends at the finish time.
    int remaining_burst_time;
    int ready_queue_time;
    char state ; /* N = not arrived, W = waiting, R = ready, E = executing (running) */


    ptr next;

};
typedef ptr pos ;
typedef ptr Queue;

struct Gantt_chart
{
    int process_id;
    int beign;
    int end;

};

//prototypes
ptr DeQueue (Queue Q);
ptr shortest_burst_time (Queue ready_queue);
void shortest_job_first(ptr processes [num_processes], Queue ready_queue);
float avg_waiting_time (ptr processes [num_processes]);
float avg_turn_around_time (ptr processes [num_processes]);
void print_proecesses (ptr processes [num_processes]);
void remove_from_queue (Queue ready_queue , int pid);
ptr shortest_remainig_time_process (Queue ready_queue);
void shortest_remaining_time_first (ptr processes [num_processes], Queue ready_queue,int gant_chart [duration]);
void preemptive_gantt_chart_drawing (int gantt_chart [duration]);
void Round_robin(ptr processes [num_processes], Queue ready_queue, int q);
ptr highest_priority(Queue ready_queue);
void Non_preemptive_priority(ptr processes [num_processes], Queue ready_queue, int age);


int main()
{
    //defining the processes
    ptr processes [num_processes];
    //allocating the processes
    for (int i=0 ; i< num_processes ; i++)
    {
        processes[i] = (ptr)malloc (sizeof(struct node));
        processes[i]->state = 'N';
        processes[i]->total_cpu_time = 0;
        processes[i]->Queue_waiting_time = 0;
        processes[i]->total_waiting_queue_time =0;

    }

    //setting the data for each process
    set_processes(processes);

    //initializing ready queue
    Queue ready_queue = (Queue)malloc (sizeof(struct node));
    ready_queue->next = NULL;

    //defining an array to hold gantt chart data
    int gantt_chart [duration];

    //creating menu
    int choice;
    printf("Choose an algorithm:\n\n");
    printf("1. First come first served.\n");
    printf("2. Shortest job first.\n");
    printf("3. Shortest remaining time first.\n");
    printf("4. Round Robin.\n");
    printf("5. Preemptive priority .\n");
    printf("6. Non preemptive Priority.\n");
    printf("7.Exit\n");
    scanf("%d",&choice);

    while(choice != 7)
    {
        printf("Gantt chart:\n\n");
        switch (choice)
        {
            case 1:
                FCFS(processes,ready_queue);
                printf("Avg waiting time = %f\n",avg_waiting_time(processes));
                printf("Avg turn around time = %f\n",avg_turn_around_time(processes));
                break;

            case 2:
                shortest_job_first(processes,ready_queue);
                printf("Avg waiting time = %f\n",avg_waiting_time(processes));
                printf("Avg turn around time = %f\n",avg_turn_around_time(processes));
                break;

            case 3:
                shortest_remaining_time_first(processes,ready_queue,gantt_chart);
                preemptive_gantt_chart_drawing(gantt_chart);
                printf("Avg waiting time = %f\n",avg_waiting_time(processes));
                printf("Avg turn around time = %f\n",avg_turn_around_time(processes));
                break;

            case 4:
                Round_robin(processes,ready_queue,1);
                printf("Avg waiting time = %f\n",avg_waiting_time(processes));
                printf("Avg turn around time = %f\n",avg_turn_around_time(processes));
                break;

            case 5:
                preemptive_priority(processes,ready_queue,1,gantt_chart);
                preemptive_gantt_chart_drawing(gantt_chart);
                printf("Avg waiting time = %f\n",avg_waiting_time(processes));
                printf("Avg turn around time = %f\n",avg_turn_around_time(processes));
                break;

            case 6:
                Non_preemptive_priority(processes,ready_queue,1);
                printf("Avg waiting time = %f\n",avg_waiting_time(processes));
                printf("Avg turn around time = %f\n",avg_turn_around_time(processes));
                break;

            default: printf("Invalid option");
        }
        clear_processes(processes,ready_queue);

        printf("\nChoose an algorithm:\n\n");
        printf("1. First come first served.\n");
        printf("2. Shortest job first.\n");
        printf("3. Shortest remaining time first.\n");
        printf("4. Round Robin.\n");
        printf("5. Preemptive priority .\n");
        printf("6. Non preemptive Priority.\n");
        printf("7. Exit\n");
        scanf("%d",&choice);
    }



    return 0;
}
void clear_processes (ptr processes [num_processes], Queue ready_queue)
{
    set_processes(processes);
    ready_queue->next = NULL;

    for (int i=0 ; i<num_processes ; i++)
    {
        processes[i]->total_cpu_time = 0;
        processes[i]->Queue_waiting_time;
        processes[i]->total_waiting_queue_time =0 ;
        processes[i]->final_waiting_time =0;
        processes[i]->remaining_burst_time = processes[i]->burst_time;
        processes[i]->ready_queue_time = 0;
        processes[i]->state = 'N' ;
    }
}
int getSize (Queue Q)
{
    ptr p = Q->next;
    int c = 0;
    while(p != NULL)
    {
        c++;
        p=p->next;
    }
    return c;
}
void printQueue (Queue Q)
{
    pos p = Q->next;
    while(p != NULL)
    {
        printf("pid = %d",p->pid);
//        printf("arrival time = %d\n",p->arrival_time);
//        printf("burst time = %d\n",p->burst_time);
//        printf("come back time = %d\n",p->come_back_time);
        printf("priority = %d\n",p->priority);
//        p = p ->next;
//        printf("\n\n");
        p = p->next;
    }
}
void EnQueue (Queue Q, ptr newNode)
{
    pos p = Q;
    while(p->next != NULL)
    {
        p = p->next;
    }
    //Queue newNode = (Queue)malloc (sizeof(struct node));
    p->next = newNode;
    newNode->next = NULL;
}
ptr DeQueue (Queue Q)
{
    if(!isEmpty (Q))
    {
        pos p = Q->next;
        Q->next = p->next;
        return p;
    }
    else
        printf("Queue is empty\n");
    return NULL;
}
int isEmpty (Queue Q)
{
    return getSize(Q)==0;
}
//manual set of processes information
void set_processes (ptr processes [num_processes])
{
    processes[0]->pid = 1;
    processes[0]->arrival_time = 0;
    processes[0]->burst_time = 10;
    processes[0]->come_back_time = 2;
    processes[0]->priority = 300;

    processes[1]->pid = 2;
    processes[1]->arrival_time = 1;
    processes[1]->burst_time = 8;
    processes[1]->come_back_time = 4;
    processes[1]->priority = 300;

    processes[2]->pid = 3;
    processes[2]->arrival_time = 3;
    processes[2]->burst_time = 14;
    processes[2]->come_back_time = 6;
    processes[2]->priority = 300;

    processes[3]->pid = 4;
    processes[3]->arrival_time = 4;
    processes[3]->burst_time = 7;
    processes[3]->come_back_time = 8;
    processes[3]->priority = 300;

    processes[4]->pid = 5;
    processes[4]->arrival_time = 6;
    processes[4]->burst_time = 5;
    processes[4]->come_back_time = 3;
    processes[4]->priority = 300;

    processes[5]->pid = 6;
    processes[5]->arrival_time = 7;
    processes[5]->burst_time = 4;
    processes[5]->come_back_time = 6;
    processes[5]->priority = 300;

    processes[6]->pid = 7;
    processes[6]->arrival_time = 8;
    processes[6]->burst_time = 6;
    processes[6]->come_back_time = 9;
    processes[6]->priority = 300;

}
void FCFS (ptr processes [num_processes], Queue ready_queue)
{
    for(int i=0 ; i<num_processes ; i++)
    {
        if(processes[i]->arrival_time == 0)
        {
            processes[i]->state = 'R';
            EnQueue(ready_queue,processes[i]);
        }
    }

    int current_time=0;
    while(current_time < duration)
    {
        for(int j=0 ; j<num_processes ; j++) {
         if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
         {
             processes[j]->state = 'R';
             processes[j]->Queue_waiting_time = 0;
             EnQueue(ready_queue,processes[j]);
         }

         if(processes[j]->arrival_time == current_time)
         {
             EnQueue(ready_queue,processes[j]);
             processes[j]->state = 'R';
         }

        }
        ptr current_process = DeQueue(ready_queue);

        //drawing gantt chart
        printf("|%d  p%d",current_time,current_process->pid);
        for(int i=0 ; i< current_process->burst_time ; i++)
        {
            for(int j=0 ; j<num_processes ; j++)
            {
                if( processes[j]->pid == current_process->pid)
                    continue;

                if(processes[j]->arrival_time == current_time)
                {
                    EnQueue(ready_queue,processes[j]);
                    processes[j]->state = 'R';
                }
                if(processes[j]->state == 'W')
                {
                    if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
                    {
                        processes[j]->state = 'R';
                        processes[j]->Queue_waiting_time = 0;
                        EnQueue(ready_queue,processes[j]);
                    }
                    else
                    {
                        processes[j]->Queue_waiting_time ++;
                        processes[j]->total_waiting_queue_time++;
                    }
                }
            }
            if(current_time == duration )
            {
                break;
            }
            current_time++;
            current_process->total_cpu_time++;
        }
        printf("    %d|\n",current_time);
        current_process->final_waiting_time = current_process->total_waiting_queue_time;
        current_process->finish_time = current_time;
        current_process->state = 'W';
    }
}
ptr shortest_burst_time (Queue ready_queue)
{
    ptr p = ready_queue->next;
    int min = p->burst_time;
    ptr min_time_process = p;

    while (p != NULL)
    {
        if (p->burst_time < min)
        {
            min =  p->burst_time;
            min_time_process = p;
        }
        if(p != NULL)
            p = p->next;
    }
    return min_time_process;


}
void shortest_job_first(ptr processes [num_processes], Queue ready_queue)
{
    for(int i=0 ; i<num_processes ; i++)
    {
        if(processes[i]->arrival_time == 0)
        {
            processes[i]->state = 'R';
            EnQueue(ready_queue,processes[i]);
        }
    }

    int current_time=0;
    while(current_time < duration)
    {
        for(int j=0 ; j<num_processes ; j++)
        {
         if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
         {
             processes[j]->state = 'R';
             processes[j]->Queue_waiting_time = 0;
             EnQueue(ready_queue,processes[j]);
         }
         if(processes[j]->arrival_time == current_time)
                {
                    EnQueue(ready_queue,processes[j]);
                    processes[j]->state = 'R';
                }

        }

        ptr current_process = shortest_burst_time(ready_queue);

        //drawing gantt chart
        printf("|%d  p%d",current_time,current_process->pid);
        for(int i=0 ; i< current_process->burst_time ; i++)
        {
            for(int j=0 ; j<num_processes ; j++)
            {
                if( processes[j]->pid == current_process->pid)
                    continue;

                if(processes[j]->arrival_time == current_time)
                {
                    EnQueue(ready_queue,processes[j]);
                    processes[j]->state = 'R';
                }
                if(processes[j]->state == 'W')
                {
                    if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
                    {
                        processes[j]->state = 'R';
                        processes[j]->Queue_waiting_time = 0;
                        EnQueue(ready_queue,processes[j]);
                    }
                    else
                    {
                        processes[j]->Queue_waiting_time ++;
                        processes[j]->total_waiting_queue_time++;
                    }
                }
            }
            if(current_time == duration )
            {
                break;
            }
            current_time++;
            current_process->total_cpu_time++;
        }
        printf("    %d|\n",current_time);
        current_process->final_waiting_time = current_process->total_waiting_queue_time;
        current_process->finish_time = current_time;
        current_process->state = 'W';
        remove_from_queue(ready_queue,current_process->pid);
    }
}
float avg_waiting_time (ptr processes [num_processes])
{
    float total_waiting_time =0;
    int num_of_counted_processes= 0;
    for (int i=0 ; i< num_processes ; i++)
    {
        if(processes[i]->total_cpu_time != 0 )
        {
            total_waiting_time += processes[i]->finish_time - processes[i]->arrival_time - processes[i]->total_cpu_time - processes[i]->final_waiting_time;
            num_of_counted_processes ++;
        }
    }
    float result = total_waiting_time / num_of_counted_processes;
    return result;
}
float avg_turn_around_time (ptr processes [num_processes])
{
    float total_turnaround_time =0;
    int num_of_counted_processes= 0;
    for (int i=0 ; i< num_processes ; i++)
    {
        if(processes[i]->total_cpu_time != 0 )
        {
            total_turnaround_time += processes[i]->finish_time - processes[i]->arrival_time;
            num_of_counted_processes ++;
        }
    }
    float result = total_turnaround_time / num_of_counted_processes;
    return result;
}
void print_proecesses (ptr processes [num_processes])
{
    for(int i=0 ; i<num_processes ; i++)
    {
        printf("process no.%d: \n" ,i+1);
        printf(" pid = %d\n",processes[i]->pid);
        printf(" arrival time = %d\n",processes[i]->arrival_time);
        printf(" burst time = %d\n",processes[i]->burst_time);
        printf(" come back time = %d\n",processes[i]->come_back_time);
        printf(" priority = %d\n",processes[i]->priority);
        printf(" state = %c\n",processes[i]->state);
        printf("\n");
    }
}
void remove_from_queue (Queue ready_queue , int pid)
{
    if (ready_queue == NULL) {
        printf("Error, Queue is empty\n");
        return;
    }

    ptr temp = ready_queue;
    ptr prev = NULL;

    while (temp != NULL && temp->pid != pid) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Error, not found\n");
        return;
    }

    if (prev == NULL) {
        ready_queue = temp->next;
    } else {
        prev->next = temp->next;
    }

}
void shortest_remaining_time_first (ptr processes [num_processes], Queue ready_queue,int gant_chart [duration])
{
    for(int i=0 ; i<num_processes ; i++)
    {
        processes[i]->remaining_burst_time = processes[i]->burst_time;
        if(processes[i]->arrival_time == 0)
        {
            processes[i]->state = 'R';
            EnQueue(ready_queue,processes[i]);
        }
    }

    int current_time =0;
    int i=0;
    while(current_time < duration)
    {
        for(int j=0 ; j<num_processes ; j++)
        {
         if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
         {
             processes[j]->state = 'R';
             processes[j]->Queue_waiting_time = 0;
             EnQueue(ready_queue,processes[j]);
         }
         if(processes[j]->arrival_time == current_time)
         {
            EnQueue(ready_queue,processes[j]);
            processes[j]->state = 'R';
         }

        }

        ptr current_process = shortest_remainig_time_process(ready_queue);
        gant_chart[i++] = current_process->pid;

        current_process->remaining_burst_time --;
        current_process->total_cpu_time++;

        for(int j=0 ; j<num_processes ; j++)
        {
            if( processes[j]->pid == current_process->pid)
                continue;

            if(processes[j]->arrival_time == current_time)
            {
                EnQueue(ready_queue,processes[j]);
                processes[j]->state = 'R';
            }
            if(processes[j]->state == 'W')
            {
                if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
                {
                    processes[j]->state = 'R';
                    processes[j]->Queue_waiting_time = 0;
                    EnQueue(ready_queue,processes[j]);
                }
                else
                {
                    processes[j]->Queue_waiting_time ++;
                    processes[j]->total_waiting_queue_time++;
                }
            }
        }

        if(current_process->remaining_burst_time == 0)
        {
            current_process->state = 'W';
            current_process->remaining_burst_time = current_process->burst_time;
            remove_from_queue(ready_queue,current_process->pid);
        }

        if(current_time == duration )
        {
            break;
        }
        current_time++;
        current_process->final_waiting_time = current_process->total_waiting_queue_time;
        current_process->finish_time = current_time;
    }

}
ptr shortest_remainig_time_process (Queue ready_queue)
{
    ptr p = ready_queue->next;
    int min = p->remaining_burst_time;
    ptr min_time_process = p;

    while (p != NULL)
    {
        if (p->remaining_burst_time < min)
        {
            min =  p->remaining_burst_time;
            min_time_process = p;
        }
        if(p != NULL)
            p = p->next;
    }
    return min_time_process;


}
void preemptive_gantt_chart_drawing (int gantt_chart [duration])
{
     for(int i=0 ; i< duration ; i++)
    {
        printf("|%d   p%d",i,gantt_chart[i]);
        while ( gantt_chart[i] == gantt_chart[i+1])
        {
            i++;
        }
        printf("    %d|\n",i+1);

    }

}
Round_robin(ptr processes [num_processes], Queue ready_queue, int q)
{
    for(int i=0 ; i<num_processes ; i++)
    {
        processes[i]->remaining_burst_time = processes[i]->burst_time;
        if(processes[i]->arrival_time == 0)
        {
            processes[i]->state = 'R';
            EnQueue(ready_queue,processes[i]);
        }
    }

    int current_time=0;
    while(current_time < duration)
    {
        for(int j=0 ; j<num_processes ; j++)
        {
         if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
         {
             processes[j]->state = 'R';
             processes[j]->Queue_waiting_time = 0;
             EnQueue(ready_queue,processes[j]);
         }
         if(processes[j]->arrival_time == current_time)
         {
             EnQueue(ready_queue,processes[j]);
             processes[j]->state = 'R';
         }

        }

        ptr current_process = DeQueue(ready_queue);

        //drawing gantt chart
        printf("|%d  p%d",current_time,current_process->pid);
        for(int i=0 ; i<q ; i++)
        {
            for(int j=0 ; j<num_processes ; j++)
            {
                if( processes[j]->pid == current_process->pid)
                    continue;

                if(processes[j]->arrival_time == current_time)
                {
                    EnQueue(ready_queue,processes[j]);
                    processes[j]->state = 'R';
                }
                if(processes[j]->state == 'W')
                {
                    if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
                    {
                        processes[j]->state = 'R';
                        processes[j]->Queue_waiting_time = 0;
                        EnQueue(ready_queue,processes[j]);
                    }
                    else
                    {
                        processes[j]->Queue_waiting_time ++;
                        processes[j]->total_waiting_queue_time++;
                    }
                }
            }
            if(current_time == duration )
            {
                break;
            }

            current_time++;
            current_process->remaining_burst_time--;
            current_process->total_cpu_time++;

            if(current_process->remaining_burst_time == 0)
            {
                current_process->state = 'W';
                current_process->remaining_burst_time = current_process->burst_time;
                break;
            }
        }
        printf("    %d|\n",current_time);
        current_process->final_waiting_time = current_process->total_waiting_queue_time;
        current_process->finish_time = current_time;

        if(current_process->state != 'W')
            EnQueue(ready_queue,current_process);


    }
}
void Non_preemptive_priority(ptr processes [num_processes], Queue ready_queue, int age)
{
     for(int i=0 ; i<num_processes ; i++)
    {
        processes[i]->ready_queue_time =0;
        if(processes[i]->arrival_time == 0)
        {
            processes[i]->state = 'R';
            EnQueue(ready_queue,processes[i]);
        }
    }

    int current_time=0;
    while(current_time < duration)
    {
        for(int j=0 ; j<num_processes ; j++)
        {
         if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
         {
             processes[j]->state = 'R';
             processes[j]->Queue_waiting_time = 0;
             EnQueue(ready_queue,processes[j]);
         }
         if(processes[j]->arrival_time == current_time)
                {
                    EnQueue(ready_queue,processes[j]);
                    processes[j]->state = 'R';
                }

        }

        ptr current_process = highest_priority(ready_queue);

        //drawing gantt chart
        printf("|%d  p%d",current_time,current_process->pid);
        for(int i=0 ; i< current_process->burst_time ; i++)
        {
            for(int j=0 ; j<num_processes ; j++)
            {
                if( processes[j]->pid == current_process->pid)
                    continue;

                if(processes[j]->arrival_time == current_time)
                {
                    EnQueue(ready_queue,processes[j]);
                    processes[j]->state = 'R';
                }
                if(processes[j]->state == 'W')
                {
                    if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
                    {
                        processes[j]->state = 'R';
                        processes[j]->Queue_waiting_time = 0;
                        EnQueue(ready_queue,processes[j]);
                    }
                    else
                    {
                        processes[j]->Queue_waiting_time ++;
                        processes[j]->total_waiting_queue_time++;
                    }
                }
                if(processes[j]->state == 'R')
                {
                    if(processes[j]->ready_queue_time == age && processes[j]->priority !=0)
                    {
                        processes[j]->priority--;
                        processes[j]->ready_queue_time =0;
                    }
                    else
                        processes[j]->ready_queue_time++;
                }
            }
            if(current_time == duration )
            {
                break;
            }
            current_time++;
            current_process->total_cpu_time++;
        }
        printf("    %d|\n",current_time);
        current_process->final_waiting_time = current_process->total_waiting_queue_time;
        current_process->finish_time = current_time;
        current_process->state = 'W';
        remove_from_queue(ready_queue,current_process->pid);
    }

}
ptr highest_priority(Queue ready_queue)
{
    ptr p = ready_queue->next;
    int min = p->priority;
    ptr min_priority_process = p;

    while (p != NULL)
    {
        if (p->priority < min)
        {
            min =  p->priority;
            min_priority_process = p;
        }
        if(p != NULL)
            p = p->next;
    }
    return min_priority_process;
}

void preemptive_priority(ptr processes [num_processes], Queue ready_queue, int age,int gant_chart [duration])
{
    ptr current_process = processes[0];

    for(int i=0 ; i<num_processes ; i++)
    {
        processes[i]->ready_queue_time =0;
        processes[i]->remaining_burst_time = processes[i]->burst_time;
        if(processes[i]->arrival_time == 0)
        {
            processes[i]->state = 'R';
            EnQueue(ready_queue,processes[i]);
        }
    }

    int current_time =0;
    int i=0;
    while(current_time < duration)
    {
        for(int j=0 ; j<num_processes ; j++)
        {
         if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
         {
             processes[j]->state = 'R';
             processes[j]->Queue_waiting_time = 0;
             EnQueue(ready_queue,processes[j]);
         }
         if(processes[j]->arrival_time == current_time)
         {
            EnQueue(ready_queue,processes[j]);
            processes[j]->state = 'R';
         }
         if(processes[j]->state == 'R')
            {
                if(processes[j]->ready_queue_time == age && processes[j]->priority !=0)
                {
                    processes[j]->priority--;
                    processes[j]->ready_queue_time =0;
                }
            }
        }

        ptr newProc = highest_priority(ready_queue);
        if(newProc->priority < current_process->priority && current_process->state != 'W')
            current_process = newProc;

        if (current_process->state == 'W')
            current_process = newProc;

        gant_chart[i++] = current_process->pid;

        current_process->remaining_burst_time --;
        current_process->total_cpu_time++;

        for(int j=0 ; j<num_processes ; j++)
        {
            if( processes[j]->pid == current_process->pid)
                continue;

            if(processes[j]->arrival_time == current_time)
            {
                EnQueue(ready_queue,processes[j]);
                processes[j]->state = 'R';
            }
            if(processes[j]->state == 'W')
            {
                if(processes[j]->Queue_waiting_time == processes[j]->come_back_time)
                {
                    processes[j]->state = 'R';
                    processes[j]->Queue_waiting_time = 0;
                    EnQueue(ready_queue,processes[j]);
                }
                else
                {
                    processes[j]->Queue_waiting_time ++;
                    processes[j]->total_waiting_queue_time++;
                }
            }
            if(processes[j]->state == 'R')
            {
                if(processes[j]->ready_queue_time == age && processes[j]->priority !=0)
                {
                    processes[j]->priority--;
                    processes[j]->ready_queue_time =0;
                }
                else
                    processes[j]->ready_queue_time++;
            }
        }

        if(current_process->remaining_burst_time == 0)
        {
            current_process->state = 'W';
            current_process->remaining_burst_time = current_process->burst_time;
            remove_from_queue(ready_queue,current_process->pid);
        }

        if(current_time == duration )
        {
            break;
        }
        current_time++;
        current_process->final_waiting_time = current_process->total_waiting_queue_time;
        current_process->finish_time = current_time;
    }
}





