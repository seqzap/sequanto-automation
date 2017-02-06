#include "SequantoAutomation.h"
#include "code/automation_automation.h"
/* To try this example use the menu item:
 *
 *     Tools->Generate Automation
 *
 * Before compiling.
 *
 * BEGIN AUTOMATION
 *
 * name arduino_io
 * property /sequanto_automation_version sequanto_automation_version
 *
 * property /digital/(2..54)/direction digital_direction_get digital_direction_set
 * property /digital/(2..54)/pin digital_pin_get digital_pin_set
 * #property /digital/(2..54)/counter digital_counter_get digital_counter_set
 * #property /digital/(2..54)/counter_enabled digital_counter_enabled_get digital_counter_enabled_set
 * #property /digital/(2..54)/count_on_high2low digital_counter_high2low_get digital_counter_high2low_set
 * #property /digital/(2..54)/count_on_low2high digital_counter_low2high_get digital_counter_low2high_set
 *
 * # property /digital/(0..14)/mode digital_mode_get digital_mode_set
 * # property /digital/(0..14)/counter digital_counter_get digital_counter_set
 * # property /digital/(0..14)/pin digital_pin_get digital_pin_set
 *
 * function /analog/use_default_reference analog_in_use_default_reference
 * function /analog/use_external_reference analog_in_use_external_reference
 * property /analog/(0..5)/raw analog_in_get_raw_value
 * property /analog/(0..5)/value analog_in_get_value
 *
 * END AUTOMATION */

/* Skip the first two pins, they are used by the USB port for communication. */
#define PIN_OFFSET 2
#ifdef  ARDUINO_AVR_MEGA2560
#define NUMBER_OF_PINS 54
#else
#define NUMBER_OF_PINS 13
#endif

static char buff[10];

const char * sequanto_automation_version ( void )
{
    sq_get_constant_string_copy ( SQ_STRING_CONSTANT(SQ_SCM_REVISION), buff );
    return buff;
}

enum DIGITAL_PIN_DIRECTION {
    DIGITAL_PIN_INPUT,
    DIGITAL_PIN_OUTPUT
};

static int s_counters[NUMBER_OF_PINS];
static SQBool io_direction[NUMBER_OF_PINS];
static SQBool io_last_read[NUMBER_OF_PINS];
static SQBool io_last_written[NUMBER_OF_PINS];
static SQBool io_counter_enable[NUMBER_OF_PINS];
static SQBool io_trig_h2l[NUMBER_OF_PINS];
static SQBool io_trig_l2h[NUMBER_OF_PINS];

static const char DIGITAL_PIN_INPUT_TEXT[] SQ_CONST_VARIABLE = "Input";
static const char DIGITAL_PIN_OUTPUT_TEXT[] SQ_CONST_VARIABLE = "Output";

SQBool digital_pin_get ( int _pin )
{
    if ( io_direction[_pin] == SQ_TRUE )
    {
      return io_last_written[_pin];
    }
    else
    {
      return io_last_read[_pin];
    }
}

void digital_pin_set ( int _pin, SQBool _value )
{
    //if ((io_direction& PIN_MASK(_pin)) != 0)
    {
        digitalWrite ( _pin, _value == SQ_TRUE ? HIGH : LOW );
        io_last_written[_pin] = _value;
        //sq_digital_pin_updated ( _pin, _value );
    }
    /*
      else
      {
      sq_logf ( "Trying to set pin %i, which is not an output pin.", _pin );
      }
    */
}

const char * digital_direction_get ( int _pin )
{
    if ( io_direction[_pin] == SQ_TRUE )
    {
        sq_get_constant_string_copy(DIGITAL_PIN_OUTPUT_TEXT, buff);
    }
    else
    {
        sq_get_constant_string_copy(DIGITAL_PIN_INPUT_TEXT, buff);
    }
    return buff;
}

