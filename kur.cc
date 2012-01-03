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

class KUR : public FitnessFunction {
		size_t numObjs,numVars;

	public:
		KUR(Params& p);
		virtual ~KUR();

		virtual void operator () (Individual& indiv);
};

KUR::KUR(Params& p) : FitnessFunction(p) {
	numObjs=p.getInt("numObjs",2);
	numVars=p.getInt("numVars",3);
}

KUR::~KUR() {
}

void KUR::operator () (Individual& indiv) {
	double f,x,xx;
	indiv.getFitness().resize(numObjs);
	f=0;
	x=((RealGene*)indiv.getGenome()[0])->getValue();
	for(size_t i=0;i<numVars-1;i++) {
		xx=((RealGene*)indiv.getGenome()[i+1])->getValue();
		f+=-10*exp(-0.2*sqrt(x*x+xx*xx));
		x=xx;
	}
	indiv.getFitness()[0]=f;
	f=0;
	for(size_t i=0;i<numVars;i++) {
		x=((RealGene*)indiv.getGenome()[i])->getValue();
		f+=pow(fabs(x),0.8)+5*pow(sin(x),3);
	}
	indiv.getFitness()[1]=f;
}

extern "C" Loadable* KUR_newInstance(Params& p) {
	return new KUR(p);
}
