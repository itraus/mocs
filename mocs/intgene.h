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

#ifndef __INTGENE_H__
#define __INTGENE_H__

#include <mocs/gene.h>

class IntGene : public Gene {
		double dev;
		int min,max,value;

	public:
		IntGene();
		IntGene(int min,int max);
		IntGene(const IntGene& gene);
		virtual ~IntGene();

		int getValue() const;
		void setValue(int value);
		int getMin() const;
		void setMin(int value);
		int getMax() const;
		void setMax(int value);
		Gene* newGene() const;
		void init();
		void mutate();
		void step(double x);
		double getDev() const;
		void setDev(double dev);

		Gene& operator = (const Gene& gene);
		IntGene& operator = (const IntGene& gene);
		ostream& operator >> (ostream& os);
};

#endif
