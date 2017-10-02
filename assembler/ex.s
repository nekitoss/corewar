.name "11##311"
.comment "##"
		
l2:	sti	r1,%:live,%0
	and	r1,%0,r1
live:	#dfg  live	%1
	live %:live
	live %:live
	live %:live
	zjmp	%:live
	sti r1,%:live,%0
	sti r1,%:liv1,%0
	live %:liv1
	live %:liv1
	live %:liv1###
	##
liv1:
	sti r1,%:live,%0
