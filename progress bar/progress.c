#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

const int bar_length = 50, MAX_TASKS = 5;
void print_bar();
void clear_screen();

typedef struct
{
    int id;
    int progress;
    int step;
} Task;

void print_bar(Task task)
{

    printf("\nTask %d: [", task.id);

    int bar_to_show = (task.progress * bar_length) / 100;

    for (int i = 0; i < bar_length; i++)
    {
        if (i < bar_to_show)
            printf("=");
        else
            printf(" ");
    }
    printf("] %d%%", task.progress);
}

void clear_screen(void)
{
#ifdef _WIN32
    system("cls"); 
#else
    system("clear"); 
#endif

}

int main()
{
    Task tasks[MAX_TASKS];

    srand(time(NULL));
    for (int i = 0; i < MAX_TASKS; i++)
    {
        tasks[i].id = i + 1;
        tasks[i].progress = 0;
        tasks[i].step = rand()%5+1;
    }

    int task_incomplete = 1;
    while (task_incomplete)
    {
        clear_screen();
        task_incomplete = 0;
        for (int i = 0; i < MAX_TASKS; i++)
        {
            tasks[i].progress += tasks[i].step;
            if (tasks[i].progress > 100)
                tasks[i].progress = 100;
            else if (tasks[i].progress < 100)
            {
                task_incomplete = 1;
            }
            print_bar(tasks[i]);
        }

        sleep(1);
    }
    printf("\nAll Task Completed!\n");
    return 0;
}