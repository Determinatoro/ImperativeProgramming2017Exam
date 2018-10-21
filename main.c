#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*******************************************/
/* DATATYPES */
/*******************************************/

struct race_data {
    char race[28];
    char name[48];
    char first_name[31];
    char last_name[51];
    int age;
    char team[4];
    char country[4];
    char ranking[4];
    char time[9];
    int score;
};
typedef struct race_data RACE_DATA;

struct rider_data {
    char name[48];
    char first_name[31];
    char last_name[51];
    int age;
    char team[4];
    char country[4];
    int total_score;
};
typedef struct rider_data RIDER_DATA;

struct team_data {
    char name[4];
    int riders_out;
};
typedef struct team_data TEAM_DATA;

struct nation_data {
    char name[4];
    int total_score;
    int total_age;
};
typedef struct nation_data NATION_DATA;

typedef struct tm TIME_DATA;

/******************************************/
/* PROTOTYPES */
/******************************************/

int is_upper_case(const char *);

void trim_end(char *, int);

int count_lines_in_file(char *);

FILE *open_file(int *, char *);

int get_riders_who_has_completed_the_race(int, RACE_DATA *, RACE_DATA *, char *);

int get_number_of_riders_who_completed_the_race(int, RACE_DATA *, char *);

int get_nations(int, RIDER_DATA *, NATION_DATA *);

int get_races(int, RACE_DATA *, char **);

int get_teams(int, RIDER_DATA *, TEAM_DATA *);

int print_race_data_for_rider(RACE_DATA, int);

int print_rider_data(RIDER_DATA, int format);

int read_race_data_file(char *, RACE_DATA **, int *, RIDER_DATA **, int *);

void print_all_belgian_riders_under_23(int, RACE_DATA *);

void print_all_danish_riders_who_has_participated_in_one_or_more_of_the_races(int, RACE_DATA *);

void print_the_10_riders_who_got_the_most_points(int, RIDER_DATA *);

void print_for_each_of_the_races_which_team_who_has_the_most_riders_as_OTL_or_DNF(int, int, RIDER_DATA *, RACE_DATA *);

void print_the_nation_with_the_most_points(int, RIDER_DATA *);

void print_the_median_time_for_each_race(int, RACE_DATA *, int);

/******************************************/
/* VARIABLES */
/******************************************/

/* File name for the file containing all the race data */
#define FILE_NAME "cykelloeb-2017.txt"

