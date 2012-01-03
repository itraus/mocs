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

#ifndef __RAND_H__
#define __RAND_H__

#include <mocs/config.h>

class Rand {

#ifdef USE_STD_RANDOM
		static double gaussian;
		static int haveGaussian;
#else
		static double u[97];
		static double c;
		static double cd;
		static double cm;
		static int i97;
		static int j97;
		static bool test;
#endif

	public:
		static void init();
		static void setSeed(int seed);
		static int nextInt();
		static int nextInt(int max);
		static double nextDouble();
		static double nextGaussian();
};

#endif
