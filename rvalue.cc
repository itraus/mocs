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

#include <mocs/rvalue.h>

RealValue::RealValue() {
}

RealValue::RealValue(double value) : value(value) {
}

RealValue::~RealValue() {
}

double RealValue::getValue() {
	return value;
}

void RealValue::setValue(double value) {
	this->value=value;
}

Value* RealValue::newValue() const {
	Value* val=new RealValue(value);
	val->setUndefined(isUndefined());
	return val;
}
