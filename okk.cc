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

#include <mocs/realgene.h>
#include <mocs/initiator.h>
#include <mocs/ffunction.h>

#define P    100.0
#define YG   150.0
#define YMIN  50.0
#define YMAX 100.0
#define ZMAX 100.0

#define NUM_PARAM    7
#define NUM_PART  1000

enum PARAMS {A=0,B,C,E,F,L,D};

class OKK : public FitnessFunction {
		void minMaxFunc(double* x,double* minMax,double z1,double z2);
		double func(double* x,double z);
		bool constraint(double* x);

	public:
		OKK(Params& p);
		virtual ~OKK();

		virtual void operator () (Individual& indiv);
};

class OKKInit : public Initiator {
	public:
		OKKInit(Params& p);
		virtual ~OKKInit();

		virtual Individual* newIndividual() const;
};

OKK::OKK(Params& p) : FitnessFunction(p) {
}

OKK::~OKK() {
}

void OKK::minMaxFunc(double* x,double* minMax,double z1,double z2) {
	size_t i;
	double f,z,inc=(z2-z1)/NUM_PART;
	minMax[0]=minMax[1]=func(x,z1);
	for(i=1,z=z1+inc;i<NUM_PART;i++,z+=inc) {
		f=func(x,z);
		minMax[0]=min(minMax[0],f);
		minMax[1]=max(minMax[1],f);
	}
}

double OKK::func(double* x,double z) {
	double alpha,beta,g,phi;
	phi=atan(x[E]/(x[L]-z));
	g=sqrt(pow(x[L]-z,2)+x[E]*x[E]);
	alpha=acos((x[A]*x[A]+g*g-x[B]*x[B])/(2*x[A]*g))+phi;
	beta=acos((x[B]*x[B]+g*g-x[A]*x[A])/(2*x[B]*g))-phi;
	return (P*x[B]*sin(alpha+beta))/(2*x[C]*cos(alpha));
}

bool OKK::constraint(double* x) {
    double beta,g,phi,yz0,yzmax;
    phi=atan(x[E]/x[L]);
    g=sqrt(pow(x[L],2)+x[E]*x[E]);
    beta=acos((x[B]*x[B]+g*g-x[A]*x[A])/(2*x[B]*g))-phi;
	yz0=2*(x[E]+x[F]+x[C]*sin(beta+x[D]));
    phi=atan(x[E]/(x[L]-ZMAX));
    g=sqrt(pow(x[L]-ZMAX,2)+x[E]*x[E]);
    beta=acos((x[B]*x[B]+g*g-x[A]*x[A])/(2*x[B]*g))-phi;
	yzmax=2*(x[E]+x[F]+x[C]*sin(beta+x[D]));
	return (YMIN-yzmax>=0 && yzmax>=0 && yz0-YMAX>=0 && YG-yz0>=0 &&
		pow(x[A]+x[B],2)-x[L]*x[L]-x[E]*x[E]>=0 && x[L]-ZMAX>=0 &&
		pow(x[L]-ZMAX,2)+pow(x[A]-x[E],2)-x[B]*x[B]>=0);
}

void OKK::operator () (Individual& indiv) {
	double minMax[2],x[NUM_PARAM];
	indiv.getFitness().resize(2);
	for(size_t i=0;i<NUM_PARAM;i++) {
		x[i]=((RealGene*)indiv.getGenome()[i])->getValue();
	}
	if(constraint(x)) {
		minMaxFunc(x,minMax,0,ZMAX);
		indiv.getFitness()[0]=minMax[1]-minMax[0];
		indiv.getFitness()[1]=P/min(minMax[0],minMax[1]);
		if(indiv.getFitness()[0]>100 || indiv.getFitness()[1]<0.8) {
			indiv.getFitness()[0]=1000;
			indiv.getFitness()[1]=1000;
		}
	} else {
		indiv.getFitness()[0]=1000;
		indiv.getFitness()[1]=1000;
	}
}

OKKInit::OKKInit(Params& p) : Initiator(p) {
}

OKKInit::~OKKInit() {
}

Individual* OKKInit::newIndividual() const {
	Individual& indiv=*new Individual(NUM_PARAM);
	indiv.getGenome()[A]=new RealGene(10,150);
	indiv.getGenome()[B]=new RealGene(10,150);
	indiv.getGenome()[C]=new RealGene(100,200);
	indiv.getGenome()[E]=new RealGene(0,50);
	indiv.getGenome()[F]=new RealGene(10,150);
	indiv.getGenome()[L]=new RealGene(100,300);
	indiv.getGenome()[D]=new RealGene(1,3.14);
	indiv.getGenome().init();
	indiv.setValue(HUGE);
	return &indiv;
}

extern "C" Loadable* OKK_newInstance(Params& p) {
	return new OKK(p);
}

extern "C" Loadable* OKKInit_newInstance(Params& p) {
	return new OKKInit(p);
}
