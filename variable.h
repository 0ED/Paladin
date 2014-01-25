/*
 * Paladin.
 * Copyright (C) 2013 TasukuTAKAHASHI All Rights Reserved.
 * This file is part of Paladin.
 *
 * Paladin is programming language, and open source software.
 * you can redistribute it and/or modify it.
 * Enjoy Paladin !! */

#ifndef __INCLUDE_VARIABLE_H__
#define __INCLUDE_VARIABLE_H__

typedef struct variable { 
	int          kind;
	int			 integer;
	double		 real;
	char		*string;
} Variable;

#endif /* !__INCLUDE_VARIABLE_H__*/

