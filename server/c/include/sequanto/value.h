/*
 * Copyright 2010 Rasmus Toftdahl Olesen <rasmus@sequanto.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you
 * may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef SEQUANTO_VALUE_H_
#define SEQUANTO_VALUE_H_

#include <sequanto/types.h>
#include <sequanto/stream.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
	VALUE_TYPE_NO_VALUE,
	VALUE_TYPE_INTEGER,
	VALUE_TYPE_FLOAT,
	VALUE_TYPE_BOOLEAN,
	VALUE_TYPE_STRING,
	VALUE_TYPE_SQSTRINGOUT = VALUE_TYPE_STRING,
	VALUE_TYPE_BYTE_ARRAY,
	VALUE_TYPE_NULL,
   VALUE_TYPE_VOID,
} SQValueType;

typedef struct
{
	SQValueType m_type;
   union
   {
      int m_integerValue;
      float m_floatValue;
      SQBool m_booleanValue;
      char * m_stringValue;
      struct
      {
         SQByte * m_byteArrayValue;
         size_t m_byteArrayLength;
      } ArrayValue;
   } Value;
} SQValue;

/**
 * Initialize the SQValue as having no value.
 */
void sq_value_init ( SQValue * _value );

/**
 * Initialize the SQValue as an integer.
 */
void sq_value_integer ( SQValue * _value, int _initialValue);

/**
 * Initialize the SQValue as a float.
 */
void sq_value_float ( SQValue * _value, float _initialValue);

/**
 * Initialize the SQValue as a boolean.
 */
void sq_value_boolean ( SQValue * _value, SQBool _initialValue);

/**
 * Initialize the SQValue as a string.
 *
 * Please note that the given value will _not_ be copied, the string will be free'ed when sq_value_free(...) is called.
 */
void sq_value_string ( SQValue * _value, char * _initialValue);

/**
 * Initialize the SQValue as a string.
 *
 * Please note that the given value will be copied and the string will be free'ed when sq_value_free(...) is called.
 */
void sq_value_string_copy ( SQValue * _value, const char * const _initialValue);

/**
 * Initialize the SQValue as a byte array.
 *
 * The initial value is _not_ copied.
 *
 * @see sq_value_string
 */
void sq_value_byte_array ( SQValue * _value, SQByte * _initialValue, size_t _byteArrayLength );

/**
 * Initialize the SQValue as a null.
 */
void sq_value_null ( SQValue * _value );

/**
 * Write the given value to the given stream.
 */
SQBool sq_value_write ( SQValue * _value, SQStream * _stream );

/**
 * Free any memory that the given SQValue is consuming (string or byte array) and set the type to "NO VALUE".
 */
void sq_value_free ( SQValue * _value );

/**
 * Write values from _start to _start + _numberOfValues separated by space.
 */
SQBool sq_values_write ( SQValue * _start, size_t _numberOfValues, SQStream * _stream );

/**
 * Parse a list of values separated by spaces and terminated by \r\n from _buffer.
 *
 * @return the number of values read.
 */
size_t sq_values_parse ( SQValue * _start, size_t _maximumValues, SQByte * _buffer );

#ifdef __cplusplus
}
#endif

#endif /* SEQUANTO_VALUE_H_ */