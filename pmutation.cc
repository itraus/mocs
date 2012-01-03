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
#include <mocs/pmutation.h>

extern "C" Loadable* PolynomialMutation_newInstance(Params& p) {
	return new PolynomialMutation(p);
}

PolynomialMutation::PolynomialMutation(Params& p) : UniformMutation(p) {
	etam=p.getDouble("etam",15);
}

PolynomialMutation::~PolynomialMutation() {
}

void PolynomialMutation::operator () (Individual& indiv) {
	double u;
	for(size_t i=0;i<indiv.size();i++) {
		if(Rand::nextDouble()<indiv.getGenome().getDev()) {
			indiv.getGenome()[i]->setDev(1);
			u=Rand::nextDouble();
			if(u<0.5) {
				indiv.getGenome()[i]->step(pow(2*u,1/(etam+1))-1);
			} else {
				indiv.getGenome()[i]->step(1-pow(2*(1-u),1/(etam+1)));
			}
		}
	}
}