/******************************************/
/* MAIN */
/******************************************/
int main(int argc, char *argv[]) {
    int race_data_array_counter, rider_data_array_counter;
    RACE_DATA *race_data_array;
    RIDER_DATA *rider_data_array;
    char input[5];

    if (!read_race_data_file(FILE_NAME, &race_data_array, &race_data_array_counter, &rider_data_array,
                             &rider_data_array_counter)) {
        return 0;
    }

    /* Print all statistics if given the command "--print" */
    if (argc > 1 && strcmp(argv[1], "--print") == 0) {
        print_all_belgian_riders_under_23(race_data_array_counter, race_data_array);
        printf("\n\n");
        print_all_danish_riders_who_has_participated_in_one_or_more_of_the_races(race_data_array_counter,
                                                                                 race_data_array);
        printf("\n\n");
        print_the_10_riders_who_got_the_most_points(rider_data_array_counter, rider_data_array);
        printf("\n\n");
        print_for_each_of_the_races_which_team_who_has_the_most_riders_as_OTL_or_DNF(rider_data_array_counter,
                                                                                     race_data_array_counter,
                                                                                     rider_data_array, race_data_array);
        printf("\n\n");
        print_the_nation_with_the_most_points(rider_data_array_counter, rider_data_array);
        printf("\n\n");
        print_the_median_time_for_each_race(race_data_array_counter, race_data_array, 1);
        printf("\n\nPress [ENTER] to Continue...\n");
        fflush(stdout);
        getchar();
    } else {
        int run_program = 1;

        while (run_program) {
            int run_commands = 1;

            printf("//////////////////////////////////////////\n\n");
            printf("   WELCOME TO THE CYCLING RACE MANAGER    \n");
            printf("            ____     ___				  \n");
            printf("              \\       \\				  \n");
            printf("               \\_______\\				  \n");
            printf("               /\\      /\\				  \n");
            printf("         _____/  \\    /  \\_____		  \n");
            printf("        /    /\\   \\  /   /\\    \\	  \n");
            printf("       /    /__\\___\\/   /  \\    \\	  \n");
            printf("       \\       /        \\       /		  \n");
            printf("        \\_____/          \\_____/		  \n\n");
            printf("//////////////////////////////////////////\n\n");

            printf("Type a number or a command\n\n");
            printf("1     | Belgian riders under 23\n");
            printf("2     | Danish riders who anticipated in one or more of the races\n");
            printf("3     | The 10 riders who got the most points\n");
            printf("4     | Team who has the most riders as OTL or DNF in each race\n");
            printf("5     | The nation with the most points\n");
            printf("6     | The median time for each race\n");
            printf("clear | Clear all content on the screen\n");
            printf("exit  | Exit the program\n");

            while (run_commands) {
                printf("\nCommand: ");
                scanf("%5s", input);

                if (strcmp(input, "exit") == 0) {
                    run_program = 0;
                    run_commands = 0;
                } else if (strcmp(input, "clear") == 0) {
                    system("clear");
                    run_commands = 0;
                } else {
                    switch (atoi(input)) {
                        case 1:
                            printf("\n");
                            print_all_belgian_riders_under_23(race_data_array_counter, race_data_array);
                            break;
                        case 2:
                            printf("\n");
                            print_all_danish_riders_who_has_participated_in_one_or_more_of_the_races(
                                    race_data_array_counter, race_data_array);
                            break;
                        case 3:
                            printf("\n");
                            print_the_10_riders_who_got_the_most_points(rider_data_array_counter, rider_data_array);
                            break;
                        case 4:
                            printf("\n");
                            print_for_each_of_the_races_which_team_who_has_the_most_riders_as_OTL_or_DNF(
                                    rider_data_array_counter, race_data_array_counter,
                                    rider_data_array, race_data_array);
                            break;
                        case 5:
                            printf("\n");
                            print_the_nation_with_the_most_points(rider_data_array_counter, rider_data_array);
                            break;
                        case 6:
                            printf("\n");
                            print_the_median_time_for_each_race(race_data_array_counter, race_data_array, 1);
                            break;
                        default:
                            printf("\nCommand not found\n");
                            break;
                    }
                }
            }
        }
    }

    free(race_data_array);
    free(rider_data_array);

    return 1;
}

/*******************************************/
/* FUNCTIONS */
/*******************************************/

/***********************************/
/* TOOL FUNCTIONS */
/***********************************/

/* Check if a string only has upper case letters */
int is_upper_case(const char *input_string) {
    int i;

    int len = (int) strlen(input_string);
    for (i = 0; i < len; i++) {
        if (input_string[i] >= 'a' && input_string[i] <= 'z') {
            return 0;
        }
    }

    return 1;
}

/* Trim end of string from ' ' and '0' */
void trim_end(char *str, int size_of_string) {
    int i;

    for (i = size_of_string - 1; i >= 0; i--) {
        if (str[i] == ' ')
            str[i] = '\0';
        else
            break;
    }
}

/* Count lines in a file */
int count_lines_in_file(char *file_name) {
    int ch = 0, lines = 0;
    FILE *fp;

    fp = fopen(file_name, "r");

    if (fp == NULL) {
        return 0;
    }

    lines++;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            lines++;
    }

    return lines;
}

/* Open a file and count the lines */
FILE *open_file(int *number_of_lines, char *file_name) {
    FILE *fp;

    *number_of_lines = count_lines_in_file(file_name);

    fp = fopen(file_name, "r");

    if (fp == NULL) {
        printf("\nCould not read file: \"%s\"\n", file_name);
        return NULL;
    }

    return fp;
}

