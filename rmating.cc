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

#include <mocs/rand.h>
#include <mocs/rmating.h>

extern "C" Loadable* RandomMating_newInstance(Params& p) {
	return new RandomMating(p);
}

RandomMating::RandomMating(Params& p) : MatingSelection(p) {
}

RandomMating::~RandomMating() {
}

void RandomMating::operator () (Population& pop,size_t& a,size_t& b) {
	if(a==~0u) {
		a=Rand::nextInt(pop.size());
	}
	if(pop.size()>1) {
		while((b=Rand::nextInt(pop.size()))==a);
	} else {
		b=a;
	}
}
