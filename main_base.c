/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/******************************************************************************
 * NOTE 1: The FreeRTOS demo threads will not be running continuously, so
 * do not expect to get real time behaviour from the FreeRTOS Linux port, or
 * this demo application.  Also, the timing information in the FreeRTOS+Trace
 * logs have no meaningful units.  See the documentation page for the Linux
 * port for further information:
 * https://freertos.org/FreeRTOS-simulator-for-Linux.html
 *
 *
 * NOTE 2:  This file only contains the source code that is specific to the
 * basic demo.  Generic functions, such FreeRTOS hook functions, are defined
 * in main.c.
 ******************************************************************************
 *
 * main_base() creates two tasks.  It then starts the scheduler.
 *
 *
 * NOTE:  Console input and output relies on Linux system calls, which can
 * interfere with the execution of the FreeRTOS Linux port. This demo only
 * uses Linux system call occasionally. Heavier use of Linux system calls
 * may crash the port.
 */

#include <stdio.h>
#include <pthread.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Local includes. */
#include "console.h"

/* Priorities at which the tasks are created. */
#define TASK1_PRIORITY    ( tskIDLE_PRIORITY + 1 )
#define TASK2_PRIORITY       ( tskIDLE_PRIORITY + 2 )

/* The rate at which data is sent to the queue.  The times are converted from
 * milliseconds to ticks using the pdMS_TO_TICKS() macro. */
#define FREQUENCY_MS_TASK1         pdMS_TO_TICKS( 2000UL )
#define FREQUENCY_MS_TASK2         pdMS_TO_TICKS( 10000UL )


/* Constantes */

#define Max_Num 20 
#define Min 0
#define Max 100
#define Tam_FileName 6


/*-----------------------------------------------------------*/

/*
 * The tasks as described in the comments at the top of this file.
 */
static void prvTask1( void * pvParameters );
static void prvTask2( void * pvParameters );
static void prvTask3.1( void * pvParameters );
static void prvTask3.2( void * pvParameters );
static void prvTask3.3( void * pvParameters );
static void prvTask3.4( void * pvParameters );
static void prvTask3.5( void * pvParameters );
static void prvTask4( void * pvParameters );




/*-----------------------------------------------------------*/

/*** SEE THE COMMENTS AT THE TOP OF THIS FILE ***/
void main_base( void )
{

    /* Start the two tasks as described in the comments at the top of this
     * file. */
    xTaskCreate( prvTask1,                        /* The function that implements the task. */
                 "Task1",                            /* The text name assigned to the task - for debug only as it is not used by the kernel. */
                 configMINIMAL_STACK_SIZE,        /* The size of the stack to allocate to the task. */
                 NULL,                            /* The parameter passed to the task - not used in this simple case. */
                 TASK1_PRIORITY,                  /* The priority assigned to the task. */
                 NULL );                          /* The task handle is not required, so NULL is passed. */

    xTaskCreate( prvTask2, "Task2", configMINIMAL_STACK_SIZE, NULL, TASK2_PRIORITY, NULL );


    /* Start the tasks and get the scheduler running. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following
     * line will never be reached.  If the following line does execute, then
     * there was insufficient FreeRTOS heap memory available for the idle and/or
     * timer tasks to be created.  See the memory management section on the
     * FreeRTOS web site for more details. */
    for( ; ; )
    {
    }
}
/*-----------------------------------------------------------*/

static void prvTask1( void * pvParameters )
{
    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {

        /* Send to the queue - causing the queue receive task to unblock and
         * write to the console.  0 is used as the block time so the send operation
         * will not block - it shouldn't need to block as the queue should always
         * have at least one space at this point in the code. */
        Char nameFile[Tam_FileName +1]; 
        RandomName(nameFile, Tam_FileName);
        File *file = fopen (nameFile , "w");
        if ( file != NULL){

            for ( int i = 0 ; i > Max_Num ; i++){
                int numero = rand() % (Max - Min +1 )  + Min; 

                fprintf(file , "%d\n",numero )
            }
        fclose();
        }

        /* Place this task in the blocked state until it is time to run again.
        *  The block time is specified in ticks, pdMS_TO_TICKS() was used to
        *  convert a time specified in milliseconds into a time specified in ticks.
        *  While in the Blocked state this task will not consume any CPU time. */
        vTaskDelay( FREQUENCY_MS_TASK1 );
    }
}
/*-----------------------------------------------------------*/


static void prvTask2( void * pvParameters )
{
    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Send to the queue - causing the queue receive task to unblock and
         * write to the console.  0 is used as the block time so the send operation
         * will not block - it shouldn't need to block as the queue should always
         * have at least one space at this point in the code. */
        console_print( "Message from task 2\n" );
        for( int i=0 ; i < 1000000 ; i++ )
        {
        }

        /* Place this task in the blocked state until it is time to run again.
        *  The block time is specified in ticks, pdMS_TO_TICKS() was used to
        *  convert a time specified in milliseconds into a time specified in ticks.
        *  While in the Blocked state this task will not consume any CPU time. */
        vTaskDelay( FREQUENCY_MS_TASK2 );
    }
}
/*-----------------------------------------------------------*/

