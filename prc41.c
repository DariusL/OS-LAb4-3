#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>

#define MKrIlg 50

int main ( void )

{
	int      x;                    /* isejimo variantas */
	int      fd[2];                /* deskriptoriu masyvas ( kanalui ) */
	pid_t    pid;                  /* Proceso identifikatorius */

	if ( pipe ( fd ) == -1 )
	{ 
		fprintf ( stderr, "Nepavyko sukurti programinio kanalo !\n" );
		exit    ( 1 );
	}

	/* ------------------- Dalijames ------------------ */

	pid = fork ();
	if ( pid == 0 )
		/* -------------------- Vaikas -------------------- */
	{
		/* ---- Skaitome is kanalo ---- */
		int id;
		usleep(100);
		read ( fd[0], &id, sizeof(int));
		printf("tevo id is pipe: %d\n", id);
		printf("getppid() = %d\n", getppid());
		printf ( "Vaikas baige darba ...\n" );
	}
	else if ( pid == -1 )
	{
		fprintf ( stderr, "Nepavyko sukurti vaiko !\n" );
		exit    ( 4 );
	}
	else
	{
		/* ------------ Tevo procesas---------- */
		int id = getpid();
		write(fd[1], &id, sizeof(int));
		printf("issiustas id = %d\n", id);
		printf("Tevas baigia darba\n");
		wait(&id);
	}
	return 0;
}
