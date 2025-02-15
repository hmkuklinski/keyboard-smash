#include <stdio.h> //for printf and scanf
#include <stdlib.h> //for random number generator
#include <time.h> //for random number generator
#include <string.h>

int get_index(char);
void tutorial();

int main(){
    /*character array that holds different symbols */
    char letters[] = "qwertyuiopasdfghjklzxcvbnm1234567890~`!@#$^&*()+_-|/";
    int letters_length = strlen(letters);
    int playing = 1;
    char input[4]; //for asking user to play again
    tutorial();
    /*outer loop to allow multiple games if user so desires:*/
    while(playing){
        /*welcome message and prompt for playing game:*/
        printf("\n\nWould you like to play? ");
        scanf("%3s", input); /*read in max of 3 characters - yes; */
        
        /*what if user enters a value that is more than 3 characters? still in the buffer...*/
        while(getchar()!='\n'){
            /*do nothing!*/
        };

        /*to store the user's guess in character string (one extra for null terminator)*/
        char user_guess[5]; 

        /*seed the random number generator*/
        srand((unsigned int)time(NULL));

        /*to generate and store the answer's random number in random array:*/
        int random[4];
        for(int i=0;i<4;i++){
            int val = rand() % letters_length;
            random[i] = val;
        }

        /*convert int to char and store in answer (one extra for null terminator)*/
        char answer[5];

        /*This array stores the correct number of each symbol, with index values corresponding to symbol in the letters string */
        int answer_count[letters_length];
        int reset_count[letters_length];
        for(int i=0;i<letters_length;i++){
            answer_count[i] = 0;
            reset_count[i]=0;
        }
        
        /*process to convert random gen index values to char values and update symbol counter */
        for(int i=0;i<4;i++){
            answer[i]= letters[random[i]]; /* to assign a char (symbol) to our answer string, take rand generated index and get char in symbols string */
            answer_count[random[i]]++;
            reset_count[random[i]]++;
        }
        answer[4]='\0'; /*null terminator*/
         
        int total_rounds = 0;
       

        /*loop to simulate the rounds (goes upwards of ten rounds and exits if answer was given)*/
        for(int rounds = 1; rounds<15;rounds++){
           
            /*ask if user wants to quit the game */
            if ((input[0]=='n' || input[0]=='N')&& (input[1]=='o'|| input[1]=='O')){
                playing = 0;
                break;
            }

            /* have to reset the count values from previous round */
            for(int i=0;i<letters_length;i++){
                answer_count[i] = reset_count[i];
            }

            printf("\n--------");

            /* Prompt that states the current guess number and prompts for user guess: */
            printf("\n\nEnter guess number %d: ", rounds);
            scanf("%4s", user_guess); /*takes max four characters, and because its s, will add null terminator afterwards*/
            
             /*what if user enters a value that is more than 3 characters? still in the buffer...*/
            while(getchar()!='\n'){
                /*do nothing!*/
            };

            /*variables to track correctness and placement*/
            int correct = 0;
            int wrong_place = 0;

            /* Array to help keep track of elements in the correct spots:
            * ---> if the array is correctly placed, the current index value is placed in the corresponding index position
            * ---> if the element is not correctly placed, will keep a -1 value
            */
            int correct_order[letters_length];
            for(int i=0;i<letters_length;i++){
                correct_order[i]= -1;
            }

            

            /* Determining the correct guess in the correct placement: */
            for(int letter = 0; letter<4;letter++){
                /* if both letters in the user's string and the answer string match: 
                * - want to increment the correct counter and replace the value in correct_order array with current index
                */
                if( user_guess[letter]==answer[letter]){
                    correct++; 
                    correct_order[letter] = letter;
                    /* have to update the character tracker: takes the current character, finds respective index, then decrement */
                    char currchar = user_guess[letter];
                    int currindex = get_index(currchar);
                    answer_count[currindex]--;
                    
                } //if it is not correct placement, leave as -1
            }
           
            
            //loop to find the wrong placement:
            // STEPS: access answer_count to see what letters need to be included, see if any of these letters in guess --> return number if so
            for(int i=0;i<4;i++){
                //the item is not in correct place:
                if (correct_order[i]==-1){
                    char ch = user_guess[i]; //get the character at this index
                    int ch_index = get_index(ch); //generate index value

                    if (answer_count[ch_index]>0){
                        wrong_place++;
                        answer_count[ch_index]--;
                    }
                }
            }
            
            total_rounds++;
            /*if they are at end of round, print correct and misplacements */
            if (correct!=4){
                printf("\nSymbols in the correct place: %d\n", correct);
                printf("\nSymbols correct but in the wrong position: %d\n", wrong_place);
            }
            else{ /*they have found the answer!*/
                printf("\nSymbols in the correct place: %d\n", correct);
                printf("\nSymbols correct but in the wrong position: %d\n", wrong_place);
                break;
            }

        }
        /*display message based on whether successful or failure*/
        if(playing){
            if (total_rounds<10){
                printf("\nYou have completed the game in %d rounds! Congratulations!\n\n",total_rounds);
                printf("-------------------------------------\n");
            }
            else{
                printf("\nThe culprit got away! The correct answer was: %s\nBetter luck next time!\n\n", answer);
                printf("-------------------------------------\n");
            }
        }
        


    }
    return 0;
}
int get_index(char c){
    char possiblechars[] = "qwertyuiopasdfghjklzxcvbnm1234567890~`!@#$^&*()+_-|/";
    int length = strlen(possiblechars);
    for(int i=0;i<length;i++){
        if (possiblechars[i]==c){
            return i;
        }
    }
    return -1;
    
}

void tutorial(){
    printf("-----------------------------------------------------------------------------------------------------------\n");
    printf("\n _______  __   __  _______  _______  __   __      _______  ___      _______  __   __  _______  __   __ ");
    printf("\n|       ||  |_|  ||   _   ||       ||  | |  |    |       ||   |    |       ||  | |  ||       ||  | |  |");
    printf("\n|  _____||       ||  |_|  ||  _____||  |_|  |    |  _____||   |    |    ___||  | |  ||_     _||  |_|  |");
    printf("\n| |_____ |       ||       || |_____ |       |    | |_____ |   |    |   |___ |  |_|  |  |   |  |       |");
    printf("\n|_____  ||       ||       ||_____  ||       |    |_____  ||   |___ |    ___||       |  |   |  |       |");
    printf("\n _____| || ||_|| ||   _   | _____| ||   _   |     _____| ||       ||   |___ |       |  |   |  |   _   |");
    printf("\n|_______||_|   |_||__| |__||_______||__| |__|    |_______||_______||_______||_______|  |___|  |__| |__|");
    printf("\n                   Decode the secret message left at the crime scene!\n");
    printf("                 (Font Title from: http://patorjk.com/software/taag/)\n\n");
    printf("                                        INSTRUCTIONS\n");
    printf("* Select four characters/symbols/letters that you\'d like to test and then hit Enter \n\t-> NOTE: Forbidden characters include: ; %%, \\ \n");
    printf("* You\'ll get feedback on whether the letters you entered are in the correct place or need to be moved. \n* You\'ll have 15 tries to get it right.If you don\'t figure it out, the culprit will get away!\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
}