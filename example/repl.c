/*
 *  A threaded server
 *  by Martin Broadhurst (www.martinbroadhurst.com)
 *  Compile with -pthread
 */

#include <stdio.h>
#include <string.h> /* memset() */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <fcntl.h>
#include <getopt.h>

#include <tinyscheme/scheme.h>
#include <tinyscheme/dynload.h>

#define PORT       "37146" /* Port to listen on */
#define BACKLOG        10  /* Passed to listen() */
#define MAX_BUF_SIZE 1000
#define INIT_FILE  "init.scm"

static char scheme_init_file[80];

/* scheme_load_string does not like
   carriage returns so strip them out */
void strip_cr( char *p, int max_len )
{
  int i;

  for( i=0; i < max_len && p[i]!='\0'; ++i )
    ;

  if( i > 0 && p[i-1]=='\n' )
    p[i-1] = '\0';
}


/**
 * illustration of a C function binding

  try:
  (func1 "hello" 42 1.24)
 */
static pointer func1(scheme *sc, pointer args)
{
  pointer arg;
  pointer retval;
  char    *strarg;
  double  realnumber;
  int     intnumber;
  int     i = 1;
  char    outbuf[80];

  while( args != sc->NIL )
  {
    outbuf[0] = '\0';
    if( is_string( arg = pair_car(args)) )
    {
      strarg = string_value( arg );
      snprintf( outbuf, sizeof(outbuf), "argument %d is string %s\n", i++, strarg );
    }
    else if( is_real( arg = pair_car(args) ) )
    {
      realnumber = rvalue( arg );
      snprintf( outbuf, sizeof(outbuf), "argument %d is real number %lf\n", i++, realnumber );
    }
    else if( is_integer( arg = pair_car(args) ) )
    {
      intnumber = ivalue( arg );
      snprintf( outbuf, sizeof(outbuf), "argument %d is integer number %d\n", i++, intnumber );
    }

    if( outbuf[0] != '\0' )
      putstr( sc, outbuf );

    args = pair_cdr( args );
  }

  if( i > 1 )
    retval = sc -> T;
  else
    retval = sc -> F;

  return(retval);
}


static int read_init_file( scheme* sc, FILE* fd_socket )
{
  FILE* fp;

  fp = fopen( scheme_init_file, "r" );
  if( fp != NULL )
  {
    if( fd_socket )
      fprintf( fd_socket, "initialized with init file %s\n", scheme_init_file );

    scheme_load_named_file( sc, fp, scheme_init_file );
    if( sc->retcode!=0 && fd_socket ) {
      fprintf(fd_socket, "Errors encountered reading %s\n", scheme_init_file );
    }
    fclose( fp );
    return sc->retcode;
  }
  else
    return 0;
}

static void init_ff( scheme* sc )
{
  /* illustration how to define a "foreign" function
     implemented in C */
  scheme_define( sc, sc->global_env, mk_symbol( sc, "func1" ), mk_foreign_func( sc, func1 ) );
}

/* read-print-eval-loop invoked from socket handler thread */
static void *repl(void *pnewsock)
{
  /* send(), recv(), close() */
  int sockfd = *((int*)pnewsock);
  FILE *fdin, *fdout;
  scheme sc;

  /* intialize the scheme object */
  if( !scheme_init(&sc) ) {
    fprintf(stderr,"Could not initialize scheme interpreter!\n");
    return NULL;
  }

  fdin = fdopen( sockfd, "r" );
  fdout = fdopen( sockfd, "w" );

  /* set standard input and output ports */
  sc.interactive_repl=1;
  scheme_set_input_port_file(&sc, fdin );
  scheme_set_output_port_file(&sc, fdout );

  fprintf( fdout, "tinyscheme %s\n", tiny_scheme_version );
  read_init_file( &sc, fdout );
  init_ff( &sc );
  fprintf( fdout, "(quit) exits repl session.\n" );
  scheme_load_named_file( &sc, fdin, 0);

  printf("close connection!\n");

  fclose( fdin );
  fclose( fdout );
  close( sockfd );
  scheme_deinit(&sc);

  return NULL;
}

