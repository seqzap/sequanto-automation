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

#include <stdlib.h>
#include <string.h>

#include "config.h"

#include "sequanto/system.h"
#include "sequanto/stream.h"

#include <due_can.h>

typedef struct _SQStream
{
    SQStreamDataReceivedFunction m_handler;
    void * m_handlerData;
} _SQStream;

static CAN_FRAME s_sendFrame;

SQStream * sq_stream_open ( int _portNumber )
{
   Can0.init(SQ_ARDUINO_CAN_BAUD_RATE);
   s_sendFrame.id = SQ_ARDUINO_CAN_ID;
    SQStream * ret = (SQStream*) malloc ( sizeof(SQStream) );
    ret->m_handler = NULL;
    ret->m_handlerData = NULL;
    return ret;
}

void sq_stream_close ( SQStream * _stream )
{
    free ( _stream );
}

void sq_stream_set_data_received_handler ( SQStream * _stream, SQStreamDataReceivedFunction _handler, void * _data )
{
    _stream->m_handler = _handler;
    _stream->m_handlerData = _data;
}

void sq_stream_poll( SQStream * _stream )
{
}

static CAN_FRAME s_frame;
static SQByte s_dataIndex;
size_t sq_stream_data_available ( SQStream * _stream )
{
   if (Can0.rx_avail())
   {
      Can0.read(s_frame);
      s_dataIndex = 0;
      return s_frame.length;
   }
   else
   {
      return 0;
   }
}

SQBool sq_stream_write_string ( SQStream * _stream, const char * const _string )
{
   int i;
   size_t stringIndex = 0;
   size_t length = strlen(_string);
   while ( length > 0 )
   {
      if ( length >= 8 )
      {
         s_sendFrame.length = 8;
         for ( i = 0; i < 8; i++ )
         {
            s_sendFrame.data.bytes[i] = _string[stringIndex];
            stringIndex++;
         }
         Can0.sendFrame(s_sendFrame);
         length -= 8;
      }
      else
      {
         s_sendFrame.length = length;
         for ( i = 0; i < length; i++ )
         {
            s_sendFrame.data.bytes[i] = _string[stringIndex];
            stringIndex++;
         }
         Can0.sendFrame(s_sendFrame);
      }
   }
   return SQ_TRUE;
}

SQBool sq_stream_write_SQStringOut ( SQStream * _stream, SQStringOut *pString )
{
    while (pString->HasMore(pString))
    {
       sq_stream_write_byte( _stream, pString->GetNext(pString) );
    }
    return SQ_TRUE;
}

SQBool sq_stream_write_byte ( SQStream * _stream, SQByte _byte )
{
   s_sendFrame.length = 1;
   s_sendFrame.data.bytes[0] = _byte;
   Can0.sendFrame(s_sendFrame);
   return SQ_TRUE;
}

SQBool sq_stream_read_byte ( SQStream * _stream, SQByte * _byte )
{
   if ( s_dataIndex < s_frame.length )
   {
      *_byte  = s_frame.data.bytes[s_dataIndex];
      s_dataIndex++;
      return SQ_TRUE;
   }
   else
   {
      return SQ_FALSE;
   }
}

void sq_stream_enter_write ( SQStream * _stream )
{
}

void sq_stream_exit_write ( SQStream * _stream )
{
}

void sq_stream_join ( SQStream * _stream )
{
}
