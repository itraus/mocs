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
#include <mocs/nucrossover.h>

extern "C" Loadable* NonUniformCrossover_newInstance(Params& p) {
	return new NonUniformCrossover(p);
}

NonUniformCrossover::NonUniformCrossover(Params& p) : CrossoverOperator(p) {
	crossPoints=p.getInt("crossPoints",2);
}

NonUniformCrossover::~NonUniformCrossover() {
}

void NonUniformCrossover::operator () (const Individual& a,const Individual& b,Individual*& c,Individual*& d) {
	size_t i,j,k;
	vector<size_t> points1,points2,aligns;
	c=new Individual;
	d=new Individual;
	crossAlign=p.getInt("crossAlign",1);
	c->getFitness().resize(a.getFitness().size());
	d->getFitness().resize(a.getFitness().size());
	c->getGenome().setDev((a.getGenome().getDev()+b.getGenome().getDev())/2);
	d->getGenome().setDev((a.getGenome().getDev()+b.getGenome().getDev())/2);
	c->setValue(HUGE);
	d->setValue(HUGE);
	for(i=0;i<crossPoints;i++) {
		aligns.push_back(Rand::nextInt(crossAlign));
		points1.push_back(Rand::nextInt(a.size()/crossAlign));
		points2.push_back(Rand::nextInt(b.size()/crossAlign));
	}
	sort(points1.begin(),points1.end());
	sort(points2.begin(),points2.end());
	if(crossAlign>1) {
		for(i=1;i<crossPoints;) {
			for(i=1;i<crossPoints;i++) {
				if((points1[i-1]==points1[i] || points2[i-1]==points2[i]) && aligns[i-1]>aligns[i]) {
					swap(aligns[i-1],aligns[i]);
					break;
				}
			}
		}
		for(i=0;i<crossPoints;i++) {
			points1[i]=points1[i]*crossAlign+aligns[i];
			points2[i]=points2[i]*crossAlign+aligns[i];
		}
	}
	points1.push_back(a.size());
	points2.push_back(b.size());
	for(i=0,j=0,k=0;j<=crossPoints;j++) {
		if(j&1) {
			for(;i!=points2[j];i++) {
				c->getGenome().add(b.getGenome()[i]->newGene());
			}
			for(;k!=points1[j];k++) {
				d->getGenome().add(a.getGenome()[k]->newGene());
			}
			i=points1[j];
			k=points2[j];
		} else {
			for(;i!=points1[j];i++) {
				c->getGenome().add(a.getGenome()[i]->newGene());
			}
			for(;k!=points2[j];k++) {
				d->getGenome().add(b.getGenome()[k]->newGene());
			}
			i=points2[j];
			k=points1[j];
		}
	}
}
