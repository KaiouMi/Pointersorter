#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdbool.h>

typedef struct _Node{
    char* data;
    struct _Node * next;
}Node;


//method to compare two strings
int compare(char * string1, char * string2){

    int result;
    int index = 0;
    bool done = false;

    while(done == false){
//printf("ascii str1 %d ans ascii str2 %d\n", (int)string1[index], (int)string2[index] );
        if((int)string1[index] > (int)string2[index]){
            if((int)string2[index] <= 90 && (int)string1[index] > 90){
                result = -1;
                done = true;
                break;
            } else {

                result = 1;
                done = true;
                break;
            }

        } else if ((int)string1[index] < (int)string2[index]){
            if((int)string1[index] <= 90 && (int)string2[index] > 90){
                result = 1;
                done = true;
                break;
             } else {
                result = -1;
                done = true;
                break;
            }
            
        } else {
            while((int)string1[index] == (int)string2[index]){
                index++;
                if((int)string1[index] == '\0' && (int)string2[index] == '\0'){
                    result = 0;
                    done = true;
                    break;
                } else if ((int)string1[index] == '\0'){
                    result = -1;
                    done = true;
                    break;
                } else if ((int)string2[index] == '\0'){
                    result = 1;
                    done = true;
                    break;
                }
            }  
        }
    }

    return result;
}

Node* sort(Node * head, char * word){
//printf("in sort\n");
    if(head == NULL){
	    head = (Node*)malloc(sizeof(Node));
        head->data = strdup(word);
	    head->next = NULL;
        return head;
    } 

//printf("head->data %s\n", head->data);
    Node * ptr = head;
    Node * temp = NULL;
    temp = (Node *)malloc(sizeof(Node));
    int num = 0; //this is the int that will come from the compare method

    num = compare(ptr->data, word);
    if(num == -1){
      temp->data = strdup(word);
      temp->next = ptr;
      head = temp;
//printf("should be here, ptr is %s temp->data %s temp->next->data %s\n", ptr->data, temp->data, temp->next->data);
    } else if (num == 0){
      temp->data = strdup(word);
      temp->next = ptr->next;
      ptr->next = temp;
    } else {
      while(ptr->next != NULL){
	if(compare(ptr->data,word) == 1 && compare(ptr->next->data, word) <= 0){
	  temp->data = strdup(word);
	  temp->next = ptr->next;
	  ptr->next = temp;
	  break;
	}
	  
	ptr = ptr->next;
      }
      if(ptr->next == NULL){
	temp->data = strdup(word);
	temp->next = NULL;
	ptr->next = temp;
      }
    }		    


    return head;
}

//method is used in order to count how many letters are in the input string, as will as account for a space char in order to separate words in the main method

int countindex(char arr[], int length){
    
    int count = 0, token = 0;
    int i;
    for(i = 0; i < length; i++){
        if(isalpha(arr[i])){
            token = 0;
            count++;
        } else {
            if(token == 0){
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char ** argv){

    //making sure that there is a correct number of inputs 
   if(argv[1] == NULL){
       printf("Error: please input a string");
       return 0;
   }  

   if(argc > 2){
       printf("Error: incorrect number of inputs");
       return 0;
   } 


    /*
        length is the size of the new array that will hold the words with only one non-letter between each word
        argvlength is the size of the input string
    */
    int length = 0, argvlength = 0, count = 0;
    argvlength = strlen(argv[1]);
    if(argvlength == 0){
	printf("Error: empty string\n");
	return 0;
    }

   
    length = countindex(argv[1], argvlength);

    char * list;
    list = (char *)malloc(length * sizeof(char));

    int i; 
    int keep = 0;
    bool word = false;
    for(i = 0; i < argvlength; i++){
        if(isalpha(argv[1][i])){
	    word = true;
            list[count] = argv[1][i];
	        keep = 0;
           // printf("list[count] %c\n", list[count]);
        count++;  
        } else {
            if(keep == 0){

                list[count] = '-';
          //      printf("list[count] %c\n", list[count]);
                count++;  		
            }
		keep++;
        }      


    } 


if(word == false){
  printf("Error: no word input\n");
  return 0;
}

    /*
        after this point, the input string in argv[1] has now be put into another char array with only a single '-' splitting up each word
    */  

    char * split = strtok(list, "-");
    char * array[count];

    Node * head = NULL;
    
//printf("%s\n", split);

    while(split != NULL){

      head = sort(head, split);
      split = strtok(NULL, "-");

    }	
//printf("about to print\n");
    while(head != NULL){
	printf("%s\n", head->data);
	head = head->next;
    }


    return 0;
} 
