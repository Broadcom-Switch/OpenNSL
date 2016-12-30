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

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <opennsl/error.h>
#include <opennsl/types.h>
#include <examples/util.h>
#include <cJSON.h>
#include <examples/rpc_utils.h>


int process_response(char *buffer, int length, int api_id)
{
  char *json;
  char jsonrpc[JSON_MAX_NODE_LENGTH] = {0};
  cJSON *root, *json_jsonrpc;
  cJSON *json_result;
  cJSON *json_error, *json_code, *json_message;
  int len = 0;


  if (0 == length)
  {
    printf("no bytes read. error !!\n");
    return -1;
  }

  /* Validating 'length' */
  if (length > strlen(buffer))
  {
    printf("Invalid value for parameter length %d ", len );
    return -1;
  }

  json = strstr(buffer, "\r\n\r\n");

  if (NULL == json)
  {
    /* the http header is not present.
       assume that the passed buffer is json.
       if not the validation would fail */

    json = buffer;
  }

  printf("Response message:\n%d:%s\n",length,json);

  len = strlen(json);

  /* Parse JSON to a C-JSON root */
  root = cJSON_Parse(json);
  JSON_VALIDATE_JSON_POINTER(root, "root", -1);

  /* Parsing and Validating 'jsonrpc' from JSON buffer */
  json_jsonrpc = cJSON_GetObjectItem(root, "jsonrpc");
  JSON_VALIDATE_JSON_POINTER(json_jsonrpc, "jsonrpc", -1);
  cJSON_Print(json_jsonrpc);
  JSON_VALIDATE_JSON_AS_STRING(json_jsonrpc, "jsonrpc", -1);
  /* Copy the string, with a limit on max characters */
  strncpy (&jsonrpc[0], json_jsonrpc->valuestring, JSON_MAX_NODE_LENGTH - 1);
  /* Ensure that 'jsonrpc' in the JSON equals "2.0" */
  JSON_COMPARE_STRINGS_AND_CLEANUP ("jsonrpc", &jsonrpc[0], "2.0");

  /* Parsing and Validating 'id' from JSON buffer */
  json_error = cJSON_GetObjectItem(root, "error");
  if(json_error)
  {
    json_code = cJSON_GetObjectItem(json_error, "code");
    JSON_VALIDATE_JSON_POINTER(json_code, "code", -1);
    cJSON_Print(json_code);
    JSON_VALIDATE_JSON_AS_NUMBER(json_code, "code");

    json_message = cJSON_GetObjectItem(json_error, "message");
    JSON_VALIDATE_JSON_POINTER(json_message, "message", -1);
    cJSON_Print(json_message);
    JSON_VALIDATE_JSON_AS_STRING(json_message, "message", -1);

    printf("Received FAILURE response,%s(%d), from the server.\n",json_message->valuestring, json_code->valueint);
  }
  else
  {
    json_result = cJSON_GetObjectItem(root, "result");
    JSON_VALIDATE_JSON_POINTER(json_result, "result", -1);

    switch(api_id)
    {
      case 1:
      {
	cJSON_Print(json_result);
	JSON_VALIDATE_JSON_AS_NUMBER(json_result, "result");

	printf("Result:%d.\n", json_result->valueint);

	break;
      } /* End of case 1 */

      case 2:
      {
        cJSON *json_btm, *json_ebt, *json_es;

	json_ebt = cJSON_GetObjectItem(json_result, "enable-buffer-tracking");
	JSON_VALIDATE_JSON_POINTER(json_ebt, "enable-buffer-tracking", -1);
	cJSON_Print(json_ebt);
	JSON_VALIDATE_JSON_AS_NUMBER(json_ebt, "enable-buffer-tracking");

	json_btm = cJSON_GetObjectItem(json_result, "buffer-tracking-mode");
	JSON_VALIDATE_JSON_POINTER(json_btm, "buffer-tracking-mode", -1);
	cJSON_Print(json_btm);
	JSON_VALIDATE_JSON_AS_STRING(json_btm, "buffer-tracking-mode", -1);

	json_es = cJSON_GetObjectItem(json_result, "enable-snapshots");
	JSON_VALIDATE_JSON_POINTER(json_es, "enable-snapshots", -1);
	cJSON_Print(json_es);
	JSON_VALIDATE_JSON_AS_NUMBER(json_es, "enable-snapshots");

	printf("enable-buffer-tracking:%d\nbuffer-tracking-mode:%s\nenable-snapshots:%d.\n", json_ebt->valueint, json_btm->valuestring,json_es->valueint);

	break;
      } /* End of case 2 */

      case 3:
      {
        cJSON *json_gport;

	json_gport = cJSON_GetObjectItem(json_result, "global-port-id");
	JSON_VALIDATE_JSON_POINTER(json_gport, "global-port-id", -1);
	cJSON_Print(json_gport);
	JSON_VALIDATE_JSON_AS_NUMBER(json_gport, "global-port-id");

	printf("gport:%d.\n", json_gport->valueint);

	break;
      } /* End of case 3 */

      case 4:
      {
        cJSON *json_device, *json_revision;

	json_device = cJSON_GetObjectItem(json_result, "device");
	JSON_VALIDATE_JSON_POINTER(json_device, "device", -1);
	cJSON_Print(json_device);
	JSON_VALIDATE_JSON_AS_NUMBER(json_device, "device");

	json_revision = cJSON_GetObjectItem(json_result, "revision");
	JSON_VALIDATE_JSON_POINTER(json_revision, "revision", -1);
	cJSON_Print(json_revision);
	JSON_VALIDATE_JSON_AS_NUMBER(json_revision, "revision");

	printf("Device:%d Revision:%d.\n", json_device->valueint, json_revision->valueint);

	break;
      } /* End of case 4 */

      case 5:
      {
        cJSON *json_maxunits;

	json_maxunits = cJSON_GetObjectItem(json_result, "max-units");
	JSON_VALIDATE_JSON_POINTER(json_maxunits, "max-units", -1);
	cJSON_Print(json_maxunits);
	JSON_VALIDATE_JSON_AS_NUMBER(json_maxunits, "max-units");

	printf("Max-Units:%d.\n", json_maxunits->valueint);

	break;
      } /* End of case 5 */
      case 6:
      {
        cJSON *json_ge, *json_xe, *json_ce, *json_port, *json_cpu, *json_all;

	json_ge = cJSON_GetObjectItem(json_result, "ge-bmp");
	JSON_VALIDATE_JSON_POINTER(json_ge, "ge-bmp", -1);
	cJSON_Print(json_ge);
/*	JSON_VALIDATE_JSON_AS_ARRAY(json_ge, "ge-bmp");*/

	json_xe = cJSON_GetObjectItem(json_result, "xe-bmp");
	JSON_VALIDATE_JSON_POINTER(json_xe, "xe-bmp", -1);
	cJSON_Print(json_xe);
/*	JSON_VALIDATE_JSON_AS_ARRAY(json_xe, "xe-bmp");*/

	json_ce = cJSON_GetObjectItem(json_result, "ce-bmp");
	JSON_VALIDATE_JSON_POINTER(json_ce, "ce-bmp", -1);
	cJSON_Print(json_ce);
/*	JSON_VALIDATE_JSON_AS_ARRAY(json_ce, "ce-bmp");*/

	json_port = cJSON_GetObjectItem(json_result, "port-bmp");
	JSON_VALIDATE_JSON_POINTER(json_port, "port-bmp", -1);
	cJSON_Print(json_port);
/*	JSON_VALIDATE_JSON_AS_ARRAY(json_port, "port-bmp");*/

	json_cpu = cJSON_GetObjectItem(json_result, "cpu-bmp");
	JSON_VALIDATE_JSON_POINTER(json_cpu, "cpu-bmp", -1);
	cJSON_Print(json_cpu);
/*	JSON_VALIDATE_JSON_AS_ARRAY(json_cpu, "cpu-bmp");*/

	json_all = cJSON_GetObjectItem(json_result, "all-bmp");
	JSON_VALIDATE_JSON_POINTER(json_all, "all-bmp", -1);
	cJSON_Print(json_all);
/*	JSON_VALIDATE_JSON_AS_ARRAY(json_all, "all-bmp");*/

	break;
      } /* End of case 6 */

      default:
	break;
    } /* End of switch */
  }


  if (root != NULL)
  {
    cJSON_Delete(root);
  }
  return 0;
}

