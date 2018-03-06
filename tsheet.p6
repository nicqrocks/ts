#!/usr/bin/env perl6

constant $tsloc = %*ENV<TSLOC> || $*HOME ~ "/Documents/ts";

sub USAGE() {
	print Q:c:to/END/;
	USAGE: {$*PROGRAM-NAME} [OPTIONS]
	Options:
		-a|--after  DATE		Restrict times to after a given date.

		-b|--before DATE		Restrict times to before a given date.

		-t|--totals     		Display a total for each week.

	END
}

sub MAIN(:after(:$a) is copy, :before(:$b) is copy, :totals(:$t)) {
	my %info;
	my $week = 0;
	my $sum = 0;

	if $a.defined  { $a  = qqx{date -d "$a"  '+%F'}.chomp; }
	if $b.defined { $b = qqx{date -d "$b" '+%F'}.chomp; }

	for $tsloc.IO.lines -> $l {
		#Split apart the line.
		my ($stat, $iso) = $l.split: ',';
		my $dt = DateTime.new: $iso;

		#Check if there are any limits.
		if $a.defined  { next unless $dt.Date > Date.new($a);  }
		if $b.defined { next unless $dt.Date < Date.new($b); }

		#Save the info.
		#say ($stat == 1 ?? "out: " !! "in:  ") ~ $dt.hh-mm-ss;
		%info{$dt.yyyy-mm-dd}[$stat] = $dt;
	}

	for %info.keys.sort -> $d {
		FIRST { $week = Date.new($d).week[1]; }
		my @t = %info{$d}<>;

		my $diff = @t[0,1]».defined.all
			?? sprintf("%.2f", (@t[1] - @t[0]) / 3600)
			!! "?.??";

		for @t[0,1] {
			$_ = .WHAT ~~ DateTime
				?? sprintf("%02d:%02d", .hour, .minute)
				!! "??:??";
		}

		($d, |@t, $diff).join(',').say;

		if $t {
			$sum += $diff unless $diff ~~ /\?+/;
			if ($week != Date.new($d).week[1]) {
				++$week;
				say "Week $week: $sum";
				$sum = 0;
			}
		}
	}
}
