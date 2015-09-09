/**
 *  hello-scheme for illustration how to embed
 *  the tiny scheme interpreter in a C program
 *
 *  2012, OL
 */

#include <stdio.h>
#include <string.h>
#include <tinyscheme/scheme.h>
#include <tinyscheme/dynload.h>


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
 */
pointer func1(scheme *sc, pointer args)
{
  pointer arg;
  pointer retval;
  char    *strarg;
  double  realnumber;
  int     intnumber;
  int     i = 1;

  while( args != sc->NIL )
  {
    if( is_string( arg = pair_car(args)) )
    {
      strarg = string_value( arg );
      printf( "argument %d is string %s\n", i++, strarg );
    }
    else if( is_real( arg = pair_car(args) ) )
    {
      realnumber = rvalue( arg );
      printf( "argument %d is real number %lf\n", i++, realnumber );
    }
    else if( is_integer( arg = pair_car(args) ) )
    {
      intnumber = ivalue( arg );
      printf( "argument %d is integer number %d\n", i++, intnumber );
    }

    args = pair_cdr( args );
  }

  if( i > 1 )
    retval = sc -> T;
  else
    retval = sc -> F;

  return(retval);
}


/*
 * Simple REPL
 */
int main( int argc, char* argv[] )
{
  scheme sc;

  char   cmd_str[80];


  /* intialize the scheme object */
  if( !scheme_init(&sc) ) {
    fprintf(stderr,"Could not initialize!\n");
    return 2;
  }

  /* set standard input and output ports */
  scheme_set_input_port_file(&sc, stdin);
  scheme_set_output_port_file(&sc, stdout);


  /* illustration how to define a "foreign" function
     implemented in C */
  scheme_define(&sc,sc.global_env,mk_symbol(&sc,"func1"),mk_foreign_func(&sc, func1));


  puts("Tiny Scheme REPL:");
  puts("try e.g. the following commands:");
  puts("   (write (+ 1 2))");
  puts("   (func1 \"hello\" 42 1.24)\n");

  do {
    printf("\n>");
    fgets( cmd_str, 80, stdin );
    strip_cr( cmd_str, 80 );

    scheme_load_string( &sc, cmd_str );
  } while(1);


  scheme_deinit(&sc);

  return 0;
}
