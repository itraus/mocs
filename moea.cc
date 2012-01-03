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

#include <mocs/moea.h>
#include <mocs/rand.h>
#include <mocs/loader.h>
#include <mocs/ffunction.h>
#include <mocs/coperator.h>
#include <mocs/moperator.h>

MOEA::MOEA(const char* file) {
	p.load(file);
	p.init();
}

MOEA::MOEA(char** files,size_t num) {
	for(size_t i=0;i<num;i++) {
		p.load(files[i]);
	}
	p.init();
}

MOEA::~MOEA() {
	delete pop;
}

void MOEA::init() {
	initiator=(Initiator*)p.get("initiator");
	algorithm=(EvolutionaryAlgorithm*)p.get("algorithm");
	population=p.getInt("parents",100);
	pop=new Population(population);
	Rand::setSeed(p.getInt("seed",0));
	init(*pop);
}

void MOEA::init(Population& pop) {
	for(size_t i=0;i<population;i++) {
		pop[i]=initiator->newIndividual();
	}
	algorithm->init(pop);
}

void MOEA::output(size_t i,Population& pop) {
	cout << "# i " << i << endl;
	cout << pop;
}

void MOEA::final(Population& pop) {
	cout << "# f" << endl;
	for(size_t i=0;i<pop.size();i++) {
		cout << i << " | " << *pop[i] << " | " << pop[i]->getGenome() << endl;
	}
}

void MOEA::operator () () {
	Population* newPop;
	size_t num=p.getInt("iterations",100);
	for(size_t i=0;i<num;i++) {
		newPop=(*algorithm)(*pop);
		if(newPop!=pop) {
			delete pop;
			pop=newPop;
		}
		output(i,*pop);
	}
	newPop=algorithm->final(*pop);
	if(newPop!=pop) {
		delete pop;
		pop=newPop;
	}
	final(*newPop);
}
