#!/bin/sh

# MOCS - Multi-Objective Classifier System
# Copyright (C) 2003 by Ivan Traus
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.

REAL=breast-w,bupa,pima-indians,mamografies,glass,grid-tao,ionosphere,iris,biopsies
NOMINAL=led,mux11,primary-tumour,audiology,vote
MIXED=learning,cmc

cd mocs
#../run.pl cvmocs,stats $REAL,$MIXED,$NOMINAL nsgaii normal-
#../run.pl cvmocs,stats $REAL,$MIXED,$NOMINAL spea2 normal-
#../run.pl cvmocs,stats $REAL,$MIXED,$NOMINAL ngga normal-
#../run.pl cvmocs,stats $REAL,$MIXED,$NOMINAL moga normal-
#../run.pl cvmocs,stats led moga normal-
#../run.pl cvmocs,stats $REAL,$MIXED,$NOMINAL moes normal-
../run.pl cvmocs,stats $REAL,$MIXED,$NOMINAL ngga general-
../run.pl cvmocs,stats $REAL,$MIXED,$NOMINAL ngga adapt-
../run.pl cvmocs,stats $REAL,$MIXED,$NOMINAL ngga instance-