/***********************************/
/* HELPER FUNCTIONS */
/***********************************/

/* Get riders who completed a given race */
int
get_riders_who_has_completed_the_race(int race_data_array_counter, RACE_DATA *race_data_array,
                                      RACE_DATA *race_data_array_single_race,
                                      char *race) {
    int i, race_data_array_single_race_counter;
    RACE_DATA race_data;

    race_data_array_single_race_counter = 0;

    for (i = 0; i < race_data_array_counter; i++) {
        race_data = race_data_array[i];
        if (strcmp(race_data.race, race) == 0 && strcmp(race_data.ranking, "OTL") != 0 &&
            strcmp(race_data.ranking, "DNF") != 0) {
            race_data_array_single_race[race_data_array_single_race_counter++] = race_data;
        }
    }

    return race_data_array_single_race_counter;
}

/* Get number of riders who completed a given race */
int get_number_of_riders_who_completed_the_race(int race_data_array_counter, RACE_DATA *race_data_array,
                                                char *race) {
    int i, number;
    RACE_DATA race_data;

    number = 0;

    for (i = 0; i < race_data_array_counter; i++) {
        race_data = race_data_array[i];
        if (strcmp(race_data.race, race) == 0 && strcmp(race_data.ranking, "OTL") != 0 &&
            strcmp(race_data.ranking, "DNF") != 0)
            number++;
    }

    return number;
}

/* Get all the nations in the races */
int get_nations(int rider_data_array_counter, RIDER_DATA *rider_data_array, NATION_DATA *nations) {
    int i, j, nations_counter;
    NATION_DATA nation;

    nations_counter = 0;

    for (i = 0; i < rider_data_array_counter; i++) {
        int already_contains_nation = 0;
        for (j = 0; j < nations_counter; j++) {
            if (strcmp(nations[j].name, rider_data_array[i].country) == 0)
                already_contains_nation = 1;
        }

        if (!already_contains_nation) {
            strcpy(nation.name, rider_data_array[i].country);
            nations[nations_counter++] = nation;
        }
    }

    return nations_counter;
}

/* Get all the race names */
int get_races(int race_data_array_counter, RACE_DATA *race_data_array, char **race_names) {
    int i, j, race_names_counter;

    race_names_counter = 0;

    for (i = 0; i < race_data_array_counter; i++) {
        int already_contains_race_name = 0;
        for (j = 0; j < race_names_counter; j++) {
            if (strcmp(race_names[j], race_data_array[i].race) == 0) {
                already_contains_race_name = 1;
                break;
            }
        }

        if (!already_contains_race_name) {
            if (strcmp(race_data_array[i].race, "") != 0)
                race_names[race_names_counter++] = race_data_array[i].race;
        }
    }

    return race_names_counter;
}

/* Get all the teams */
int get_teams(int rider_data_array_counter, RIDER_DATA *rider_data_array, TEAM_DATA *team_data_array) {
    int i, j, team_data_array_counter;
    TEAM_DATA team_data;

    team_data_array_counter = 0;

    for (i = 0; i < rider_data_array_counter; i++) {
        int already_contains_team = 0;
        for (j = 0; j < team_data_array_counter; j++) {
            if (strcmp(team_data_array[j].name, rider_data_array[i].team) == 0)
                already_contains_team = 1;
        }

        if (!already_contains_team) {
            strcpy(team_data.name, rider_data_array[i].team);
            team_data_array[team_data_array_counter++] = team_data;
        }
    }

    return team_data_array_counter;
}

