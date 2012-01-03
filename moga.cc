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
#include <algorithm>

#include <mocs/moga.h>
#include <mocs/rand.h>

size_t MOGA::order::k;

extern "C" Loadable* MOGA_newInstance(Params& p) {
	return new MOGA(p);
}

MOGA::MOGA(Params& p) : EvolutionaryAlgorithm(p) {
	sharing=p.getDouble("sharing",0.1);
	crossProb=p.getDouble("crossProb",0.5);
	population=p.getInt("population",100);
	parents=p.getInt("parents",population);
	best=p.getInt("best",population/4);
	elitism=p.getBool("elitism",false);
}

MOGA::~MOGA() {
}

void MOGA::init(Population& pop) {
	func=(FitnessFunction*)p.get("fitness");
	mating=(MatingSelection*)p.get("mating");
	mutate=(MutationOperator*)p.get("mutation");
	crossOp=(CrossoverOperator*)p.get("crossover");
	selection=(SelectionOperator*)p.get("selection");
	(*func)(pop);
	assignFitness(pop);
}

Population* MOGA::final(Population& pop) {
	size_t i,j;
	Population* newPop=new Population;
	for(i=0;i<pop.size();i++) {
		for(j=0;j<pop.size() && !(pop[j]->getFitness()<pop[i]->getFitness());j++);
		if(j==pop.size()) {
			newPop->add(new Individual(*pop[i]));
		}
	}
	return newPop;
}

void MOGA::assignFitness(Population& pop) {
	size_t i,j;
	double value,dist;
	for(i=0;i<pop.size();i++) {
		pop[i]->setValue(1);
		for(j=0;j<pop.size();j++) {
			if(i!=j) {
				if(pop[j]->getFitness()<pop[i]->getFitness()) {
					pop[i]->setValue(pop[i]->getValue()+1);
				}/* else if(pop[j]->getFitness()==pop[i]->getFitness()) {
					if(i<j) {
						pop[j]->setValue(pop[j]->getValue()+1);
					} else {
						pop[i]->setValue(pop[i]->getValue()+1);
					}
				}*/
			}
		}
	}
	sort(pop.begin(),pop.end(),Individual::lesser());
	for(i=0;i<pop.size();) {
		for(j=i+1;j<pop.size() && *pop[i]==*pop[j];j++);
		value=(pop.size()-(i+j+1)/2.0)/(pop.size()-1);
		for(;i<j;i++) {
			pop[i]->setValue(value);
		}
	}
	for(i=0;i<pop.size();i++) {
		for(j=0,value=1.0;j<pop.size();j++) {
			if(i!=j) {
				dist=pop[i]->getFitness()-pop[j]->getFitness();
				if(dist<=sharing) {
					if(sharing>0) {
						value+=1.0-dist/sharing;
					} else {
						value+=1.0;
					}
				}
			}
		}
		pop[i]->setValue(pop[i]->getValue()/value);
	}
	partial_sort(&pop[0],&pop[parents],&pop[pop.size()],Individual::greater());
	for(i=0;i<parents;i++) {
		pop[i]->setValue(i);
	}
	for(i=parents;i<pop.size();i++) {
		delete pop[i];
	}
	pop.resize(parents);
}

Population* MOGA::crossover(Population& pop) {
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

void MOGA::addBest(Population& pop,Population& old) {
	size_t i,j;
	Population temp;
	if(best<old.size()) {
		for(i=0;i<old.size();i++) {
			for(j=0;j<old.size();j++) {
				if(old[j]->getFitness()<old[i]->getFitness()) {
					break;
				}
			}
			if(j==old.size()) {
				for(j=0;j<temp.size();j++) {
					if(temp[j]->getFitness()==old[i]->getFitness()) {
						break;
					}
				}
				if(j==temp.size()) {
					temp.add(old[i]);
					pop.add(new Individual(*old[i]));
					pop.back()->setValue(0);
				}
			}
		}
		temp.clear();
		order::k=0;
		partial_sort(&old[0],&old[best],&old[old.size()],order());
	}
	for(i=0;i<best;i++) {
		pop.add(new Individual(*old[i]));
		pop.back()->setValue(0);
	}
}

Population* MOGA::operator () (Population& pop) {
	Population& newPop=*(*selection)(pop);
	crossover(newPop);
	(*mutate)(newPop);
	(*func)(newPop);
	if(elitism) {
		Population* tmp=new Population(pop);
		newPop.add(*tmp);
		tmp->clear();
		delete tmp;
	}
	assignFitness(newPop);
	if(best>0) {
		addBest(newPop,pop);
	}
	return &newPop;
}
