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

#include <string>

#ifndef STATIC
#include <dlfcn.h>
#endif

#include <mocs/loader.h>

Loadable* Loader::newInstance(const char* name,Params& p) {
#ifdef STATIC
	return newInstanceStatic(name,p);
#else
	return newInstanceDynamic(name,p);
#endif
}

#ifdef STATIC

extern "C" {
	Loadable* AccuracyFitness_newInstance(Params& p);
	Loadable* AccuracySizeCoveringFitness_newInstance(Params& p);
	Loadable* AccuracySizeFitness_newInstance(Params& p);
	Loadable* AccuracySizeGeneralityFitness_newInstance(Params& p);
	Loadable* AdaptiveMutation_newInstance(Params& p);
	Loadable* Arff_newInstance(Params& p);
	Loadable* BestAccuracy_newInstance(Params& p);
	Loadable* BestCompromise_newInstance(Params& p);
	Loadable* ClassifierFitnessFunction_newInstance(Params& p);
	Loadable* FitnessProportionateMating_newInstance(Params& p);
	Loadable* Init_newInstance(Params& p);
	Loadable* InstanceInit_newInstance(Params& p);
	Loadable* InstanceModel_newInstance(Params& p);
	Loadable* KUR_newInstance(Params& p);
	Loadable* MOES_newInstance(Params& p);
	Loadable* MOGA_newInstance(Params& p);
	Loadable* NGGA_newInstance(Params& p);
	Loadable* NSGAII_newInstance(Params& p);
	Loadable* NearestNeighbourMating_newInstance(Params& p);
	Loadable* NonUniformCrossover_newInstance(Params& p);
	Loadable* NormalMutation_newInstance(Params& p);
	Loadable* OKK_newInstance(Params& p);
	Loadable* OKKInit_newInstance(Params& p);
	Loadable* PolynomialMutation_newInstance(Params& p);
	Loadable* RandomMating_newInstance(Params& p);
	Loadable* RegressionRuleModel_newInstance(Params& p);
	Loadable* RuleInit_newInstance(Params& p);
	Loadable* RuleModel_newInstance(Params& p);
	Loadable* MixedModel_newInstance(Params& p);
	Loadable* SF2_newInstance(Params& p);
	Loadable* SPEA2_newInstance(Params& p);
	Loadable* SimulatedBinaryCrossover_newInstance(Params& p);
	Loadable* TournamentMating_newInstance(Params& p);
	Loadable* TournamentSelection_newInstance(Params& p);
	Loadable* UniformCrossover_newInstance(Params& p);
	Loadable* UniformMutation_newInstance(Params& p);
	Loadable* ZDT6_newInstance(Params& p);
}

struct {
	char* name;
	Loadable* (*func)(Params&);
} funcsLoader[]={
	{"AccuracyFitness",AccuracyFitness_newInstance},
	{"AccuracySizeCoveringFitness",AccuracySizeCoveringFitness_newInstance},
	{"AccuracySizeFitness",AccuracySizeFitness_newInstance},
	{"AccuracySizeGeneralityFitness",AccuracySizeGeneralityFitness_newInstance},
	{"AdaptiveMutation",AdaptiveMutation_newInstance},
	{"Arff",Arff_newInstance},
	{"BestAccuracy",BestAccuracy_newInstance},
	{"BestCompromise",BestCompromise_newInstance},
	{"ClassifierFitnessFunction",ClassifierFitnessFunction_newInstance},
	{"FitnessProportionateMating",FitnessProportionateMating_newInstance},
	{"Init",Init_newInstance},
	{"InstanceInit",InstanceInit_newInstance},
	{"InstanceModel",InstanceModel_newInstance},
	{"KUR",KUR_newInstance},
	{"MOES",MOES_newInstance},
	{"MOGA",MOGA_newInstance},
	{"NGGA",NGGA_newInstance},
	{"NSGAII",NSGAII_newInstance},
	{"NearestNeighbourMating",NearestNeighbourMating_newInstance},
	{"NonUniformCrossover",NonUniformCrossover_newInstance},
	{"NormalMutation",NormalMutation_newInstance},
	{"OKK",OKK_newInstance},
	{"OKKInit",OKKInit_newInstance},
	{"PolynomialMutation",PolynomialMutation_newInstance},
	{"RandomMating",RandomMating_newInstance},
	{"RegressionRuleModel",RegressionRuleModel_newInstance},
	{"RuleInit",RuleInit_newInstance},
	{"RuleModel",RuleModel_newInstance},
	{"MixedModel",MixedModel_newInstance},
	{"SF2",SF2_newInstance},
	{"SPEA2",SPEA2_newInstance},
	{"SimulatedBinaryCrossover",SimulatedBinaryCrossover_newInstance},
	{"TournamentMating",TournamentMating_newInstance},
	{"TournamentSelection",TournamentSelection_newInstance},
	{"UniformCrossover",UniformCrossover_newInstance},
	{"UniformMutation",UniformMutation_newInstance},
	{"ZDT6",ZDT6_newInstance},
	{0,0}
};

Loadable* Loader::newInstanceStatic(const char* name,Params& p) {
	size_t i;
	for(i=0;funcsLoader[i].name && strcmp(funcsLoader[i].name,name)!=0;i++);
	assert(funcsLoader[i].name);
	return (*funcsLoader[i].func)(p);
}

#else

Loadable* Loader::newInstanceDynamic(const char* name,Params& p) {
	char* str;
	void* handler;
	string file,sym;
	Loadable* (*func)(Params&);
	str=strstr(name,":");
	if((str=strstr(name,":"))) {
		sym.assign(str+1);
		file.assign(name,str-name);
		handler=dlopen(file.c_str(),RTLD_NOW|RTLD_GLOBAL);
		if(!handler) {
			cerr << dlerror() << endl;
			assert(handler);
		}
		sym+="_newInstance";
		func=(Loadable* (*)(Params&))dlsym(handler,sym.c_str());
	} else {
		sym.assign(name);
		handler=dlopen(0,RTLD_NOW|RTLD_GLOBAL);
		if(!handler) {
			cerr << dlerror() << endl;
			assert(handler);
		}
		sym+="_newInstance";
		func=(Loadable* (*)(Params&))dlsym(handler,sym.c_str());
	}
	if(!func) {
		cerr << dlerror() << endl;
		assert(func);
	}
	return (*func)(p);
}

#endif
