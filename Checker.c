#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define REQUIRED_NUMBER_OF_ARGUMENTS 3 //Number of arguments needed for operation
#define DICTIONARY_SIZE 45427//Number of words in the dictionary
#define KEY_NOT_FOUND -1//Return value for absent key

char *upper(char *string);
int binarySearch(char dictionary[][100] , int min , int max, char *key);
int main(int argc , char *argv[]){
	FILE *dictPointer , *inputPointer , *outputPointer;//3 pointers for 3 files to open
	const char *dictFileName = "linux.words";//Dictionary file name
	char dictionary[DICTIONARY_SIZE][100], word[100] , buffer[100] , suggestions[10][100];
	int i, N, sCount, option;
    
    //Check for required number of arguments
	if(argc != 3)
		printf("Error\nCorrect Usage: checker input output\n");
	else{
        //Checks for file opening
		if((dictPointer = fopen(dictFileName, "r")) == NULL){
			printf("Dictionary not found.\n");
			exit(0);
		}
		if((inputPointer = fopen(argv[1] , "r")) == NULL){
			printf("Input file not found: %s\n" , argv[1]);
			exit(0);
		}
		if((outputPointer = fopen(argv[2] , "w")) == NULL){
			printf("Could not open output file: %s" , argv[2]);
			exit(0);
		}
		i = 0;
        //Read dictionary into memory
		while(fscanf(dictPointer , "%s" , dictionary[i]) != EOF)
			i++;
		fclose(dictPointer);

		while(fscanf(inputPointer , "%s" , word) != EOF){
			memset(suggestions , '\0' , sizeof(suggestions[0][0]) * 10 * 100);//Set all contents of suggestions to '\0'
			sCount = 0;
			N = strlen(word) - 1;
			
			if(binarySearch(dictionary, 0 , DICTIONARY_SIZE -1, word) != KEY_NOT_FOUND){
				fprintf(outputPointer , "%s " , word);
			}
			else{
				while(N >= 0 && sCount < 10){
					for(i = 0; i < N; i++){
						buffer[i] = word[i];
					}
					buffer[i] = '\0';
					if(binarySearch(dictionary, 0 , DICTIONARY_SIZE -1, buffer) != KEY_NOT_FOUND){
						strcpy(suggestions[sCount] , buffer);
						sCount++;
					}
					N = N-1;
				}
                if(sCount == 0){
                    printf("No suggestions for %s\n" , word);
                    fprintf(outputPointer , "%s ", word);
                }
                else{
				    printf("Word: %s not found , did you mean?\n", word);
				    for(i = 0; i < sCount; i++){
					
					    printf("%d. %s\n" , (i+1) , suggestions[i]);
					
				    }
				    printf("Enter digit beside chosen replacement text: ");
				    scanf("%d" , &option);
				    fprintf(outputPointer , "%s " , suggestions[option-1]);
			    }
		}
    }
   }
	return 0;
}

//Binary Search implemented to search the dictionay
int binarySearch(char dictionary[][100] , int min , int max, char *key){
	int mid;
	if(min > max)
		return KEY_NOT_FOUND;
	mid = min + ((max - min)/2);
	if(strcmp(upper(dictionary[mid]) , upper(key)) == 0)
		return mid;
	else if(strcmp(upper(key) , upper(dictionary[mid])) < 0)
		return binarySearch(dictionary, min , mid-1, key);
	else
		return  binarySearch(dictionary, mid+1 , max, key);
}

//Takes a string returns the upper case version of that string.
char *upper(char *string){
	int i;
	char *g_buffer = malloc(strlen(string));//Create a string the same size as argument
	for(i = 0; i < strlen(string); i++){
		g_buffer[i] = toupper(string[i]);//Store the upper case version of each char
	}
	g_buffer[i] = '\0';//Terminate string
	return g_buffer;
}
	
