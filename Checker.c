#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define REQUIRED_NUMBER_OF_ARGUMENTS 3
#define DICTIONARY_SIZE 45427
#define KEY_NOT_FOUND -1

char *upper(char *string);
int binarySearch(char dictionary[][100] , int min , int max, char *key);
int main(int argc , char *argv[]){
	FILE *dictPointer , *inputPointer , *outputPointer;
	const char *dictFileName = "linux.words";
	char dictionary[DICTIONARY_SIZE][100], word[100] , buffer[100] , suggestions[10][100];
	int i, N, sCount, option;
	if(argc != 3)
		printf("Error\nCorrect Usage: checker input output\n");
	else{
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
		while(fscanf(dictPointer , "%s" , dictionary[i]) != EOF)
			i++;
		fclose(dictPointer);
		while(fscanf(inputPointer , "%s" , word) != EOF){
			memset(suggestions , '\0' , sizeof(suggestions[0][0]) * 10 * 100);
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

char *upper(char *string){
	int i;
	char *g_buffer = malloc(strlen(string));
	for(i = 0; i < strlen(string); i++){
		g_buffer[i] = toupper(string[i]);
	}
	g_buffer[i] = '\0';
	return g_buffer;
}
	
