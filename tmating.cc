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

#include <vector>

#include <mocs/rand.h>
#include <mocs/tmating.h>

extern "C" Loadable* TournamentMating_newInstance(Params& p) {
	return new TournamentMating(p);
}

TournamentMating::TournamentMating(Params& p) : MatingSelection(p) {
}

TournamentMating::~TournamentMating() {
}

void TournamentMating::operator () (Population& pop,size_t& a,size_t& b) {
	bool f=p.getBool("fitnessTournament",true);
	size_t i,j,k,l,t=p.getInt("tournament",4),w=p.getInt("winners",2);
	vector<size_t> pool;
	if(a!=~0u) {
		pool.push_back(a);
	}
	for(i=pool.size();i<2;) {
		for(j=0;j<t;j++) {
			k=Rand::nextInt(pop.size());
			pool.push_back(k);
		}
		for(l=0;l<w;l++,i++) {
			for(j=i+l+1,k=i+l;j<t;j++) {
				if(f) {
					if(pop[pool[j]]->getValue()<pop[pool[k]]->getValue()) {
						k=j;
					}
				} else if(pop[pool[j]]->getFitness()<pop[pool[k]]->getFitness()) {
					k=j;
				} else if(!(pop[pool[k]]->getFitness()<pop[pool[j]]->getFitness())) {
					if(pop[pool[j]]->getValue()<pop[pool[k]]->getValue()) {
						k=j;
					}
				}
			}
			swap(pool[i+l],pool[k]);
		}
		pool.resize(i+1);
	}
	a=pool[0];
	b=pool[1];
}
