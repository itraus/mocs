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
#include <cstdio>

#include <mocs/imodel.h>
#include <mocs/iielement.h>
#include <mocs/rielement.h>
#include <mocs/rattribute.h>
#include <mocs/iattribute.h>

extern "C" Loadable* InstanceModel_newInstance(Params& p) {
	return new InstanceModel(p);
}

InstanceModel::InstanceModel(Params& p) : RuleModel(p) {
}

InstanceModel::~InstanceModel() {
}

void InstanceModel::init(const char* file) {
	char* s=new char[11];
	Model::init(file);
	for(size_t i=0;i<att.size();i++) {
		if(dynamic_cast<RealAttribute*>(att[i])) {
			elems.push_back(new RealInstanceElement((RealAttribute*)att[i]));
		} else if(dynamic_cast<IntAttribute*>(att[i])) {
			elems.push_back(new IntInstanceElement((IntAttribute*)att[i]));
		} else {
			assert(true);
		}
	}
	sprintf(s,"%d",(int)elems.size());
	ruleSize=elems.size();
	p.put("crossAlign",s);
}

double InstanceModel::generality(Individual& indiv) {
	return 1;
}

double InstanceModel::eval(Individual& indiv,Instance& inst) {
	double dist,dnear;
	size_t i,j,k,knear,num,near;
	Genome& genome=indiv.getGenome();
	for(i=0,knear=0,near=0,dnear=HUGE;i<indiv.size() && dnear>0;i+=ruleSize) {
		for(j=0,k=i,dist=0,num=0;j<elems.size()-1;k+=elems[j++]->size()) {
			if(!inst[j]->isUndefined() && att[j]->getSize()>0) {
				dist+=pow((*elems[j])(&genome[k],*inst[j])/att[j]->getSize(),2);
				num++;
			}
		}
		if(num>0) {
			//dist=sqrt(dist)/num;
			dist=sqrt(dist);
		}
		if(dist<dnear) {
			dnear=dist;
			knear=k;
			near=i;
		}
	}
	if(used.find(near)==used.end()) {
		used[near]=1;
		rused++;
	} else {
		used[near]++;
	}
	return ((*elems.back())(&genome[knear],*inst.back())==0) ? 0 : 1;
}
