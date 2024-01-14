/*
 * cmd-tests.c
 *
 * Unitary tests for command behaviour
 * These tests test pre-condition, post-conditions and functional 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <CUnit/Basic.h>

#include "list/list.h"

#define NB_TESTS 12
#define BUFFER_MAX_SIZE 10240
#define DEBUG_COMMAND_STRING "./Debug/listechainee"
#define RELEASE_COMMAND_STRING "./Release/listechainee"

/* Buffer used for reading the command output */
char buf[BUFFER_MAX_SIZE];

/*
 * popen_listechainee
 *
 * Open a pipe for reading from launched command listechainee
 */
FILE *
popen_listechainee(char* args)
{
  /* Compute the size of the string to allocate for command */
  char *cmd = (char*)malloc(strlen("./Debug/listechainee") + strlen(args) + 2);
  /* Format the command  */
  sprintf(cmd, DEBUG_COMMAND_STRING " %s", args);
  /* Open the pipe for launching the command with a shell: 'sh -c "<command>"' */
  /* The returned file pointer will allow us to read ("r") the command standard output/error  */
  FILE *fp = popen(cmd, "r");
  /* Free the command string allocated */
  free((void*)cmd);
  /* Return the file pointer */
  return fp;
}

/*
 * These are the expected results as strings
 */
char* results[NB_TESTS] = {
  "",
  "listechainee: info: option 'v' was incremented for verbosity !",
  "listechainee: info: option 'v' was incremented for verbosity !\n"
  "listechainee: info: option 'h' was set !\n"
  "listechainee: usage: listechainee [-hvdAPxXqN] [-l <filename>] [-s <filename>] [-t|-I|-r <elem>]\n",
  "listechainee: info: option 'v' was incremented for verbosity !",
  "listechainee: info: option 'v' was incremented for verbosity !\n"
  "listechainee: info: option 'h' was set !\n"
  "listechainee: usage: listechainee [-hvdAPxXqN] [-l <filename>] [-s <filename>] [-t|-I|-r <elem>]\n",
  "Liste: 1\n",
  "Liste: 2\n",
  "Liste: 3\n",
  "Liste: 4\n",
  "Liste: 2,1\n",
  "Liste: 2,1\n",
  NULL
};

#define TEST_COMMAND_ARGS_VS_RESULT_NB(args, nb)  					\
  /* Initialize the buffer to \x00 */			  					\
  bzero((void*)buf, BUFFER_MAX_SIZE);			  					\
  /* Open the command with a pipe */			  					\
  FILE *fp = popen_listechainee(args);			  					\
  /* Read the command output with the pipe */	  					\
  fread(buf, BUFFER_MAX_SIZE-1, 1, fp);			  					\
  /* Test assertion */			                  					\
  CU_ASSERT(strncmp(buf, results[nb], strlen(results[nb])) == 0);   \
  /* Close the pipe */			                  					\
  pclose(fp);

/*
 * test_command_basic_invocation_0
 *
 * Basic tests for the command invocation without args
 */
void
test_command_basic_invocation_0(void)
{
  TEST_COMMAND_ARGS_VS_RESULT_NB("", 0);
}

/*
 * test_command_basic_invocation_v
 *
 * Basic tests for the command invocation with '-v' arg
 */
void
test_command_basic_invocation_v(void)
{
  TEST_COMMAND_ARGS_VS_RESULT_NB("-v", 1);
}

/*
 * test_command_basic_invocation_vh
 *
 * Basic tests for the command invocation with '-v -h' args
 */
void
test_command_basic_invocation_vh(void)
{
  TEST_COMMAND_ARGS_VS_RESULT_NB("-v -h", 2);
}

/*
 * test_command_basic_invocation_verbose
 *
 * Basic tests for the command invocation with '--verbose' arg
 */
void
test_command_basic_invocation_verbose(void)
{
  TEST_COMMAND_ARGS_VS_RESULT_NB("--verbose", 3);
}

/*
 * test_command_basic_invocation_verbose_help
 *
 * Basic tests for the command invocation with '--verbose --help' args
 */
void
test_command_basic_invocation_verbose_help(void)
{
  TEST_COMMAND_ARGS_VS_RESULT_NB("--verbose --help", 4);  
}

/*
 * test_command_basic_invocation_A1d
 *
 * Basic tests for the command invocation with '-A 1 -d' args
 */
void
test_command_basic_invocation_A1d(void)
{
  TEST_COMMAND_ARGS_VS_RESULT_NB("-A 1 -d", 5);
}

/*
 * test_command_basic_invocation_P2d
 *
 * Basic tests for the command invocation with '-P 2 -d' args
 */
void
test_command_basic_invocation_P2d(void)
{
  TEST_COMMAND_ARGS_VS_RESULT_NB("-P 2 -d", 6);
}

/*
 * test_command_basic_invocation_append_3_display
 *
 * Basic tests for the command invocation with '--append 3 --display' args
 */
void
test_command_basic_invocation_append_3_display(void)
{
  TEST_COMMAND_ARGS_VS_RESULT_NB("--append 3 --display", 7);  
}

/*
 * test_command_basic_invocation_prepend_4_display
 *
 * Basic tests for the command invocation with '--prepend 4 --display' args
 */
void
test_command_basic_invocation_prepend_4_display(void)
{
  TEST_COMMAND_ARGS_VS_RESULT_NB("--prepend 4 --display", 8);  
}

/*
 * test_command_basic_invocation_A1P2d
 *
 * Basic tests for the command invocation with '-A 1 -P 2 -d' args
 */
void
test_command_basic_invocation_A1P2d(void)
{
  TEST_COMMAND_ARGS_VS_RESULT_NB("-A 1 -P 2 -d", 9);  
}

/*
 * test_command_basic_invocation_append_1_prepend_2_display
 *
 * Basic tests for the command invocation with '--append 1 --prepend 2 --display' args
 */
void
test_command_basic_invocation_append_1_prepend_2_display(void)
{
  TEST_COMMAND_ARGS_VS_RESULT_NB("--append 1 --prepend 2 --display", 10);  
}
