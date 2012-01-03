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
#include <mocs/iinit.h>
#include <mocs/intgene.h>
#include <mocs/realgene.h>
#include <mocs/instances.h>
#include <mocs/attributes.h>
#include <mocs/iattribute.h>
#include <mocs/rattribute.h>

extern "C" Loadable* InstanceInit_newInstance(Params& p) {
	return new InstanceInit(p);
}

InstanceInit::InstanceInit(Params& p) : Initiator(p) {
}

InstanceInit::~InstanceInit() {
}

Individual* InstanceInit::newIndividual() const {
	IntGene* igene;
	RealGene* rgene;
	RealAttribute* real;
	IntAttribute* integer;
	Individual& indiv=*new Individual;
	Attributes& att=*(Attributes*)p.get("attributes");
	size_t initInstances=p.getInt("initRules",15);
	double mutGenProb=p.getDouble("mutGenProb",1.0/p.getInt("crossAlign",1));
	for(size_t i=0;i<initInstances;i++) {
		for(size_t j=0;j<att.size();j++) {
			if((real=dynamic_cast<RealAttribute*>(att[j]))) {
				rgene=new RealGene(real->getMin(),real->getMax());
				indiv.getGenome().add(rgene);
				rgene->setDev(mutGenProb);
				rgene->init();
			} else if((integer=dynamic_cast<IntAttribute*>(att[j]))) {
				igene=new IntGene(integer->getMin(),integer->getMax());
				indiv.getGenome().add(igene);
				igene->setDev(mutGenProb);
				igene->init();
			}
		}
	}
	indiv.getGenome().setDev(mutGenProb);
	indiv.setValue(HUGE);
	return &indiv;
}
