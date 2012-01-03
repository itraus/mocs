#!/usr/bin/perl

@file=<STDIN>;

for($i=0;$i<10;$i++) {
	open(TEST,">test$i.arff");
	open(TRAIN,">train$i.arff");

	for($j=0;$j<=$#file;$j++) {
		if($i==($j%10)) {
			print TEST $file[$j];
		} else {
			print TRAIN $file[$j];
		}
	}

	close(TRAIN);
	close(TEST);
}
