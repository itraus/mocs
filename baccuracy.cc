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

#include <mocs/baccuracy.h>

bool operator > (vector<double>& a,vector<double>& b) {
	size_t i;
	for(i=0;i<a.size() && a[i]==b[i];i++);
	return i==a.size() || a[i]>b[i];
}

extern "C" Loadable* BestAccuracy_newInstance(Params& p) {
	return new BestAccuracy(p);
}

BestAccuracy::BestAccuracy(Params& p) : DecisionMaker(p) {
}

BestAccuracy::~BestAccuracy() {
}

Individual& BestAccuracy::choose(Population& pop) {
	size_t i,j;
	for(i=1,j=0;i<pop.size();i++) {
		if(pop[j]->getFitness()[0]>pop[i]->getFitness()[0]) {
			j=i;
		} else if(pop[j]->getFitness()[0]==pop[i]->getFitness()[0]) {
			if(pop[j]->getFitness()[3]>pop[i]->getFitness()[3]) {
				j=i;
			} else if(pop[j]->getFitness()[3]==pop[j]->getFitness()[3]) {
				if(pop[j]->getFitness()>pop[i]->getFitness()) {
					j=i;
				}
			}
		}
	}
	return *pop[j];
}
