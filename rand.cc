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
#include <cstdlib>
#include <climits>

#include <mocs/rand.h>

#ifdef USE_STDLIB_RANDOM

double Rand::gaussian=0;
int Rand::haveGaussian=0;

void Rand::init() {
	setSeed(0);
}

void Rand::setSeed(int seed) {
	srand(seed);
}

int Rand::nextInt() {
	return rand();
}

int Rand::nextInt(int max) {
	return (int)(max*(double)rand()/(RAND_MAX+1.0));
}

double Rand::nextDouble() {
	return rand()/(RAND_MAX+1.0);
}

double Rand::nextGaussian() {
	if(haveGaussian) {
		haveGaussian=0;
		return gaussian;
	} else {
		double mult,s,v1,v2;
		do {
			v1=2*nextDouble()-1;
			v2=2*nextDouble()-1;
			s=v1*v1+v2*v2;
		} while(s>=1 || s==0);
		mult=sqrt(-2*log(s)/s);
		gaussian=v2*mult;
		haveGaussian=1;
		return v1*mult;
	}
}

#else

double Rand::u[97];
double Rand::c;
double Rand::cd;
double Rand::cm;
int Rand::i97;
int Rand::j97;
bool Rand::test=false;

void Rand::init() {
	setSeed(0);
}

void Rand::setSeed(int seed) {
	double s,t;
	int ii,i,j,k,l,jj,m;
	int ij=seed&0xffff,kl=seed>>16;

	if(ij<=0 || ij>31328 || kl<=0 || kl>30081) {
		ij=1802;
		kl=9373;
	}

	i=(ij/177)%177+2;
	j=(ij%177)+2;
	k=(kl/169)%178+1;
	l=(kl%169);

	for(ii=0;ii<97;ii++) {
		s=0.0;
		t=0.5;
		for(jj=0;jj<24;jj++) {
			m=(((i*j)%179)*k)%179;
			i=j;
			j=k;
			k=m;
			l=(53*l+1)%169;
			if(((l*m%64))>=32) {
				s+=t;
			}
			t*=0.5;
		}
		u[ii]=s;
	}

	c=362436.0/16777216.0;
	cd=7654321.0/16777216.0;
	cm=16777213.0/16777216.0;
	i97=97;
	j97=33;
	test=true;
}

int Rand::nextInt() {
	return nextInt(INT_MAX);
}

int Rand::nextInt(int max) {
	return (int)(nextDouble()*max);
}

double Rand::nextDouble() {
	double uni;

	if(!test) {
		init();
	}

	uni=u[i97-1]-u[j97-1];
	if(uni<=0.0) {
		uni++;
	}
	u[i97-1]=uni;
	i97--;
	if(i97==0) {
		i97=97;
	}
	j97--;
	if(j97==0) {
		j97=97;
	}
	c-=cd;
	if(c<0.0) {
		c+=cm;
	}
	uni-=c;
	if(uni<0.0) {
		uni++;
	}

	return uni;
}

double Rand::nextGaussian() {
	double q,u,v,x,y;

	do {
		u=nextDouble();
		v=nextDouble();

		if(u<=0.0 || v<=0.0) {
		 	u=1.0;
		 	v=1.0;
		}

		v=1.7156*(v-0.5);
		x=u-0.449871;
		y=fabs(v)+0.386595;
		q=x*x+y*(0.19600*y-0.25472*x);

		if(q<0.27597) {
			break;
		}
	 } while(q>0.27846 || v*v>-4.0*log(u)*u*u);

	 return v/u;
}

#endif
