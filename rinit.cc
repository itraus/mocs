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

#include <mocs/rand.h>
#include <mocs/rinit.h>
#include <mocs/intgene.h>
#include <mocs/realgene.h>
#include <mocs/instances.h>
#include <mocs/attributes.h>
#include <mocs/iattribute.h>
#include <mocs/rattribute.h>

extern "C" Loadable* RuleInit_newInstance(Params& p) {
	return new RuleInit(p);
}

RuleInit::RuleInit(Params& p) : Initiator(p) {
}

RuleInit::~RuleInit() {
}

Individual* RuleInit::newIndividual() const {
	double x;
	IntGene* igene;
	RealGene* rgene1;
	RealGene* rgene2;
	RealAttribute* real;
	IntAttribute* integer;
	Individual& indiv=*new Individual;
	Attributes& att=*(Attributes*)p.get("attributes");
	double initGenProb=p.getDouble("initGenProb",0.75);
	double genProb=p.getDouble("genProb",0.5);
	size_t initRules=p.getInt("initRules",15);
	double mutGenProb=p.getDouble("mutGenProb",1.0/p.getInt("crossAlign",1));
	for(size_t i=0;i<initRules;i++) {
		for(size_t j=0;j<att.size();j++) {
			if((real=dynamic_cast<RealAttribute*>(att[j])) && j==att.size()-1) {
				rgene1=new RealGene(real->getMin(),real->getMax());
				rgene1->setValue(Rand::nextDouble()*(real->getMax()-real->getMin())+real->getMin());
				rgene1->setDev(mutGenProb);
				indiv.getGenome().add(rgene1);
			} else if((real=dynamic_cast<RealAttribute*>(att[j]))) {
				rgene1=new RealGene(real->getMin(),real->getMax());
				rgene2=new RealGene(real->getMin(),real->getMax());
				if(Rand::nextDouble()<initGenProb) {
					rgene1->setValue(real->getMin());
					rgene2->setValue(real->getMax());
				} else {
					x=Rand::nextDouble();
					rgene1->setValue(real->getMin()+(1-x)*Rand::nextDouble()*(real->getMax()-real->getMin()));
					rgene2->setValue(rgene1->getValue()+x*(real->getMax()-real->getMin()));
				}
				rgene1->setDev(mutGenProb);
				rgene2->setDev(mutGenProb);
				indiv.getGenome().add(rgene1);
				indiv.getGenome().add(rgene2);
			} else if((integer=dynamic_cast<IntAttribute*>(att[j]))) {
				if(j==att.size()-1) {
					igene=new IntGene(integer->getMin(),integer->getMax());
					igene->init();
				} else {
					igene=new IntGene((int)(integer->getMin()-genProb*(integer->getMax()-integer->getMin()+1)/(1-genProb)),integer->getMax());
					if(Rand::nextDouble()<initGenProb) {
						igene->setValue(integer->getMin()-1);
					} else {
						igene->setValue(Rand::nextInt(integer->getMax()-integer->getMin()+1)+integer->getMin());
					}
				}
				igene->setDev(mutGenProb);
				indiv.getGenome().add(igene);
			}
		}
	}
	indiv.getGenome().setDev(mutGenProb);
	indiv.setValue(HUGE);
	return &indiv;
}
