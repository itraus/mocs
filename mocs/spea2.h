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

#ifndef __SPEA2_H__
#define __SPEA2_H__

#include <mocs/moga.h>

class SPEA2 : public MOGA {
	protected:
		size_t k;

		void assignFitness(Population& pop);

	public:
		SPEA2(Params& p);
		virtual ~SPEA2();

		struct node {
			size_t a;
			double d;

			node(size_t a,double d) : a(a), d(d) {
			}

			bool operator < (const node& b) const {
				return d<b.d;
			}
		};
};

#endif
