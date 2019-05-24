#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Digimon database!
 * Don't forget to handle invalid inputs (NULL pointers, invalid values etc.)
 */

enum digilevel {BABY, INTRAINING, ROOKIE, CHAMPION, ULTIMATE, MEGA};
char *level_to_string(enum digilevel level);

typedef struct Digimons {
    char name[128];
    int age;
    float health;
    char tamer_name[256];
    enum digilevel level;
} Digimon;


//Get minimum health index
int minimal_health_digi_index(Digimon *digis, int digis_count);

//Get number of digis at a level
int digis_at_level(Digimon *digis, int digis_count, enum digilevel level);

//Get digis owned by a tamer
int digis_by_tamer(Digimon *digis, int digis_count, char *tamer);

//Get average health of digis by tamer
float avg_digi_health_by_tamer(Digimon *digis, int digis_count, char *tamer);

void print_digi(Digimon d);

int main()
{
    Digimon digimons[100];
    srand(time(0));

    //build digis
    for (int i = 0; i < 100; i++){
        Digimon d;
        d.age = (rand() % 100) + 1; //generate an age between 0 & 100;
        d.health = ((rand() % 10000) + 1) / 100.0; //generate an age between 0 & 100;
        d.level = rand() % 6;
        strcpy(d.tamer_name, rand() % 2 == 0 ? "Jesse Smith" : "John Doe");
        digimons[i] = d;
    }

    int digi_count = sizeof(digimons) / sizeof(Digimon);

    //Check on my digis
    for (int i = 0; i < digi_count; i++){
        printf("digi %d: ", i);
        print_digi(digimons[i]);
    }

    printf("\nSickest Digi: ");
    print_digi(digimons[minimal_health_digi_index(digimons, digi_count)]);
    printf("\n");

    for (int x = 0; x < 6; x++){
        printf("Number of digis at level %s: %d\n", level_to_string(x), digis_at_level(digimons, digi_count, x));
    }

    printf("\nNumber of digis owned by Jesse Smith: %d\n", digis_by_tamer(digimons, digi_count, "Jesse Smith"));

    printf("\nAverage health of digis owned by Jesse Smith: %0.2f\n", avg_digi_health_by_tamer(digimons, digi_count, "Jesse Smith"));

    return 0;
}

char *level_to_string(enum digilevel level)
{
    switch (level) {
        case BABY:
            return "BABY";
        case INTRAINING:
            return "IN_TRAINING";
        case ROOKIE:
            return "ROOKIE";
        case CHAMPION:
            return "CHAMPION";
        case ULTIMATE:
            return "ULTIMATE";
        case MEGA:
            return "MEGA";
    }

}

float avg_digi_health_by_tamer(Digimon *digis, int digis_count, char *tamer)
{
    float cummulative_health = 0;

    for (int i = 1; i < digis_count; i++){
        if(strcmp(digis[i].tamer_name, "Jesse Smith"))
            cummulative_health += digis[i].health;
    }
    return cummulative_health;
}

int digis_by_tamer(Digimon *digis, int digis_count, char *tamer)
{
    int count = 0;

    for (int i = 1; i < digis_count; i++){
        if(strcmp(digis[i].tamer_name, "Jesse Smith"))
            count++;
    }
    return count;
}

int digis_at_level(Digimon *digis, int digis_count, enum digilevel level)
{
    int count = 0;

    for (int i = 1; i < digis_count; i++){
        if(digis[i].level == level)
            count++;
    }
    return count;
}

int minimal_health_digi_index(Digimon *digis, int digis_count)
{
    int sickest_digi_index = 0;
    for (int i = 1; i < digis_count; i++){
        if(digis[i].health < digis[sickest_digi_index].health)
            sickest_digi_index = i;
    }
    return sickest_digi_index;
}

void print_digi(Digimon d)
{
    printf("age - %d, health - %0.2f, level - %d\n", d.age, d.health, d.level);
}