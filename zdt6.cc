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
#include <mocs/realgene.h>
#include <mocs/ffunction.h>

class ZDT6 : public FitnessFunction {
		size_t numObjs,numVars;

	public:
		ZDT6(Params& p);
		virtual ~ZDT6();

		virtual void operator () (Individual& indiv);
};

ZDT6::ZDT6(Params& p) : FitnessFunction(p) {
	numVars=p.getInt("numVars",10);
	numObjs=2;
}

ZDT6::~ZDT6() {
}

void ZDT6::operator () (Individual& indiv) {
	double x,g=0;
	indiv.getFitness().resize(numObjs);
	for(size_t i=1;i<numVars;i++) {
		g+=((RealGene*)indiv.getGenome()[i])->getValue();
	}
	x=((RealGene*)indiv.getGenome()[0])->getValue();
	indiv.getFitness()[0]=1-exp(-4*x)*pow(sin(6*M_PI*x),6);
	g=1+(numVars-1)*pow(g/(numVars-1),0.25);
	indiv.getFitness()[1]=g*(1-pow(indiv.getFitness()[0]/g,2));
}

extern "C" Loadable* ZDT6_newInstance(Params& p) {
	return new ZDT6(p);
}
