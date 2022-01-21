/* Jaguar C library */
/* Copyright (C) 2006 Seb/The Removers */
/* http://removers.atari.org/ */

/* This library is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU Lesser General Public */
/* License as published by the Free Software Foundation; either */
/* version 2.1 of the License, or (at your option) any later version. */

/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU */
/* Lesser General Public License for more details. */

/* You should have received a copy of the GNU Lesser General Public */
/* License along with this library; if not, write to the Free Software */
/* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA */

#include "string.h"

char* strtok_r(char *s, const char *delim, char **save_ptr)
{
    char *token;

    token = NULL;             /* Initialize to no token. */

    if (s == NULL)            /* If not first time called... */
    {
        s = *save_ptr;            /* restart from where we left off. */
    }
        
    if (s != 0)               /* If not finished... */
    {
        *save_ptr = 0;

        s += strspn(s, delim);    /* Skip past any leading delimiters. */
        if (*s != '\0')           /* We have a token. */
        {
            token = s;
            *save_ptr = strpbrk(token, delim); /* Find token's end. */
            if (*save_ptr != 0)
            {
                /* Terminate the token and make SAVE_PTR point past it.  */
                *(*save_ptr)++ = '\0';
            }
        }
    }

    return token;
}
