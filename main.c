#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <wait.h>
/*
Alexis Matuk - A01021143
Diego Vázquez - A01168095
*/
//Declaración de nombres y matrículas a imprimir
char Alexis[6][5][5] = {{{' ','A','A','A',' '},{'A',' ',' ',' ','A'},{'A','A','A','A','A'},{'A',' ',' ',' ','A'},{'A',' ',' ',' ','A'}},{{'L',' ',' ',' ',' '} ,/**/{'L',' ',' ',' ',' '},{'L',' ',' ',' ',' '},{'L',' ',' ',' ',' '},{'L','L','L','L','L'}},/**/{{'E','E','E','E','E'},{'E',' ',' ',' ',' '},{'E','E','E','E','E'},{'E',' ',' ',' ',' '},{'E','E','E','E','E'}},/**/{{'X',' ',' ',' ','X'},{' ','X',' ','X',' '},{' ',' ','X',' ',' '},{' ','X',' ','X',' '},{'X',' ',' ',' ','X'}},/**/{{'I','I','I','I','I'},{' ',' ','I',' ',' '},{' ',' ','I',' ',' '},{' ',' ','I',' ',' '},{'I','I','I','I','I'}},/**/{{'S','S','S','S','S'},{'S',' ',' ',' ',' '},{'S','S','S','S','S'},{' ',' ',' ',' ','S'},{'S','S','S','S','S'}}};

char Diego[5][5][5] = {{{'D','D','D','D',' '},{'D',' ',' ',' ','D'},{'D',' ',' ',' ','D'},{'D',' ',' ',' ','D'},{'D','D','D','D',' '}},/**/{{'I','I','I','I','I'},{' ',' ','I',' ',' '},{' ',' ','I',' ',' '},{' ',' ','I',' ',' '},{'I','I','I','I','I'}},/**/{{'E','E','E','E','E'},{'E',' ',' ',' ',' '},{'E','E','E','E','E'},{'E',' ',' ',' ',' '},{'E','E','E','E','E'}},/**/{{'G','G','G','G','G'},{'G',' ',' ',' ',' '},{'G',' ','G','G','G'},{'G',' ',' ',' ','G'},{'G','G','G','G','G'}},/**/{{' ','O','O','O',' '},{'O',' ',' ',' ','O'},{'O',' ',' ',' ','O'},{'O',' ',' ',' ','O'},{' ','O','O','O',' '}}};

char matAlexis[9][5][5] = {{{' ','A','A','A',' '},{'A',' ',' ',' ','A'},{'A','A','A','A','A'},{'A',' ',' ',' ','A'},{'A',' ',' ',' ','A'}},/**/{{'0','0','0','0','0'},{'0',' ',' ',' ','0'},{'0',' ',' ',' ','0'},{'0',' ',' ',' ','0'},{'0','0','0','0','0'}} , /**/{{' ',' ','1',' ',' '},{' ','1','1',' ',' '},{' ',' ','1',' ',' '},{' ',' ','1',' ',' '},{'1','1','1','1','1'}}, /**/{{'0','0','0','0','0'},{'0',' ',' ',' ','0'},{'0',' ',' ',' ','0'},{'0',' ',' ',' ','0'},{'0','0','0','0','0'}}, /**/{{'2','2','2','2',' '},{' ',' ',' ',' ','2'},{' ','2','2','2','2'},{'2',' ',' ',' ',' '},{'2','2','2','2','2'}}, /**/{{' ',' ','1',' ',' '},{' ','1','1',' ',' '},{' ',' ','1',' ',' '},{' ',' ','1',' ',' '},{'1','1','1','1','1'}}, /**/{{' ',' ','1',' ',' '},{' ','1','1',' ',' '},{' ',' ','1',' ',' '},{' ',' ','1',' ',' '},{'1','1','1','1','1'}}, /**/{{' ',' ','4','4',' '},{' ','4',' ','4',' '},{'4','4','4','4','4'},{' ',' ',' ','4',' '},{' ',' ',' ','4',' '}},/**/{{'3','3','3','3',' '},{' ',' ',' ',' ','3'},{'3','3','3','3',' '},{' ',' ',' ',' ','3'},{'3','3','3','3',' '}}};

char matDiego[9][5][5] = {{{' ','A','A','A',' '},{'A',' ',' ',' ','A'},{'A','A','A','A','A'},{'A',' ',' ',' ','A'},{'A',' ',' ',' ','A'}},/**/{{'0','0','0','0','0'},{'0',' ',' ',' ','0'},{'0',' ',' ',' ','0'},{'0',' ',' ',' ','0'},{'0','0','0','0','0'}} , /**/{{' ',' ','1',' ',' '},{' ','1','1',' ',' '},{' ',' ','1',' ',' '},{' ',' ','1',' ',' '},{'1','1','1','1','1'}}, /**/{{' ',' ','1',' ',' '},{' ','1','1',' ',' '},{' ',' ','1',' ',' '},{' ',' ','1',' ',' '},{'1','1','1','1','1'}}, /**/{{' ','6','6','6','6'},{'6',' ',' ',' ',' '},{'6','6','6','6',' '},{'6',' ',' ',' ','6'},{' ','6','6','6',' '}}, /**/{{' ','8','8','8',' '},{'8',' ',' ',' ','8'},{' ','8','8','8',' '},{'8',' ',' ',' ','8'},{' ','8','8','8',' '}}, /**/{{'0','0','0','0','0'},{'0',' ',' ',' ','0'},{'0',' ',' ',' ','0'},{'0',' ',' ',' ','0'},{'0','0','0','0','0'}}, /**/{{' ','9','9','9',' '},{'9',' ',' ',' ','9'},{' ','9','9','9','9'},{' ',' ',' ',' ','9'},{'9','9','9','9',' '}},/**/{{'5','5','5','5','5'},{'5',' ',' ',' ',' '},{'5','5','5','5',' '},{' ',' ',' ',' ','5'},{'5','5','5','5','5'}}};

