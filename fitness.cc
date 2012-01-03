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

#include <mocs/fitness.h>

Fitness::Fitness() {
}

Fitness::Fitness(size_t size) : vector<double>(size) {
}

Fitness::Fitness(const Fitness& fitness) : vector<double>(fitness) {
}

Fitness::~Fitness() {
}

void Fitness::add(double value) {
	push_back(value);
}

int Fitness::operator < (const Fitness& fitness) const {
	size_t i;
	int less=false;
	for(i=0;i<size() && (*this)[i]<=fitness[i];i++) {
		less|=(*this)[i]<fitness[i];
	}
	return i==size() && less;
}

int Fitness::operator == (const Fitness& fitness) const {
	size_t i;
	for(i=0;i<size() && (*this)[i]==fitness[i];i++);
	return i==size();
}

double Fitness::operator - (const Fitness& fitness) const {
	double dist=0;
	for(size_t i=0;i<size();i++) {
		dist+=pow((*this)[i]-fitness[i],2);
	}
	return sqrt(dist);
}

Fitness::operator double () const {
	double dist=0;
	for(size_t i=0;i<size();i++) {
		dist+=(*this)[i]*(*this)[i];
	}
	return sqrt(dist);
}

ostream& operator << (ostream& os,const Fitness& fitness) {
	size_t i;
	for(i=0;i<fitness.size()-1;i++) {
		os << fitness[i] << " ";
	}
	return os << fitness[i];
}
