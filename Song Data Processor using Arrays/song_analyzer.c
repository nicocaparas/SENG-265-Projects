/** @file song_analyzer.c
 *  @brief A pipes & filters program that uses conditionals, loops, and string processing tools in C to process song
 *  data and printing it in a different format.
 *  @author Felipe R.
 *  @author Hausi M.
 *  @author Angadh S.
 *  @author Juan G.
 *  @author Nico Caparas
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief The maximum line length.
 *
 */
#define MAX_LINE_LEN 200
#define BEFORE_2020_LEN 221 
#define DURING_2020_LEN 732

// Initialize Song data structure
typedef struct{
    char song_name[50];
    char artist[100];
    int artist_count;
    int release_year;
    int spotify_playlists;
    char key[5];
    char mode[10];
} Song;

int extract_question(char *argument_1); // Get question from argument in CLI
char* extract_filename(char *argument_2); // Get file from argument in CLI

void read_data(Song* song_list,char* filename); // Reads data from file into an array

// Process questions accordingly
void process_q1(Song* song_list, int array_size);
void process_q2(Song* song_list, int array_size);
void process_q3(Song* song_list, int array_size);
void process_q4(Song* song_list, int array_size);
void process_q5(Song* song_list, int array_size);

bool find_drake(char *artist_line); // Checks if Drake is in a list of artists

