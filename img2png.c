
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>





char *fbasenoext(char* mystr)
{
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}





#include <time.h>
char *strtimestamp()
{
      long t;
      struct tm *ltime;
      time(&t);
      ltime=localtime(&t);
      char charo[50];  int fooi ; 
      fooi = snprintf( charo, 50 , "%04d%02d%02d%02d%02d%02d",
	1900 + ltime->tm_year, ltime->tm_mon +1 , ltime->tm_mday, 
	ltime->tm_hour, ltime->tm_min, ltime->tm_sec 
	);
    size_t siz = sizeof charo ; 
    char *r = malloc( sizeof charo );
    return r ? memcpy(r, charo, siz ) : NULL;
}




/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}






//////////////////////////////
 void nrun_cmd( char *thefile )
 {
       char targetfile[PATH_MAX];
       char theout[PATH_MAX];
       char cmdi[PATH_MAX];

         strncpy( theout, strtimestamp() , PATH_MAX );

         strncpy( targetfile, fbasenoext( thefile ) , PATH_MAX );
         strncat( targetfile , ".png" , PATH_MAX - strlen( targetfile ) -1 );

         strncpy( cmdi , "  convert  " , PATH_MAX );
         strncat( cmdi , "  \"" , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , thefile , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , "\"  " , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , "  \"" , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , targetfile , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , "\"  " , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , "   " , PATH_MAX - strlen( cmdi ) -1 );
         printf( "CMD:%s\n", cmdi );
         if (  fexist( targetfile ) != 1 ) 
          if (  fexist( targetfile ) != 2 ) 
            if (  fexist( thefile ) == 1 ) 
              system( cmdi );
 }






int main( int argc, char *argv[])
{
    int i ; 
    if ( argc >= 2)
    {
          for( i = 1 ; i < argc ; i++) 
          {
	    printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i ] );
            nrun_cmd( argv[ i ] );
          }
    }
    return 0;
}


