entry:
	sti		r1, %:beegees_gen, %1
	sti		r1, %:beegees, %1

wall_prep:
	ld		%0, r2
	ld		%0, r16

wall:
	live	%4902343
	st		r2, -24

beegees_gen:
	live	%4239423
	ld		%0, r16

beegees:
	live	%3442302

cc_spawn:
	live	%4320423
	zjmp	%3
	fork	%:cc_spawn

cc4:
	live	%4329034
	fork	%:cc
cc4ld:

cc4l:
	live	%4930423	
