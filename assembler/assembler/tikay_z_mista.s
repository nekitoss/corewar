.comment"Tikay z mista"
.name"Vam vsim pizda"
lb1:
	aff		r1
	fork	%:lb1
	live 	%:lb1
	zjmp	%:lb1

