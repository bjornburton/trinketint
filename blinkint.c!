/**************************************
blinkint
A most inefficient Trinket led blinker!
2014-12-30 - Bjorn Burton
Just for fun.
**************************************/
// AVR clock frequency in Hz, used by util/delay.h
# define F_CPU 8000000UL

# include <avr/io.h> // need some port access
# include <avr/interrupt.h> // have need of an interrupt
# include <util/delay.h> // need to delay

# include <stdlib.h>
# include <math.h>

/* LED port */
# define LED_RED PORTB1
# define LED_RED_DD DDB1
# define ON 1
# define OFF 0

/* amplitude */
# define Y_STEPS 100.0F

/* y position */
# define X_LIMIT_RIGHT 100.0F
# define X_LIMIT_LEFT 0.0F
# define X_STEPS  (X_LIMIT_RIGHT - X_LIMIT_LEFT)
# define RIGHT 1
# define LEFT -1

/* Function Declatations */
void delay(unsigned intervals);
void ledcntl(char state);
void initTimerCounter1(void);


int main()
 {
  unsigned x_position = X_LIMIT_LEFT; // starting on the left
  char x_direction = RIGHT; // moving toward the right
 
    // set the data direction register to output-mode for the LED
  DDRB |= (1<<LED_RED_DD);
  

  for (;;) // forever - two loops per cycle
      {
       // figure how far into the wave we are
       float wave_portion = x_position/X_STEPS; 

       // sine amplitude is used for illumination duration 
       char amplitude = Y_STEPS * sin(M_PI*wave_portion); 
       
       ledcntl(ON); // flip the led on
       delay(amplitude); // on for the duration of wave amplitude
        
       ledcntl(OFF); // now flip it off
       delay(Y_STEPS - amplitude); // off for the remainder
        
       { // managment of location on wave
        x_position += x_direction;
        if(x_position == X_LIMIT_RIGHT) x_direction = LEFT;
        if(x_position == X_LIMIT_LEFT)  x_direction = RIGHT;
       }

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
    TCCR1 = 0;                  //stop the timer
    TCNT1 = 0;                  //zero the timer
    GTCCR = _BV(PSR1);          //reset the prescaler
    OCR1A = 243;                //set the compare value
    OCR1C = 243;
    TIMSK = _BV(OCIE1A);        //interrupt on Compare Match A
    //start timer, ctc mode, prescaler clk/16384    
    TCCR1 = _BV(CTC1) | _BV(CS13) | _BV(CS12) | _BV(CS11) | _BV(CS10);
    sei();
}

ISR(TIMER1_COMPA_vect)
{
    //comment out one of the two lines below
    digitalWrite(4, LOW);       //turn the LED off
    //PINB |= _BV(PINB4);         //flash the LED by toggling PB4
}
