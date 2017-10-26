.name "lld_DR"
.comment "lld"

	live %1
	lld %2, r4
	st r4, 40
	zjmp %2900
	