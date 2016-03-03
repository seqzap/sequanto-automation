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
static SQByte s_sendIndex;
static CAN_FRAME s_frame;
static SQByte s_dataIndex;

SQStream * sq_stream_open ( int _portNumber )
{
   Can0.init(SQ_ARDUINO_CAN_BAUD_RATE);
   Can0.watchFor();

   /*
   int filter;
   // extended
   for (filter = 0; filter < 3; filter++)
   {
     Can0.setRXFilter(filter, 0, 0, true);
   }
   //standard
   for (filter = 3; filter < 7; filter++)
   {
     Can0.setRXFilter(filter, 0, 0, false);
     }*/

   s_dataIndex = 0;
   s_frame.length = 0;
   s_sendFrame.id = SQ_ARDUINO_CAN_ID;
   s_sendFrame.priority = 0;
   s_sendFrame.extended = true;
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

size_t sq_stream_data_available ( SQStream * _stream )
{
   if ( s_dataIndex == s_frame.length )
   {
      if (Can0.rx_avail())
      {
         Serial.println(" RX");
         Can0.read(s_frame);
         s_dataIndex = 0;
         return s_frame.length;
      }
      else
      {
         return 0;
      }
   }
   else
   {
      return s_frame.length - s_dataIndex;
   }
}

SQBool sq_stream_read_byte ( SQStream * _stream, SQByte * _byte )
{
   if ( s_dataIndex < s_frame.length )
   {
      *_byte  = s_frame.data.bytes[s_dataIndex];
      Serial.print((char) *_byte);
      s_dataIndex++;
      return SQ_TRUE;
   }
   else
   {
      return SQ_FALSE;
   }
}

static void can0_send()
{
   size_t i;
   for ( i = 0; i < s_sendFrame.length; i++ )
   {
      Serial.print((char) s_sendFrame.data.bytes[i]);
   }
   bool sent = false;
   do
   {
      sent = Can0.sendFrame(s_sendFrame);
   } while ( !sent );
}

SQBool sq_stream_write_string ( SQStream * _stream, const char * const _string )
{
   size_t length = strlen(_string);
   for ( size_t i = 0; i < length; i++ )
   {
      sq_stream_write_byte(_stream, _string[i]);
   }
   /*
   size_t i;
   size_t stringIndex = 0;
   size_t left = strlen(_string);
   while ( left > 0 )
   {
      if ( left > 8 )
      {
         s_sendFrame.length = 8;
         for ( i = 0; i < 8; i++ )
         {
            s_sendFrame.data.bytes[i] = _string[stringIndex];
            stringIndex++;
         }
         can0_send();
         left -= 8;
      }
      else
      {
         s_sendFrame.length = left;
         for ( i = 0; i < left; i++ )
         {
            s_sendFrame.data.bytes[i] = _string[stringIndex];
            stringIndex++;
         }
         can0_send();
         left = 0;
      }
   }
   */
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
   s_sendFrame.data.bytes[s_sendIndex] = _byte;
   s_sendIndex ++;
   if ( s_sendIndex == 8 )
   {
      s_sendFrame.length = 8;
      can0_send();
      s_sendIndex = 0;
   }
   return SQ_TRUE;
}

void sq_stream_enter_write ( SQStream * _stream )
{
   Serial.print(" TX ");
   s_sendIndex = 0;
}

void sq_stream_exit_write ( SQStream * _stream )
{
   if ( s_sendIndex > 0 )
   {
      s_sendFrame.length = s_sendIndex;
      can0_send();
      s_sendIndex = 0;
   }
}

void sq_stream_join ( SQStream * _stream )
{
}
