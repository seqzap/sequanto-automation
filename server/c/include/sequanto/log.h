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

#ifndef SEQUANTO_LOG_H_
#define SEQUANTO_LOG_H_

#include <sequanto/macros.h>
#include <sequanto/log.h>
#include <stdarg.h>

SQ_BEGIN_DECL

/**
 * @defgroup log Write log message to the client.
 *
 * These functions provides a simple way for the server (target) to
 * send logging statements to any conneted client.
 *
 * These log messages are sent to the client using the !LOG
 * asynchronous message introduced in revision 2 of the automation
 * protocol.
 *
 * @ingroup c
 *
 * @{
 */

/**
 * If this token is defined it will disable all calls to the sequanto
 * automation library, this is very useful to e.g. disable the
 * automation interface in release builds without having to modify
 * your code.
 */
#ifdef SQ_DISABLE_AUTOMATION_INTERFACE

#define sq_log(_message) /* Disabled because SQ_DISABLE_AUTOMATION_INTERFACE is defined. */
#define sq_logf(...) /* Disabled because SQ_DISABLE_AUTOMATION_INTERFACE is defined. */

#else

/**
 * Write a log message to the connected clients (if any).
 *
 * The message will automatically be escaped such that it adheres to the automation protocol.
 *
 * @param _message The message to write.
 */
SQ_DECL void sq_log ( const char * _message );

/**
 * Write a log message to the connected clients (if any) using a
 * printf-like syntax.
 *
 * Generally you can safely just assume that normal printf
 * statements work, e.g. %d and %i means integer, %f means float
 * (double) and %s means string.
 *
 * Currently the accepted statements are:
 *
 *    %d, %i: Write an integer
 *    %f: Write a double or a float
 *    %b: Write a SQBool.
 *    %x, %p: Write an integer as hexadecimal (useful when memory addresses).
 *    %s: Write a null terminated string.
 *
 * @param _format The message to write, including any printf-like statements.
 */
SQ_DECL void sq_logf ( const char * _format, ... );

#endif

/**
 * @}
 */

SQ_END_DECL

#endif
