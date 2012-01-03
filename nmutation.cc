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
#include <mocs/nmutation.h>

extern "C" Loadable* NormalMutation_newInstance(Params& p) {
	return new NormalMutation(p);
}

NormalMutation::NormalMutation(Params& p) : UniformMutation(p) {
	epsilon=p.getDouble("epsilon",1e-10);
}

NormalMutation::~NormalMutation() {
}

void NormalMutation::operator () (Individual& indiv) {
	Gene* gene;
	double n,ni,dev,tau,tau2;
	n=Rand::nextGaussian();
	tau=1.0/sqrt(2.0*sqrt((double)indiv.size()));
	tau2=1.0/sqrt(2.0*indiv.size());
	for(size_t i=0;i<indiv.size();i++) {
		gene=indiv.getGenome()[i];
		ni=Rand::nextGaussian();
		dev=gene->getDev()*exp(tau2*n+tau*ni);
		if(dev<epsilon) {
			dev=epsilon;
		}
		gene->setDev(dev);
		if(Rand::nextDouble()<dev) {
			gene->step(dev*Rand::nextGaussian());
		}
	}
}
