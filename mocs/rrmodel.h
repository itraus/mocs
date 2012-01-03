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

#ifndef __RRMODEL_H__
#define __RRMODEL_H__

#include <mocs/rmodel.h>

class RegressionRuleModel : public RuleModel {

	public:
		RegressionRuleModel(Params& p);
		virtual ~RegressionRuleModel();

		virtual double size(const Individual& indiv);
		virtual double test(Individual& indiv,Instance& inst);
		virtual double eval(Individual& indiv,Instance& inst);
};

#endif
