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

$prefix=$ARGV[3];

sub moea {
	my ($prob,$algo);
	$prob=$_[0];
	$algo=$_[1];
	mkdir $prefix."out",0755;
	mkdir $prefix."out/$prob",0755;
	mkdir $prefix."out/$prob/$algo",0755;
	system "( time ../../imoea ".$prefix."moea.cfg $algo.cfg data/$prob/$prob.cfg >> ".$prefix."out/$prob/$algo/out ) 2>> ".$prefix."out/$prob/$algo/time";
}

sub mocs {
	my ($prob,$algo);
	$prob=$_[0];
	$algo=$_[1];
	mkdir $prefix."out",0755;
	mkdir $prefix."out/$prob",0755;
	mkdir $prefix."out/$prob/$algo",0755;
	system "( time ../../imocs ".$prefix."mocs.cfg $algo.cfg data/$prob/$prob.cfg data/$prob/$prob.arff data/$prob/$prob.arff >> ".$prefix."out/$prob/$algo/out ) 2>> ".$prefix."out/$prob/$algo/time";
}

sub cvmocs {
	my ($i,$prob,$algo);
	$prob=$_[0];
	$algo=$_[1];
	mkdir $prefix."out",0755;
	mkdir $prefix."out/$prob",0755;
	mkdir $prefix."out/$prob/$algo",0755;
	for($i=0;$i<10;$i++) {
		system "( time ../../imocs ".$prefix."mocs.cfg $algo.cfg data/$prob/$prob.cfg data/$prob/train$i.arff data/$prob/test$i.arff >> ".$prefix."out/$prob/$algo/out ) 2>> ".$prefix."out/$prob/$algo/time";
	}
}

sub plot {
	my ($prob,$algo,$i,$line,$iter);
	$prob=$_[0];
	$algo=$_[1];
	open IN,"<".$prefix."out/$prob/$algo/out";
	open VISIT,"| sort | uniq > ".$prefix."out/$prob/$algo/visit";
	open FINAL,"| sort | uniq > ".$prefix."out/$prob/$algo/final";
	open PARETO,"| sort | uniq | ./nondom.pl > ".$prefix."out/$prob/$algo/pareto";
	$i=0;
	while($line=<IN>) {
		chop $line;
		if($line =~ /^# p.* iterations=([^ ]+)/) {
			$iter=$1;
		} elsif($line =~ /^# i ([^ ]+)/) {
			$i=$1;
		} elsif($line =~ /^# f/) {
			$i=-1;
		} elsif($line =~ /^[^|]+\|[^|]+\|([^|\n]+)/) {
			if($i==-1) {
				print PARETO "$1\n";
			} elsif($i==$iter-1) {
				print FINAL "$1\n";
			}
			print VISIT "$1\n";
		}
	}
	close PARETO;
	close FINAL;
	close VISIT;
	close IN;
	system "test -f data/$prob/pareto.gpi && cp data/$prob/*.gpi ".$prefix."out/$prob";
	system "cd ".$prefix."out/$prob/$algo ; gnuplot ../../../plot.gpi";
}

sub cvplot {
	my ($prob,$algo,$i,$line,$fold,$iter,@rules,@iteration,@numPop,@a,@b,$j);
	$prob=$_[0];
	$algo=$_[1];
	open IN,"<".$prefix."out/$prob/$algo/out";
	$i=0;
	$fold=0;
	@a=();
	@b=();
	@iteration=();
	@rules=();
	@numPop=();
	while($line=<IN>) {
		chop $line;
		if($line =~ /^# p.* iterations=([^ ]+)/) {
			$iter=$1;
			if($fold>0) {
				close VISIT;
				close FINAL;
				close PARETO;
				system "awk '{ print \$7,\$5,\$6; }' < $prefix"."out/$prob/$algo/pareto".($fold-1)." | sort -n | ./avg.pl > $prefix"."out/$prob/$algo/overfit".($fold-1);
			}
			open VISIT,"| sort | uniq > ".$prefix."out/$prob/$algo/visit$fold";
			open FINAL,"| sort | uniq > ".$prefix."out/$prob/$algo/final$fold";
			open PARETO,"| sort | uniq > ".$prefix."out/$prob/$algo/pareto$fold";
		} elsif($line =~ /^# i ([^ ]+) \| ([^ ]+) 1 1 [^ ]+ \| ([^ ]+) ([^ ]+) ([^ ]+)$/) {
			$i=$1;
			@b=(100.0*(1.0-$2),$3,$4,1.0-$5);
			if($fold==0) {
				$iteration[$i]=join " ",@b;
			} else {
				@a=split " ",$iteration[$i];
				for($j=0;$j<=$#b;$j++) {
					$a[$j]+=$b[$j];
				}
				$iteration[$i]=join " ",@a;
			}
		} elsif($line =~ /^# f/) {
			$i=-1;
			$fold++;
		} elsif($i==-1 && $line =~ /^[^ ]+ \| [^ ]+ \| ([^|]+) \| .* ([0-9\.]+) ([0-9\.]+) ([0-9]+)$/) {
			print PARETO "$1 $2 $3 $4\n";
		} elsif($line =~ /^[^ ]+ \| [^ ]+ \| ([^|]+) \| [^ ]+ \| [^ ]+ ([^ ]+)$/) {
			if($i==-1) {
			} elsif($i==$iter-1) {
				print FINAL "$1\n";
				print VISIT "$1\n";
				$numPop[$i]++;
				$rules[$i]+=$2;
			} else {
				print VISIT "$1\n";
				$numPop[$i]++;
				$rules[$i]+=$2;
			}
		}
	}
	close VISIT;
	close PARETO;
	close FINAL;
	close IN;
	system "awk '{ print \$7,\$5,\$6; }' < $prefix"."out/$prob/$algo/pareto".($fold-1)." | sort -n | ./avg.pl > $prefix"."out/$prob/$algo/overfit".($fold-1);
	system "cat $prefix"."out/$prob/$algo/overfit? | sort -n | ./avg.pl > $prefix"."out/$prob/$algo/overfit";
	open EVOL,">".$prefix."out/$prob/$algo/evol";
	for($i=0;$i<=$#iteration;$i++) {
		print EVOL $i." ";
		map { print EVOL ($_*1.0/$fold)." "; } split " ",$iteration[$i];
		print EVOL ($rules[$i]*1.0/$numPop[$i])."\n";
	}
	close EVOL;
	system "cd ".$prefix."out/$prob/$algo ; gnuplot ../../../cvplot.gpi";
}