/* Print race data */
int print_race_data_for_rider(RACE_DATA race_data, int format) {
    switch (format) {
        case 0:
            printf("%-27s%-47s%-4d%-4s%-4s%-4s%-9s%-3d\n", race_data.race, race_data.name, race_data.age,
                   race_data.team,
                   race_data.country, race_data.ranking, race_data.time, race_data.score);
            break;
        case 1:
            printf("%-47s%-4d%-4s\n", race_data.name, race_data.age, race_data.team);
            break;
        default:
            break;
    }

    return 0;
}

/* Print rider data */
int print_rider_data(RIDER_DATA rider_data, int format) {
    switch (format) {
        case 0:
            printf("%-47s%-4d%-4s%-4s%-4d\n", rider_data.name, rider_data.age, rider_data.team, rider_data.country,
                   rider_data.total_score);
            break;
        default:
            break;
    }

    return 0;
}

/* Read race data file */
int read_race_data_file(char *file_name, RACE_DATA **temp_race_data_array, int *temp_race_data_array_counter,
                        RIDER_DATA **temp_rider_data_array, int *temp_rider_data_array_counter) {
    int i, j, rider_data_array_counter = 0, race_data_array_counter, counter = 0, word_counter, upper_case_word_counter, lower_case_word_counter, score, already_in_array;
    char *name_copy, *first_name, *last_name, **words, *word, **upper_case_words, **lower_case_words;
    RACE_DATA *race_data_array, race_data;
    RIDER_DATA *rider_data_array;
    FILE *file;

    /* Get number of lines in the file */
    file = open_file(&race_data_array_counter, file_name);
    /* Exit program if can't open the file or the file is empty */
    if (file == NULL || race_data_array_counter == 0) {
        fclose(file);
        return 0;
    }

    race_data_array = malloc(sizeof(RACE_DATA) * race_data_array_counter);

    /* Get data from file */
    while (fscanf(file, "%[^\"]\"%[^\"]\" %d %s %s %s %s\n", race_data.race, race_data.name, &race_data.age,
                  race_data.team, race_data.country, race_data.ranking, race_data.time) != EOF) {
        /* Trim race name */
        trim_end(race_data.race, (int) strlen(race_data.race));

        /* Copy name into new pointer */
        name_copy = malloc(strlen(race_data.name) + 1);
        strcpy(name_copy, race_data.name);

        /* Split name into words */
        word_counter = 0;
        words = malloc(sizeof(race_data.name));
        word = strtok(name_copy, " ");
        while (word != NULL) {
            words[word_counter++] = word;
            word = strtok(NULL, " ");
        }

        /* Seperate upper and lowercase words */
        upper_case_word_counter = 0;
        lower_case_word_counter = 0;
        upper_case_words = malloc(sizeof(race_data.name));
        lower_case_words = malloc(sizeof(race_data.name));

        for (i = 0; i < word_counter; i++) {
            char *temp_word = words[i];
            if (is_upper_case(temp_word)) {
                upper_case_words[upper_case_word_counter++] = temp_word;
            } else {
                lower_case_words[lower_case_word_counter++] = temp_word;
            }
        }

        /* Get firstname */
        first_name = malloc(sizeof(race_data.name));
        for (i = 0; i < lower_case_word_counter; i++) {
            if (i == 0)
                strcpy(first_name, lower_case_words[i]);
            else {
                strcat(first_name, " ");
                strcat(first_name, lower_case_words[i]);
            }
        }

        /* Get lastname */
        last_name = malloc(sizeof(race_data.name));
        for (i = 0; i < upper_case_word_counter; i++) {
            if (i == 0)
                strcpy(last_name, upper_case_words[i]);
            else {
                strcat(last_name, " ");
                strcat(last_name, upper_case_words[i]);
            }
        }

        /* Copy the values into the race data */
        strcpy(race_data.first_name, first_name);
        strcpy(race_data.last_name, last_name);

        /* Add race data to array */
        race_data_array[counter++] = race_data;

        free(words);
        free(upper_case_words);
        free(lower_case_words);
        free(first_name);
        free(last_name);
    }

    /* Close file */
    fclose(file);

    *temp_race_data_array = race_data_array;
    *temp_race_data_array_counter = race_data_array_counter;

    rider_data_array_counter = 0;
    rider_data_array = malloc(sizeof(RIDER_DATA) * race_data_array_counter);

    /* Calculate scores */
    for (i = 0; i < race_data_array_counter; i++) {
        race_data = race_data_array[i];

        score = 0;
        if (strcmp(race_data.ranking, "DNF") != 0) {

            score += 2;

            if (strcmp(race_data.ranking, "OTL") != 0) {
                int number = get_number_of_riders_who_completed_the_race(race_data_array_counter, race_data_array,
                                                                         race_data.race);

                char *ptr;
                long ranking_value = strtol(race_data.ranking, &ptr, 4);

                score += (number - ranking_value) / 17;

                switch (ranking_value) {
                    case 1:
                        score += 8;
                        break;
                    case 2:
                        score += 5;
                        break;
                    case 3:
                        score += 3;
                        break;
                    default:
                        break;
                }
            }
        }

        race_data_array[i].score = score;

        already_in_array = 0;

        for (j = 0; j < rider_data_array_counter; j++) {
            if (strcmp(rider_data_array[j].name, race_data.name) == 0) {
                already_in_array = 1;
                rider_data_array[j].total_score += score;
            }
        }

        if (!already_in_array) {
            RIDER_DATA rider_data;

            strcpy(rider_data.name, race_data.name);
            strcpy(rider_data.first_name, race_data.first_name);
            strcpy(rider_data.last_name, race_data.last_name);
            rider_data.age = race_data.age;
            strcpy(rider_data.team, race_data.team);
            strcpy(rider_data.country, race_data.country);
            rider_data.total_score = score;

            rider_data_array[rider_data_array_counter++] = rider_data;
        }
    }

    *temp_rider_data_array = rider_data_array;
    *temp_rider_data_array_counter = rider_data_array_counter;

    return 1;
}

