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

#include <mocs/realgene.h>
#include <mocs/initiator.h>

class Init : public Initiator {
		size_t numVars;
		double minValue,maxValue;
	public:
		Init(Params& p);
		virtual ~Init();

		virtual Individual* newIndividual() const;
};

Init::Init(Params& p) : Initiator(p) {
	numVars=p.getInt("numVars",10);
	minValue=p.getDouble("minValue",0);
	maxValue=p.getDouble("maxValue",1);
}

Init::~Init() {
}

Individual* Init::newIndividual() const {
	Individual* indiv=new Individual(numVars);
	for(size_t i=0;i<numVars;i++) {
		indiv->getGenome()[i]=new RealGene(minValue,maxValue);
		indiv->getGenome()[i]->setDev(1.0/numVars);
	}
	indiv->getGenome().init();
	indiv->getGenome().setDev(1.0/numVars);
	indiv->setValue(HUGE);
	return indiv;
}

extern "C" Loadable* Init_newInstance(Params& p) {
	return new Init(p);
}
