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

ifndef CXX
CXX=g++
endif 

ifeq ($(CXX),icc)
LDFLAGS+=-shared-libcxa
#OPT=-O3 -unroll -ip -ipo -ipo_obj -vec_report0 -Ob2 -mcpu=pentium4 -xW -march=pentium4
OPT=-O3 -xN -tpp7 -ipo
#WARN=-Wall
ANSI=-no-gcc
else
ifeq ($(CPU),no)
ARCH=
else
ARCH=-m64 -mtune=generic
endif
OPT=-g0 -fomit-frame-pointer -ffast-math -O3 $(ARCH)
DEBUG=-ggdb -DDEBUG -pg
WARN=-Wall -Wdeprecated -Wno-long-long -Wredundant-decls
ANSI=-ansi -pedantic -pipe
endif

ifeq ($(STAT),1)
STATIC=-static -DSTATIC
ifeq ($(CXX),icc)
LIB=
else
LIB=-lm
endif
else
STATIC=-fpic -rdynamic
ifeq ($(CXX),icc)
LIB=-ldl -L. -lmocs
else
LIB=-lm -ldl -L. -lmocs
endif
endif
LDFLAGS+=$(STATIC)

ifeq ($(DEB),1)
CXXFLAGS=-I. $(WARN) $(ANSI) $(DEBUG) $(STATIC)
else
CXXFLAGS=-I. $(WARN) $(ANSI) $(OPT) $(STATIC) -DNDEBUG
endif

LEX=flex
YACC=bison

ifeq ($(STAT),1)
TARGETS=imoea-static imocs-static metrics-static
else
TARGETS=imoea imocs metrics libmocs.so
endif
ALL_TARGETS=imoea-static imocs-static metrics-static metrics imoea imocs libmocs.so
PARSER=params.tab.cc params.tab.h params.yy.cc arff.tab.cc arff.tab.h arff.yy.cc

METRICS_OBJ = \
	metrics.o

MOCS_OBJ= \
	imocs.o

MOEA_OBJ= \
	imoea.o

LIBMOCS_OBJ= \
	sf2.o \
	zdt6.o \
	kur.o \
	okk.o \
	init.o \
	rand.o \
	intgene.o \
	realgene.o  \
	genome.o  \
	fitness.o  \
	ffunction.o \
	individual.o  \
	initiator.o \
	population.o  \
	moperator.o \
	umutation.o \
	nmutation.o \
	pmutation.o \
	amutation.o \
	soperator.o \
	tselection.o \
	coperator.o \
	ucrossover.o \
	nucrossover.o \
	sbcrossover.o \
	ealgorithm.o \
	attribute.o \
	attributes.o \
	rattribute.o \
	iattribute.o \
	value.o \
	ivalue.o \
	rvalue.o \
	instance.o \
	instances.o \
	afitness.o \
	asfitness.o \
	asgfitness.o \
	ascfitness.o \
	cffunction.o \
	dmaker.o \
	baccuracy.o \
	bcompromise.o \
	mselection.o \
	nnmating.o \
	fpmating.o \
	rmating.o \
	tmating.o \
	iloader.o \
	arff.o \
	arff.tab.o \
	arff.yy.o \
	model.o \
	rmodel.o \
	imodel.o \
	mmodel.o \
	rrmodel.o \
	element.o \
	rrelement.o \
	rielement.o \
	irelement.o \
	iielement.o \
	rinit.o \
	iinit.o \
	moga.o \
	moes.o \
	ngga.o \
	nsgaii.o \
	spea2.o \
	moea.o \
	mocs.o \
	loader.o  \
	loadable.o \
	params.o \
	params.tab.o \
	params.yy.o

OBJ=$(LIBMOCS_OBJ) $(MOEA_OBJ) $(MOCS_OBJ) $(METRICS_OBJ)

METRICS_SRC= \
	metrics.cc

MOCS_SRC= \
	imocs.cc