/***********************************/
/* SORT FUNCTIONS */
/***********************************/

/* Sort nations highest total score first if equal then lowest age first */
int sort_nations(const void *elem1, const void *elem2) {
    const NATION_DATA *first = elem1, *second = elem2;

    if (first->total_score < second->total_score)
        return 1;
    else if (first->total_score > second->total_score)
        return -1;
    else {
        if (first->total_age > second->total_age)
            return 1;
        else if (first->total_age < second->total_age)
            return -1;
        else
            return 0;
    }
}

/* Sort teams highest number of riders out first */
int sort_teams(const void *elem1, const void *elem2) {
    const TEAM_DATA *first = elem1, *second = elem2;

    if (first->riders_out < second->riders_out)
        return 1;
    else if (first->riders_out > second->riders_out)
        return -1;
    else
        return 0;
}

/* Sort rider scores highest total score first if equal the lowest age first */
int sort_rider_scores(const void *elem1, const void *elem2) {
    const RIDER_DATA *first = elem1, *second = elem2;

    int res = 0;

    if (first->total_score < second->total_score)
        res = 1;
    else if (first->total_score > second->total_score)
        res = -1;
    else {
        if (first->age < second->age)
            res = -1;
        else if (first->age > second->age)
            res = 1;
        else {
            return strcmp(first->last_name, second->last_name);
        }
    }

    return res;
}

/* Sort danish riders according to team names */
int sort_danish_riders(const void *elem1, const void *elem2) {
    const RACE_DATA *first = elem1, *second = elem2;

    int res = strcmp(first->team, second->team);

    if (res == 0) {
        res = strcmp(first->first_name, second->first_name);
    }

    return res;
}

/*******************************************/
/* ASSIGNMENTS */
/*******************************************/

