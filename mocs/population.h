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

#ifndef __POPULATION_H__
#define __POPULATION_H__

#include <vector>

#include <mocs/individual.h>

class Population : public vector<Individual*> {
	public:
		Population();
		Population(size_t size);
		Population(const Population& pop);
		virtual ~Population();

		void add(Individual* indiv);
		void add(Population& pop);
};

ostream& operator << (ostream& os,const Population& pop);

#endif
