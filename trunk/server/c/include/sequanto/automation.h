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

#ifndef SEQUANTO_AUTOMATION_H_
#define SEQUANTO_AUTOMATION_H_

#include <sequanto/types.h>
#include <sequanto/stream.h>
#include <sequanto/server.h>
#include <sequanto/system.h>
#include <sequanto/log.h>

#ifdef __cplusplus
extern "C"
{
#endif

void sq_init ( void );
void sq_shutdown ( void );

#ifdef __cplusplus
}
#endif

#endif /* SEQUANTO_AUTOMATION_H_ */
