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

#include <cstdio>

#include <mocs/params.h>
#include <mocs/loader.h>

extern FILE* params_in;

int params_parse(void*);

Params::Params() {
}

Params::Params(const char* file) {
	load(file);
	depth=0;
}

Params::~Params() {
}

void Params::init() {
	Loadable* obj;
	hash_map<const char*,char*,hash_str>::iterator i;
	cout << "# p" << p << endl;
	for(i=p.begin();i!=p.end();i++) {
		if(i->second[0]=='@') {
			obj=Loader::newInstance(i->second+1,*this);
			delete [] i->second;
			i->second=(char*)obj;
		}
	}
}

void Params::load(const char* file) {
	depth=0;
	files.clear();
	files.push_back(strdup(file));
	while(!files.empty()) {
		params_in=fopen(files.front(),"r");
		assert(params_in!=false);
		params_parse((void*)this);
		fclose(params_in);
		free(files.front());
		files.pop_front();
		depth++;
	}
}

void Params::put(const char* name,const void* value) {
	if(strcmp(name,"include")==0) {
		files.push_back(strdup((char*)value));
	} else if(depth==0 || p.find(name)==p.end()) {
		if(p.find(name)==p.end()) {
			p[strdup(name)]=(char*)value;
		} else {
			p[name]=(char*)value;
		}
	}
}

void* Params::get(const char* name) {
	hash_map<const char*,char*,hash_str>::iterator i=p.find(name);
	return (i==p.end()) ? 0 : i->second;
}

int Params::getInt(const char* name,int value) {
	hash_map<const char*,char*,hash_str>::iterator i=p.find(name);
	return (i==p.end()) ? value : atoi(i->second);
}

bool Params::getBool(const char* name,bool value) {
	hash_map<const char*,char*,hash_str>::iterator i=p.find(name);
	return (i==p.end()) ? value : (strcmp(i->second,"true")==0);
}

double Params::getDouble(const char* name,double value) {
	hash_map<const char*,char*,hash_str>::iterator i=p.find(name);
	return (i==p.end()) ? value : atof(i->second);
}

char* Params::get(const char* name,const char* value) {
	hash_map<const char*,char*,hash_str>::iterator i=p.find(name);
	return (i==p.end()) ? (char*)value : i->second;
}

ostream& operator << (ostream& os,hash_map<const char*,char*,hash_str>& h) {
	hash_map<const char*,char*,hash_str>::iterator i;
	for(i=h.begin();i!=h.end();i++) {
		os << ' ' << i->first << '=' << i->second;
	}
	return os;
}
