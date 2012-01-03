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

#ifndef __ARFF_H__
#define __ARFF_H__

#include <vector>

#include <mocs/iloader.h>
#include <mocs/attributes.h>

class Arff : public InstanceLoader {
	protected:
		size_t att,num;
		vector<vector<string> > nominals;

	public:
		Arff(Params& p);
		virtual ~Arff();

		virtual void load(const char* file);

		void addNominal();
		void addNominalValue(const char* value);
		void endNominal();
		void addInteger(const char* inf,const char* sup);
		void addReal();
		void addInstance();
		void addValue(const char* value);
		void endInstance();
};

#endif
