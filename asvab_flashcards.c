#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_console()
{
    system("clear");
}

int main (int argc, char** argv)
{
    if (argc == 1)
    {
        char input[100];
        char buffer[1024];
        int correct = 0;
        int incorrect = 0;
        FILE* f = fopen("C:/Users/mosir/Documents/c_exercise/asvab_flashcards/cards.csv","r");
        if (!f)
        {
            printf("Error: File not found.");
            return 0;
        }
        clear_console();
        while (fgets(buffer,1024,f))
        {
            clear_console();
            char* value = strtok(buffer,";");
            
            printf("%s\nanswer: ",value);
            fflush(stdout); 
            
            fgets(input,sizeof input,stdin);
            fflush(stdin);

            char* result = strtok(NULL,";");

            if (strcmp(input,result) == 0)
            {
                correct++;
                printf("\n\nCORRECT!\n");
            }
            else if (strlen(input) >= strlen(result) * 0.7 && strstr(result,input))
            {
                correct++;
                printf("\n\nCORRECT!\n\nALSO: %s",result);
            }
            else
            {
                incorrect++;
                printf("\n\nINCORRECT!\n\nANSWER: %s\n",result);
            }
            printf("press enter to continue");
            fflush(stdout); 

            getchar();
        }
        clear_console();
        printf("correct: %d\nincorrect: %d\n\n %d%%",correct,incorrect,(int)(((float)correct / (float)(incorrect + correct)) * 100));
        fclose(f);
    }
    else if (argc == 3)
    {
        FILE* f = fopen("./cards.csv","a");
        if (!f)
        {
            printf("Error: File not found.");
            return 0;
        }
        fprintf(f,"%s;%s",argv[1],argv[2]);
        fclose(f);
    }
    else
        printf("Use flashcards: asvab_flashcards\n\nAdd new flashcard: asvab_flashcards [question] [answer]");
    return 0;
}