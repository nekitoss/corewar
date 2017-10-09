.name "zork"
.comment "I'M ALIIIIVE"

l2:		
		ld -3,r0
		sti	r1,%-45,%-1
		and r10, %0, r1
live:
		live %:live
		zjmp %:live
