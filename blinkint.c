/**************************************
Trinketint
Interrupted Trinket led blinker!
2014-12-29
Bjorn Burton

Just for fun.
**************************************/
// AVR clock frequency in Hz, used by util/delay.h
# define F_CPU 8000000UL

# include <avr/io.h> // need some port access
# include <avr/interrupt.h> // have need of an interrupt
# include <avr/sleep.h> // have need of sleep
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
volatile char overflow = 0; 

int main(void)
{

 /* set the led port direction */
  DDRB |= (1<<LED_RED_DD);

 /* turn the led on */
  ledcntl(ON);       //turn the LED on

 /* set up the timer */
  initTimerCounter1();

 /* configure sleep_mode() to go to "idle". Idle allows
    the counters and comparator to continue during sleep. */
  MCUCR &= ~(1<<SM1); 
  MCUCR &= ~(1<<SM0);

 for (;;) // forever
  {
   static unsigned char intcount = 0; 
  
  /* preset the counter at each itteration */
  TCNT1 = 12;      //reset counter to count 244: 256-244=12
 
 /* now we wait in idle for any interrupt event */
  sleep_mode();

  /* some interrupt was detected! */

  if(overflow) // overflow check
    {
      if(intcount++ == 1) //toggle after about 1/2 second
        {
         static char toggle = 0;
         
         if(toggle = (toggle)?0:1) ledcntl(ON);
           else ledcntl(OFF);

         intcount = 0;
         }
    overflow = 0; //reset int flag
    }
  }  

return 0; // it's the right thing to do!
}


/* simple led control */
void ledcntl(char state)
{
  PORTB = state ? PORTB | (1<<LED_RED) : PORTB & ~(1<<LED_RED);
}


/* configure the interrupt */
void initTimerCounter1(void)
{
 //GTCCR = 0;
 //TCCR0A = 0;
 //TCCR1 &= ~( (1<<COM1A1) | (1<<COM1A0) );
 //TCCR1 &= ~( (1<<COM1B1) | (1<<COM1B0) );

 /* set a very long prescal */
 TCCR1 = ((1<<CS10) | (1<<CS11) | (1<<CS12) | (1<<CS13));

 /* Timer/counter 1 ovf int enable */
 TIMSK |= (1<<TOIE1);

 /* global interupt enable flag */
 sei();
}

/* this is not much of an ISR */
ISR(TIMER1_OVF_vect)
{
 overflow++;
}
