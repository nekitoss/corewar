.name "Vam vsim pizda"
.comment "Tikay z mista"
lb1: live	%1
	fork	%:lb1
	live 	%:lb1
	zjmp	%:lb1

