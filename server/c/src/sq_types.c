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

#include <string.h>

#include "config.h"

#include "sequanto/types.h"

char sq_external_get_next_fixed_length ( SQStringOut * _string )
{
    return (_string->Data.m_text)[_string->m_index++];
}

SQBool sq_external_has_more_fixed_length ( SQStringOut * _string )
{
    return ( _string->m_index < _string->Extra.m_length ) ? SQ_TRUE : SQ_FALSE;
}

SQStringOut sq_external_fixed_length_string (char * _text, int _length)
{
    SQStringOut so;
    so.GetNext = sq_external_get_next_fixed_length;
    so.HasMore = sq_external_has_more_fixed_length;
    so.m_index = 0;
    so.Data.m_text = _text;
    so.Extra.m_length = _length;
    return so;
}

SQByteArray * sq_byte_array_create_prealloc ( size_t _length )
{
    SQByteArray * ret = (SQByteArray*) malloc ( sizeof(SQByteArray) );
    ret->m_start = (SQByte*) malloc ( _length * sizeof(SQByte) );
    ret->m_length = _length;
    return ret;
}

SQByteArray * sq_byte_array_create ( SQByte * _start, size_t _length )
{
    SQByteArray * ret = (SQByteArray*) malloc ( sizeof(SQByteArray) );
    ret->m_start = _start;
    ret->m_length = _length;
    return ret;
}

SQByteArray * sq_byte_array_create_copy ( SQByte * _start, size_t _length )
{
    SQByteArray * ret = sq_byte_array_create_prealloc ( _length );
    memcpy ( ret->m_start, _start, _length );
    return ret;
}

SQByteArray * sq_byte_array_clone ( SQByteArray * _array )
{
    SQByte * data = (SQByte*) malloc ( _array->m_length );
    memcpy ( data, _array->m_start, _array->m_length );
    return sq_byte_array_create ( data, _array->m_length );
}

void sq_byte_array_free ( SQByteArray * _array, SQBool _alsoFreeData )
{
    if ( _alsoFreeData == SQ_TRUE )
    {
        free ( _array->m_start );
    }
    free ( _array );
}

#ifdef SQ_ARDUINO

#include <avr/pgmspace.h>

static char buffer[100];

const char * sq_get_constant_string ( const char * const _constantString )
{
    return strcpy_P ( buffer, _constantString );
}

void sq_get_constant_string_copy ( const char * const _constantString, char * _output )
{
    strcpy_P ( _output, _constantString );
}

#else

const char * sq_get_constant_string ( const char * const _constantString )
{
    return _constantString;
}

#endif
