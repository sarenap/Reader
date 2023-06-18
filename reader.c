#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 256
int main(int argc, char **argv)
{

    int in_cols = 0;  /* number of columns in input */
    int out_cols = 0; /* number of columns to output */

    /* readbuffer need to be initialized to NULL for getline to work properly */
    char *readbuffer = NULL; /* read buffer for processing lines in input */

    /* pointers to arrays which will be allocated dynamically by you */
    char **buf = NULL; /* pointer to array of pointers to the start of
                             each field in input buffer */
    int *obuf = NULL;  /* pointer to array of output indices */

    /* local variables to store the statistics */
    unsigned int linecnt = 0;   /* number of lines in input */
    unsigned int lngst_fld = 0; /* longest field in input */

    int stats_flag = 0; /* keep track of whether -s flag is passed in or not* /

    /* TODO: process named command line options using getopt and store the information
        in the appropriate local variables */
    int c;
    /* TODO: fill out this skeleton code calling getopt */
    while ((c = getopt(argc, argv, "c:s:")) != -1)
    {
        switch (c)
        {
	case 'c':
	    in_cols = atoi(optarg);
	    break;
        case 's':
	    stats_flag = 1;
            break;
        default:
            abort();
        }
    }

    /* TODO: process other command line arguments (list of output columns) */
    if( optind < argc ){
	 out_cols = argc - optind; //find out cols
    }

    //convert string to int, store strings in obuf
    obuf = malloc(sizeof(int) * out_cols); //obuf is array of ints.
    for( int i = 0; i < out_cols; i++ ){
 	// obuf[i] = atoi( argv[ optind + i ] ); do pointer arithmetic instead
	 *( obuf + i ) = atoi( *(argv + optind + i ));
    }
    

    /* TODO: allocate arrays dynamically */
    buf = malloc(sizeof(char* ) * in_cols); //buf is array of ptrs to ptrs

    /* TODO: parse the input from stdin line by line and output
     the target columns as described in the writeup */
    size_t n = BUF_SIZE; //size for getline. when to use input_cols???
    while(getline( &readbuffer, &n, stdin ) != -1 ){
	    linecnt++;
	   
	    char *curr = readbuffer; //assign addr of readbuffer to *curr
	    int curr_len = 0; //length of curr string
	    
	    while( *curr != ' ' && *curr != '\n' && *curr != '\0' && *curr != '\t'){ //record not start w white space
		curr++;
		curr_len++;
	    }
	    if( curr_len > lngst_fld ) lngst_fld = curr_len;
	    if( *curr == ' ' || *curr == '\t' ) curr++; //skip white spaces
    

    //populate buff. array of strings. CHECK THIS
    char *start = readbuffer;
    int buf_idx = 0;

    while( *start != '\n' && *start != '\0'){ //record not start w white space
	//buf[buf_idx++] = start; //replace by char. pointer arith H E R E
	*(buf + (buf_idx++) ) = start;

	while( *start != ' ' && *start != '\n' && *start != '\0' && *start != '\t' ) start++;
	if( *start == ' ' || *start == '\t' || *start == '\n' ){//space tab newline. pg 10
		*start = '\0'; //replace all space and tab w null termnator
		start++;
	}
	//buf[buf_idx] = NULL; //terminate array do i neeed? H E R E
    }

    //output coloumns. CHCK THIS
    for(int i = 0; i < out_cols -1; i++){
	//if( obuf[i] < buf_idx ) printf("%s", buf[obuf[i]]); H E R E
	if( *( obuf + i ) < buf_idx ) printf("%s ", *( buf + *(obuf + i ) ));
	
    }
    printf("%s\n", *(buf + *(obuf + out_cols - 1 )));
    if(stats_flag == 1) printf("\n"); //H E R E
   
    }//curly brace of getline

    /* TODO: use this line to print out the statistics when -s flag is set */
    
    
    if(stats_flag == 1){
    printf("Number of lines: %d\nLongest field: %d characters\n", linecnt, lngst_fld); //print out last el of obuf with a newline
    }

    /* TODO: free the memory for arrays allocated with malloc */
    free(buf);
    free(obuf);
    free(readbuffer);
    return 0;
}