MOEA_SRC= \
	imoea.cc

LIBMOCS_SRC= \
	sf2.cc \
	zdt6.cc \
	kur.cc \
	okk.cc \
	init.cc \
	rand.cc \
	intgene.cc \
	realgene.cc \
	genome.cc \
	fitness.cc \
	ffunction.cc \
	individual.cc \
	initiator.cc \
	population.cc \
	moperator.cc \
	umutation.cc \
	nmutation.cc \
	pmutation.cc \
	amutation.cc \
	soperator.cc \
	tselection.cc \
	coperator.cc \
	ucrossover.cc \
	nucrossover.cc \
	sbcrossover.cc \
	ealgorithm.cc \
	attribute.cc \
	attributes.cc \
	rattribute.cc \
	iattribute.cc \
	value.cc \
	ivalue.cc \
	rvalue.cc \
	instance.cc \
	instances.cc \
	afitness.cc \
	asfitness.cc \
	asgfitness.cc \
	ascfitness.cc \
	cffunction.cc \
	dmaker.cc \
	baccuracy.cc \
	bcompromise.cc \
	mselection.cc \
	nnmating.cc \
	fpmating.cc \
	rmating.cc \
	tmating.cc \
	iloader.cc \
	arff.cc \
	arff.tab.cc \
	arff.yy.cc \
	model.cc \
	rmodel.cc \
	imodel.cc \
	mmodel.cc \
	rrmodel.cc \
	element.cc \
	rrelement.cc \
	rielement.cc \
	irelement.cc \
	iielement.cc \
	rinit.cc \
	iinit.cc \
	moga.cc \
	moes.cc \
	ngga.cc \
	nsgaii.cc \
	spea2.cc \
	moea.cc \
	mocs.cc \
	loader.cc \
	loadable.cc \
	params.cc \
	params.tab.cc \
	params.yy.cc

SRC=$(LIBMOCS_SRC) $(MOEA_SRC) $(MOCS_SRC) $(METRICS_SRC)

.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

all: $(TARGETS)

params.tab.cc: params.y
	$(YACC) -d -pparams_ -bparams params.y
	mv params.tab.c params.tab.cc

params.yy.cc: params.lex params.tab.cc
	$(LEX) -i -Pparams_ -o$@ params.lex

arff.tab.cc: arff.y
	$(YACC) -d -parff_ -barff arff.y
	mv arff.tab.c arff.tab.cc

arff.yy.cc: arff.lex arff.tab.cc
	$(LEX) -i -Parff_ -o$@ arff.lex

