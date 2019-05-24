#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* Create a smartphone register application
 * Read the content of smartphones.txt and store the informations in a structure called "smartphone:
 * - the name of the gadget (which is shorter than 256 characters) (Don't bother with the underscore('_') character, it's the part of the name)
 * - the year of the release (e.g. 2016)
 * - the type of the screen size (as a custom type, see below)
 *
 * In the in_file the size is given in cm but you should store the screen size type in an enumeration ("screen_size"),
 * the valid types are:
 *  - BIG -> (>= 15 cm)
 *  - MEDIUM -> (>= 12 cm)
 *  - SMALL -> (< 12 cm)
 *
 * The smartphones should be stored in an array.
 *
 * Implement the following functions:
 * - get_oldest_phone()
 *    - it should return the name of oldest device
 *    - it is up to you how your function declaration looks like (return type and arguments)
 * - get_screen_size_num_phones()
 *    - it returns the num_phones of phones which has "screen_size" size
 *    - it is up to you how your function declaration looks like (return type and arguments)
 *
 * Your main function should invoke these functions and print the following:
 * The ..... is the oldest device in the database
 * There are .... phones with BIG (>= 15 cm) screen size
 * There are .... phones with SMALL (< 12 cm) screen size
 *
 *
 * Additionally, you need to create a new in_file(prices.txt) that looks like this:
 * <NAME> <PRICE>
 * <NAME> <PRICE>
 * .
 * .
 * .
 *
 * To calculate the price use the following method. The base price of every phone is 300$.
 * If the size is SMALL, that adds 0$ to the value
 * If the size is MEDIUM, that adds 100$ to the value
 * If the size is BIG, that doubles the base price.
 *
 * The price also depends on the age. For every year that passed since its release,
 * the phone loses 50$ but the maximum value that it can lose because of the age is 250$
 */
#define CHUNK 1024 /* read 1024 bytes at a time */

enum PhoneScreenType {BIG, MEDIUM, SMALL};

typedef struct phone_s {
    char name[256];
    int year;
    enum PhoneScreenType type;
} Phone;

int get_oldest_phone(Phone *phones, int num_phones);

int get_screen_size_num_phones(Phone *phones, int num_phones, enum PhoneScreenType type);

int main()
{
    char buf[CHUNK];
    FILE *in_file;
    FILE *out_file;
    int num_phones = 0;

    Phone phones[100];

    in_file = fopen("/Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/phones.txt", "r");
    if (in_file) {
        for (num_phones = 0; fgets(buf, CHUNK, in_file); num_phones++) {
            Phone phone;
            char *ptr = malloc((char) 50); //Give enough space to copy junk into so i'm not bashing unknown memory space

            char *in_name = strtok(buf, " ");
            char *in_year = strtok(NULL, " ");
            char *in_size = strtok(NULL, " ");

            strcpy(phone.name, in_name);
            phone.year = strtol(in_year, &ptr, 10);

            int size = strtol(in_size, &ptr, 10);
            if (size >= 15)
                phone.type = BIG;
            else if (size >= 12)
                phone.type = MEDIUM;
            else
                phone.type = SMALL;

            phones[num_phones] = phone;
        }

        fclose(in_file);
    }

    Phone oldest = phones[get_oldest_phone(phones, num_phones)];

    printf("\nThe %s is the oldest device in the database\n", oldest.name);

    printf("\nThere are %d phones with BIG (>= 15 cm) screen size\n", get_screen_size_num_phones(phones, num_phones, BIG));
    printf("There are %d phones with MEDIUM (12 cm -> 15 cm) screen size\n", get_screen_size_num_phones(phones, num_phones, MEDIUM));
    printf("There are %d phones with SMALL (< 12 cm) screen size\n", get_screen_size_num_phones(phones, num_phones, SMALL));

    out_file = fopen("/Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/prices.txt", "w");
    if (out_file) {
        for (int i = 1; i < num_phones; i++) {
            int price = 300;
            switch (phones[i].type){
                case MEDIUM:
                    price += 100;
                    break;
                case BIG:
                    price *= 2;
                    break;
                case SMALL:
                    break;
            }

            int age = 2019 - phones[i].year <= 5 ? 2019 - phones[i].year : 5;
            price -= age * 50;


            {
                char out_string[100];
                sprintf(out_string, "%s %d\n", phones[i].name, price);
                fputs(out_string, out_file);
            }

        }
        fclose(out_file);
    }

    return 0;
}

//return index of oldest phone
int get_oldest_phone(Phone *phones, int num_phones)
{
    int index = 0;
    for (int i = 1; i < num_phones; i++) {
        if (phones[i].year < phones[index].year)
            index = i;
    }
    return index;
}

int get_screen_size_num_phones(Phone *phones, int num_phones, enum PhoneScreenType type)
{
    int count = 0;
    for (int i = 1; i < num_phones; i++) {
        if (phones[i].type == type)
            count++;
    }
    return count;
}