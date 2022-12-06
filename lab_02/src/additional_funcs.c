#include "../inc/additional_funcs.h"
#include "../inc/return_codes.h"

#include <string.h>
#include <ctype.h>
#include <stdio.h>

size_t check_birthday(const size_t day, const size_t mounth, const size_t year)
{
    size_t rc; // код возврата

    if (day > 0 && day <= 31)
        if (mounth > 0 && mounth <= 12)
            if (year > 0 && year <= 2022)
                rc = OK;
            else
                rc = BIRTHDAY_ERROR;
        else
            rc = BIRTHDAY_ERROR;
    else
        rc = BIRTHDAY_ERROR;

    return rc;
}

void copy_struct(subscriber_t *temp_subs, const subscriber_t *subs, const size_t size)
{
    for (size_t index = 0; index < size; index++)
    {
        strcpy(temp_subs[index].last_name, subs[index].last_name);
        strcpy(temp_subs[index].first_name, subs[index].first_name);
        temp_subs[index].phone = subs[index].phone;
        strcpy(temp_subs[index].street, subs[index].street);
        strcpy(temp_subs[index].house, subs[index].house);
        temp_subs[index].status = subs[index].status;
        
        if (subs[index].status == personal)
        {
            temp_subs[index].subs_info.person_info.birthday.day = subs[index].subs_info.person_info.birthday.day;
            temp_subs[index].subs_info.person_info.birthday.month = subs[index].subs_info.person_info.birthday.month;
            temp_subs[index].subs_info.person_info.birthday.year = subs[index].subs_info.person_info.birthday.year;
        }
        else
        {
            strcpy(temp_subs[index].subs_info.company_info.position, subs[index].subs_info.company_info.position);
            strcpy(temp_subs[index].subs_info.company_info.name, subs[index].subs_info.company_info.name);
        }
    }
}

void create_key_arr(subscriber_t *subs, key_t *key, size_t const size)
{
    for (size_t index = 0; index < size; index++)
    {
        key[index].key = subs[index].phone;
        key[index].cout = index;
    }
}