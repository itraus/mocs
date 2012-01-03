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

#include <mocs/attributes.h>

Attributes::Attributes() {
}

Attributes::Attributes(size_t size) : vector<Attribute*>(size) {
}

Attributes::Attributes(const Attributes& att) : vector<Attribute*>(att) {
}

Attributes::~Attributes() {
}

void Attributes::add(Attribute* att) {
	push_back(att);
}

void Attributes::adjust(Attributes& att) {
	for(size_t i=0;i<size();i++) {
		(*this)[i]->adjust(*att[i]);
	}
}
