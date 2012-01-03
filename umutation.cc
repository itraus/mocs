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

#include <mocs/rand.h>
#include <mocs/umutation.h>

extern "C" Loadable* UniformMutation_newInstance(Params& p) {
	return new UniformMutation(p);
}

UniformMutation::UniformMutation(Params& p) : MutationOperator(p) {
}

UniformMutation::~UniformMutation() {
}

void UniformMutation::operator () (Individual& indiv) {
	for(size_t i=0;i<indiv.size();i++) {
		indiv.getGenome()[i]->mutate();
	}
}

void UniformMutation::operator () (Population& pop) {
	double mutProb=p.getDouble("mutProb",1.0);
	for(size_t i=0;i<pop.size();i++) {
		if(pop[i]->getValue()<HUGE || Rand::nextDouble()<mutProb) {
			(*this)(*pop[i]);
			pop[i]->setValue(HUGE);
		}
	}
}