/* Assignment 1 */
void print_all_belgian_riders_under_23(int race_data_array_counter, RACE_DATA *race_data_array) {
    int i, j, number_of_belgian_riders_under_23, already_in_array;
    RACE_DATA *belgian_riders_under_23_race_data_array, race_data;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 1. Belgian riders under 23\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    number_of_belgian_riders_under_23 = 0;
    belgian_riders_under_23_race_data_array = malloc(sizeof(RACE_DATA) * race_data_array_counter);

    for (i = 0; i < race_data_array_counter; i++) {
        race_data = race_data_array[i];

        if (strcmp(race_data.country, "BEL") == 0 && race_data.age < 23) {
            already_in_array = 0;

            for (j = 0; j < number_of_belgian_riders_under_23; j++) {
                if (strcmp(belgian_riders_under_23_race_data_array[j].name, race_data.name) == 0)
                    already_in_array = 1;
            }

            if (!already_in_array) {
                belgian_riders_under_23_race_data_array[number_of_belgian_riders_under_23++] = race_data;
            }
        }
    }

    for (i = 0; i < race_data_array_counter; i++) {
        race_data = belgian_riders_under_23_race_data_array[i];

        if (strcmp(race_data.country, "BEL") == 0 && race_data.age < 23) {
            print_race_data_for_rider(race_data, 1);
        }
    }
}

/* Assignment 2 */
void print_all_danish_riders_who_has_participated_in_one_or_more_of_the_races(int race_data_array_counter,
                                                                              RACE_DATA *race_data_array) {
    int i, j, number_of_danish_riders;
    RACE_DATA *danish_riders_race_data_array, race_data;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 2. Danish riders who participated in one or more of the races\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    number_of_danish_riders = 0;
    danish_riders_race_data_array = malloc(sizeof(RACE_DATA) * race_data_array_counter);

    for (i = 0; i < race_data_array_counter; i++) {
        race_data = race_data_array[i];

        if (strcmp(race_data.country, "DEN") == 0) {
            int already_in_array = 0;

            for (j = 0; j < number_of_danish_riders; j++) {
                if (strcmp(danish_riders_race_data_array[j].name, race_data.name) == 0)
                    already_in_array = 1;
            }

            if (!already_in_array) {
                danish_riders_race_data_array[number_of_danish_riders++] = race_data;
            }
        }
    }

    qsort(danish_riders_race_data_array, (size_t) number_of_danish_riders, sizeof(race_data), sort_danish_riders);

    for (i = 0; i < number_of_danish_riders; i++) {
        race_data = danish_riders_race_data_array[i];
        print_race_data_for_rider(race_data, 1);
    }

    free(danish_riders_race_data_array);
}

/* Assignment 3 */
void print_the_10_riders_who_got_the_most_points(int rider_data_array_counter, RIDER_DATA *rider_data_array) {
    int i;
    RIDER_DATA rider_data;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 3. The 10 riders who got the most points\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    qsort(rider_data_array, (size_t) rider_data_array_counter, sizeof(rider_data), sort_rider_scores);

    for (i = 0; i < 10; i++) {
        rider_data = rider_data_array[i];
        print_rider_data(rider_data, 0);
    }
}

/* Assignment 4 */
void print_for_each_of_the_races_which_team_who_has_the_most_riders_as_OTL_or_DNF(int rider_data_array_counter,
                                                                                  int race_data_array_counter,
                                                                                  RIDER_DATA *rider_data_array,
                                                                                  RACE_DATA *race_data_array) {
    int i, j, k, l, number_of_teams, number_of_races;
    TEAM_DATA *team_data_array;
    char **race_names;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 4. Team who has the most riders as OTL or DNF in each race\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    /* Get teams */
    team_data_array = malloc(sizeof(TEAM_DATA) * rider_data_array_counter);
    number_of_teams = get_teams(rider_data_array_counter, rider_data_array, team_data_array);

    /* Get race names */
    race_names = malloc(sizeof(char) * 28);
    number_of_races = get_races(race_data_array_counter, race_data_array, race_names);

    for (i = 0; i < number_of_races; i++) {
        for (j = 0; j < race_data_array_counter; j++) {
            if (j == 0) {
                for (l = 0; l < number_of_teams; l++) {
                    team_data_array[l].riders_out = 0;
                }
            }

            for (k = 0; k < number_of_teams; k++) {
                if (strcmp(race_data_array[j].race, race_names[i]) == 0 &&
                    strcmp(race_data_array[j].team, team_data_array[k].name) == 0 &&
                    (strcmp(race_data_array[j].ranking, "OTL") == 0 || strcmp(race_data_array[j].ranking, "DNF") == 0)
                        ) {
                    team_data_array[k].riders_out++;
                }
            }
        }

        qsort(team_data_array, (size_t) number_of_teams, sizeof(TEAM_DATA), sort_teams);

        printf("%-27s %s %d\n", race_names[i], team_data_array[0].name, team_data_array[0].riders_out);
    }

    free(team_data_array);
    free(race_names);
}

