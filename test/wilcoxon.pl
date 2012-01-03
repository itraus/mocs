#!/usr/bin/perl -w

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

sub normalz {
	$x=shift;
	@b=(0.319381530,-0.356563782,1.781477937,-1.821255978,1.330274429);
	$p=0.2316419;
	$t=1/(1+$p*$x);
	$fact=$t;
	$sum=0;
	for($i=0;$i<=$#b;$i++) {
		$sum+=$b[$i]*$fact;
		$fact*=$t;
	}
	return 2*$sum*exp(-$x*$x/2.0)/(sqrt(2*3.14159265358979323846));
}

$n=0;
while(<STDIN>) {
	chop $_;
	($a,$b)=split " ",$_;
	if($a-$b!=0.0) {
		$x[$n]=$a-$b;
		$xx[$n]=abs($x[$n]);
		$n++;
	}
}

for($i=0;$i<$n-1;$i++) {
	for($j=$i+1,$min=$i;$j<$n;$j++) {
		if($xx[$j]<$xx[$min]) {
			$min=$j;
		}
	}
	$t=$x[$i];
	$x[$i]=$x[$min];
	$x[$min]=$t;
	$t=$xx[$i];
	$xx[$i]=$xx[$min];
	$xx[$min]=$t;
}

for($i=0;$i<$n;) {
	for($j=$i+1;$j<$n && $x[$i]==$x[$j];$j++) {}
	$rank=($i+$j+1.0)/2.0;
	for(;$i<$j;$i++) {
		$r[$i]=$rank;
	}
}

for($i=0,$wplus=0.0,$wminus=0.0;$i<$n;$i++) {
	if($x[$i]>0.0) {
		$wplus+=$r[$i];
	} else {
		$wminus+=$r[$i];
	}
}

$w=$wplus;
if($wplus<$wminus) {
	$w=$wminus;
}
$z=abs($w-0.5-$n*($n+1.0)/4.0)/sqrt($n*($n+1.0)*(2.0*$n+1.0)/24.0);
$p=100.0*(1.0-normalz($z));
if($wplus<$wminus) {
	$p=-$p;
}

print "# n $n\n";
print "# w+ $wplus\n";
print "# w- $wminus\n";
print "# t $z\n";
print "# p $p\n";