sub cvpop {
	my ($prob,$algo,$i,$j,$k,$l,$line,$fold,@r);
	$prob=$_[0];
	$algo=$_[1];
	open IN,"<".$prefix."out/$prob/$algo/out";
	$i=0;
	$fold=-1;
	while($line=<IN>) {
		chop $line;
		if($line =~ /^# p/) {
			$i=0;
		} elsif($line =~ /^# f/) {
			$i=-1;
			$j=0;
			$fold++;
			if($fold>0) {
				close POP;
			}
			open POP,">".$prefix."out/$prob/$algo/pop$fold";
		} elsif($i==-1 && $line =~ /^[^ ]+ \| [^ ]+ \| [^|]+ \| \[[0-9\.]+\] (.*) \| [0-9\.]+ [0-9\.]+ ([0-9]+)$/) {
			print POP "($j) ";
			@r=split " ",$1;
			$k=scalar@r/$2;
			for($l=0;$l<=$#r;$l++) {
				if(($l%$k)==$k-1) {
					print POP ":".$r[$l];
					if($l<$#r) {
						printf POP ",";
					}
				} elsif($r[$l]<0) {
					print POP "#";
				} else {
					print POP $r[$l];
				}
			}
			print POP "\n";
			$j++;
		}
	}
	close POP;
}

sub metrics {
	system "../../metrics < $prefix"."out/$prob/$algo/out > $prefix"."out/$prob/$algo/metrics";
	system "cd ".$prefix."out/$prob/$algo ; gnuplot ../../../metrics.gpi";
}

sub stats {
	my ($prob,$algo,$n,$line,@test,@rules,@test2,@rules2,$std_test,$std_rules,$std_test2,$std_rules2,$avg_test,$avg_rules,$avg_test2,$avg_rules2);
	$prob=$_[0];
	$algo=$_[1];
	mkdir $prefix."out",0755;
	mkdir $prefix."out/$prob",0755;
	mkdir $prefix."out/$prob/$algo",0755;
	open IN,"<".$prefix."out/$prob/$algo/out";
	$n=0;
	$nn=0;
	while($line=<IN>) {
		chop $line;
		if($line =~ /^# t ([0-9\.]+) ([0-9\.]+)$/) {
			$test[$n]=$1;
			$rules[$n]=$2;
			$n++;
		} elsif($line =~ /^# T ([0-9\.]+)$/) {
			$train[$nn]=$1;
			$nn++;
		}
	}
	open STATS,">".$prefix."out/$prob/$algo/stats";
	$avg_test=0;
	$avg_rules=0;
	$avg_train=0;
	for($i=0;$i<$n;$i++) {
		$avg_test+=$test[$i];
		$avg_rules+=$rules[$i];
		$avg_train+=$train[$i];
	}
	$avg_test/=$n;
	$avg_rules/=$n;
	$std_test=0;
	$std_rules=0;
	$avg_train/=$n;
	$std_train=0;
	for($i=0;$i<$n;$i++) {
		$std_test+=($test[$i]-$avg_test)*($test[$i]-$avg_test);
		$std_rules+=($rules[$i]-$avg_rules)*($rules[$i]-$avg_rules);
		$std_train+=($train[$i]-$avg_train)*($train[$i]-$avg_train);
	}
	$std_test=sqrt($std_test/$n);
	$std_rules=sqrt($std_rules/$n);
	$std_train=sqrt($std_train/$n);
	print STATS "# $prob/$algo Tba $avg_train $std_train\n";
	print STATS "# $prob/$algo tba $avg_test $std_test\n";
	print STATS "# $prob/$algo rba $avg_rules $std_rules\n";
	close STATS;
	close IN;
}

if(scalar@ARGV!=3 && scalar@ARGV!=4) {
	print "usage: ./run.pl moea,mocs,plot,cvmocs,cvplot,metrics,stats,cvpop problems algorithms [prefix]\n";
	exit;
}

if($ARGV[2] eq "all") {
	@algorithms=map { ($a,$b)=split "\\.",$_; $_=$a; } split " ",`echo *.cfg`;
} else {
	@algorithms=split ",",$ARGV[2];
}

if($ARGV[1] eq "all") {
	@problems=map { ($a,$b)=split "/",$_; $_=$b; } split " ",`echo data/*`;
} else {
	@problems=split ",",$ARGV[1];
}

foreach $prob (@problems) {
	foreach $algo (@algorithms) {
		foreach $run (split ",",$ARGV[0]) {
			if($algo ne "moea" && $algo ne "mocs") {
				print "$run/$prob/$algo\n";
				eval $run.' $prob,$algo';
			}
		}
	}
}
