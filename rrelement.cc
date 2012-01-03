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

#include <mocs/rvalue.h>
#include <mocs/realgene.h>
#include <mocs/rrelement.h>

RealRuleElement::RealRuleElement(RealAttribute* att) : att(att) {
}

RealRuleElement::~RealRuleElement() {
}

size_t RealRuleElement::size() const {
	return 2;
}

double RealRuleElement::operator () (Gene** gene,Value& value) {
	double inf=((RealGene*)gene[0])->getValue();
	double sup=((RealGene*)gene[1])->getValue();
	double rvalue=((RealValue*)&value)->getValue();
	return ((rvalue>=inf && rvalue<=sup) || (rvalue>=sup && rvalue<=inf)) ? 0 : min(fabs(rvalue-inf),fabs(rvalue-sup));
}

double RealRuleElement::spread(Gene** gene) {
	return fabs(((RealGene*)gene[0])->getValue()-((RealGene*)gene[1])->getValue());
}
