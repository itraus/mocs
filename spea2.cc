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

#include <mocs/spea2.h>

bool operator < (vector<SPEA2::node>& a,vector<SPEA2::node>& b) {
	size_t i;
	assert(a.size()==b.size());
	for(i=0;i<a.size() && i<b.size();i++) {
		if(a[i].d<b[i].d) {
			return true;
		} else if(a[i].d>b[i].d) {
			return false;
		}
	}
	return true;
}

extern "C" Loadable* SPEA2_newInstance(Params& p) {
	return new SPEA2(p);
}

SPEA2::SPEA2(Params& p) : MOGA(p) {
	k=p.getInt("k",(int)sqrt(2.0*parents));
}

SPEA2::~SPEA2() {
}

void SPEA2::assignFitness(Population& pop) {
	double d;
	size_t i,j;
	vector<size_t> nd;
	vector<size_t> s(pop.size(),0);
	vector<double> r(pop.size(),0);
	vector<vector<node> > nn(pop.size());
	vector<vector<double> > dist(pop.size());
	nd.reserve(pop.size()*2);
	for(i=0;i<pop.size();i++) {
		nn[i].reserve(pop.size());
		dist[i].resize(pop.size());
		for(j=i+1;j<pop.size();j++) {
			if(pop[j]->getFitness()<pop[i]->getFitness()) {
				s[j]++;
			} else if(pop[i]->getFitness()<pop[j]->getFitness()) {
				s[i]++;
			}
		}
	}
	for(i=0;i<pop.size();i++) {
		dist[i][i]=0;
		nn[i].push_back(node(i,0));
		for(j=i+1;j<pop.size();j++) {
			d=pop[i]->getFitness()-pop[j]->getFitness();
			dist[i][j]=d;
			dist[j][i]=d;
			nn[i].push_back(node(j,d));
			nn[j].push_back(node(i,d));
			if(pop[j]->getFitness()<pop[i]->getFitness()) {
				r[i]+=s[j];
			} else if(pop[i]->getFitness()<pop[j]->getFitness()) {
				r[j]+=s[i];
			}
		}
		if(r[i]==0) {
			nd.push_back(i);
		}
		partial_sort(&nn[i][0],&nn[i][k],&nn[i][nn[i].size()],less<node>());
		pop[i]->setValue(r[i]+1.0/(nn[i][k-1].d+2.0));
	}
	for(;nd.size()>parents;) {
		j=0;
		for(i=1;i<nd.size();i++) {
			if(nn[nd[i]]<nn[nd[j]]) {
				j=i;
			}
		}
		i=nd[j];
		nd[j]=nd.back();
		nd.pop_back();
		pop[i]->setValue(HUGE);
		for(j=0;j<nd.size();j++) {
			for(vector<node>::iterator vi=nn[nd[j]].begin();vi!=nn[nd[j]].end();vi++) {
				if(vi->a==i) {
					nn[nd[j]].erase(vi);
					break;
				}
			}
		}
	}
	partial_sort(&pop[0],&pop[parents],&pop[pop.size()],Individual::lesser());
	for(i=0;i<parents;i++) {
		pop[i]->setValue(i);
	}
	for(i=parents;i<pop.size();i++) {
		delete pop[i];
	}
	pop.resize(parents);
}
