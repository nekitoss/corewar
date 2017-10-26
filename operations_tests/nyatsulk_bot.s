.name "nyatsulk_bot"
.comment "I will live forever"


l1:		sti r2, %0, %1
		ld 1, r2
		st r2, r6
		st r6, 900
		fork %5

live:	live %1
		ld %2, r4
		st r4, r5
		zjmp %:live
		ld %2, r4
		st r4, r5
		ld %1, r1
		ld %1, r2
		sub r1, r2, r3
		zjmp %-2222

# start:	live %0
# 		ld %7, r1
# 		ld %514, r2
# 		fork %555
# 		live %1
# 		st r1, 100
# 		ld %1, r1
# 		live %0
# 		ld %-1, r2
# 		add r1, r2, r3
# 		st r3, 100
# 		zjmp %-15 
# 		sti r1, %15, r2
# 		and r2, %1, r1
# 		zjmp %:end


# end:	live %0
# 		sti r2, %-20, r1
# 		fork %-130
# 		add r1, r2, r3
# 		ld -13, r1
# 		zjmp %:st
# 		live %0
# 		zjmp %:st

# st:		ld %1, r1
# 		live %0
# 		st r1, -450
# 		st r1, -451
# 		st r1, -452
# 		st r1, -453
# 		st r1, -454
# 		st r1, -455
# 		st r1, -456
# 		st r1, r2

			


# start:
# 	ld		%55576069, r6
# 	ld		%4, r5
# 	fork	%:core
# 	fork	%:prep
# 	zjmp	%:core
# wall:
# 	st		r2, -450
# 	st		r2, -451
# 	st		r2, -452
# 	st		r2, -453
# 	st		r2, -454
# 	st		r2, -455
# 	st		r2, -456
# 	st		r2, -457
# 	st		r2, -458
# 	st		r2, -459
# 	st		r2, -460
# 	st		r2, -461
# 	st		r2, -462
# 	st		r2, -463
# 	st		r2, -464
# 	st		r2, -465
# 	st		r2, -466
# 	st		r2, -467
# 	st		r2, -468
# 	st		r2, -469
# 	st		r2, -470
# 	st		r2, -471
# 	st		r2, -472
# 	st		r2, -473
# 	st		r2, -474
# 	st		r2, -475
# 	st		r2, -476
# 	st		r2, -477
# 	st		r2, -478
# 	st		r2, -479
# 	st		r2, -480
# 	st		r2, -481
# 	st		r2, -482
# 	st		r2, -483
# 	st		r2, -484
# 	st		r2, -485
# 	st		r2, -486
# 	st		r2, -487
# 	st		r2, -488
# 	zjmp	%:survive
# core:
# 	st		r1, 6
# 	live	%0
# 	fork	%:survive
# 	fork	%:core
# 	zjmp	%:wall
# prep:
# 	st		r1, 32
# 	st		r1, 32
# 	st		r1, 32
# 	st		r1, 32
# 	st		r1, 32
# 	fork	%:imp
# 	zjmp	%:survive
# survive:
# 	live	%0
# 	live	%0
# 	live	%0
# 	live	%0
# 	live	%0
# 	zjmp	%:wall
# imp:
# 	fork	%:imp
# 	st		r6, r5