/* Assignment 5 */
void print_the_nation_with_the_most_points(int rider_data_array_counter, RIDER_DATA *rider_data_array) {
    int i, j, nations_counter;
    NATION_DATA *nations;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 5. The nation with the most points\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    nations = malloc(sizeof(NATION_DATA) * rider_data_array_counter);
    nations_counter = get_nations(rider_data_array_counter, rider_data_array, nations);

    for (i = 0; i < rider_data_array_counter; i++) {
        for (j = 0; j < nations_counter; j++) {
            if (strcmp(rider_data_array[i].country, nations[j].name) == 0) {
                nations[j].total_score += rider_data_array[i].total_score;
                nations[j].total_age += rider_data_array[i].age;
                break;
            }
        }
    }

    qsort(nations, (size_t) nations_counter, sizeof(NATION_DATA), sort_nations);

    printf("%s\n", nations[0].name);

    free(nations);
}

/* Assignment 6 */
void
print_the_median_time_for_each_race(int race_data_array_counter, RACE_DATA *race_data_array, int only_median) {
    int i, j, number_of_races, median_index;
    char **race_names;
    RACE_DATA *race_data_array_single_race;

    printf("///////////////////////////////////////////////////////////////\n");
    printf("// 6. The median time for each race\n");
    printf("///////////////////////////////////////////////////////////////\n\n");

    race_names = malloc(sizeof(char) * 28);
    race_data_array_single_race = malloc(sizeof(RACE_DATA) * race_data_array_counter);

    number_of_races = get_races(race_data_array_counter, race_data_array, race_names);

    for (i = 0; i < number_of_races; i++) {
        char *race_name = race_names[i];

        int race_data_array_single_race_counter = get_riders_who_has_completed_the_race(race_data_array_counter,
                                                                                        race_data_array,
                                                                                        race_data_array_single_race,
                                                                                        race_name);

        TIME_DATA *times = malloc(sizeof(TIME_DATA) * race_data_array_single_race_counter);
        int timesCounter = 0;

        for (j = 0; j < race_data_array_single_race_counter; j++) {
            TIME_DATA time;

            sscanf(race_data_array_single_race[j].time, "%d:%d:%d", &time.tm_hour, &time.tm_min, &time.tm_sec);

            times[timesCounter++] = time;
        }

        median_index =
                (race_data_array_single_race_counter / 2) +
                (race_data_array_single_race_counter % 2 == 0 ? -1 : 0);

        if (i != 0)
            printf("\n");
        printf("%s\n\n", race_name);

        for (j = 0; j < timesCounter; j++) {
            TIME_DATA time = times[j];

            if ((only_median && j == median_index) || only_median == 0) {
                if (j == median_index && !only_median) {
                    printf("\n");
                }

                printf("%-3d ", j + 1);

                if (j == median_index) {
                    printf("Median ");
                }

                printf("%d:%02d:%02d\n", time.tm_hour, time.tm_min, time.tm_sec);

                if (j == median_index && !only_median) {
                    printf("\n");
                }
            }
        }

        free(times);
    }

    free(race_names);
    free(race_data_array_single_race);
}