/**
 * Function: main
 * --------------
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
    // Check if corrent number of arguments passed
    if(argc!=3){
        printf("Please check number of arguments.");
        return 1;
    }

    // Assume all passed arguments are valid

    // Get the actual value of the argument

    int question_num = extract_question(argv[1]);
    char* file_name = extract_filename(argv[2]);
    
    // Get file length based on file_name
    int file_length;

    if(strcmp(file_name,"during_2020s.csv")==0){
        file_length = DURING_2020_LEN;
    }
    else{
        file_length = BEFORE_2020_LEN;
    }

    // Create an array of Songs called song_list
    Song song_list[file_length];

    // Read file data into song_list array 
    read_data(song_list,file_name);
    
    // Process data depending on question number
    switch(question_num){
        case 1: 
            process_q1(song_list,file_length);
            break;
        case 2: 
            process_q2(song_list,file_length);
            break;
        case 3:
            process_q3(song_list,file_length);
            break;   
        case 4: 
            process_q4(song_list,file_length);
            break;
        case 5: 
            process_q5(song_list,file_length);
    }

    exit(0);
}

// HELPER FUNCTIONS START HERE

int extract_question(char *argument_1){
    // Copy argument to variable 
    char str_argument_1[15];
    strcpy(str_argument_1,argument_1);

    // Extract actual value of argument 
    char *question_num;
    question_num = strtok(str_argument_1,"=");
    question_num = strtok(NULL," ");
    // Convert to int 
    int num = atoi(question_num);

    return num;
}

char* extract_filename(char *argument_2){
    // Copy argument to variable 
    char str_argument_2[25];
    strcpy(str_argument_2,argument_2);

    // Extract actual value of argument 
    char *file_name;
    file_name = strtok(str_argument_2,"=");
    file_name = strtok(NULL,"=");

    return file_name;
}

void read_data(Song* song_list,char* filename){
    FILE* input_file = fopen(filename,"r");

    int song_count = 0;

    char line[MAX_LINE_LEN];

    // Copy attributes accordingly based on Song struct
    while(fgets(line,MAX_LINE_LEN,input_file)!=NULL){
        char* token;
        
        token = strtok(line,","); // song name
        strcpy(song_list[song_count].song_name,token);

        token = strtok(NULL,","); // artist name
        strcpy(song_list[song_count].artist,token);

        token = strtok(NULL,","); // artist count 
        song_list[song_count].artist_count = atoi(token);

        token = strtok(NULL,","); // release year
        song_list[song_count].release_year = atoi(token);

        token = strtok(NULL,","); // spotify playlists
        song_list[song_count].spotify_playlists = atoi(token);

        token = strtok(NULL,","); // streams 
        // We will not add it since steams is not used in this assignment

        token = strtok(NULL,","); // key
        strcpy(song_list[song_count].key,token);

        token = strtok(NULL,","); // mode
        strcpy(song_list[song_count].mode,token);

        song_count++;  
    }
    
    fclose(input_file);
}

void process_q1(Song* song_list, int array_size){

    FILE* output_file = fopen("output.csv","w");

    if(output_file==NULL){
        printf("\nFile creation failed!");
    }

    fprintf(output_file,"Artist(s),Song\n");

    // Iterate through song_list, if artist == Rae Spoon then print to output file
    for (int i = 0; i < array_size; i++){
        if(strcmp(song_list[i].artist,"Rae Spoon")==0){
            fprintf(output_file,"%s,%s\n",song_list[i].artist,song_list[i].song_name);
        }
    }

    fclose(output_file);
}

void process_q2(Song* song_list, int array_size){

    FILE* output_file = fopen("output.csv","w");

    if(output_file==NULL){
        printf("\nFile creation failed!");
    }

    fprintf(output_file,"Artist(s),Song\n");

    // Iterate through song_list, if artist == Tate McRae then print to output file
    for (int i = 0; i < array_size; i++){
        if(strcmp(song_list[i].artist,"Tate McRae")==0){
            fprintf(output_file,"%s,%s\n",song_list[i].artist,song_list[i].song_name);
        }
    }

    fclose(output_file);
}

void process_q3(Song* song_list, int array_size){

    FILE* output_file = fopen("output.csv","w");

    if(output_file==NULL){
        printf("\nFile creation failed!");
    }

    fprintf(output_file,"Artist(s),Song\n");

    // Iterate through song_list, if artist == The Weeknd and mode == Major then print to output file
    for (int i = 0; i < array_size; i++){
        if(strcmp(song_list[i].artist,"The Weeknd")==0 && strcmp(song_list[i].mode,"Major\n")==0){
            fprintf(output_file,"%s,%s\n",song_list[i].artist,song_list[i].song_name);
        }
    }

    fclose(output_file);
}

void process_q4(Song* song_list, int array_size){

    FILE* output_file = fopen("output.csv","w");

    if(output_file==NULL){
        printf("\nFile creation failed!");
    }

    fprintf(output_file,"Artist(s),Song\n");

    // Iterate through song_list, if spotify_playlists > 5000 and key == A or D then print to output file
    for (int i = 0; i < array_size; i++){
        if(song_list[i].spotify_playlists > 5000){
            if(strcmp(song_list[i].key,"A")==0 || strcmp(song_list[i].key,"D")==0){
                fprintf(output_file,"%s,%s\n",song_list[i].artist,song_list[i].song_name);
            }
        }
    }

    fclose(output_file);
}

void process_q5(Song* song_list, int array_size){

    FILE* output_file = fopen("output.csv","w");

    if(output_file==NULL){
        printf("\nFile creation failed!");
    }

    fprintf(output_file,"Artist(s),Song\n");

    // Iterate through song_list, if release_year == 2021 or 2022, and Drake is one of the artists then print to output file
    for (int i = 0; i < array_size; i++){
        if(song_list[i].release_year == 2021 || song_list[i].release_year == 2022){
            bool drake_found = find_drake(song_list[i].artist); // Call Drake function 

            if(drake_found == true){
                //printf("\n%s",song_list[i].artist);
                fprintf(output_file,"%s,%s\n",song_list[i].artist,song_list[i].song_name);
            }
        }              
    }   

    fclose(output_file);
}

bool find_drake(char *artist_line){
    char* token;
    char line_artist[100];
    strcpy(line_artist,artist_line);

    bool drake_found = false;

    token = strtok(line_artist," ");

    // Check if first string in the line is == Drake
    if(strcmp(token,"Drake")==0){
        drake_found = true;
    }
    // Continue checking until end of line
    while(token!=NULL && drake_found == false){
        //If 'Drake' is found then break out of loop and change bool to true
        if(strcmp(token,"Drake")==0){
            drake_found = true;
        }
        token = strtok(NULL," ");
    }

    return drake_found;
}

