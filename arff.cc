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
#include <string>
#include <cstdio>
#include <cstdlib>

#include <mocs/arff.h>
#include <mocs/ivalue.h>
#include <mocs/rvalue.h>
#include <mocs/iattribute.h>
#include <mocs/rattribute.h>

extern FILE* arff_in;

int arff_parse(void*);

extern "C" Loadable* Arff_newInstance(Params& p) {
	return new Arff(p);
}

Arff::Arff(Params& p) : InstanceLoader(p) {
}

Arff::~Arff() {
}

void Arff::load(const char* file) {
	att=0;
	nominals.clear();
	instances.clear();
	attributes.clear();
	arff_in=fopen(file,"r");
	assert(arff_in!=false);
	arff_parse((void*)this);
	fclose(arff_in);
}

void Arff::addNominal() {
	num=0;
	nominals.resize(att+1);
}

void Arff::addNominalValue(const char* value) {
	nominals.back().push_back(string(value));
}

void Arff::endNominal() {
	attributes.add(new IntAttribute(0,nominals.back().size()-1));
	att++;
}

void Arff::addInteger(const char* inf,const char* sup) {
	attributes.add(new RealAttribute(atof(inf),atof(sup)));
	att++;
}

void Arff::addReal() {
	attributes.add(new RealAttribute(HUGE,-HUGE));
	att++;
}

void Arff::addInstance() {
	num=0;
	instances.add(Instance());
}

void Arff::addValue(const char* value) {
	if(dynamic_cast<RealAttribute*>(attributes[num])) {
		instances.back().push_back(new RealValue(atof(value)));
		if(value[0]!='?') {
			((RealAttribute*)(attributes[num]))->adjust(atof(value));
		}
	} else if(dynamic_cast<IntAttribute*>(attributes[num])) {
		if(nominals[num].size()>0) {
			size_t i;
			for(i=0;i<nominals[num].size() && strcasecmp(nominals[num][i].c_str(),value);i++);
			assert(i<nominals[num].size() || value[0]=='?');
			instances.back().push_back(new IntValue(i));
		} else {
			instances.back().push_back(new IntValue(atoi(value)));
		}
	}
	if(value[0]=='?') {
		instances.back().back()->setUndefined(true);
	}
	num++;
}

void Arff::endInstance() {
}
