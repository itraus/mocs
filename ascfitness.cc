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

#include <mocs/model.h>
#include <mocs/ascfitness.h>

#define ACCURACY	0
#define COVERING	1
#define ACCURACY_R	2
#define SIZE		3

extern "C" Loadable* AccuracySizeCoveringFitness_newInstance(Params& p) {
	return new AccuracySizeCoveringFitness(p);
}

AccuracySizeCoveringFitness::AccuracySizeCoveringFitness(Params& p) : FitnessFunction(p) {
}

AccuracySizeCoveringFitness::~AccuracySizeCoveringFitness() {
}

void AccuracySizeCoveringFitness::operator () (Individual& indiv) {
	Model& model=*(Model*)p.get("model");
	indiv.getFitness().resize(4);
	indiv.getFitness()[ACCURACY]=model.eval(indiv);
	indiv.getFitness()[ACCURACY]=1;
	indiv.getFitness()[ACCURACY_R]=model.wrong(indiv);
	indiv.getFitness()[COVERING]=model.unknown(indiv);
	indiv.getFitness()[SIZE]=model.size(indiv);
	if(indiv.getFitness()[SIZE]>1) {
		indiv.getFitness()[SIZE]=1;
		indiv.getFitness()[COVERING]=1;
		indiv.getFitness()[ACCURACY]=1;
		indiv.getFitness()[ACCURACY_R]=1;
	}
}
