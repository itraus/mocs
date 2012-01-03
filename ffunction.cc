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

#include <mocs/ffunction.h>

FitnessFunction::FitnessFunction(Params& p) : Loadable(p) {
}

FitnessFunction::~FitnessFunction() {
}

void FitnessFunction::operator () (Population& pop) {
	for(size_t i=0;i<pop.size();i++) {
		if(pop[i]->getValue()==HUGE) {
			(*this)(*pop[i]);
			pop[i]->setValue(0);
		}
	}
}