libmocs.so: $(LIBMOCS_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared -o $@ $(LIBMOCS_OBJ)

imoea: libmocs.so $(MOEA_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(MOEA_OBJ) $(LIBMOCS) $(LIB)

imoea-static: $(MOEA_OBJ) $(LIBMOCS_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(MOEA_OBJ) $(LIBMOCS_OBJ) $(LIB)

imocs: libmocs.so $(MOCS_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(MOCS_OBJ) $(LIBMOCS) $(LIB)

imocs-static: $(MOCS_OBJ) $(LIBMOCS_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(MOCS_OBJ) $(LIBMOCS_OBJ) $(LIB)

metrics: libmocs.so $(METRICS_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(METRICS_OBJ) $(LIBMOCS) $(LIB)

metrics-static: libmocs.so $(METRICS_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(METRICS_OBJ) $(LIBMOCS_OBJ) $(LIB)

ifeq ($(STAT),1)
test: $(TARGETS)
	cp -f imoea-static test/moea/imoea
	cp -f imocs-static test/mocs/imocs
	cp -f metrics-static test/moea/metrics
	cp -f metrics-static test/mocs/metrics
else
test: $(TARGETS)
	cp -f imoea libmocs.so test/moea
	cp -f imocs libmocs.so test/mocs
	cp -f metrics test/moea/metrics
	cp -f metrics test/mocs/metrics
endif

backup: $(PARSER) $(SRC)
	tar cvzf ../backup/mocs-`date +%Y-%m-%d-%H%M`.tgz $(SRC) $(PARSER) mocs/*.h *.lex *.y `find -name Makefile -o -name \*.cfg -o -name \*.gpi -o -name \*.pl -o -name \*.sh -o -name \*.arff`

depend: $(SRC)
	makedepend -Y '-s# Dependències' -- $(CXXFLAGS) -- $(SRC) > /dev/null 2>&1
	
clean:
	rm -f *.bak *.il $(OBJ) $(PARSER) $(ALL_TARGETS)

# Dependències

sf2.o: ./mocs/realgene.h ./mocs/gene.h ./mocs/config.h ./mocs/ffunction.h
sf2.o: ./mocs/loadable.h ./mocs/params.h ./mocs/population.h
sf2.o: ./mocs/individual.h ./mocs/genome.h ./mocs/fitness.h
zdt6.o: ./mocs/realgene.h ./mocs/gene.h ./mocs/config.h ./mocs/ffunction.h
zdt6.o: ./mocs/loadable.h ./mocs/params.h ./mocs/population.h
zdt6.o: ./mocs/individual.h ./mocs/genome.h ./mocs/fitness.h
kur.o: ./mocs/realgene.h ./mocs/gene.h ./mocs/config.h ./mocs/ffunction.h
kur.o: ./mocs/loadable.h ./mocs/params.h ./mocs/population.h
kur.o: ./mocs/individual.h ./mocs/genome.h ./mocs/fitness.h
okk.o: ./mocs/realgene.h ./mocs/gene.h ./mocs/config.h ./mocs/initiator.h
okk.o: ./mocs/loadable.h ./mocs/params.h ./mocs/individual.h ./mocs/genome.h
okk.o: ./mocs/fitness.h ./mocs/ffunction.h ./mocs/population.h
init.o: ./mocs/realgene.h ./mocs/gene.h ./mocs/config.h ./mocs/initiator.h
init.o: ./mocs/loadable.h ./mocs/params.h ./mocs/individual.h ./mocs/genome.h
init.o: ./mocs/fitness.h
rand.o: ./mocs/rand.h ./mocs/config.h
intgene.o: ./mocs/rand.h ./mocs/config.h ./mocs/intgene.h ./mocs/gene.h
realgene.o: ./mocs/rand.h ./mocs/config.h ./mocs/realgene.h ./mocs/gene.h
genome.o: ./mocs/genome.h ./mocs/gene.h ./mocs/config.h
fitness.o: ./mocs/fitness.h ./mocs/config.h
ffunction.o: ./mocs/ffunction.h ./mocs/loadable.h ./mocs/params.h
ffunction.o: ./mocs/config.h ./mocs/population.h ./mocs/individual.h
ffunction.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
individual.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h
individual.o: ./mocs/config.h ./mocs/fitness.h
initiator.o: ./mocs/initiator.h ./mocs/loadable.h ./mocs/params.h
initiator.o: ./mocs/config.h ./mocs/individual.h ./mocs/genome.h
initiator.o: ./mocs/gene.h ./mocs/fitness.h
population.o: ./mocs/population.h ./mocs/individual.h ./mocs/genome.h
population.o: ./mocs/gene.h ./mocs/config.h ./mocs/fitness.h
moperator.o: ./mocs/moperator.h ./mocs/loadable.h ./mocs/params.h
moperator.o: ./mocs/config.h ./mocs/population.h ./mocs/individual.h
moperator.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
umutation.o: ./mocs/rand.h ./mocs/config.h ./mocs/umutation.h
umutation.o: ./mocs/moperator.h ./mocs/loadable.h ./mocs/params.h
umutation.o: ./mocs/population.h ./mocs/individual.h ./mocs/genome.h
umutation.o: ./mocs/gene.h ./mocs/fitness.h
nmutation.o: ./mocs/rand.h ./mocs/config.h ./mocs/nmutation.h
nmutation.o: ./mocs/umutation.h ./mocs/moperator.h ./mocs/loadable.h
nmutation.o: ./mocs/params.h ./mocs/population.h ./mocs/individual.h
nmutation.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
pmutation.o: ./mocs/rand.h ./mocs/config.h ./mocs/pmutation.h
pmutation.o: ./mocs/umutation.h ./mocs/moperator.h ./mocs/loadable.h
pmutation.o: ./mocs/params.h ./mocs/population.h ./mocs/individual.h
pmutation.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
amutation.o: ./mocs/rand.h ./mocs/config.h ./mocs/amutation.h
amutation.o: ./mocs/pmutation.h ./mocs/umutation.h ./mocs/moperator.h
amutation.o: ./mocs/loadable.h ./mocs/params.h ./mocs/population.h
amutation.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h
amutation.o: ./mocs/fitness.h
soperator.o: ./mocs/soperator.h ./mocs/loadable.h ./mocs/params.h
soperator.o: ./mocs/config.h ./mocs/population.h ./mocs/individual.h
soperator.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
tselection.o: ./mocs/rand.h ./mocs/config.h ./mocs/tselection.h
tselection.o: ./mocs/soperator.h ./mocs/loadable.h ./mocs/params.h
tselection.o: ./mocs/population.h ./mocs/individual.h ./mocs/genome.h
tselection.o: ./mocs/gene.h ./mocs/fitness.h
coperator.o: ./mocs/coperator.h ./mocs/loadable.h ./mocs/params.h
coperator.o: ./mocs/config.h ./mocs/individual.h ./mocs/genome.h
coperator.o: ./mocs/gene.h ./mocs/fitness.h
ucrossover.o: ./mocs/rand.h ./mocs/config.h ./mocs/ucrossover.h
ucrossover.o: ./mocs/coperator.h ./mocs/loadable.h ./mocs/params.h
ucrossover.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h
ucrossover.o: ./mocs/fitness.h
nucrossover.o: ./mocs/rand.h ./mocs/config.h ./mocs/nucrossover.h
nucrossover.o: ./mocs/coperator.h ./mocs/loadable.h ./mocs/params.h
nucrossover.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h
nucrossover.o: ./mocs/fitness.h
sbcrossover.o: ./mocs/rand.h ./mocs/config.h ./mocs/realgene.h ./mocs/gene.h
sbcrossover.o: ./mocs/sbcrossover.h ./mocs/coperator.h ./mocs/loadable.h
sbcrossover.o: ./mocs/params.h ./mocs/individual.h ./mocs/genome.h
sbcrossover.o: ./mocs/fitness.h
ealgorithm.o: ./mocs/ealgorithm.h ./mocs/loadable.h ./mocs/params.h
ealgorithm.o: ./mocs/config.h ./mocs/population.h ./mocs/individual.h
ealgorithm.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
attribute.o: ./mocs/attribute.h ./mocs/value.h ./mocs/config.h
attributes.o: ./mocs/attributes.h ./mocs/attribute.h ./mocs/value.h
attributes.o: ./mocs/config.h
rattribute.o: ./mocs/rattribute.h ./mocs/attribute.h ./mocs/value.h
rattribute.o: ./mocs/config.h
iattribute.o: ./mocs/iattribute.h ./mocs/attribute.h ./mocs/value.h
iattribute.o: ./mocs/config.h
value.o: ./mocs/value.h ./mocs/config.h
ivalue.o: ./mocs/ivalue.h ./mocs/value.h ./mocs/config.h
rvalue.o: ./mocs/rvalue.h ./mocs/value.h ./mocs/config.h
instance.o: ./mocs/instance.h ./mocs/value.h ./mocs/config.h
instances.o: ./mocs/instances.h ./mocs/instance.h ./mocs/value.h
instances.o: ./mocs/config.h
afitness.o: ./mocs/model.h ./mocs/iloader.h ./mocs/loadable.h ./mocs/params.h
afitness.o: ./mocs/config.h ./mocs/instances.h ./mocs/instance.h
afitness.o: ./mocs/value.h ./mocs/attributes.h ./mocs/attribute.h
afitness.o: ./mocs/initiator.h ./mocs/individual.h ./mocs/genome.h
afitness.o: ./mocs/gene.h ./mocs/fitness.h ./mocs/afitness.h
afitness.o: ./mocs/ffunction.h ./mocs/population.h
asfitness.o: ./mocs/model.h ./mocs/iloader.h ./mocs/loadable.h
asfitness.o: ./mocs/params.h ./mocs/config.h ./mocs/instances.h
asfitness.o: ./mocs/instance.h ./mocs/value.h ./mocs/attributes.h
asfitness.o: ./mocs/attribute.h ./mocs/initiator.h ./mocs/individual.h
asfitness.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
asfitness.o: ./mocs/asfitness.h ./mocs/ffunction.h ./mocs/population.h
asgfitness.o: ./mocs/model.h ./mocs/iloader.h ./mocs/loadable.h
asgfitness.o: ./mocs/params.h ./mocs/config.h ./mocs/instances.h
asgfitness.o: ./mocs/instance.h ./mocs/value.h ./mocs/attributes.h
asgfitness.o: ./mocs/attribute.h ./mocs/initiator.h ./mocs/individual.h
asgfitness.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
asgfitness.o: ./mocs/asgfitness.h ./mocs/ffunction.h ./mocs/population.h
ascfitness.o: ./mocs/model.h ./mocs/iloader.h ./mocs/loadable.h
ascfitness.o: ./mocs/params.h ./mocs/config.h ./mocs/instances.h
ascfitness.o: ./mocs/instance.h ./mocs/value.h ./mocs/attributes.h
ascfitness.o: ./mocs/attribute.h ./mocs/initiator.h ./mocs/individual.h
ascfitness.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
ascfitness.o: ./mocs/ascfitness.h ./mocs/ffunction.h ./mocs/population.h
cffunction.o: ./mocs/model.h ./mocs/iloader.h ./mocs/loadable.h
cffunction.o: ./mocs/params.h ./mocs/config.h ./mocs/instances.h
cffunction.o: ./mocs/instance.h ./mocs/value.h ./mocs/attributes.h
cffunction.o: ./mocs/attribute.h ./mocs/initiator.h ./mocs/individual.h
cffunction.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
cffunction.o: ./mocs/cffunction.h ./mocs/ffunction.h ./mocs/population.h
dmaker.o: ./mocs/dmaker.h ./mocs/loadable.h ./mocs/params.h ./mocs/config.h
dmaker.o: ./mocs/population.h ./mocs/individual.h ./mocs/genome.h
dmaker.o: ./mocs/gene.h ./mocs/fitness.h
baccuracy.o: ./mocs/baccuracy.h ./mocs/dmaker.h ./mocs/loadable.h
baccuracy.o: ./mocs/params.h ./mocs/config.h ./mocs/population.h
baccuracy.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h
baccuracy.o: ./mocs/fitness.h
bcompromise.o: ./mocs/bcompromise.h ./mocs/dmaker.h ./mocs/loadable.h
bcompromise.o: ./mocs/params.h ./mocs/config.h ./mocs/population.h
bcompromise.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h
bcompromise.o: ./mocs/fitness.h
mselection.o: ./mocs/mselection.h ./mocs/loadable.h ./mocs/params.h
mselection.o: ./mocs/config.h ./mocs/population.h ./mocs/individual.h
mselection.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
nnmating.o: ./mocs/rand.h ./mocs/config.h ./mocs/nnmating.h
nnmating.o: ./mocs/mselection.h ./mocs/loadable.h ./mocs/params.h
nnmating.o: ./mocs/population.h ./mocs/individual.h ./mocs/genome.h
nnmating.o: ./mocs/gene.h ./mocs/fitness.h
fpmating.o: ./mocs/rand.h ./mocs/config.h ./mocs/fpmating.h
fpmating.o: ./mocs/mselection.h ./mocs/loadable.h ./mocs/params.h
fpmating.o: ./mocs/population.h ./mocs/individual.h ./mocs/genome.h
fpmating.o: ./mocs/gene.h ./mocs/fitness.h
rmating.o: ./mocs/rand.h ./mocs/config.h ./mocs/rmating.h ./mocs/mselection.h
rmating.o: ./mocs/loadable.h ./mocs/params.h ./mocs/population.h
rmating.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
tmating.o: ./mocs/rand.h ./mocs/config.h ./mocs/tmating.h ./mocs/mselection.h
tmating.o: ./mocs/loadable.h ./mocs/params.h ./mocs/population.h
tmating.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
iloader.o: ./mocs/iloader.h ./mocs/loadable.h ./mocs/params.h ./mocs/config.h
iloader.o: ./mocs/instances.h ./mocs/instance.h ./mocs/value.h
iloader.o: ./mocs/attributes.h ./mocs/attribute.h
arff.o: ./mocs/arff.h ./mocs/iloader.h ./mocs/loadable.h ./mocs/params.h
arff.o: ./mocs/config.h ./mocs/instances.h ./mocs/instance.h ./mocs/value.h
arff.o: ./mocs/attributes.h ./mocs/attribute.h ./mocs/ivalue.h
arff.o: ./mocs/rvalue.h ./mocs/iattribute.h ./mocs/rattribute.h
arff.tab.o: ./mocs/config.h ./mocs/arff.h ./mocs/iloader.h ./mocs/loadable.h
arff.tab.o: ./mocs/params.h ./mocs/instances.h ./mocs/instance.h
arff.tab.o: ./mocs/value.h ./mocs/attributes.h ./mocs/attribute.h
arff.yy.o: ./mocs/config.h arff.tab.h
model.o: ./mocs/rand.h ./mocs/config.h ./mocs/model.h ./mocs/iloader.h
model.o: ./mocs/loadable.h ./mocs/params.h ./mocs/instances.h
model.o: ./mocs/instance.h ./mocs/value.h ./mocs/attributes.h
model.o: ./mocs/attribute.h ./mocs/initiator.h ./mocs/individual.h
model.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
rmodel.o: ./mocs/rmodel.h ./mocs/model.h ./mocs/iloader.h ./mocs/loadable.h
rmodel.o: ./mocs/params.h ./mocs/config.h ./mocs/instances.h
rmodel.o: ./mocs/instance.h ./mocs/value.h ./mocs/attributes.h
rmodel.o: ./mocs/attribute.h ./mocs/initiator.h ./mocs/individual.h
rmodel.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h ./mocs/element.h
rmodel.o: ./mocs/irelement.h ./mocs/iattribute.h ./mocs/rrelement.h
rmodel.o: ./mocs/rattribute.h ./mocs/rielement.h
imodel.o: ./mocs/imodel.h ./mocs/rmodel.h ./mocs/model.h ./mocs/iloader.h
imodel.o: ./mocs/loadable.h ./mocs/params.h ./mocs/config.h
imodel.o: ./mocs/instances.h ./mocs/instance.h ./mocs/value.h
imodel.o: ./mocs/attributes.h ./mocs/attribute.h ./mocs/initiator.h
imodel.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
imodel.o: ./mocs/element.h ./mocs/iielement.h ./mocs/iattribute.h
imodel.o: ./mocs/rielement.h ./mocs/rattribute.h
mmodel.o: ./mocs/mmodel.h ./mocs/imodel.h ./mocs/rmodel.h ./mocs/model.h
mmodel.o: ./mocs/iloader.h ./mocs/loadable.h ./mocs/params.h ./mocs/config.h
mmodel.o: ./mocs/instances.h ./mocs/instance.h ./mocs/value.h
mmodel.o: ./mocs/attributes.h ./mocs/attribute.h ./mocs/initiator.h
mmodel.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
mmodel.o: ./mocs/element.h
rrmodel.o: ./mocs/rvalue.h ./mocs/value.h ./mocs/config.h ./mocs/rrmodel.h
rrmodel.o: ./mocs/rmodel.h ./mocs/model.h ./mocs/iloader.h ./mocs/loadable.h
rrmodel.o: ./mocs/params.h ./mocs/instances.h ./mocs/instance.h
rrmodel.o: ./mocs/attributes.h ./mocs/attribute.h ./mocs/initiator.h
rrmodel.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
rrmodel.o: ./mocs/element.h ./mocs/realgene.h
element.o: ./mocs/element.h ./mocs/gene.h ./mocs/config.h ./mocs/value.h
rrelement.o: ./mocs/rvalue.h ./mocs/value.h ./mocs/config.h ./mocs/realgene.h
rrelement.o: ./mocs/gene.h ./mocs/rrelement.h ./mocs/element.h
rrelement.o: ./mocs/rattribute.h ./mocs/attribute.h
rielement.o: ./mocs/rvalue.h ./mocs/value.h ./mocs/config.h ./mocs/realgene.h
rielement.o: ./mocs/gene.h ./mocs/rielement.h ./mocs/element.h
rielement.o: ./mocs/rattribute.h ./mocs/attribute.h
irelement.o: ./mocs/ivalue.h ./mocs/value.h ./mocs/config.h ./mocs/intgene.h
irelement.o: ./mocs/gene.h ./mocs/irelement.h ./mocs/element.h
irelement.o: ./mocs/iattribute.h ./mocs/attribute.h
iielement.o: ./mocs/ivalue.h ./mocs/value.h ./mocs/config.h ./mocs/intgene.h
iielement.o: ./mocs/gene.h ./mocs/iielement.h ./mocs/element.h
iielement.o: ./mocs/iattribute.h ./mocs/attribute.h
rinit.o: ./mocs/rand.h ./mocs/config.h ./mocs/rinit.h ./mocs/initiator.h
rinit.o: ./mocs/loadable.h ./mocs/params.h ./mocs/individual.h
rinit.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h ./mocs/intgene.h
rinit.o: ./mocs/realgene.h ./mocs/instances.h ./mocs/instance.h
rinit.o: ./mocs/value.h ./mocs/attributes.h ./mocs/attribute.h
rinit.o: ./mocs/iattribute.h ./mocs/rattribute.h
iinit.o: ./mocs/rand.h ./mocs/config.h ./mocs/iinit.h ./mocs/initiator.h
iinit.o: ./mocs/loadable.h ./mocs/params.h ./mocs/individual.h
iinit.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h ./mocs/intgene.h
iinit.o: ./mocs/realgene.h ./mocs/instances.h ./mocs/instance.h
iinit.o: ./mocs/value.h ./mocs/attributes.h ./mocs/attribute.h
iinit.o: ./mocs/iattribute.h ./mocs/rattribute.h
moga.o: ./mocs/moga.h ./mocs/ffunction.h ./mocs/loadable.h ./mocs/params.h
moga.o: ./mocs/config.h ./mocs/population.h ./mocs/individual.h
moga.o: ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h ./mocs/coperator.h
moga.o: ./mocs/moperator.h ./mocs/soperator.h ./mocs/ealgorithm.h
moga.o: ./mocs/mselection.h ./mocs/rand.h
moes.o: ./mocs/moes.h ./mocs/moga.h ./mocs/ffunction.h ./mocs/loadable.h
moes.o: ./mocs/params.h ./mocs/config.h ./mocs/population.h
moes.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
moes.o: ./mocs/coperator.h ./mocs/moperator.h ./mocs/soperator.h
moes.o: ./mocs/ealgorithm.h ./mocs/mselection.h ./mocs/rand.h
ngga.o: ./mocs/ngga.h ./mocs/moga.h ./mocs/ffunction.h ./mocs/loadable.h
ngga.o: ./mocs/params.h ./mocs/config.h ./mocs/population.h
ngga.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
ngga.o: ./mocs/coperator.h ./mocs/moperator.h ./mocs/soperator.h
ngga.o: ./mocs/ealgorithm.h ./mocs/mselection.h ./mocs/rand.h
nsgaii.o: ./mocs/nsgaii.h ./mocs/moga.h ./mocs/ffunction.h ./mocs/loadable.h
nsgaii.o: ./mocs/params.h ./mocs/config.h ./mocs/population.h
nsgaii.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
nsgaii.o: ./mocs/coperator.h ./mocs/moperator.h ./mocs/soperator.h
nsgaii.o: ./mocs/ealgorithm.h ./mocs/mselection.h
spea2.o: ./mocs/spea2.h ./mocs/moga.h ./mocs/ffunction.h ./mocs/loadable.h
spea2.o: ./mocs/params.h ./mocs/config.h ./mocs/population.h
spea2.o: ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h ./mocs/fitness.h
spea2.o: ./mocs/coperator.h ./mocs/moperator.h ./mocs/soperator.h
spea2.o: ./mocs/ealgorithm.h ./mocs/mselection.h
moea.o: ./mocs/moea.h ./mocs/initiator.h ./mocs/loadable.h ./mocs/params.h
moea.o: ./mocs/config.h ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h
moea.o: ./mocs/fitness.h ./mocs/ealgorithm.h ./mocs/population.h
moea.o: ./mocs/rand.h ./mocs/loader.h ./mocs/ffunction.h ./mocs/coperator.h
moea.o: ./mocs/moperator.h
mocs.o: ./mocs/mocs.h ./mocs/moea.h ./mocs/initiator.h ./mocs/loadable.h
mocs.o: ./mocs/params.h ./mocs/config.h ./mocs/individual.h ./mocs/genome.h
mocs.o: ./mocs/gene.h ./mocs/fitness.h ./mocs/ealgorithm.h
mocs.o: ./mocs/population.h ./mocs/model.h ./mocs/iloader.h
mocs.o: ./mocs/instances.h ./mocs/instance.h ./mocs/value.h
mocs.o: ./mocs/attributes.h ./mocs/attribute.h ./mocs/dmaker.h
mocs.o: ./mocs/baccuracy.h ./mocs/bcompromise.h
loader.o: ./mocs/loader.h ./mocs/loadable.h ./mocs/params.h ./mocs/config.h
loadable.o: ./mocs/loadable.h ./mocs/params.h ./mocs/config.h
params.o: ./mocs/params.h ./mocs/config.h ./mocs/loader.h ./mocs/loadable.h
params.tab.o: ./mocs/config.h ./mocs/params.h
params.yy.o: ./mocs/config.h params.tab.h
imoea.o: ./mocs/moea.h ./mocs/initiator.h ./mocs/loadable.h ./mocs/params.h
imoea.o: ./mocs/config.h ./mocs/individual.h ./mocs/genome.h ./mocs/gene.h
imoea.o: ./mocs/fitness.h ./mocs/ealgorithm.h ./mocs/population.h
imocs.o: ./mocs/mocs.h ./mocs/moea.h ./mocs/initiator.h ./mocs/loadable.h
imocs.o: ./mocs/params.h ./mocs/config.h ./mocs/individual.h ./mocs/genome.h
imocs.o: ./mocs/gene.h ./mocs/fitness.h ./mocs/ealgorithm.h
imocs.o: ./mocs/population.h ./mocs/model.h ./mocs/iloader.h
imocs.o: ./mocs/instances.h ./mocs/instance.h ./mocs/value.h
imocs.o: ./mocs/attributes.h ./mocs/attribute.h ./mocs/dmaker.h
metrics.o: ./mocs/config.h ./mocs/fitness.h
