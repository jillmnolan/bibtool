/*** io.c **********************************************************************
** 
** This file is part of BibTool.
** It is distributed under the GNU General Public License.
** See the file COPYING for details.
** 
** (c) 1996-2018 Gerd Neugebauer
** 
** Net: gene@gerd-neugebauer.de
** 
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2, or (at your option)
** any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
**-----------------------------------------------------------------------------
** Description:
**
**
******************************************************************************/

#include <bibtool/general.h>
#include <bibtool/error.h>
#include <bibtool/io.h>
#include <bibtool/symbols.h>
#include "config.h"

/*****************************************************************************/
/* Internal Programs							     */
/*===========================================================================*/

#ifdef __STDC__
#define _ARG(A) A
#else
#define _ARG(A) ()
#endif
 void save_input_file _ARG((char *file));	   /*                        */
 void save_macro_file _ARG((char *file));	   /*                        */
 void save_output_file _ARG((char * file));	   /*                        */

/*****************************************************************************/
/* External Programs and Variables					     */
/*===========================================================================*/

/*---------------------------------------------------------------------------*/


/*****************************************************************************/
/***			 Input File Pipe Section			   ***/
/*****************************************************************************/

#define InputFilePipeIncrement 8

 static char **input_files;
 static int  input_file_size = 0;
 static int  input_file_ptr  = 0;

#define InputPipeIsFull		(input_file_ptr >= input_file_size)
#define InputPipeIsEmpty	(input_file_ptr == 0)
#define PushToInputPipe(FILE)	input_files[input_file_ptr++] = FILE
#define ForAllInputFiles(FILE)	for (FILE=input_files;			\
				     FILE<input_files[input_file_ptr];	\
				     FILE++)

/*-----------------------------------------------------------------------------
** Function:	save_input_file()
** Purpose:	The input file pipe is a dynamic array of strings.
**		This fifo stack is used to store the input \BibTeX{}
**		files to be processed by \BibTool.
**
**		This function is called to push an string into the pipe.
**		If necessary the array has to be allocated or enlarged.
**		This is done in larger junks to avoid lots of calls to
**		|realloc()|.
** Arguments:
**	file	File name to save.
** Returns:	nothing
**___________________________________________________			     */
void save_input_file(file)			   /*			     */
  char *file;					   /*			     */
{						   /*			     */
  if (file == NULL)				   /*			     */
  { WARNING("Missing input file name. Flag ignored.");/*		     */
    return;					   /*			     */
  }						   /*			     */
  if (*file == '-' && file[1] == '\0')		   /*			     */
  { file = NULL; }				   /*			     */
						   /*			     */
  if (InputPipeIsFull)				   /* No space left?	     */
  { input_file_size += InputFilePipeIncrement;	   /*			     */
						   /*			     */
    if (InputPipeIsEmpty			   /* Try to enlarge array   */
	? NULL==(input_files=			   /*			     */
		 (char**)malloc(sizeof(char*)	   /*			     */
				*(size_t)input_file_size))/*		     */
	: NULL==(input_files=			   /*			     */
		 (char**)realloc((char*)input_files,/*			     */
				 sizeof(char*)	   /*			     */
				 *(size_t)input_file_size))/*		     */
	)					   /*			     */
    { OUT_OF_MEMORY("input file pipe."); }	   /*			     */
  }						   /*			     */
  PushToInputPipe(symbol(file));		   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_no_inputs()
** Type:	int
** Purpose:	Get the number of input file names stored.
**		
** Arguments:	none
** Returns:	the number of currently stored input files
**___________________________________________________			     */
int get_no_inputs()				   /*                        */
{						   /*                        */
  return input_file_ptr;			   /*                        */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_input_file()
** Type:	char *
** Purpose:	Getter for a single input file name.
**		
** Arguments:
**	i	the index of the input file to access
** Returns:	the references input file name or NULL otherwise
**___________________________________________________			     */
char * get_input_file(i)			   /*                        */
  int i;					   /*                        */
{ return (i >= 0 && i < input_file_ptr		   /*                        */
	  ? input_files[i]			   /*                        */
	  : NULL);	 			   /*                        */
}						   /*------------------------*/


/*****************************************************************************/
/***			   Output File Section				   ***/
/*****************************************************************************/

 static char *output_file = NULL;	   	   /*			     */

/*-----------------------------------------------------------------------------
** Function:	save_output_file()
** Purpose:	Simply feed the output file name into the static variable.
**		This function is useful since it can be called from rsc.c
** Arguments:
**	file	File name to save
** Returns:	nothing
**___________________________________________________			     */
void save_output_file(file)			   /*			     */
  char * file;					   /*			     */
{ if ( output_file != NULL )			   /*			     */
  { WARNING2("Output file redefined: ",file); }	   /*			     */
  output_file = file;				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_output_file()
** Type:	char*
** Purpose:	This is the getter for the output file name.
**		
** Arguments:	none
** Returns:	the output file name or NULL for STDOUT
**___________________________________________________			     */
char* get_output_file()			   	   /*			     */
{ return output_file;				   /*			     */
}						   /*------------------------*/


/*****************************************************************************/
/***			   Macro File Section				   ***/
/*****************************************************************************/

 static char *macro_file = NULL;	   	   /*			     */

/*-----------------------------------------------------------------------------
** Function:	save_macro_file()
** Purpose:	Simply feed the macro file name into the static variable.
**		This function is useful since it can be called from rsc.c
** Arguments:
**	file	File name to save
** Returns:	nothing
**___________________________________________________			     */
void save_macro_file(file)			   /*			     */
  char *file;					   /*			     */
{ if ( macro_file != NULL )			   /*			     */
  { WARNING2("Macro file redefined: ",file); }	   /*			     */
  macro_file = file;				   /*			     */
}						   /*------------------------*/

/*-----------------------------------------------------------------------------
** Function:	get_macro_file()
** Purpose:	This is the getter for the macro file name.
**		
** Arguments:	none
** Returns:	the macro file name or NULL for none
**___________________________________________________			     */
char* get_macro_file()			   	   /*			     */
{ return macro_file;				   /*			     */
}						   /*------------------------*/
