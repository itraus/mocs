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

#include <algorithm>

#include <mocs/moes.h>
#include <mocs/rand.h>

extern "C" Loadable* MOES_newInstance(Params& p) {
	return new MOES(p);
}

MOES::MOES(Params& p) : MOGA(p) {
}

MOES::~MOES() {
}

Population* MOES::selection(Population& pop) {
	return new Population(pop);
}

Population* MOES::crossover(Population& pop) {
	size_t i,j,k;
	Individual* a;
	Individual* b;
	Population* newPop=new Population;
	for(i=0;i<population;i++) {
		if(Rand::nextDouble()<crossProb) {
			j=~0u;
			(*mating)(pop,j,k);
			(*crossOp)(*pop[j],*pop[k],a,b);
			delete b;
		} else {
			j=Rand::nextInt(pop.size());
			a=new Individual(*pop[j]);
		}
		newPop->add(a);
	}
	pop.swap(*newPop);
	delete newPop;
	return &pop;
}
