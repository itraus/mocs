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

#ifndef __NGGA_H__
#define __NGGA_H__

#include <vector>

#include <mocs/moga.h>

class NGGA : public MOGA {
	protected:
		struct fvalue {
			double d,w;
		};

		size_t n1,n2;
		double sum,cd,cw,kd,kw;
		vector<fvalue> fitness;

		void initialize(size_t indiv,Population& pop);
		void update(Population& pop);
		void update(size_t i,Population& pop);
		size_t cross(Population& pop);

	public:
		NGGA(Params& p);
		virtual ~NGGA();

		void init(Population& pop);
		Population* operator () (Population& pop);
};

#endif
