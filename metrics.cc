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
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#include <mocs/config.h>
#include <mocs/fitness.h>

#define MAX (8*1024*1024)

struct cmp {
	bool operator () (const Fitness& x,const Fitness& y) const {
		return x[0]<y[0];
	}
};

double sdist(Fitness& w,Fitness& x,Fitness& y) {
	return (w[0]-x[0])*(w[1]-x[1]);
}

void nondom(vector<Fitness>& pop) {
	size_t i,j;
	for(i=0;i<pop.size();) {
		for(j=0;j<i && !(pop[i]==pop[j]);j++);
		if(j<i) {
			swap(pop[i],pop.back());
			pop.pop_back();
		} else {
			for(j=0;j<pop.size() && !(pop[j]<pop[i]);j++);
			if(j<pop.size()) {
				swap(pop[i],pop.back());
				pop.pop_back();
			} else {
				i++;
			}
		}
	}
}

double smetric(vector<Fitness>& pop) {
	double s=0;
	for(size_t i=1;i<pop.size();i++) {
		s+=sdist(pop[i-1],pop[i],pop[0]);
	}
	return s;
}

double ssmetric(vector<Fitness>& pop) {
	double dist=0,ss=0;
	if(pop.size()<2) {
		return 0;
	}
	for(size_t i=1;i<pop.size();i++) {
		dist+=pop[i-1]-pop[i];
	}
	dist/=pop.size()-1;
	for(size_t i=1;i<pop.size();i++) {
		ss+=pow(dist-(pop[i-1]-pop[i]),2);
	}
	return sqrt(ss/(pop.size()-1));
}

int main(int argc,char** argv) {
	char line[MAX];
	Fitness ref(2),p(2);
	vector<Fitness> pop;
	vector<double> s,ss;
	int it=-1,iter=0,n=0;
	ref[0]=1;
	ref[1]=1;
	cin.getline(line,MAX);
	while(!cin.eof()) {
		if(strncmp("# p",line,3)==0) {
			iter=atoi(strstr(line," iterations=")+strlen(" iterations="));
			it=-1;
			if(s.size()==0) {
				s.resize(iter);
				ss.resize(iter);
				for(size_t i=0;i<s.size();i++) {
					s[i]=0;
					ss[i]=0;
				}
			}
		} else if(strncmp("# i",line,3)==0) {
			it++;
			if(it>0) {
				nondom(pop);
				sort(pop.begin(),pop.end(),cmp());
				ss[it-1]+=ssmetric(pop);
				pop.insert(pop.begin(),ref);
				s[it-1]+=smetric(pop);
			}
			pop.clear();
		} else if(strncmp("# f",line,3)==0) {
			nondom(pop);
			sort(pop.begin(),pop.end(),cmp());
			ss[it]+=ssmetric(pop);
			pop.insert(pop.begin(),ref);
			s[it]+=smetric(pop);
			pop.clear();
			it=-1;
			n++;
		} else if(line[0]!='#' && it!=-1) {
			p.resize(2);
			if(argc>1) {
				sscanf(line,"%*d | %*d | %lf %lf",&p[0],&p[1]);
			} else {
				sscanf(line,"%*d | %*d | %lf %*f %*f %lf",&p[0],&p[1]);
			}
			pop.push_back(p);
		}
		cin.getline(line,MAX);
	}
	for(size_t i=0;i<s.size();i++) {
		cout << i << ' ' << s[i]/n << ' ' << ss[i]/n << endl;
	}
	return 0;
}
