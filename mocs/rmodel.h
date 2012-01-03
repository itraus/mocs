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

#ifndef __RMODEL_H__
#define __RMODEL_H__

#include <mocs/model.h>
#include <mocs/element.h>

class RuleModel : public Model {
	protected:
		size_t ruleSize;
		size_t error,noclass,rused;
		vector<Element*> elems;
		hash_map<size_t,size_t> used;

	public:
		RuleModel(Params& p);
		virtual ~RuleModel();

		virtual void init(const char* file);
		virtual void prune(Individual& indiv);
		virtual double size(const Individual& indiv);
		virtual double generality(Individual& indiv);
		virtual double utility(Individual& indiv);
		virtual double spread(Individual& indiv,size_t i);
		virtual double wrong(Individual& indiv);
		virtual double unknown(Individual& indiv);
		virtual double eval(Individual& indiv,Instance& inst);
		virtual double test(Individual& indiv,Instance& inst);
		virtual double eval(Individual& indiv);
		virtual double test(Individual& indiv);
};

#endif
