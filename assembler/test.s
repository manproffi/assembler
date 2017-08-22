.name           "42"
.comment        "Just a basic Winner Program"

libe:	live	%42		# entree
	ld	%0,r5
	ld	%0,r5
	zjmp	%:t

tir:	sti	r1,%:libe,%1
	ld	%2304,r10
	ld	%1,r5
	ld	%0,r11

	ld	%4,r3

