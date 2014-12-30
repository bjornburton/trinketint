/**************************************
Trinketint
Interrupt Trinket led blinker!
2014-12-29
Bjorn Burton

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

/* Function Declarations */
void delay(unsigned intervals);
void ledcntl(char state);
void initTimerCounter1(void);

/* Global variables */
volatile char intcount = 0; 

int main(void)
{
  DDRB |= (1<<LED_RED_DD);
  ledcntl(ON);       //turn the LED on
  initTimerCounter1();

 for (;;) // forever
  {

  if(intcount > 10) //after about 5 seconds, turn off
    {
     ledcntl(OFF);
     intcount = 0;
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

 /* set a long prescale */
 TCCR1 = ((1<<CS10) | (1<<CS11) | (1<<CS12) | (1<<CS13));


 /* Timer/counter 1 ovf int enable */
 TIMSK |= (1<<TOIE1);


 TCNT1 = 12;      //reset
 
 /* global interupt enable flag */
 sei();
}

ISR(TIMER1_OVF_vect)
{
 intcount++;
 //TCNT1 = 12;      //reset
}
