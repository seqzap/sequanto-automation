#ifndef SQ_ARDUINO
#include <sequanto/automation.h>
#include <sequanto/thread.h>
#include "config.h"
#include "type_tests_automation.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef SQBool bool_t;
typedef unsigned short UINT16;

static signed long signedLongValue;
static long longValue;
static unsigned long unsignedLongValue;
static signed int signedIntegerValue;
static int integerValue;
static unsigned int unsignedIntegerValue;
static signed short signedShortValue;
static short shortValue;
static unsigned short unsignedShortValue;
static signed char signedCharValue;
static char charValue;
static unsigned char unsignedCharValue;
#ifdef HAVE_INT64_T
static int64_t int64_tValue;
#endif
static float floatValue;
static double doubleValue;
static SQBool boolValue;
static bool_t bool_tValue;
static UINT16 UINT16Value;
static SQByte s_byteArrayData[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
static SQByteArray s_byteArray;

void type_test_init( void )
{
    signedLongValue = 0;
    longValue = 0;
    unsignedLongValue = 0;
    signedIntegerValue = 0;
    integerValue = 0;
    unsignedIntegerValue = 0;
    signedShortValue = 0;
    shortValue = 0;
    unsignedShortValue =0;
    signedCharValue = 0;
    charValue = 0;
    unsignedCharValue = 0;
    floatValue = 0;
    doubleValue = 0;
    boolValue = SQ_FALSE;
    bool_tValue = 0;
    UINT16Value = 0;
    s_byteArray.m_length = sizeof(s_byteArrayData);
    s_byteArray.m_start = s_byteArrayData;
}

void type_test_reset ( void )
{

   sq_type_tests_properties_signed_long_updated ( signedLongValue );
   sq_type_tests_properties_long_updated ( longValue );
   sq_type_tests_properties_unsigned_long_updated ( unsignedLongValue );
   sq_type_tests_properties_signed_integer_updated ( signedIntegerValue );
   sq_type_tests_properties_integer_updated ( integerValue );
   sq_type_tests_properties_unsigned_integer_updated ( unsignedIntegerValue );
   sq_type_tests_properties_signed_short_updated ( signedShortValue );
   sq_type_tests_properties_short_updated ( shortValue );
   sq_type_tests_properties_unsigned_short_updated ( unsignedShortValue );
   sq_type_tests_properties_signed_char_updated ( signedCharValue );
   sq_type_tests_properties_char_updated ( charValue );
   sq_type_tests_properties_unsigned_char_updated ( unsignedCharValue );
   sq_type_tests_properties_float_updated ( floatValue );
   sq_type_tests_properties_double_updated ( doubleValue );
   sq_type_tests_properties_bool_updated ( boolValue );
   sq_type_tests_properties_bool_t_updated ( bool_tValue );
   sq_type_tests_properties_UINT16_updated (UINT16Value );
}

signed long type_test_signed_long_get ( void )
{
#ifndef SQ_ARDUINO
   //sq_log_updated ( signedLongValue, "The value of signed long was queries" );
   sq_logf ( "Returning value of signed long: %i", signedLongValue );
#endif
   return signedLongValue;
}

void type_test_signed_long_set ( signed long _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of signed long value to %i (was %i)", _value, signedLongValue );
#endif
   signedLongValue = _value;
   sq_type_tests_properties_signed_long_updated ( signedLongValue );
}

long type_test_long_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of long: %i", longValue );
#endif
   return longValue;
}

void type_test_long_set ( long _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of long value to %i (was %i)", _value, longValue );
#endif
   longValue = _value;
   sq_type_tests_properties_long_updated ( longValue );
}

unsigned long type_test_unsigned_long_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of unsigned long: %i", unsignedLongValue );
#endif
   return unsignedLongValue;
}

void type_test_unsigned_long_set ( unsigned long _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of unsigned long value to %i (was %i)", _value, unsignedLongValue );
#endif
   unsignedLongValue = _value;
   sq_type_tests_properties_unsigned_long_updated ( unsignedLongValue );
}

signed int type_test_signed_integer_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of signed int: %i", signedIntegerValue );
#endif
   return signedIntegerValue;
}

void type_test_signed_integer_set ( signed int _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of signed int value to %i (was %i)", _value, signedIntegerValue );
#endif
   signedIntegerValue = _value;
   /* sq_type_tests_properties_integer_updated ( NULL, _value ); */
   sq_type_tests_properties_signed_integer_updated ( signedIntegerValue );
}

int type_test_integer_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of int: %i", integerValue );
#endif
   return integerValue;
}

void type_test_integer_set ( int _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of int value to %i (was %i)", _value, integerValue );
#endif
   integerValue = _value;
   sq_type_tests_properties_integer_updated ( integerValue );
}

unsigned int type_test_unsigned_integer_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of unsigned int: %i", unsignedIntegerValue );
#endif
   return unsignedIntegerValue;
}

void type_test_unsigned_integer_set ( unsigned int _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of unsigned int value to %i (was %i)", _value, unsignedIntegerValue );
#endif
   unsignedIntegerValue = _value;
   sq_type_tests_properties_unsigned_integer_updated ( unsignedIntegerValue );
}

signed short type_test_signed_short_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of signed short: %i", signedShortValue );
#endif
   return signedShortValue;
}

void type_test_signed_short_set ( signed short _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of signed short value to %i (was %i)", _value, signedShortValue );
#endif
   signedShortValue = _value;
   sq_type_tests_properties_signed_short_updated ( signedShortValue );
}

short type_test_short_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of short: %i", shortValue );
#endif
   return shortValue;
}

