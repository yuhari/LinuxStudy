/*
 * who01.c - a first version of the who program
 *			open, read UTMP file, and show results
 * utmpx.h -- "/usr/include/utmpx.h"
 * 
 */
#include <stdio.h>
#include <utmpx.h>
#include <fcntl.h>
#include <unistd.h>

#define SHOWHOST    /* include remote machine on output */

/*
*	show info()
*	displays contents of the utmp struct in human readable form
*/
void show_info(struct utmpx *) ;

int main (int argc, char const *argv[])
{
	/* code */
	struct utmpx current_record;  /* read info into here */
	int 		utmpfd ;		 /* read from this descriptor */
	int			reclen = sizeof(current_record) ;
	
	if ((utmpfd = open(_PATH_UTMPX, O_RDONLY )) == -1){ //failed
		perror(_PATH_UTMPX) ; 		/* UTMP_FILE is utmp.h */
		exit(1) ;
	}
	
	while ( read(utmpfd, &current_record, reclen ) == reclen)
		show_info(&current_record) ;
	
	close(utmpfd) ;
	return 0;
}

void show_info(struct utmpx * utbufp ){
	struct utmpx * d=getutxent() ;
	
	printf("%-8.8s", d->ut_user) ;  /* the logname */
	printf(" ") ;
	printf("%-8.8s", d->ut_line) ;  /* the tty */
	printf(" ") ;
	printf("%-10ld", d->ut_tv.tv_sec) ;  /* login time */
	printf(" ") ;
#ifdef SHOWHOST
	printf("(%s)", d->ut_host) ; 	/* the host */
#endif
	printf("\n") ;
}
