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

#include <mocs/rattribute.h>

RealAttribute::RealAttribute() : min(0), max(1) {
}

RealAttribute::RealAttribute(double min,double max) : min(min), max(max) {
	size=max-min;
}

RealAttribute::~RealAttribute() {
}

double RealAttribute::getMin() const {
	return min;
}

void RealAttribute::setMin(double min) {
	this->min=min;
	size=max-min;
}

double RealAttribute::getMax() const {
	return max;
}

void RealAttribute::setMax(double max) {
	this->max=max;
	size=max-min;
}

void RealAttribute::adjust(double value) {
	if(value<min) {
		min=value;
		size=max-min;
	} else if(value>max) {
		max=value;
		size=max-min;
	}
}

void RealAttribute::adjust(Attribute& att) {
	RealAttribute* r=(RealAttribute*)&att;
	adjust(r->getMin());
	adjust(r->getMax());
	r->adjust(min);
	r->adjust(max);
}