void type_test_short_set ( short _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of short value to %i (was %i)", _value, shortValue );
#endif
   shortValue = _value;
   sq_type_tests_properties_short_updated ( shortValue );
}

unsigned short type_test_unsigned_short_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of unsigned short: %i", unsignedShortValue );
#endif
   return unsignedShortValue;
}

void type_test_unsigned_short_set ( unsigned short _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of unsigned short value to %i (was %i)", _value, unsignedShortValue );
#endif
   unsignedShortValue = _value;
   sq_type_tests_properties_unsigned_short_updated ( unsignedShortValue );
}

signed char type_test_signed_char_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of signed char: %i", signedCharValue );
#endif
   return signedCharValue;
}

void type_test_signed_char_set ( signed char _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of signed char value to %i (was %i)", _value, signedCharValue );
#endif
   signedCharValue = _value;
   sq_type_tests_properties_signed_char_updated ( signedCharValue );
}

char type_test_char_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of char: %i", charValue );
#endif
   return charValue;
}

void type_test_char_set ( char _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of char value to %i (was %i)", _value, charValue );
#endif
   charValue = _value;
   sq_type_tests_properties_char_updated ( charValue );
}

unsigned char type_test_unsigned_char_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value unsigned char: %i", unsignedCharValue );
#endif
   return unsignedCharValue;
}

void type_test_unsigned_char_set ( unsigned char _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of unsigned char value to %i (was %i)", _value, unsignedCharValue );
#endif
   unsignedCharValue = _value;
   sq_type_tests_properties_unsigned_char_updated ( unsignedCharValue );
}

#ifdef HAVE_INT64_T
int64_t type_test_int64_t_get ( void )
{
   //sq_log_updated ( int64_tValue, "The value of int64_t was queries" );
   sq_logf ( "Returning value of signed long: %i", int64_tValue );
   return int64_tValue;
}

void type_test_int64_t_set ( int64_t _value )
{
   sq_logf ( "Setting value of int64_t value to %i (was %i)", _value, int64_tValue );
   int64_tValue = _value;
   /* sq_type_tests_properties_int64_t_updated ( int64_tValue ); */
}
#endif

float type_test_float_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of float: %f", floatValue );
#endif
   return floatValue;
}

void type_test_float_set ( float _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of float value to %f (was %f)", _value, floatValue );
#endif
   floatValue = _value;
   sq_type_tests_properties_float_updated ( floatValue );
}

double type_test_double_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of double: %f", doubleValue );
#endif
   return doubleValue;
}

void type_test_double_set ( double _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of double value to %f (was %f)", _value, doubleValue );
#endif
   doubleValue = _value;
   sq_type_tests_properties_double_updated ( doubleValue );
}

SQBool type_test_bool_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of bool: %b", boolValue );
#endif
   return boolValue;
}

void type_test_bool_set ( SQBool _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of bool value to %b (was %b)", _value, boolValue );
#endif
   boolValue = _value;
   sq_type_tests_properties_bool_updated ( boolValue );
}

bool_t type_test_bool_t_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of bool_t: %b", bool_tValue );
#endif
   return bool_tValue;
}

void type_test_bool_t_set ( bool_t _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of bool_t value to %b (was %b)", _value, bool_tValue );
#endif
   bool_tValue = _value;
   sq_type_tests_properties_bool_updated ( bool_tValue );
}

UINT16 type_test_UINT16_get ( void )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Returning value of UINT16: %i", UINT16Value );
#endif
   return UINT16Value;
}

void type_test_UINT16_set ( UINT16 _value )
{
#ifndef SQ_ARDUINO
   sq_logf ( "Setting value of UINT16 value to %i (was %i)", _value, UINT16Value );
#endif
   UINT16Value = _value;
   sq_type_tests_properties_UINT16_updated ( UINT16Value );
}


void type_test_SQByteArray_set ( SQByteArray * _value )
{
    size_t i = 0;
    for ( ; i < _value->m_length && i < sizeof(s_byteArrayData); i++ )
    {
        s_byteArrayData[i] = _value->m_start[i];
    }
}

void type_test_const_SQByteArray_set ( const SQByteArray * _value )
{
    size_t i = 0;
    for ( ; i < _value->m_length && i < sizeof(s_byteArrayData); i++ )
    {
        s_byteArrayData[i] = _value->m_start[i];
    }
}

SQByteArray * type_test_SQByteArray_get ( void )
{
    return sq_byte_array_create_copy ( s_byteArrayData, sizeof(s_byteArrayData) );
}

const SQByteArray * type_test_const_SQByteArray_get ( void )
{
    return &s_byteArray;
}


#ifdef SQ_ARDUINO
void setup ( void )
{
    SequantoAutomation::init();
    type_test_init();
}

void loop ( void )
{
    SequantoAutomation::poll();
}

#else
int main ( int argc, char * argv[] )
{
#ifndef SQ_DISABLE_AUTOMATION_INTERFACE
   static SQServer server;

   sq_init ();

   sq_server_init ( &server, 4321 );

   type_test_init();

   while ( SQ_TRUE )
   {
      if ( sq_thread_is_supported() )
      {
         sq_system_sleep ( 1000 );
      }
      sq_server_poll ( &server );
   }

   sq_shutdown ();
#endif

   SQ_UNUSED_PARAMETER(argc);
   SQ_UNUSED_PARAMETER(argv);
}
#endif

int function_with_many_parameters ( int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9,
                                    int b0, int b1, int b2, int b3, int b4, int b5, int b6, int b7, int b8, int b9 )
{
    return a0 + a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9
        +  b0 + b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 + b9;
}

#ifdef __cplusplus
}
#endif
