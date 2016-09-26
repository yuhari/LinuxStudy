/*
 * who02.c - a first version of the who program
 *			open, read UTMP file, and show results
 * utmpx.h -- "/usr/include/utmpx.h"
 * man 3 endutxent
 */
#include <stdio.h>
#include <utmpx.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

//#define SHOWHOST    /* include remote machine on output */

/*
*	show info()
*	displays contents of the utmp struct in human readable form
*/
void show_info(struct utmpx *) ;
void show_time(long) ;

int main (int argc, char const *argv[])
{
	/* code */
	struct utmpx * current_record;  /* read info into here */
	int 		utmpfd ;		 /* read from this descriptor */
	int			reclen = sizeof(current_record) ;
	
	if ((utmpfd = open(_PATH_UTMPX, O_RDONLY )) == -1){ //failed
		perror(_PATH_UTMPX) ; 		/* UTMP_FILE is utmp.h */
		exit(1) ;
	}
	
	while ((current_record = getutxent()))
		show_info(current_record) ;
	
	close(utmpfd) ;
	return 0;
}

void show_info(struct utmpx * d ){
	
	if (d->ut_type != USER_PROCESS)	/* users only */
		return ;
	printf("%-8.8s", d->ut_user) ;  /* the logname */
	printf(" ") ;
	printf("%-8.8s", d->ut_line) ;  /* the tty */
	printf(" ") ;
	show_time(d->ut_tv.tv_sec) ;  /* login time */
	printf(" ") ;
#ifdef SHOWHOST
	printf("(%s)", d->ut_host) ; 	/* the host */
#endif
	printf("\n") ;
}

void show_time(long timeval) {
	char * cp ;
	cp = ctime(&timeval) ;
	printf("%12.12s", cp+4) ;
}