//wraper para aceptar más de un parámetro en la función thread
struct thread_args{
  int n;
  int k;
};

int combRes;//variable padre que modificará el thread que calcula n en k

//función para imprimir cada letra
void printLetter(int x, int y, char letter[x][y])
{
    for (int i = 0; i < 5; i++ )//5 filas por letra
    {
        printf("\n");
        for (int j = 0; j < 5; j++ )//5 columnas por letra
        {
            printf("%c", letter[i][j] );
        }
    }
}

//función para imprimir nombre o matrícula
void printName(int n, int x, int y, char name[n][x][y])
{
    for(int k = 0; k < n; k++)//tamaño del nombre a imprimir
    {
        printLetter(x,y,name[k]);
        printf("\n");
    }
}


//función printer que será llamada desde el primer thread
void *printer(void *params)
{
    printf("==================\n");
    printName(6, 5, 5, Alexis);
    printf("\n\n");
    printName(9, 5, 5, matAlexis);
    printf("==================\n");
    printName(5, 5, 5, Diego);
    printf("\n\n");
    printName(9, 5, 5, matDiego);
    printf("==================\n");
    pthread_exit(0);//salir del thread
}

//función auxiliar para caluclar el factorial, usada en el thread que calcula n en k
int factorial(int num)
{
  int x = 1;
  for(int i=1; i<=num; i++)
  {
    x*=i;
  }
  return x;
}

//función combinatorial que será llamada desde el tercer thread
void *combinatorial(void *params)
{
    struct thread_args *args = params;//desempaquetar el parámetro para usar cada valor por separado
    /*Esto se debe hacer poque pthread_create solo puede tomar un argumento. Si se encapsulan dos o más argumentos dentro de
    uno solo, se puede evitar esta restricción*/
    combRes = (factorial(args->n)/(factorial(args->n-args->k)*factorial(args->k)));
    pthread_exit(0);
}

void firstThread()
{
  pthread_t tid1;//Declaración del primer thread
  pthread_create( &tid1, NULL, printer, NULL );//Iniciar primer thread
  pthread_join( tid1, NULL );//Esperar a que acabe el prime thread
}

void secondThread(struct thread_args args)
{
  pthread_t tid2;//Declarar segundo thread
  pthread_create(&tid2, NULL, combinatorial, (void*)&args);//Iniciar el segundo thread
  pthread_join( tid2, NULL );//Esperar a que termine el segundo thread
}

int main(int argc, const char * argv[]) {
    //argc siempre va a ser 1 porque el nombre del programa se pasa como primer parámetro
    if ( argc != 3 )//Si no se pasan dos argumentos al programa, hay un error
    {
      fprintf( stderr, "Progam takes 2 parameters\n");
      exit(-1);
    }
    if ( atoi(argv[1]) < atoi(argv[2]) )//En la combinatoria, n debe ser mayor a k
    {
      fprintf( stderr, "n debe ser >= k\n");
      exit(-1);
    }
    struct thread_args args;//Declarar el struct que empaqueta los dos argumentos
    args.n =  atoi(argv[1]);
    args.k = atoi(argv[2]);
    firstThread();
    /*
    Después del primer thread se debe hacer un fork, ya que la función execlp que se debe ejecutar
    crea un proceso hijo que ejecuta un bash y termina al padre, por lo que si se hiciera execlp
    dentro de una pthread, se ejecutaría el comando pero terminaría el programa padre. Al hacer un fork
    hacemos que un proceso hijo ejecute el comando y cuando termina ese proceso hijo, no le va a pasar
    nada al padre (principal)
    */
    int pid;
    pid = fork();//iniciar fork desde esta linea
    if (pid < 0)//si pid < 0 hubo un problema con el fork
    {
      fprintf( stderr, "Fork Failed");
      exit(-1);
    }
    else if (pid == 0)//es el primer fork
    {
      execlp( "/bin/ps", "ps", "-U", "root", "-u" ,"root" ,"u", (char *) NULL);//ejecutar el comando
      /*Si se pone cualquier código en este espacio no se va a ejecutar porque execlp
      va a haber terminado el fork padre (pid = 0)
      */
    }
    else//Seguir ejecutando el proceso padre
    {
      wait( NULL );//Esperar a que termina el fork hijo
      printf("==================\n");
      secondThread(args);
      printf("La combinatoria de %d en %d es %d\n", args.n, args.k, combRes);//Imprimir el resultado obtenido por el segundo thread
      exit(0);
    }
    return 0;
}
