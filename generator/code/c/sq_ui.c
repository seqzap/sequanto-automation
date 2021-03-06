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

#include "config.h"

#include "sequanto/ui.h"

##SQ_WIDGET_TYPES_CONST##

##SQ_WIDGET_NODES_CONST##

const char * sq_widget_type_to_string ( SQWidgetType _type )
{
   switch ( _type )
   {
##SQ_WIDGET_TYPES_ENUM_FUNC##
   default:
      return SQ_WIDGET_TYPE_UNKNOWN_STRING;
   }
}
