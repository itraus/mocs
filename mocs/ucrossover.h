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

#ifndef __UCROSSOVER_H__
#define __UCROSSOVER_H__

#include <mocs/coperator.h>

class UniformCrossover : public CrossoverOperator {
	protected:
		size_t crossPoints;

	public:
		UniformCrossover(Params& p);
		virtual ~UniformCrossover();

		virtual void operator () (const Individual& a,const Individual& b,Individual*& c,Individual*& d);
};

#endif
