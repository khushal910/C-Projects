#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void fill_time(char *buffer, int format);
void fill_date(char *buffer);
int input_format();
void clear_screen();

int input_format()
{
    int format;
    printf("\nChoose the time fram\n1. 24 Hour format \n2. 12 Hour format\nEnert your choice:");
    scanf("%d", &format);
    return format;
}

void fill_time(char *buffer, int format)
{
    time_t row_time;
    struct tm *current_time;

    time(&row_time);                     // store the second from 1970 in row_time
    current_time = localtime(&row_time); // convert row_time into the human‐readable year, month, day, hour, minute, etc., in my local zone.

    if (format == 1)
        strftime(buffer, 50, "%H:%M:%S", current_time);
    else
        strftime(buffer, 50, "%I:%M:%S %p", current_time);
}

void fill_date(char *buffer)
{
    time_t row_time;
    struct tm *current_time;

    time(&row_time);
    current_time = localtime(&row_time);
    strftime(buffer, 50, "%A %B %d %Y", current_time);
}


void clear_screen(void)
{
#ifdef _WIN32
    system("cls"); // run cls command in terminal if window
#else
    system("clear"); // run clear command in terminal if mac
#endif

}

int main()
{
    char time[50], date[50];
    int format = input_format();
    while (1)
    {
        clear_screen();
        
        fill_time(time, format);
        fill_date(date);

        printf("\nCurrent Time: %s \n", time);
        printf("Date: %s\n", date);

        sleep(1); // sleep for 1 second
    }
    return 0;
}