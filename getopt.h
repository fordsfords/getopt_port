/*******************************************************************************
 * Copyright (c) 2012-2017, Kim Grasman <kim.grasman@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Kim Grasman nor the
 *     names of contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL KIM GRASMAN BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Updated by Steve Ford <fordsfords@gmail.com> to be all-inclusive in the
 * include file. No ".c" file needed. Requires adding GETOPT_PORT above
 * your "main()".
 *
 ******************************************************************************/

#ifndef INCLUDED_GETOPT_PORT_H
#define INCLUDED_GETOPT_PORT_H

#include <string.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define no_argument 1
#define required_argument 2
#define optional_argument 3

extern char* optarg;
extern int optind, opterr, optopt;

struct option {
  const char* name;
  int has_arg;
  int* flag;
  int val;
};

int getopt(int argc, char* const argv[], const char* optstring);

int getopt_long(int argc, char* const argv[],
  const char* optstring, const struct option* longopts, int* longindex);


#define GETOPT_PORT \
char* optarg; \
int optopt; \
int optind = 1; \
int opterr; \
 \
static char* optcursor = NULL; \
 \
int getopt(int argc, char* const argv[], const char* optstring) { \
  int optchar = -1; \
  const char* optdecl = NULL; \
 \
  optarg = NULL; \
  opterr = 0; \
  optopt = 0; \
 \
  if (optind >= argc) \
    goto no_more_optchars; \
 \
  if (argv[optind] == NULL) \
    goto no_more_optchars; \
 \
  if (*argv[optind] != '-') \
    goto no_more_optchars; \
 \
  if (strcmp(argv[optind], "-") == 0) \
    goto no_more_optchars; \
 \
  if (strcmp(argv[optind], "--") == 0) { \
    ++optind; \
    goto no_more_optchars; \
  } \
 \
  if (optcursor == NULL || *optcursor == '\0') \
    optcursor = argv[optind] + 1; \
 \
  optchar = *optcursor; \
 \
  optopt = optchar; \
 \
  optdecl = strchr(optstring, optchar); \
  if (optdecl) { \
    if (optdecl[1] == ':') { \
      optarg = ++optcursor; \
      if (*optarg == '\0') { \
        if (optdecl[2] != ':') { \
          if (++optind < argc) { \
            optarg = argv[optind]; \
          } else { \
            optarg = NULL; \
            optchar = (optstring[0] == ':') ? ':' : '?'; \
          } \
        } else { \
          optarg = NULL; \
        } \
      } \
 \
      optcursor = NULL; \
    } \
  } else { \
    optchar = '?'; \
  } \
 \
  if (optcursor == NULL || *++optcursor == '\0') \
    ++optind; \
 \
  return optchar; \
 \
no_more_optchars: \
  optcursor = NULL; \
  return -1; \
} \


#if defined(__cplusplus)
}
#endif

#endif // INCLUDED_GETOPT_PORT_H
