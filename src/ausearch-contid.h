/*
* ausearch-contid.h - Header file for ausearch-contid.c
* adapted from ausearch-string.h
* Copyright (c) 2005,2008,2019 Red Hat Inc., Durham, North Carolina.
* All Rights Reserved.
*
* This software may be freely redistributed and/or modified under the
* terms of the GNU General Public License as published by the Free
* Software Foundation; either version 2, or (at your option) any
* later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING. If not, write to the
* Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor 
* Boston, MA 02110-1335, USA.
*
* Authors:
*   Steve Grubb <sgrubb@redhat.com>
*   Richard Guy Briggs <rgb@redhat.com>
*/

#ifndef AUCONTID_HEADER
#define AUCONTID_HEADER

#include "config.h"

/* This is the node of the linked list. message & item are the only elements
 * at this time. Any data elements that are per item goes here. */
typedef struct _cnode{
  unsigned long long id;		// The audit container id
  unsigned int hits;	// Number of times this contid was attempted to be added
  struct _cnode* next;	// Next contid node pointer
} cnode;

/* This is the linked list head. Only data elements that are 1 per
 * event goes here. */
typedef struct {
  cnode *head;		// List head
  cnode *cur;		// Pointer to current node
  unsigned int cnt;	// How many items in this list
} clist;

void clist_create(clist *l);
static inline void clist_first(clist *l) { l->cur = l->head; }
void clist_last(clist *l);
cnode *clist_next(clist *l);
static inline cnode *clist_get_cur(clist *l) { return l->cur; }
void clist_append(clist *l, cnode *node);
void clist_clear(clist* l);

/* append a contid if its not already on the list */
int clist_add_if_uniq(clist *l, const unsigned long long id);
void clist_sort_by_hits(clist *l);

#endif

