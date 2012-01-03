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

#include <math.h>
#include <mocs/rvalue.h>
#include <mocs/rrmodel.h>
#include <mocs/realgene.h>

extern "C" Loadable* RegressionRuleModel_newInstance(Params& p) {
	return new RegressionRuleModel(p);
}

RegressionRuleModel::RegressionRuleModel(Params& p) : RuleModel(p) {
}

RegressionRuleModel::~RegressionRuleModel() {
}

double RegressionRuleModel::size(const Individual& indiv) {
	/*size_t k=p.getInt("kNN",2);
	return max(k+1,indiv.size()/ruleSize)/(double)inst.size();*/
	return (indiv.size()/ruleSize)/(double)inst.size();
}

double RegressionRuleModel::test(Individual& indiv,Instance& inst) {
	//return (eval(indiv,inst)<0.08) ? 0 : 1;
	return eval(indiv,inst);
}

double RegressionRuleModel::eval(Individual& indiv,Instance& inst) {
	size_t i,j,k,num;
	vector<pair<size_t,double> > all;
	vector<pair<size_t,double> > closer;
	double dist,value,total,c;
	Genome& genome=indiv.getGenome();

	for(i=0;i<indiv.size();i+=ruleSize) {
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

		value=sqrt(elems.size()-1.0)-dist;
		all.push_back(pair<size_t,double>(k,value));
	}

	num=p.getInt("kNN",2);

	for(i=0,total=0;i<num && all.size()>0;i++) {
		for(j=1,k=0;j<all.size();j++) {
			if(all[j].second>all[k].second) {
				k=j;
			}
		}

		swap(all[k],all.back());
		closer.push_back(all.back());
		total+=closer.back().second;
		all.pop_back();
	}

	c=p.getDouble("c",elems.size()-1);

	for(i=0;i<closer.size();i++) {
		closer[i].second=exp(c*closer[i].second/total);
	}

	for(i=0,total=0;i<closer.size();i++) {
		total+=closer[i].second;
	}

	if(total==0) {
		total=closer.size();

		for(i=0;i<closer.size();i++) {
			closer[i].second=1;
		}
	}

	for(i=0,value=0;i<closer.size();i++) {
		value+=((RealGene*)genome[closer[i].first])->getValue()*closer[i].second/total;
	}

	return pow(value-((RealValue*)inst.back())->getValue(),2);
}
