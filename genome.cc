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

#include <mocs/genome.h>

Genome::Genome() : vector<Gene*>() {
	dev=0.1;
}

Genome::Genome(size_t size) : vector<Gene*>(size) {
	dev=0.1;
}

Genome::Genome(const Genome& genome) : vector<Gene*>(genome.size()) {
	dev=genome.dev;
	for(size_t i=0;i<genome.size();i++) {
		(*this)[i]=genome[i]->newGene();
	}
}

Genome::~Genome() {
	for(size_t i=0;i<size();i++) {
		delete (*this)[i];
	}
}

void Genome::init() {
	for(size_t i=0;i<size();i++) {
		(*this)[i]->init();
	}
}

void Genome::add(Gene* gene) {
	push_back(gene);
}

ostream& operator << (ostream& os,const Genome& genome) {
	size_t i;
	os << "[" << genome.getDev() << "] ";
	for(i=0;i<genome.size()-1;i++) {
		*genome[i] >> os << " ";
	}
	return *genome[i] >> os;
}

double Genome::getDev() const {
	return dev;
}

void Genome::setDev(double dev) {
	this->dev=dev;
}
