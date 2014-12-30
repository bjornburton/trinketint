/**************************************
blinkint
Interrupt Trinket led blinker!
2014-12-30 - Bjorn Burton
Just for fun.
**************************************/
// AVR clock frequency in Hz, used by util/delay.h
# define F_CPU 8000000UL

# include <avr/io.h> // need some port access
# include <avr/interrupt.h> // have need of an interrupt
# include <stdlib.h>

/* LED port */
# define LED_RED PORTB1
# define LED_RED_DD DDB1
# define ON 1
# define OFF 0

/* Misc */
# define TRUE 1
# define FALSE 0

/* Function Declatations */
void delay(unsigned intervals);
void ledcntl(char state);
void initTimerCounter1(void);

/* Global variables */
volatile char flagint = FALSE; 

int main(void)
{
  DDRB |= (1<<LED_RED_DD);
  ledcntl(ON);       //turn the LED off
  initTimerCounter1();

  for (;;) // forever
  {

  if(flagint)
    {
     ledcntl(OFF);
     flagint=FALSE;
    }

  }  

return 0; // it's the right thing to do!
}


/* simple led control */
void ledcntl(char state)
{
  PORTB = state ? PORTB | (1<<LED_RED) : PORTB & ~(1<<LED_RED);
}



void initTimerCounter1(void)
{
 //GTCCR = 0;
 //TCCR0A = 0;
 //TCCR1 &= ~( (1<<COM1A1) | (1<<COM1A0) );
 //TCCR1 &= ~( (1<<COM1B1) | (1<<COM1B0) );

 /* set a prescale */
 TCCR1 = (1<<CS10);

 /* Timer/counter 1 ovf int enable */
 TIMSK |= (1<<TOIE1);

 /* Timer/Counter1 Output Compare Interrupt disable */

  TCNT1 = 0;      //reset
 
 /* global interupt enable flag */
 sei();
}

ISR(TIMER1_OVF_vect)
{
 flagint = TRUE;
 TCNT1 = 0;      //reset
}
