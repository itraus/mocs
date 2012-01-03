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
#include <mocs/ffunction.h>

class SF2 : public FitnessFunction {
		size_t numObjs,numVars;

	public:
		SF2(Params& p);
		virtual ~SF2();

		virtual void operator () (Individual& indiv);
};

SF2::SF2(Params& p) : FitnessFunction(p) {
	numObjs=p.getInt("numObjs",2);
	numVars=p.getInt("numVars",1);
}

SF2::~SF2() {
}

void SF2::operator () (Individual& indiv) {
	double x;
	indiv.getFitness().resize(numObjs);
	x=((RealGene*)indiv.getGenome()[0])->getValue();
	indiv.getFitness()[0]=x*x;
	indiv.getFitness()[1]=(x-2)*(x-2);
}

extern "C" Loadable* SF2_newInstance(Params& p) {
	return new SF2(p);
}
