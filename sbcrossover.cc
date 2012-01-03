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

#include <cmath>
#include <vector>
#include <algorithm>

#include <mocs/rand.h>
#include <mocs/realgene.h>
#include <mocs/sbcrossover.h>

extern "C" Loadable* SimulatedBinaryCrossover_newInstance(Params& p) {
	return new SimulatedBinaryCrossover(p);
}

SimulatedBinaryCrossover::SimulatedBinaryCrossover(Params& p) : CrossoverOperator(p) {
	etac=p.getDouble("etac",2.0);
}

SimulatedBinaryCrossover::~SimulatedBinaryCrossover() {
}

void SimulatedBinaryCrossover::operator () (const Individual& a,const Individual& b,Individual*& c,Individual*& d) {
	double xa,xb,u,betac;
	c=new Individual;
	d=new Individual;
	c->getFitness().resize(a.getFitness().size());
	d->getFitness().resize(a.getFitness().size());
	u=Rand::nextDouble();
	if(u<=0.5) {
		betac=pow(2.0*u,1.0/(etac+1));
	} else {
		betac=pow(1.0/(2.0*(1.0-u)),1.0/(etac+1));
	}
	for(size_t i=0;i<a.size();i++) {
		c->getGenome().add(a.getGenome()[i]->newGene());
		d->getGenome().add(a.getGenome()[i]->newGene());
		xa=((RealGene*)a.getGenome()[i])->getValue();
		xb=((RealGene*)b.getGenome()[i])->getValue();
		((RealGene*)c->getGenome()[i])->setValue(0.5*((1+betac)*xa+(1-betac)*xb));
		((RealGene*)d->getGenome()[i])->setValue(0.5*((1-betac)*xa+(1+betac)*xb));
		xa=a.getGenome()[i]->getDev();
		xb=b.getGenome()[i]->getDev();
		c->getGenome()[i]->setDev(0.5*((1+betac)*xa+(1-betac)*xb));
		d->getGenome()[i]->setDev(0.5*((1-betac)*xa+(1+betac)*xb));
	}
	c->getGenome().setDev((a.getGenome().getDev()+b.getGenome().getDev())/2);
	d->getGenome().setDev((a.getGenome().getDev()+b.getGenome().getDev())/2);
	c->setValue(HUGE);
	d->setValue(HUGE);
}