void print_help( const char* app_name )
{
  printf("%s: tinyscheme repl server\n\n", app_name );
  printf("Invocation: %s [ options ]\n\n", app_name );
  printf("Options:\n");
  printf("--port\n-p\n");
  printf("\tSpecifies the port the server is connected to. Default port %s is used\n", PORT);
  printf("\tin case nothing is specified.\n\n");
  printf("--console\n-c\n");
  printf("\tConnect repl server to standard I/O.\n\n");
  printf("--init\n-i\n");
  printf("\tSpecifies the scheme init script loaded after start up.\n\n");
  printf("--help\n-h\n");
  printf("\tThis help screen.\n\n");
  printf("(C) GNU-General Public Licence, written by Otto Linnemann, 2015\n\n");
}

int main( int argc, char* argv[] )
{
  int sock;
  char port[6];
  pthread_t thread;
  struct addrinfo hints, *res;
  int reuseaddr = 1; /* true */
  int optindex, optchar, error = 0;
  int console_flag = 0;
  const struct  option long_options[] =
  {
    { "help",     no_argument,        NULL,   'h' },
    { "port",     required_argument,  NULL,   'p' },
    { "init",     required_argument,  NULL,   'i' },
    { NULL }
  };

  /* default arguments */
  strncpy( scheme_init_file, INIT_FILE, sizeof(scheme_init_file) );
  strncpy( port, PORT, sizeof(port) );

  /* parse command line arguments, port, init file, etc */
#if HAVE_GETOPT_LONG
  /*
   *  retrieve command line options, currently only -w
   */
  while( ( optchar = getopt_long( argc, argv, "hcp:i:", long_options, &optindex ) ) != -1 )
  {
    switch ( optchar )
    {
      case 'h':
        print_help( argv[0] );
        return -1;
        break;

      case 'c':
        console_flag = 1;
        break;

      case 'p':
        strncpy(port, optarg, sizeof(port) );
        break;

      case 'i':
        strncpy( scheme_init_file, optarg, sizeof(scheme_init_file) );
        break;

      default:
       fprintf(stderr, "input argument error!\n");
       return -1;
    }
  }

  argv += (optind-1);
  argc -= (optind-1);
#endif

  printf( "starting tinyscheme %s server\n", tiny_scheme_version );

  /* main loop */
  if( console_flag )
  {
    /* standard I/O */
    scheme sc;

    /* intialize the scheme object */
    if( !scheme_init(&sc) ) {
      fprintf(stderr,"Could not initialize scheme interpreter!\n");
      return -1;
    }

    /* set standard input and output ports */
    sc.interactive_repl=1;
    scheme_set_input_port_file(&sc, stdin );
    scheme_set_output_port_file(&sc, stdout );
    printf( "tinyscheme %s\n", tiny_scheme_version );
    read_init_file( &sc, stdout );
    init_ff( &sc );
    printf( "(quit) exits repl session.\n" );

    scheme_load_named_file( &sc, stdin, 0 );
    printf("exit repl!\n");
    scheme_deinit(&sc);
  }
  else
  {
    /* socket I/O */

    /* Get the address info */
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(NULL, port, &hints, &res) != 0) {
      perror("getaddrinfo");
      return 1;
    }

    /* Create the socket */
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock == -1) {
      perror("socket");
      return 1;
    }

    /* Enable the socket to reuse the address */
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(int)) == -1) {
      perror("setsockopt");
      return 1;
    }

    /* Bind to the address */
    if (bind(sock, res->ai_addr, res->ai_addrlen) == -1) {
      perror("bind");
      return 0;
    }

    freeaddrinfo(res);

    /* Listen */
    if (listen(sock, BACKLOG) == -1) {
      perror("listen");
      return 0;
    }

    printf( "waiting for connections on port %s ...\n", port );

    while (1)
    {
      size_t size = sizeof(struct sockaddr_in);
      struct sockaddr_in their_addr;
      int newsock = accept( sock, (struct sockaddr*)&their_addr,  ((socklen_t *)&size) );
      if (newsock == -1)
      {
        perror("accept");
      }
      else
      {
        printf( "Got a connection from %s on port %d\n",
                inet_ntoa(their_addr.sin_addr), htons(their_addr.sin_port));

        if ( pthread_create(&thread, NULL, repl, &newsock) != 0 ) {
          fprintf(stderr, "Failed to create thread\n");
        }
      }
    } /* while(1) */
  }

  close(sock);

  return 0;
}
