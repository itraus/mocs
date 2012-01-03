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

#include <mocs/mocs.h>

MOCS::MOCS(const char* file) : MOEA(file) {
}

MOCS::MOCS(char** files,size_t num) : MOEA(files,num) {
}

MOCS::~MOCS() {
	delete model;
}

void MOCS::output(size_t i,Population& pop) {
	Individual* indiv=&dmaker->choose(pop);
	cout << "# i " << i <<  " | ";
	cout << indiv->getFitness() << " | " << 100*(1-test->test(*indiv)) << " ";
	cout << model->getInstances().size()*model->size(*indiv) << " ";
	model->test(*indiv);
	cout << model->generality(*indiv) << endl;
	for(size_t i=0;i<pop.size();i++) {
		cout << i << " | " << *pop[i] << " | ";
		cout << pop[i]->getGenome().getDev() << " | ";
		cout << 100*(1-pop[i]->getFitness()[0]) << " ";
		cout << model->getInstances().size()*model->size(*pop[i]) << endl;
	}
}

void MOCS::final(Population& pop) {
	double t;
	Individual* indiv;
	for(size_t i=0;i<pop.size();i++) {
		pop[i]->getFitness()[0]=model->test(*pop[i]);
		//model->prune(*pop[i]);
		pop[i]->getFitness().back()=model->size(*pop[i]);
	}
	indiv=&dmaker->choose(pop);
	t=100*(1-indiv->getFitness()[0]);
	cout << "# t " << 100*(1-test->test(*indiv)) << " ";
	cout << model->getInstances().size()*model->size(*indiv) << endl;
	cout << "# T " << t << endl;
	cout << "# f" << endl;
	for(size_t i=0;i<pop.size();i++) {
		cout << i << " | " << *pop[i] << " | " << pop[i]->getGenome() << " | ";
		cout << 100*(1-pop[i]->getFitness()[0]) << " ";
		cout << 100*(1-test->test(*pop[i])) << " ";
		cout << model->getInstances().size()*model->size(*pop[i]) << endl;
	}
}

void MOCS::init(const char* itrain,const char* itest) {
	dmaker=(DecisionMaker*)p.get("decisionMaker");
	model=(Model*)p.get("model");
	model->init(itrain);
	test=(Model*)p.get("test");
	test->init(itest);
	model->getAttributes().adjust(test->getAttributes());
	p.put("instances",(void*)&model->getInstances());
	p.put("attributes",(void*)&model->getAttributes());
	MOEA::init();
}
