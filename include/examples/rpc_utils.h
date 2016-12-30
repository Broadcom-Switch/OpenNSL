/*****************************************************************************
  *
  * Copyright © 2016 Broadcom.  The term "Broadcom" refers
  * to Broadcom Limited and/or its subsidiaries.
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  *
  * You may obtain a copy of the License at
  * http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ***************************************************************************/

#ifndef INCLUDE_RPC_UTILS_H
#define INCLUDE_RPC_UTILS_H

#ifdef  __cplusplus
extern "C"
{
#endif

#include <stdint.h> 
#include <sys/socket.h> 

#define JSON_MAX_NODE_LENGTH 64
#define RPC_MAX_BUFFER_LEN 1023
#define JSON_MAX_NODE_LENGTH 64

#define EXAMPLE_CONFIG_PORT 7891
#define DEF_SERVER "127.0.0.1"


#define _jsonlog(format,args...)              printf(format, ##args)

#define JSON_VALIDATE_POINTER(x,y,z)  do { \
    if ((x) == NULL) { \
        _jsonlog("Invalid (NULL) value for parameter %s ", (y) ); \
        return (z); \
        } \
} while(0)

#define JSON_VALIDATE_JSON_POINTER(x,y,z) do { \
      if ((x) == NULL) { \
            _jsonlog("Error parsing JSON %s ", (y) ); \
            return (z); \
            } \
}while(0)

#define JSON_VALIDATE_POINTER_AND_CLEANUP(x,y,z)  do { \
      if ((x) == NULL) { \
            _jsonlog("Invalid (NULL) value for parameter %s ", (y) ); \
            if (root != NULL) { \
                  cJSON_Delete(root); \
                  } \
            return (z); \
            } \
} while(0)

#define JSON_VALIDATE_JSON_POINTER_AND_CLEANUP(x,y,z)  do { \
      if ((x) == NULL) { \
            _jsonlog("Error parsing JSON %s ", (y) ); \
            if (root != NULL) { \
                  cJSON_Delete(root); \
                  } \
            return (z); \
            } \
}while(0)


#define JSON_VALIDATE_JSON_AS_STRING(x,y,z)  do { \
      if ((x)->type != cJSON_String) { \
            _jsonlog("Error parsing JSON, %s not a string ", (y) ); \
            if (root != NULL)  { \
                  cJSON_Delete(root); \
                  } \
            return (z); \
            } \
      if((x)->valuestring == NULL) { \
            _jsonlog("Error parsing JSON, %s not a valid string ", (y) ); \
            if (root != NULL) { \
                  cJSON_Delete(root); \
                  } \
            return (z); \
            } \
}while(0)

#define JSON_VALIDATE_JSON_AS_NUMBER(x,y)   do { \
      if ((x)->type != cJSON_Number) { \
            _jsonlog("Error parsing JSON, %s not a integer ", (y) ); \
            if (root != NULL)  { \
                  cJSON_Delete(root); \
                  } \
            return (-1); \
            } \
}while(0)

#define JSON_COMPARE_STRINGS_AND_CLEANUP(x,y,z)  do { \
      if (strcmp((y), (z)) != 0) { \
            _jsonlog("The JSON contains invalid value for %s (actual %s, required %s) ", (x), (y), (z) ); \
            if (root != NULL) { \
                  cJSON_Delete(root); \
                  } \
            return (-1); \
            } \
}while(0)

#define JSON_COMPARE_VALUE_AND_CLEANUP(x,y,z)  do { \
      if ((y) != (z)) { \
            _jsonlog("The JSON contains invalid value for %s (actual %d, required %d) ", (x), (y), (z) ); \
            if (root != NULL) { \
                  cJSON_Delete(root); \
                  } \
            return (-1); \
            } \
}while(0)


#define JSON_CHECK_VALUE_AND_CLEANUP(x,y,z)  do { \
      if ( ((x) < (y)) || ( (x) > (z)) ) { \
            _jsonlog("The JSON number out of range %d (min %d, max %d) ", (x), (y), (z) ); \
            if (root != NULL) { \
                  cJSON_Delete(root); \
                  } \
            return (-1); \
            } \
}while(0)




#ifdef  __cplusplus
}
#endif

#endif /* !INCLUDE_RPC_UTILS_H */