/******************************************************************
 * @brief      main function for the client   
 *
 * @param[in] argc, argv 
 *
 *
 * @retval   none   
 *
 * @note    : The server name can be provided as command line arg 
 *********************************************************************/
int main(int argc, char *argv[]){
  int clientSocket;
  int temp = 0, choice;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  char server[128] = {0};
  char buffer[1024] = {0};

  /*---- Create the socket. The three arguments are: ----*/
  /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  if (clientSocket == -1)
  {
    printf("failed to create socket \n");
    exit(0);
  }

  /*---- Configure settings of the server address struct ----*/
  /* Address family = Internet */
  serverAddr.sin_family = AF_INET;
  /* Set port number, using htons function to use proper byte order */
  serverAddr.sin_port = htons(EXAMPLE_CONFIG_PORT);

  /*If the server hostname is supplied*/

  if(argc > 1)
  {
    /*Use the supplied argument*/
    strncpy(server, argv[1],(sizeof(server) - 1));
    printf("Connecting to the server %s, port %d ...\n", server, EXAMPLE_CONFIG_PORT);
  }
  else
  {
    /*Use the default server name or IP*/
    strcpy(server, DEF_SERVER);
  }

  /* Set IP address to localhost */
  serverAddr.sin_addr.s_addr = inet_addr(server);
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*---- Connect the socket to the server using the address struct ----*/
  addr_size = sizeof serverAddr;
  temp = connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);
  if (temp == -1)
  {
    printf("failed to connect \n");
    close(clientSocket);
    exit(0);
  }

  while (1) 
  {
    printf("\r\nUser menu: Select one of the following JSON-RPC APIs\r\n");
    printf("1. configure-buffer-tracking\n");
    printf("2. get-buffer-tracking\n");
    printf("3. get-global-portid\n");
    printf("4. get-unit-info\n");
    printf("5. get-max-units\n");
    printf("6. get-port-config\n");
    printf("7. get-gportid\n");
    printf("0. Quit the application\n");

    if(example_read_user_choice(&choice) != OPENNSL_E_NONE)
    {
        printf("Invalid option entered. Please re-enter.\n");
        continue;
    }

    switch(choice)
    {
      case 1:
      {
        char *json_api_template = "{\
	       \"jsonrpc\" : \"2.0\",\
	       \"method\" : \"configure-buffer-tracking\",\
	       \"unit\" : 0,\
	       \"params\" : {	\
			   \"enable-buffer-tracking\" : 1,\
			   \"buffer-tracking-mode\" : \"peak\",\
			   \"enable-snapshots\" : 1\
			    },\
	       \"id\" : 1\
	}";
        strncpy (buffer, json_api_template, 1023);
        break;
      } /* End of case 1 */

      case 2:
      {
	char *json_api_template = "{\
	       \"jsonrpc\" : \"2.0\",\
	       \"method\" : \"get-buffer-tracking\",\
	       \"unit\" : 0,\
	       \"params\" : {	},\
	       \"id\" : 2\
	}";
        strncpy (buffer, json_api_template, 1023);

        break;
      } /* End of case 2 */

      case 3:
      {
	char *json_api_template = "{\
	       \"jsonrpc\" : \"2.0\",\
	       \"method\" : \"get-global-portid\",\
	       \"unit\" : 0,\
	       \"params\" : {	\
			   \"local-port\" : 2\
			    },\
	       \"id\" : 3\
	}";
        strncpy (buffer, json_api_template, 1023);

        break;
      } /* End of case 3 */

      case 4:
      {
	char *json_api_template = "{\
	       \"jsonrpc\" : \"2.0\",\
	       \"method\" : \"get-unit-info\",\
	       \"unit\" : 0,\
	       \"params\" : {	},\
	       \"id\" : 4\
	}";
        strncpy (buffer, json_api_template, 1023);

        break;
      } /* End of case 4 */

      case 5:
      {
	char *json_api_template = "{\
	       \"jsonrpc\" : \"2.0\",\
	       \"method\" : \"get-max-units\",\
	       \"unit\" : 0,\
	       \"params\" : {	},\
	       \"id\" : 5\
	}";
        strncpy (buffer, json_api_template, 1023);

        break;
      } /* End of case 5 */

      case 6:
      {
	char *json_api_template = "{\
	       \"jsonrpc\" : \"2.0\",\
	       \"method\" : \"get-port-config\",\
	       \"unit\" : 0,\
	       \"params\" : {	},\
	       \"id\" : 6\
	}";
        strncpy (buffer, json_api_template, 1023);

        break;
      } /* End of case 6 */

      case 7:
      {
	char *json_api_template = "{\
	       \"jsonrpc\" : \"2.0\",\
	       \"method\" : \"get-gportid\",\
	       \"unit\" : 0,\
	       \"params\" : {	\
			   \"local-port\" : 2\
			    },\
	       \"id\" : 7\
	}";
        strncpy (buffer, json_api_template, 1023);

        break;
      } /* End of case 6 */

      case 0:
      {
        printf("Exiting the application.\n");
        close(clientSocket);
        exit(0);
      }
      default:
        continue;
    } /* End of switch */

    temp = send(clientSocket, buffer, strlen(buffer), 0);
    if (0 > temp)
    {
      printf("failed to send any data \n");
    }
    else
    {
      memset(buffer, 0, sizeof(buffer));
      temp = read (clientSocket, buffer, RPC_MAX_BUFFER_LEN);
      if (temp < 0)
      {
	/* Read error. */
	perror ("read");
	printf("Error reading from the socket.\n");
	break;
      }
      else if (temp == 0)
      {
	printf("End of file reached.\n");
	/* End-of-file. */
	break;
      }
      else
      {
	/* Data read. */
	temp = process_response(buffer, temp, choice);
	if(temp)
	{
	  printf("Error processing the response.\n");
	}
      }
    }
  } /* End of while */

  close(clientSocket);
  exit(0);
}

