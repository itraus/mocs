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
#include <mocs/model.h>

Model::Model(Params& p) : Loadable(p) {
}

Model::~Model() {
	delete loader;
}

Instances& Model::getInstances() {
	return inst;
}

Attributes& Model::getAttributes() {
	return att;
}

void Model::init(const char* file) {
	loader=(InstanceLoader*)p.get("loader");
	loader->load(file);
	inst=loader->getInstances();
	att=loader->getAttributes();
}

double Model::eval(Individual& indiv) {
	double error=0;
	for(size_t i=0;i<inst.size();i++) {
		error+=eval(indiv,inst[i]);
	}
	if(Rand::nextDouble()<p.getDouble("pruneProb",0.1)) {
		prune(indiv);
	}
	return error/inst.size();
}

double Model::test(Individual& indiv) {
	double error=0;
	for(size_t i=0;i<inst.size();i++) {
		error+=test(indiv,inst[i]);
	}
	return error/inst.size();
}
