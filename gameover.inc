.model small
.stack 100h
include ..\CIELAN~1\home.inc
.data
.code

GameOverScreen proc near
	mov al,13h
	mov ah,0
	int 10h
	

	mov ax, 0600h
	mov bh, 4fh
	mov cx, 0010h	
	mov dx, 184fh
	int 10h


mov al,0101b
;;;;;;;;;;;;G;;;;;;;;;;
	mov t1,70
	mov t2,100
	mov t3,40
	mov t4,0
	call drawvertical
	
	mov t1,40
	mov t2,70
	mov t3,70
	mov t4,0
	call drawhorizontal
	
	mov t1,40
	mov t2,60
	mov t3,97
	mov t4,0
	call drawhorizontal
	
	mov t1,85
	mov t2,100 
	mov t3,57
	mov t4,0
	call drawvertical
	
	mov t1,60
	mov t2,70
	mov t3,85
	mov t4,0
	call drawhorizontal
	
	mov t1,85
	mov t2,100
	mov t3,67
	mov t4,0
	call drawvertical
	
	;;;;;;;;A;;;;;;;;
	mov t1,70
	mov t2,100
	mov t3,73
	mov t4,0
	call drawvertical
	mov t3,93
	mov t4,0
	call drawvertical
	mov t1,73
	mov t2,93
	mov t3,70
	mov t4,0
	call drawhorizontal
	mov t1,78
	mov t2,87
	mov t3,84
	mov t4,0
	call drawhorizontal
	
	;;;;;;;;;;;;;;;;;;M;;;;;;;;;;;
	mov t1,70
	mov t2,100
	mov t3,100
	mov t4,0
	call drawvertical
	
	mov t1,70
	mov t2,85
	mov t3,100
	call cross
	inc t3
	call cross
	inc t3
	call cross
	inc t3 
	call cross
	
	mov t3,130
	call revcross
	inc t3
	call revcross
	inc t3
	call revcross
	inc t3
	call revcross
	
	mov t3,130
	mov t2,100
	mov t4,0
	call drawvertical
	
	

	;;;;;;;;;;;E;;;;;;;;;;;
	mov t3,136
	mov t4,0
	call drawvertical
	
	mov t1,136
	mov t2,156
	mov t3,70
	mov t4,0
	call drawhorizontal
	mov t3,97
	mov t4,0
	call drawhorizontal
	mov t3,84
	mov t2,148
	mov t4,0
	call drawhorizontal


mov al,0001b
	;;;;;;;;;;;O;;;;;;;;;;;;;;
	mov t1,70
	mov t2,100
	mov t3,170
	mov t4,0
	call drawvertical
	mov t3,190
	mov t4,0
	call drawvertical
	mov t1,170
	mov t2,190
	mov t3,70
	mov t4,0
	call drawhorizontal
	mov t3,97
	mov t4,0
	call drawhorizontal
	;;;;;;;;;V;;;;;;;;
	mov t1,70
	mov t2,88
	mov t3,200
	mov t4,0
	call drawvertical
	
	mov t1,88
	mov t2,100
	mov t3,200
	call cross
	inc t3
	call cross
	inc t3 
	call cross
	inc t3 
	call cross
	
	mov t3,224
	call revcross
	inc t3 
	call revcross
	inc t3 
	call revcross
	inc t3
	call revcross
	
	mov t1,70
	mov t2,88
	mov t3,224
	mov t4,0
	call drawvertical
	
    ;;;E;;;;;;;;;;
    
	mov t1,70
	mov t2,100
	mov t3,232
	mov t4,0
	call drawvertical
		
	mov t1,232
	mov t2,252
	mov t3,70
	mov t4,0
	call drawhorizontal
	mov t3,97
	mov t4,0
	call drawhorizontal
	mov t3,84
	mov t4,0
	mov t2,246
	call drawhorizontal
	
;;;;;;;;;;R;;;;;;;;;;;;;;;	
	mov t1,70
	mov t2,100
	mov t3,259
	mov t4,0
	call drawvertical
	mov t3,274
	mov t2,85
	mov t4,0
	call drawvertical
	mov t1,259
	mov t2,274
	mov t3,70
	mov t4,0
	call drawhorizontal
	mov t4,0
	mov t3,82
	call drawhorizontal
	mov t1,85
	mov t2,100
	mov t3,259
	call cross
	inc t3
	call cross
	inc t3
	call cross
	inc t3 
	call cross
    
    ret

GameOverScreen endp
