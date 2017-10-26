.name "sub_RRR_no_zjmp"
.comment "sub"

	live %1
	ld %1, r1
	st r1, 100
	ld %-1, r2
	st r2, 100
	st r3, 100
	sub r1, r2, r3
	st r3, 100
	zjmp %-10
