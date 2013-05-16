#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>

static int gauta = 0;

void fun(){
	gauta = 1;
}

int main ( void )

{
	int      x;                    /* isejimo variantas */
	int      fd[2];                /* deskriptoriu masyvas ( kanalui ) */
	pid_t    pid;                  /* Proceso identifikatorius */

	char buf[128];
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
		signal(SIGUSR1, fun);
		while(gauta == 0);
		read(fd[0], buf, sizeof(buf));
		printf("gautas vardas: %s\n", buf);
	}
	else if ( pid == -1 )
	{
		fprintf ( stderr, "Nepavyko sukurti vaiko !\n" );
		exit    ( 4 );
	}
	else
	{
		/* ------------ Tevo procesas---------- */
		printf("Irasykite varda\n");
		scanf("%s", buf);		
		write(fd[1], buf, sizeof(buf));
		kill(pid, SIGUSR1);
		wait(&x);
	}
	return 0;
}
