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
#include <mocs/asgfitness.h>

#define ACCURACY	0
#define GENERALITY	1
#define NONE		2
#define SIZE		3

extern "C" Loadable* AccuracySizeGeneralityFitness_newInstance(Params& p) {
	return new AccuracySizeGeneralityFitness(p);
}

AccuracySizeGeneralityFitness::AccuracySizeGeneralityFitness(Params& p) : FitnessFunction(p) {
}

AccuracySizeGeneralityFitness::~AccuracySizeGeneralityFitness() {
}

void AccuracySizeGeneralityFitness::operator () (Individual& indiv) {
	Model& model=*(Model*)p.get("model");
	indiv.getFitness().resize(4);
	indiv.getFitness()[ACCURACY]=model.eval(indiv);
	indiv.getFitness()[GENERALITY]=model.generality(indiv);
	indiv.getFitness()[SIZE]=model.size(indiv);
	if(indiv.getFitness()[SIZE]>1) {
		indiv.getFitness()[SIZE]=1;
		indiv.getFitness()[ACCURACY]=1;
		indiv.getFitness()[GENERALITY]=1;
	}
	indiv.getFitness()[NONE]=1;
}
