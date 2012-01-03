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

#ifndef __INDIVIDUAL_H__
#define __INDIVIDUAL_H__

#include <mocs/genome.h>
#include <mocs/fitness.h>

class Individual {
		double value;
		Genome genome;
		Fitness fitness;

	public:
		Individual();
		Individual(size_t size);
		Individual(const Individual& indiv);
		~Individual();

		size_t size() const;
		Genome& getGenome();
		const Genome& getGenome() const;
		Fitness& getFitness();
		const Fitness& getFitness() const;
		double getValue() const;
		void setValue(double value);

		int operator < (const Individual& indiv) const;
		int operator == (const Individual& indiv) const;

		struct lesser {
			int operator () (const Individual* a,const Individual* b) const {
				return *a<*b;
			}
		};

		struct lesserf {
			int operator () (const Individual* a,const Individual* b) const {
				return a->getFitness()<b->getFitness();
			}
		};

		struct greater {
			int operator () (const Individual* a,const Individual* b) const {
				return *b<*a;
			}
		};

		struct greaterf {
			int operator () (const Individual* a,const Individual* b) const {
				return b->getFitness()<a->getFitness();
			}
		};
};

ostream& operator << (ostream& os,const Individual& indiv);

#endif
