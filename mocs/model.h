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

#ifndef __MODEL_H__
#define __MODEL_H__

#include <mocs/iloader.h>
#include <mocs/loadable.h>
#include <mocs/initiator.h>
#include <mocs/instances.h>
#include <mocs/individual.h>

class Model : public Loadable {
	protected:
		Attributes att;
		Instances inst;
		InstanceLoader* loader;

	public:
		Model(Params& p);
		virtual ~Model();

		virtual Instances& getInstances();
		virtual Attributes& getAttributes();
		virtual void init(const char* file);
		virtual void prune(Individual& indiv) = 0;
		virtual double size(const Individual& indiv) = 0;
		virtual double generality(Individual& indiv) = 0;
		virtual double utility(Individual& indiv) = 0;
		virtual double wrong(Individual& indiv) = 0;
		virtual double unknown(Individual& indiv) = 0;
		virtual double eval(Individual& indiv,Instance& inst) = 0;
		virtual double test(Individual& indiv,Instance& inst) = 0;
		virtual double eval(Individual& indiv);
		virtual double test(Individual& indiv);
};

#endif
