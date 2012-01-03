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

#include <mocs/nsgaii.h>

extern "C" Loadable* NSGAII_newInstance(Params& p) {
	return new NSGAII(p);
}

NSGAII::NSGAII(Params& p) : MOGA(p) {
}

NSGAII::~NSGAII() {
}

void NSGAII::assignFitness(Population& pop) {
	size_t i,j,k;
	vector<size_t> h,f;
	vector<size_t> fronts;
	vector<size_t> n(pop.size());
	vector<vector<size_t> > s(pop.size());
	bool pushEqual=p.getBool("pushEqual",false);
	bool pushMoreThanTwoEqual=p.getBool("pushMoreThanTwoEqual",false);
	h.reserve(pop.size());
	f.reserve(pop.size());
	for(i=0;i<pop.size();i++) {
		n[i]=0;
		s[i].reserve(pop.size());
		for(j=0;j<pop.size();j++) {
			if(pop[i]->getFitness()<pop[j]->getFitness()) {
				s[i].push_back(j);
			} else if(pop[j]->getFitness()<pop[i]->getFitness()) {
				n[i]++;
			}
		}
		if(n[i]==0) {
			f.push_back(i);
		}
	}
	fronts.reserve(pop.size());
	fronts.push_back(0);
	for(i=1;f.size()>0;i++) {
		h.clear();
		fronts.push_back(fronts.back()+f.size());
		for(;f.size()>0;f.pop_back()) {
			j=f.back();
			for(;s[j].size()>0;s[j].pop_back()) {
				k=s[j].back();
				n[k]--;
				if(n[k]==0) {
					h.push_back(k);
				}
			}
			pop[j]->setValue(i);
		}
		f.swap(h);
	}
	sort(pop.begin(),pop.end(),Individual::lesser());
	for(i=0;i<pop.size();i++) {
		pop[i]->setValue(0);
	}
	for(i=1;i<fronts.size() && fronts[i-1]<parents;i++) {
		if(pushEqual) {
			for(k=fronts[i-1];k<fronts[i]-1;k++) {
				for(j=k+1;j<fronts[i];j++) {
					if(pop[k]->getFitness()==pop[j]->getFitness()) {
						fronts[i]--;
						swap(pop[j],pop[fronts[i]]);
					}
				}
			}
		}
		for(k=0;k<pop[0]->getFitness().size();k++) {
			order::k=k;
			sort(&pop[fronts[i-1]],&pop[fronts[i]],order());
			pop[fronts[i-1]]->setValue(HUGE);
			pop[fronts[i]-1]->setValue(HUGE);
			for(j=fronts[i-1]+1;j<fronts[i]-1;j++) {
				if(pop[j]->getValue()<HUGE) {
					pop[j]->setValue(pop[j]->getValue()+fabs(pop[j+1]->getFitness()[k]-pop[j-1]->getFitness()[k]));
				}
			}
		}
		sort(&pop[fronts[i-1]],&pop[fronts[i]],Individual::greater());
		if(pushMoreThanTwoEqual) {
			for(;pop[fronts[i]-1]->getValue()==0;fronts[i]--);
		}
	}
	for(i=0;i<parents;i++) {
		pop[i]->setValue(i);
	}
	for(i=parents;i<pop.size();i++) {
		delete pop[i];
	}
	pop.resize(parents);
}