static void prvTask3.1( void * pvParameters )
{
    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Send to the queue - causing the queue receive task to unblock and
         * write to the console.  0 is used as the block time so the send operation
         * will not block - it shouldn't need to block as the queue should always
         * have at least one space at this point in the code. */
        console_print( "Message from task 2\n" );
        for( int i=0 ; i < 1000000 ; i++ )
        {
        }

        /* Place this task in the blocked state until it is time to run again.
        *  The block time is specified in ticks, pdMS_TO_TICKS() was used to
        *  convert a time specified in milliseconds into a time specified in ticks.
        *  While in the Blocked state this task will not consume any CPU time. */
        vTaskDelay( FREQUENCY_MS_TASK2 );
    }
}

/*-----------------------------------------------------------*/

static void prvTask3.2( void * pvParameters )
{
    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Send to the queue - causing the queue receive task to unblock and
         * write to the console.  0 is used as the block time so the send operation
         * will not block - it shouldn't need to block as the queue should always
         * have at least one space at this point in the code. */
        console_print( "Message from task 2\n" );
        for( int i=0 ; i < 1000000 ; i++ )
        {
        }

        /* Place this task in the blocked state until it is time to run again.
        *  The block time is specified in ticks, pdMS_TO_TICKS() was used to
        *  convert a time specified in milliseconds into a time specified in ticks.
        *  While in the Blocked state this task will not consume any CPU time. */
        vTaskDelay( FREQUENCY_MS_TASK2 );
    }
}


/*-----------------------------------------------------------*/

static void prvTask3.3( void * pvParameters )
{
    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Send to the queue - causing the queue receive task to unblock and
         * write to the console.  0 is used as the block time so the send operation
         * will not block - it shouldn't need to block as the queue should always
         * have at least one space at this point in the code. */
        console_print( "Message from task 2\n" );
        for( int i=0 ; i < 1000000 ; i++ )
        {
        }


        /* Place this task in the blocked state until it is time to run again.
        *  The block time is specified in ticks, pdMS_TO_TICKS() was used to
        *  convert a time specified in milliseconds into a time specified in ticks.
        *  While in the Blocked state this task will not consume any CPU time. */
        vTaskDelay( FREQUENCY_MS_TASK2 );
    }
}
/*-----------------------------------------------------------*/

static void prvTask3.4( void * pvParameters )
{
    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Send to the queue - causing the queue receive task to unblock and
         * write to the console.  0 is used as the block time so the send operation
         * will not block - it shouldn't need to block as the queue should always
         * have at least one space at this point in the code. */
        console_print( "Message from task 2\n" );
        for( int i=0 ; i < 1000000 ; i++ )
        {
        }

        /* Place this task in the blocked state until it is time to run again.
        *  The block time is specified in ticks, pdMS_TO_TICKS() was used to
        *  convert a time specified in milliseconds into a time specified in ticks.
        *  While in the Blocked state this task will not consume any CPU time. */
        vTaskDelay( FREQUENCY_MS_TASK2 );
    }
}
/*-----------------------------------------------------------*/

static void prvTask3.5( void * pvParameters )
{
    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Send to the queue - causing the queue receive task to unblock and
         * write to the console.  0 is used as the block time so the send operation
         * will not block - it shouldn't need to block as the queue should always
         * have at least one space at this point in the code. */
        console_print( "Message from task 2\n" );
        for( int i=0 ; i < 1000000 ; i++ )
        {
        }

        /* Place this task in the blocked state until it is time to run again.
        *  The block time is specified in ticks, pdMS_TO_TICKS() was used to
        *  convert a time specified in milliseconds into a time specified in ticks.
        *  While in the Blocked state this task will not consume any CPU time. */
        vTaskDelay( FREQUENCY_MS_TASK2 );
    }
}

/*-----------------------------------------------------------*/

static void prvTask4( void * pvParameters )
{
    /* Prevent the compiler warning about the unused parameter. */
    ( void ) pvParameters;

    for( ; ; )
    {
        /* Send to the queue - causing the queue receive task to unblock and
         * write to the console.  0 is used as the block time so the send operation
         * will not block - it shouldn't need to block as the queue should always
         * have at least one space at this point in the code. */
        console_print( "Message from task 2\n" );
        for( int i=0 ; i < 1000000 ; i++ )
        {
        }

        /* Place this task in the blocked state until it is time to run again.
        *  The block time is specified in ticks, pdMS_TO_TICKS() was used to
        *  convert a time specified in milliseconds into a time specified in ticks.
        *  While in the Blocked state this task will not consume any CPU time. */
        vTaskDelay( FREQUENCY_MS_TASK2 );
    }
}



void RandomName(char nameFile*, int tam){
    const char character[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIKLMNOPQRSTUVWXYZ" ;
    int totalChar = sizeof(character) -1 ; 
    

    for ( int  i ; i < tam ; i++){

        nameFile = character[rand()% totalChar]
    }

    nameFile[tam] = '\0'
}
