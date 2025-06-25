#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "birthdays.h"

// Converte "YYYY-MM-DD" in struct tm
static int parse_date(const char *birthdate, struct tm *out)
{
    return sscanf(birthdate, "%4d-%2d-%2d", &out->tm_year, &out->tm_mon, &out->tm_mday) == 3;
}

// Restituisce 1 se il compleanno è entro 30 giorni
int is_upcoming_birthday(const char *birthdate)
{
    if (!birthdate)
        return 0;

    time_t now = time(NULL);
    struct tm today = *localtime(&now);
    struct tm bday;

    if (!parse_date(birthdate, &bday))
        return 0;

    bday.tm_year = today.tm_year;  // considera quest'anno
    bday.tm_mon -= 1;              // tm_mon è 0-based

    time_t bday_time = mktime(&bday);
    if (bday_time == -1) return 0;

    double diff = difftime(bday_time, now) / (60 * 60 * 24);
    return diff >= 0 && diff <= 30;
}

void show_upcoming_birthdays(t_contact_list *list)
{
    printf("Upcoming birthdays in the next 30 days:\n");
    for (int i = 0; i < list->size; i++)
    {
        t_contact *c = list->array[i];
        if (is_upcoming_birthday(c->birthdate))
        {
            printf("[%d] %s - %s\n", c->id, c->name, c->birthdate);
        }
    }
}
