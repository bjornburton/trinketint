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
# include <util/delay.h> // need to delay
# include <stdlib.h>

/* LED port */
# define LED_RED PORTB1
# define LED_RED_DD DDB1
# define ON 1
# define OFF 0

/* Function Declatations */
void delay(unsigned intervals);
void ledcntl(char state);
void initTimerCounter1(void);


int main()
{
  DDRB |= (1<<LED_RED_DD);
  ledcntl(ON);       //turn the LED off
  void initTimerCounter1(void);

  TCNT1 = 0;      //reset
  
  for (;;) // forever
  {

  }  

return 0; // it's the right thing to do!
}

/* run-time variable delay in 100 us intervals */
void delay(unsigned intervals)
{
  while(intervals-- > 0)
        _delay_us(100); // _delay_us takes a constant only
}


/* simple led control */
void ledcntl(char state)
{
  PORTB = state ? PORTB | (1<<LED_RED) : PORTB ^ (1<<LED_RED);
}



void initTimerCounter1(void)
{
 GTCCR = 0;
 TCCR0A = 0;
 TCCR1 &= ~( (1<<COM1A1) | (1<<COM1A0) );
 TCCR1 &= ~( (1<<COM1B1) | (1<<COM1B0) );

 /* set a long prescale */
 TCCR1 = ( (1<<CS13) | (1<<CS12) );

 /* Timer/counter 1 ovf int enable */
 TIMSK = (1<<TOIE0) | (1<<TOIE1);

 /* Timer/Counter1 Output Compare Interrupt disable */
 // TIMSK &= ~(1<<OCIE1A);

/* global interupt enable flag */
 sei();
}

ISR(TIMER1_OVF_vect)
{
 ledcntl(OFF); 
 TCNT1 = 0;      //reset
}
