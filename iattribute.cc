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

#include <mocs/iattribute.h>

IntAttribute::IntAttribute() : min(0), max(1) {
}

IntAttribute::IntAttribute(int min,int max) : min(min), max(max) {
	size=max-min+1;
}

IntAttribute::~IntAttribute() {
}

int IntAttribute::getMin() const {
	return min;
}

void IntAttribute::setMin(int min) {
	this->min=min;
	size=max-min+1;
}

int IntAttribute::getMax() const {
	return max;
}

void IntAttribute::setMax(int max) {
	this->max=max;
	size=max-min+1;
}

void IntAttribute::adjust(int value) {
	if(value<min) {
		min=value;
		size=max-min+1;
	} else if(value>max) {
		max=value;
		size=max-min+1;
	}
}

void IntAttribute::adjust(Attribute& att) {
	IntAttribute* i=(IntAttribute*)&att;
	adjust(i->getMin());
	adjust(i->getMax());
	i->adjust(min);
	i->adjust(max);
}
