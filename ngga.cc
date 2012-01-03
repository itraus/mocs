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

#include <mocs/ngga.h>
#include <mocs/rand.h>

extern "C" Loadable* NGGA_newInstance(Params& p) {
	return new NGGA(p);
}

NGGA::NGGA(Params& p) : MOGA(p) {
	n1=p.getInt("n1",population/3);
	n2=p.getInt("n2",population/3);
	kd=p.getDouble("kd",0.0);
	kw=p.getDouble("kw",1.0/population);
	cd=p.getDouble("cd",10.0);
	cw=p.getDouble("cw",0.05);
}

NGGA::~NGGA() {
}

void NGGA::init(Population& pop) {
	MOGA::init(pop);
	fitness.resize(pop.size());
	for(size_t i=0;i<pop.size();i++) {
		initialize(i,pop);
	}
}

void NGGA::initialize(size_t indiv,Population& pop) {
	size_t i,j;
	double dist;
	fitness[indiv].d=0;
	fitness[indiv].w=0;
	pop[indiv]->setValue(0);
	for(i=0;i<n1;i++) {
		while((j=Rand::nextInt(pop.size()))==indiv);
		if(pop[indiv]->getFitness()<pop[j]->getFitness()) {
			fitness[j].d++;
		} else if(pop[j]->getFitness()<pop[indiv]->getFitness()) {
			fitness[indiv].d++;
		}
		dist=pop[j]->getFitness()-pop[indiv]->getFitness();
		if(dist<=sharing) {
			if(sharing>0) {
				dist=1.0-dist/sharing;
			} else {
				dist=1.0;
			}
			fitness[j].w+=dist;
			fitness[indiv].w+=dist;
		}
	}
}

void NGGA::update(Population& pop) {
	size_t a,b;
	double dist;
	for(size_t i=0;i<n2;i++) {
		a=Rand::nextInt(pop.size());
		while((b=Rand::nextInt(pop.size()))==a);
		fitness[a].d*=1.0-kd;
		fitness[b].d*=1.0-kd;
		if(pop[a]->getFitness()<pop[b]->getFitness()) {
			fitness[b].d++;
		} else if(pop[b]->getFitness()<pop[a]->getFitness()) {
			fitness[a].d++;
		}
		fitness[a].w*=1.0-kw;
		fitness[b].w*=1.0-kw;
		dist=pop[a]->getFitness()-pop[b]->getFitness();
		if(dist<=sharing) {
			if(sharing>0) {
				dist=1.0-dist/sharing;
			} else {
				dist=1.0;
			}
			fitness[a].w+=dist;
			fitness[b].w+=dist;
		}
		update(a,pop);
		update(b,pop);
	}
}

void NGGA::update(size_t i,Population& pop) {
	pop[i]->setValue(cw*fitness[i].w+cd*fitness[i].d);
}

size_t NGGA::cross(Population& pop) {
	size_t i,j,worst;
	Individual* a;
	Individual* b;
	for(i=1,worst=0;i<pop.size();i++) {
		if(*pop[worst]<*pop[i]) {
			worst=i;
		}
	}
	i=~0u;
	(*mating)(pop,i,j);
	if(Rand::nextDouble()<crossProb) {
		(*crossOp)(*pop[i],*pop[j],a,b);
		delete b;
		delete pop[worst];
	} else {
		if(i==worst) {
			a=pop[worst];
		} else {
			a=new Individual(*pop[i]);
			delete pop[worst];
		}
	}
	pop[worst]=a;
	return worst;
}

Population* NGGA::operator () (Population& pop) {
	size_t i,j;
	for(;pop.size()>parents;pop.pop_back()) {
		update(pop);
		for(i=1,j=0;i<pop.size();i++) {
			if(*pop[j]<*pop[i]) {
				j=i;
			}
		}
		swap(pop[j],pop.back());
		delete pop.back();
	}
	for(i=0;i<population;i++) {
		update(pop);
		j=cross(pop);
		if(pop[j]->getValue()<HUGE || Rand::nextDouble()<p.getDouble("mutProb",1.0)) {
			(*mutate)(*pop[j]);
		}
		(*func)(*pop[j]);
		initialize(j,pop);
		update(j,pop);
	}
	return &pop;
}
