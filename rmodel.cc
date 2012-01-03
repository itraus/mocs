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

#include <cstdio>

#include <mocs/rmodel.h>
#include <mocs/irelement.h>
#include <mocs/rrelement.h>
#include <mocs/rielement.h>
#include <mocs/rattribute.h>
#include <mocs/iattribute.h>

extern "C" Loadable* RuleModel_newInstance(Params& p) {
	return new RuleModel(p);
}

RuleModel::RuleModel(Params& p) : Model(p), ruleSize(0) {
}

RuleModel::~RuleModel() {
}

void RuleModel::init(const char* file) {
	char* s=new char[11];
	assert(s);
	Model::init(file);
	for(size_t i=0;i<att.size();i++,ruleSize+=elems.back()->size()) {
		if(dynamic_cast<IntAttribute*>(att[i])) {
			elems.push_back(new IntRuleElement((IntAttribute*)att[i]));
		} else if(i==att.size()-1 && dynamic_cast<RealAttribute*>(att[i])) {
			elems.push_back(new RealInstanceElement((RealAttribute*)att[i]));
		} else if(dynamic_cast<RealAttribute*>(att[i])) {
			elems.push_back(new RealRuleElement((RealAttribute*)att[i]));
		} else {
			assert(true);
		}
	}
	sprintf(s,"%d",(int)ruleSize);
	p.put("crossAlign",s);
}

double RuleModel::size(const Individual& indiv) {
	return (indiv.size()/ruleSize)/(double)inst.size();
}

double RuleModel::generality(Individual& indiv) {
	double value=0;
	for(hash_map<size_t,size_t>::iterator i=used.begin();i!=used.end();i++) {
		value+=spread(indiv,i->first);
	}
	return (rused>0) ? (1-value/rused) : 1;
}

double RuleModel::utility(Individual& indiv) {
	size_t rules=indiv.size()/ruleSize;
	return (rules-rused)/rules;
}

double RuleModel::wrong(Individual& indiv) {
	return (noclass<inst.size()) ? error/(double)(inst.size()-noclass) : 1;
}

double RuleModel::unknown(Individual& indiv) {
	return noclass/(double)inst.size();
}

double RuleModel::eval(Individual& indiv,Instance& inst) {
	double dist;
	size_t i,j=0,k=0;
	Genome& genome=indiv.getGenome();
	for(i=0,dist=HUGE;i<indiv.size() && dist>0;i+=ruleSize) {
		for(j=0,k=i,dist=0;j<elems.size()-1 && dist==0;k+=elems[j++]->size()) {
			if(!inst[j]->isUndefined() && att[j]->getSize()>0) {
				dist+=(*elems[j])(&genome[k],*inst[j])/att[j]->getSize();
			}
		}
	}
	if(j==elems.size()-1 && dist==0) {
		i-=ruleSize;
		if(used.find(i)==used.end()) {
			used[i]=1;
			rused++;
		} else {
			used[i]++;
		}
		if((*elems.back())(&genome[k],*inst.back())==0) {
			return 0;
		} else {
			error++;
			return 1;
		}
	}
	noclass++;
	return 1;
}

double RuleModel::test(Individual& indiv,Instance& inst) {
	return eval(indiv,inst);
}

double RuleModel::spread(Individual& indiv,size_t i) {
	size_t j,k;
	double value;
	for(j=0,k=i,value=1;j<elems.size()-1;k+=elems[j++]->size()) {
		if(att[j]->getSize()>0) {
			value*=elems[j]->spread(&indiv.getGenome()[k])/att[j]->getSize();
		}
	}
	return value;
}

void RuleModel::prune(Individual& indiv) {
	if(rused>1 && rused<indiv.size()/ruleSize) {
		size_t i,j;
		Genome *gen=new Genome;
		hash_map<size_t,size_t>* util=new hash_map<size_t,size_t>;
		for(i=0;i<indiv.size();i+=ruleSize) {
			if(used.find(i)==used.end()) {
				for(j=0;j<ruleSize;j++) {
					delete indiv.getGenome()[i+j];
				}
			} else {
				(*util)[gen->size()]=used[i];
				for(j=0;j<ruleSize;j++) {
					gen->add(indiv.getGenome()[i+j]);
				}
			}
		}
		indiv.getGenome().clear();
		gen->swap(indiv.getGenome());
		delete gen;
		used.clear();
		util->swap(used);
		delete util;
	}
}

double RuleModel::eval(Individual& indiv) {
	error=0;
	rused=0;
	noclass=0;
	used.clear();
	return Model::eval(indiv);
}

double RuleModel::test(Individual& indiv) {
	error=0;
	rused=0;
	noclass=0;
	used.clear();
	return Model::test(indiv);
}
