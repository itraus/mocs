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

#include <mocs/individual.h>

Individual::Individual() {
}

Individual::Individual(size_t size) : genome(size) {
}

Individual::Individual(const Individual& indiv) : genome(indiv.genome), fitness(indiv.fitness) {
	value=indiv.value;
}

Individual::~Individual() {
}

size_t Individual::size() const {
	return genome.size();
}

Genome& Individual::getGenome() {
	return genome;
}

const Genome& Individual::getGenome() const {
	return genome;
}

Fitness& Individual::getFitness() {
	return fitness;
}

const Fitness& Individual::getFitness() const {
	return fitness;
}

double Individual::getValue() const {
	return value;
}

void Individual::setValue(double value) {
	this->value=value;
}

int Individual::operator < (const Individual& indiv) const {
	return value<indiv.value;
}

int Individual::operator == (const Individual& indiv) const {
	return value==indiv.value;
}

ostream& operator << (ostream& os,const Individual& indiv) {
	return os << indiv.getValue() << " | " << indiv.getFitness();
}
