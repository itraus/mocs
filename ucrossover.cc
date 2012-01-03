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

#include <mocs/rand.h>
#include <mocs/ucrossover.h>

extern "C" Loadable* UniformCrossover_newInstance(Params& p) {
	return new UniformCrossover(p);
}

UniformCrossover::UniformCrossover(Params& p) : CrossoverOperator(p) {
	crossPoints=p.getInt("crossPoints",2);
}

UniformCrossover::~UniformCrossover() {
}

void UniformCrossover::operator () (const Individual& a,const Individual& b,Individual*& c,Individual*& d) {
	size_t i,j;
	vector<size_t> points;
	c=new Individual;
	d=new Individual;
	c->getFitness().resize(a.getFitness().size());
	d->getFitness().resize(a.getFitness().size());
	points.resize(crossPoints+1);
	for(i=0;i<crossPoints;i++) {
		points[i]=Rand::nextInt(a.size());
	}
	points[crossPoints]=a.size();
	sort(points.begin(),points.end());
	for(i=0,j=0;j<=crossPoints;j++) {
		for(;i<points[j];i++) {
			if(j&1) {
				c->getGenome().add(b.getGenome()[i]->newGene());
				d->getGenome().add(a.getGenome()[i]->newGene());
			} else {
				c->getGenome().add(a.getGenome()[i]->newGene());
				d->getGenome().add(b.getGenome()[i]->newGene());
			}
		}
	}
	c->getGenome().setDev((a.getGenome().getDev()+b.getGenome().getDev())/2);
	d->getGenome().setDev((a.getGenome().getDev()+b.getGenome().getDev())/2);
	c->setValue(HUGE);
	d->setValue(HUGE);
}
