.name "zork"
.comment "I'M ALIIIIVE"

l2:		
		ld 65535, r2
		sti	r1, %:live , %1
		and r10, %0, r1
live:
		live %1
		zjmp %:live
