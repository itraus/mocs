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
#include <mocs/intgene.h>

IntGene::IntGene() {
	dev=0.1;
}

IntGene::IntGene(int min,int max) {
	this->dev=0.1;
	this->min=min;
	this->max=max;
}

IntGene::IntGene(const IntGene& gene) {
	this->dev=gene.dev;
	this->min=gene.min;
	this->max=gene.max;
	this->value=gene.value;
}

IntGene::~IntGene() {
}

int IntGene::getValue() const {
	return value;
}

void IntGene::setValue(int value) {
	if(value>max) {
		value=max;
	} else if(value<min) {
		value=min;
	} else {
		this->value=value;
	}
}

int IntGene::getMin() const {
	return min;
}

void IntGene::setMin(int min) {
	this->min=min;
}

int IntGene::getMax() const {
	return max;
}

void IntGene::setMax(int max) {
	this->max=max;
}

IntGene& IntGene::operator = (const IntGene& gene) {
	this->dev=gene.dev;
	this->min=gene.min;
	this->max=gene.max;
	this->value=gene.value;
	return *this;
}

Gene* IntGene::newGene() const {
	return new IntGene(*this);
}

void IntGene::init() {
	value=min+Rand::nextInt(max-min+1);
}

void IntGene::mutate() {
	if(Rand::nextDouble()<dev) {
		init();
	}
}

void IntGene::step(double x) {
	mutate();
}

double IntGene::getDev() const {
	return dev;
}

void IntGene::setDev(double dev) {
	this->dev=dev;
}

Gene& IntGene::operator = (const Gene& gene) {
	*this=*(const IntGene*)&gene;
	return *(Gene*)this;
}

ostream& IntGene::operator >> (ostream& os) {
	return os << value;
}
