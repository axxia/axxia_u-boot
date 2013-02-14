#include <common.h>
#include <config.h>

/*
  ----------------------------------------------------------------------
  idisplay
*/

void inline idisplay( inumber_t * number ) {

  printf( "%lu: value=%lu shifted=%d\n",
          IVALUE( ( number ) ), number->value, number->shifted );

  return;

}

/*
  ----------------------------------------------------------------------
  imaximize
*/

void inline imaximize( inumber_t * number ) {

  int shifted_ = 0;

  while( 0 == ( 0x80000000UL & ISHIFT( number->value, shifted_ ) ) ) {

    ++ shifted_;

  }

  number->value = ISHIFT( number->value, shifted_ );
  number->shifted += shifted_;

  return;

}

/*
  ----------------------------------------------------------------------
  iminimize
*/

void inline iminimize( inumber_t * number ) {

  int shifted_ = 0;

  while( 0 == ( 1 & ISHIFT( number->value, shifted_ ) ) ) {

    -- shifted_;

  }

  number->value = ISHIFT( number->value, shifted_ );
  number->shifted += shifted_;

  while( 0x10000 < number->value ) {

    number->value >>= 1;
    -- number->shifted;

  }

  return;

}

/*
  ----------------------------------------------------------------------
  idivide
*/

void idivide( inumber_t * numerator, inumber_t * denominator,
              inumber_t * quotient ) {

  imaximize( numerator );
  iminimize( denominator );
  quotient->value = numerator->value / denominator->value;
  quotient->shifted = numerator->shifted - denominator->shifted;

  return;

}

/*
  ----------------------------------------------------------------------
  imultiply
*/

void imultiply( inumber_t * multiplicand, inumber_t * multiplier,
                inumber_t * product ) {

  iminimize( multiplicand );
  iminimize( multiplier );
  product->value = multiplicand->value * multiplier->value;
  product->shifted = multiplicand->shifted + multiplier->shifted;

  return;

}
