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
#include <mocs/realgene.h>

RealGene::RealGene() {
	dev=0.1;
}

RealGene::RealGene(double min,double max) {
	this->dev=0.1;
	this->min=min;
	this->max=max;
}

RealGene::RealGene(const RealGene& gene) {
	this->dev=gene.dev;
	this->min=gene.min;
	this->max=gene.max;
	this->value=gene.value;
}

RealGene::~RealGene() {
}

double RealGene::getValue() const {
	return value;
}

void RealGene::setValue(double value) {
	if(value>max) {
		value=max;
	} else if(value<min) {
		value=min;
	} else {
		this->value=value;
	}
}

double RealGene::getMin() const {
	return min;
}

void RealGene::setMin(double min) {
	this->min=min;
}

double RealGene::getMax() const {
	return max;
}

void RealGene::setMax(double max) {
	this->max=max;
}

RealGene& RealGene::operator = (const RealGene& gene) {
	this->dev=gene.dev;
	this->min=gene.min;
	this->max=gene.max;
	this->value=gene.value;
	return *this;
}

Gene* RealGene::newGene() const {
	return new RealGene(*this);
}

void RealGene::init() {
	value=min+(max-min)*Rand::nextDouble();
}

void RealGene::mutate() {
	if(Rand::nextDouble()<=dev) {
		init();
	}
}

void RealGene::step(double x) {
	value+=x*(max-min);
	if(value>max) {
		value=max;
	} else if(value<min) {
		value=min;
	}
}

double RealGene::getDev() const {
	return dev;
}

void RealGene::setDev(double dev) {
	this->dev=dev;
}

Gene& RealGene::operator = (const Gene& gene) {
	*this=*(const RealGene*)&gene;
	return *(Gene*)this;
}

ostream& RealGene::operator >> (ostream& os) {
	return os << value;
}
