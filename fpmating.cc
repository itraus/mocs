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
#include <mocs/fpmating.h>

extern "C" Loadable* FitnessProportionateMating_newInstance(Params& p) {
	return new FitnessProportionateMating(p);
}

FitnessProportionateMating::FitnessProportionateMating(Params& p) : MatingSelection(p) {
}

FitnessProportionateMating::~FitnessProportionateMating() {
}

void FitnessProportionateMating::operator () (Population& pop,size_t& a,size_t& b) {
	size_t i,j;
	double f1,f2,fmax,total,sum;
	sum=pop[0]->getValue();
	fmax=sum;
	for(i=1;i<pop.size();i++) {
		sum+=pop[i]->getValue();
		if(pop[i]->getValue()>fmax) {
			fmax=pop[i]->getValue();
		}
	}
	total=fmax*pop.size()-sum;
	f1=Rand::nextDouble()*total;
	f2=f1+total/2.0;
	if(f2>=total) {
		f2-=total;
	}
	for(i=0;i<pop.size() && f1>(fmax-pop[i]->getValue());f1-=fmax-pop[i]->getValue(),i++);
	for(j=0;j<pop.size() && f2>(fmax-pop[j]->getValue());f2-=fmax-pop[j]->getValue(),j++);
	assert(i<pop.size());
	assert(j<pop.size());
	a=i;
	b=j;
}
