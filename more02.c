/* 
	Assignment: 6.11 with additional features
	Name: Majdi Aburamadan
	Program Statement: Expand on more to run in noecho,
	noncanonical mode and respond to interrupt and quit
    Input: SPACE SIQQUIT CTRL C
    Output:Depending on command.
    Usage: No Screenshots for this program
 */
#include	<stdio.h>
#include    <sys/ioctl.h>
#include    <stdlib.h> 
#include    <termios.h>
#include    <signal.h>
#include    <fcntl.h>
#define	PAGELEN	24
#define	LINELEN	512

void do_more(FILE *);
int see_more(FILE *);

int main( int ac , char *av[] )
{
	FILE	*fp;
	int fd;
void	funcHandler(int);
struct winsize wbuf;

tty_mode(0);
set_cr_noecho_mode();
signal( SIGINT, funcHandler );	
signal( SIGQUIT, funcHandler );	
tty_mode(1);
       
	if ( ac == 1 )
		do_more( stdin );
	else
		while ( --ac )
			if ( (fp = fopen( *++av , "r" )) != NULL )
			{
				do_more( fp ) ; 
				fclose( fp );
			}
			else
				exit(1);
	

if ( ioctl(fd, TIOCGWINSZ, &wbuf) != -1 )
      return wbuf.ws_row;
     return 24;
}

void do_more( FILE *fp )
/*
 *  read PAGELEN lines, then call see_more() for further instructions
 */
{
	char	line[LINELEN];
	int	num_of_lines = 0;
	int	see_more(FILE *), reply;
	FILE	*fp_tty;

	fp_tty = fopen( "/dev/tty", "r" );	   /* NEW: cmd stream   */
	if ( fp_tty == NULL )			   /* if open fails     */
		exit(1);                           /* no use in running */

	while ( fgets( line, LINELEN, fp ) ){		/* more input	*/
		if ( num_of_lines == PAGELEN ) {	/* full screen?	*/
			reply = see_more(fp_tty);  /* NEW: pass FILE *  */
			if ( reply == 0 )		/*    n: done   */
				break;
			num_of_lines -= reply;		/* reset count	*/
		}
		if ( fputs( line, stdout )  == EOF )	/* show line	*/
			exit(1);			/* or die	*/
		num_of_lines++;				/* count it	*/
	}
}

int see_more(FILE *cmd)				   /* NEW: accepts arg  */
/*
 *	print message, wait for response, return # of lines to advance
 *	q means no, space means yes, CR means one line
 */
{
	int	c;

	printf("\033[7m more? \033[m");		/* reverse on a vt100	*/
	while( (c=getc(cmd)) != EOF )		/* NEW: reads from tty  */
	{
		if ( c == 'q' )			/* q -> N		*/
			return 0;
		if ( c == ' ' )			/* ' ' => next page	*/
			return PAGELEN;		/* how many to show	*/
		if ( c == '\n' )		/* Enter key => 1 line	*/
			return 1;	
		//if ( c == )	
	}
	return 0;
}
set_cr_noecho_mode()
/* 
 * purpose: put file descriptor 0 into chr-by-chr mode and noecho mode
 *  method: use bits in termios
 */
{
	struct	termios	ttystate;

	tcgetattr( 0, &ttystate);		/* read curr. setting	*/
	ttystate.c_lflag    	&= ~ICANON;	/* no buffering		*/
	ttystate.c_lflag    	&= ~ECHO;	/* no echo either	*/
	ttystate.c_cc[VMIN]  	=  1;		/* get 1 char at a time	*/
	tcsetattr( 0 , TCSANOW, &ttystate);	/* install settings	*/
}

//Also handles SigQuit according to directions
// " respond to interrupt (^C) and kill (SIGQUIT, ^\)
//	 which will reset the terminal back to original mode."

void funcHandler(int signum)
/*
 * purpose: called if SIGINT and SIGQUIT is detected
 *  action: reset tty and scram
 */
{
	tty_mode(1);
	exit(2);
}

tty_mode(int how)
{
	static struct termios original_mode;
	static int            original_flags;
	static int            stored = 0;

	if ( how == 0 ){
		tcgetattr(0, &original_mode);
		original_flags = fcntl(0, F_GETFL);
		stored = 1;
	}
	else if ( stored ) {
		tcsetattr(0, TCSANOW, &original_mode); 
		fcntl( 0, F_SETFL, original_flags);	
	}
}
