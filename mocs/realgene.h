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

#ifndef __REALGENE_H__
#define __REALGENE_H__

#include <mocs/gene.h>

class RealGene : public Gene {
		double min,max,dev,value;

	public:
		RealGene();
		RealGene(double min,double max);
		RealGene(const RealGene& gene);
		virtual ~RealGene();

		double getValue() const;
		void setValue(double value);
		double getMin() const;
		void setMin(double min);
		double getMax() const;
		void setMax(double max);
		Gene* newGene() const;
		void init();
		void mutate();
		void step(double x);
		double getDev() const;
		void setDev(double dev);

		Gene& operator = (const Gene& gene);
		RealGene& operator = (const RealGene& gene);
		ostream& operator >> (ostream& os);
};

#endif
