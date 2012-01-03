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

#include <mocs/rand.h>
#include <mocs/amutation.h>

extern "C" Loadable* AdaptiveMutation_newInstance(Params& p) {
	return new AdaptiveMutation(p);
}

AdaptiveMutation::AdaptiveMutation(Params& p) : PolynomialMutation(p) {
	epsilon=p.getDouble("epsilon",1e-10);
}

AdaptiveMutation::~AdaptiveMutation() {
}

void AdaptiveMutation::operator () (Individual& indiv) {
	double mutGenProb=indiv.getGenome().getDev();
	if(mutGenProb<epsilon) {
		mutGenProb=epsilon;
	}
	indiv.getGenome().setDev(mutGenProb*exp(Rand::nextGaussian()/sqrt((double)indiv.size())));
	PolynomialMutation::operator()(indiv);
}