void digital_direction_set ( int _pin, const char * _mode )
{
    enum DIGITAL_PIN_DIRECTION dir = DIGITAL_PIN_INPUT;
    if ( SQ_CONSTANT_STRCMP ( _mode, DIGITAL_PIN_INPUT_TEXT ) == 0 )
    {
        dir = DIGITAL_PIN_INPUT;
    }
    else if ( SQ_CONSTANT_STRCMP ( _mode, DIGITAL_PIN_OUTPUT_TEXT ) == 0 )
    {
        dir = DIGITAL_PIN_OUTPUT;
    }
    else
    {
        //sq_logf ( "Trying to set illegal mode: %s", _mode );
        return;
    }

    switch ( dir )
    {
    case DIGITAL_PIN_INPUT:
        pinMode ( _pin, INPUT );
        /* Set pull-up resistor. */
        digitalWrite ( _pin, HIGH );
        //sq_digital_pin_updated ( _pin, digital_pin_get(_pin) );
        io_direction[_pin] = SQ_FALSE;
        break;

    case DIGITAL_PIN_OUTPUT:
        pinMode ( _pin, OUTPUT );
        digitalWrite ( _pin, LOW );
        io_direction[_pin] = SQ_TRUE;
        break;
    }
}

int digital_counter_get ( int _pin )
{
    return s_counters[_pin];
}

void digital_counter_set ( int _pin, int _counter )
{
    s_counters[_pin] = _counter;
}

SQBool digital_counter_enabled_get ( int _pin )
{
    return io_counter_enable[_pin];
}

void digital_counter_enabled_set ( int _pin, SQBool _value )
{
    io_counter_enable[_pin] = _value;
}

SQBool digital_counter_high2low_get ( int _pin )
{
    return io_trig_h2l[_pin];
}

void digital_counter_high2low_set ( int _pin, SQBool _value )
{
    io_trig_h2l[_pin] = _value;
}

SQBool digital_counter_low2high_get ( int _pin )
{
    return io_trig_l2h[_pin];
}

void digital_counter_low2high_set ( int _pin, SQBool _value )
{
    io_trig_l2h[_pin] = _value;
}

int analog_in_get_value ( int _pin )
{
    unsigned int ret = analogRead(_pin);
    ret *= 49;
    ret += 5;
    ret /= 10;
    return (int) ret;
}

int analog_in_get_raw_value ( int _pin )
{
    return analogRead(_pin);
}

void analog_in_use_default_reference ( void  )
{
    analogReference ( DEFAULT );
}

void analog_in_use_external_reference ( void  )
{
    analogReference ( EXTERNAL );
}

void setup ( void )
{
    int i;
    for ( i = PIN_OFFSET; i < NUMBER_OF_PINS; i++ )
    {
        pinMode ( i, INPUT);
        digitalWrite ( i, HIGH );   // pull-up
        s_counters[i] = 0;
        io_direction[i] = SQ_FALSE;
        io_last_read[i] = SQ_FALSE;
        io_last_written[i] = SQ_FALSE;
        io_counter_enable[i] = SQ_FALSE;
        io_trig_h2l[i] = SQ_TRUE;
        io_trig_l2h[i] = SQ_FALSE;
    }
    SequantoAutomation::init();
}

//unsigned int inputs = PIND | (((unsigned int)PINB) << 8 );
//unsigned int changed, trigged = 0;

void loop ( void )
{
    int i;
    SequantoAutomation::poll();
    
    for ( i = PIN_OFFSET ; i < NUMBER_OF_PINS ; i++ )
    {
        if ( io_direction[i] == SQ_FALSE )
        {
          SQBool read = digitalRead(i) == HIGH ? SQ_TRUE : SQ_FALSE;
          if ( read != io_last_read[i] )
          {
             //sq_digital_pin_updated ( i, digital_pin_get(i) );
          
            if ( io_counter_enable[i] == SQ_TRUE )
            {
              if ( read == SQ_FALSE && io_trig_h2l[i] == SQ_TRUE )
              {
                  s_counters[i]++;
              }
              if ( read == SQ_TRUE && io_trig_l2h[i] == SQ_TRUE )
              {
                  s_counters[i]++;
              }
            }
            io_last_read[i] = read;
          }
        }
    }
}
#include "code/automation_automation.c"

