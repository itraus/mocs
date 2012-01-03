/*
 * MOCS - Multi-Objective Classifier System
 * Copyright (C) 2003 by Ivan Traus
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <cctype>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

#include <ext/hash_map>

#if __GNUC__ >= 3

using namespace __gnu_cxx;

namespace std {
	template <>
	struct equal_to<const char*> {
		bool operator () (const char* const& x,const char* const& y) const {
			return strcmp(x,y)==0;
		}
	};
}

typedef hash<const char*> hash_str;

#else

class hash_str : public hash_compare<const char*> {
	public:
		bool operator () (const char* const& x,const char* const& y) const {
			return strcmp(x,y)<0;
		}

		size_t operator () (const char* const& key) const {
			size_t h=0;
			for(size_t i=0;key[i];h+=key[i++]);
			return h;
		}
};

#endif

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#ifndef HUGE
	#define HUGE 3.40282347e+38F
#endif

#ifndef YYSTYPE
	#define YYSTYPE string
#endif

#ifndef strcasecmp
	#define strdup strdupi
	#define strcasecmp strcmpi
#endif

inline char* strdupi(const char* a) {
	return strcpy(new char[strlen(a)+1],a);
}

inline int strcmpi(const char* a,const char* b) {
	size_t i;
	for(i=0;a[i] && b[i] && tolower(a[i])==tolower(b[i]);i++);
	return tolower(a[i])-tolower(b[i]);
}

#endif
