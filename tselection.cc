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
#include <mocs/tselection.h>

extern "C" Loadable* TournamentSelection_newInstance(Params& p) {
	return new TournamentSelection(p);
}

TournamentSelection::TournamentSelection(Params& p) : SelectionOperator(p) {
	tournament=p.getInt("tournament",2);
	winners=p.getInt("winners",1);
	population=p.getInt("population",100);
	fitnessTournament=p.getBool("fitnessTournament",true);
}

TournamentSelection::~TournamentSelection() {
}

Population* TournamentSelection::operator () (Population& pop) {
	size_t i,j,k;
	Population pool;
	Population& newPop=*new Population;
	while(newPop.size()<population) {
		for(i=0;i<tournament;i++) {
			pool.add(pop[Rand::nextInt(pop.size())]);
		}
		for(k=0;k<winners && newPop.size()<population;k++) {
			for(i=k+1,j=k;i<tournament;i++) {
				if(fitnessTournament) {
					if(pool[i]->getValue()<pool[j]->getValue()) {
						j=i;
					}
				} else if(pool[i]->getFitness()<pool[j]->getFitness()) {
					j=i;
				} else if(!(pool[j]->getFitness()<pool[i]->getFitness())) {
					if(pool[i]->getValue()<pool[j]->getValue()) {
						j=i;
					}
				}
			}
			swap(pool[k],pool[j]);
			newPop.add(new Individual(*pool[k]));
		}
		pool.clear();
	}
	return &newPop;
}
