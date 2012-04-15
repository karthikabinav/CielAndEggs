.model small
.stack 100h
include ..\CIELAN~1\STATIC.inc
.data
.code
HomePage proc near
	
    ;Set the Background Colour
    mov ax, 0600h
	mov bh, 4fh
	mov cx, 0010h	
	mov dx, 184fh
	int 10h

    ;C
	mov al,1010b
	mov t1,20
	mov t2,40
	mov t3,30
	mov t4,0
	call drawvertical
	
	mov t1,30
	mov t2,50
	mov t3,20
	mov t4,0
	call drawhorizontal
	
	mov t1,30
	mov t2,50
	mov t3,37
	mov t4,0	
	call drawhorizontal	
    
    ;I	
	mov al,0100b
	mov t1,20
	mov t2,40
	mov t3,55
	mov t4,0
	call  drawvertical
	
    ;E
	mov al,1110b
	mov t1,20
	mov t2,40
	mov t3,63
	mov t4,0
	call drawvertical
	
	mov t1,63
	mov t2,73
	mov t3,20
	mov t4,0
	call drawhorizontal

	mov t1,63
	mov t2,83
	mov t3,37
	mov t4,0
	call drawhorizontal

	mov t1,63
	mov t2,76
	mov t3,29
	mov t4,0
	call drawhorizontal
	
    ;L
	mov al,1111b
	mov t1,20
	mov t2,40
	mov t3,88
	mov t4,0
	call drawvertical

	mov t1,88
	mov t2,105
	mov t3,37
	mov t4,0
	call drawhorizontal	

    ;A
	mov al,1101b
	mov t1,20
	mov t2,40
	mov t3,120
	mov t4,0
	call drawvertical
	
	mov t1,120
	mov t2,135
	mov t3,20
	mov t4,0
	call drawhorizontal

	mov t1,20
	mov t2,40
	mov t3,135
	mov t4,0
	call drawvertical


	mov t1,125
	mov t2,131
	mov t3,30
	mov t4,0
	call drawhorizontal
	
    ;N
	mov al,0100b
	mov t1,20
	mov t2,40
	mov t3,144
	mov t4,0
	call drawvertical
	
	mov t1,22
	mov t2,37
	mov t3,144
	call cross
	inc t3
	call cross
	inc t3
	call cross
	inc t3 
	call cross

	mov t1,20
	mov t2,40
	mov t3,159
	mov t4,0
	call drawvertical	
    
    ;D
	mov al,0101b
	mov t1,20
	mov t2,40
	mov t3,167
	mov t4,0
	call drawvertical
	
	mov t1,168
	mov t2,183
	mov t3,20
	mov t4,0
	call drawhorizontal
	
	mov t1,24
	mov t2,36
	mov t3,183
	mov t4,0
	call drawvertical
	
	mov t1,168
	mov t2,183
	mov t3,37
	mov t4,0
	call drawhorizontal

    ;E
	mov al,0101b
	mov t1,20
	mov t2,40
	mov t3,197
	mov t4,0
	call drawvertical
	
	mov t1,197
	mov t2,207
	mov t3,20
	mov t4,0
	call drawhorizontal

	mov t1,197
	mov t2,217
	mov t3,37
	mov t4,0
	call drawhorizontal

	mov t1,197
	mov t2,213
	mov t3,29
	mov t4,0
	call drawhorizontal
    
    ;G
	mov al,0100b
	mov t1,20
	mov t2,40
	mov t3,221
	mov t4,0
	call drawvertical

	mov t1,221
	mov t2,232
	mov t3,37
	mov t4,0
	call drawhorizontal
	
	mov t1,221
	mov t2,240
	mov t3,20
	mov t4,0
	call drawhorizontal
	
	
	mov t1,30
	mov t2,40
	mov t3,232
	mov t4,0
	call drawvertical
	
	mov t1,228
	mov t2,242
	mov t3,30
	mov t4,0
	call drawhorizontal
	
	mov t1,30
	mov t2,40
	mov t3,239
	mov t4,0
	call drawvertical
    
    ;G
	mov al,1110b
	mov t1,20
	mov t2,40
	mov t3,246
	mov t4,0
	call drawvertical

	mov t1,246
	mov t2,257
	mov t3,37
	mov t4,0
	call drawhorizontal
	
	mov t1,246
	mov t2,265
	mov t3,20
	mov t4,0
	call drawhorizontal
	
	
	mov t1,30
	mov t2,40
	mov t3,257
	mov t4,0
	call drawvertical
	
	mov t1,253
	mov t2,267
	mov t3,30
	mov t4,0
	call drawhorizontal
	
	mov t1,30
	mov t2,40
	mov t3,264
	mov t4,0
	call drawvertical
    
    ;S
	mov al,1111b
	mov t1,20
	mov t2,33
	mov t3,271
	mov t4,0
	call drawvertical

	mov t1,271
	mov t2,287
	mov t3,30
	mov t4,0
	call drawhorizontal
	
	mov t1,271
	mov t2,287
	mov t3,37
	mov t4,0
	call drawhorizontal	
	
	mov t1,32
	mov t2,40
	mov t3,284
	mov t4,0
	call drawvertical
	
	mov t1,271
	mov t2,287
	mov t3,20
	mov t4,0
	call drawhorizontal
	
	mov al,1111b
	mov t4,0
	mov t1,65
	mov t2,114
	mov t3,30
loop1:
	call vertical
	inc t3
	inc t4
	cmp t4,100
	jle loop1
	
    ;1.play
	mov al,0010b
	
	mov t1,70
	mov t2,85
	mov t3,50
	mov t4,1
	call drawvertical
 
	mov t1,82
	mov t2,85
	mov t3,55
	mov t4,1
	call drawvertical
	
	mov t1,70
	mov t2,85
	mov t3,62
	mov t4,1
	call drawvertical
	
	mov t1,62
	mov t2,77
	mov t3,70
	mov t4,1
	call drawhorizontal
	
	mov t1,62
	mov t2,77
	mov t3,76
	mov t4,1
	call drawhorizontal
	
	mov t1,70
	mov t2,78
	mov t3,75
	mov t4,1
	call drawvertical
	
	mov t1,70
	mov t2,85
	mov t3,80
	mov t4,1
	call drawvertical
	
	mov t1,80
	mov t2,91
	mov t3,83
	mov t4,1
	call drawhorizontal
	
	mov t1,70
	mov t2,85
	mov t3,94
	mov t4,1
	call drawvertical
	
	mov t1,94
	mov t2,106
	mov t3,70
	mov t4,1
	call drawhorizontal
	
	mov t1,70
	mov t2,85
	mov t3,104
	mov t4,1
	call drawvertical
	
	mov t1,97
	mov t2,103
	mov t3,77
	mov t4,1
	call drawhorizontal
	
	mov t1,70
	mov t2,75
	mov t3,109
	mov t4,1
	call drawvertical
	
	mov t1,109
	mov t2,121
	mov t3,74
	mov t4,1
	call drawhorizontal
	
		
	mov t1,70
	mov t2,75
	mov t3,119
	mov t4,1
	call drawvertical

	mov t1,75
	mov t2,85
	mov t3,114
	mov t4,1
	call drawvertical
	
    ;exit
	mov al,0000b
	mov t1,95
	mov t2,104
	mov t3,47
	mov t4,1
	call drawvertical
	
	mov t1,34
	mov t2,48
	mov t3,95
	mov t4,1
	call drawhorizontal
	
	mov al,0000b
	mov t1,104
	mov t2,110
	mov t3,34
	mov t4,1
	call drawvertical
	mov t1,34
	mov t2,48
	mov t3,102
	mov t4,1
	call drawhorizontal
	
	mov t1,34
	mov t2,52
	mov t3,108
	mov t4,1
	call drawhorizontal
	
	mov t1,108
	mov t2,110
	mov t3,55
	mov t4,1
	call drawvertical
	
	mov t1,95
	mov t2,110
	mov t3,60
	mov t4,1
	call drawvertical
	
	mov t1,60
	mov t2,74
	mov t3,95
	mov t4,1
	call drawhorizontal
	mov t4,1
	mov t3,108
	call drawhorizontal
	mov t2,67
	mov t3,102
	mov t4,1
	call drawhorizontal
	
	mov t1,95
	mov t2,110
	mov t3,77
	call cross
	inc t3
	call cross
	inc t3
	call cross
	
	mov t1,95
	mov t2,110
	mov t3,92
	call revcross
	inc t3
	call revcross
	inc t3
	call revcross
	
	mov t1,95
	mov t2,110
	mov t3,98
	mov t4,1
	call drawvertical
	
	mov t1,104
	mov t2,118
	mov t3,95
	mov t4,1
	call drawhorizontal
	
	mov t1,95
	mov t2,110
	mov t3,110
	mov t4,1
	call drawvertical
	
    ;enjoy....
	mov al,0101b
	mov t1,140
	mov t2,170
	mov t3,50
	mov t4,0
	call drawvertical
	
	mov t1,50
	mov t2,80
	mov t3,140
	mov t4,0
	call drawhorizontal
	
	mov t1,50
	mov t2,70
	mov t3,154
	mov t4,0
	call drawhorizontal
	
	mov t1,50
	mov t2,80
	mov t3,167
	mov t4,0
	call drawhorizontal
	
	
	;N
	mov t1,140
	mov t2,170
	mov t3,83
	mov t4,0
	call drawvertical
	
	mov t1,144
	mov t2,168
	mov t3,83
	call cross
	inc t3
	call cross
	inc t3
	call cross
	inc t3 
	call cross
	inc t3 
	call cross

	mov t1,140
	mov t2,170
	mov t3,108
	mov t4,0
	call drawvertical
	
	mov t1,114
	mov t2,140
	mov t3,140
	mov t4,0
	call drawhorizontal
	
	mov t1,140
	mov t2,170
	mov t3,127
	mov t4,0
	call  drawvertical
	
	mov t1,160
	mov t2,170
	mov t3,117
	call cross
	inc t3
	call cross
	inc t3 
	call cross
	inc t3 
	call cross
	
	mov t1,140
	mov t2,170
	mov t3,143
	mov t4,0
	call drawvertical
	
	mov t1,143
	mov t2,160
	mov t3,140
	mov t4,0
	call drawhorizontal
	
	
	mov t1,143
	mov t2,160
	mov t3,167
	mov t4,0
	call drawhorizontal
	
	mov t1,140
	mov t2,170
	mov t3,160
	mov t4,0
	call drawvertical
	
	mov t1,140
	mov t2,155
	mov t3,169
	call cross
	inc t3
	call cross
	inc t3
	call cross
	inc t3 
	call cross
	
	mov t1,140
	mov t2,170
	mov t3,199
	call revcross
	inc t3
	call revcross
	inc t3
	call revcross
	inc t3 
	call revcross
	
	mov t1,166
	mov t2,170
	mov t3,196
	mov t4,0
	call drawvertical
	
	mov t1,166
	mov t2,170
	mov t3,202
	mov t4,0
	call drawvertical
	
	mov t1,166
	mov t2,170
	mov t3,208
	mov t4,0
	call drawvertical
	
	mov t1,166
	mov t2,170
	mov t3,214
	mov t4,0
	call drawvertical
	
	mov t1,166
	mov t2,170
	mov t3,220
	mov t4,0
	call drawvertical
	
;Take the Input
input1:
mov_cursor 50,50
mov ah,1
int 21h
cmp al,'1'
je game
cmp al,'2'
je game_exit
cmp al,'1'
jl input1
cmp al,'2'
jg input1

game: 
    ret
game_exit:
    
    mov al,13h
    mov ah,0
    int 10h

 	mov ax,4c00h
	int 21h
	
HomePage endp

vertical proc
    mov dx,t1
    mov bx,t2
    mov cx,t3
    
    vertical1:
	mov pixel_row,dx
    mov pixel_col,cx
    mov color,al
    DrawPixel
	inc dx
	cmp dx,bx
	jle vertical1
    ret
vertical endp

horizontal proc
    mov cx,t1
    mov bx,t2
    mov dx,t3
    horizontal1:
	mov pixel_row,dx
    mov pixel_col,cx
    mov color,al
    DrawPixel

	inc cx
	cmp cx,bx
	jle horizontal1
    ret
horizontal endp

cross proc
    mov dx,t1
    mov bx,t2
    mov cx,t3
cross1:
	mov pixel_row,dx
    mov pixel_col,cx
    mov color,al
    DrawPixel

	inc dx
	inc cx
	cmp dx,bx
	jle cross1

    ret
cross endp

drawvertical proc 
drawloop1:	
	call vertical
	inc t3
	inc t4
	cmp t4,3
	jle drawloop1
    ret
drawvertical endp

drawhorizontal proc
drawloop2:
	call horizontal
	inc t3
	inc t4
	cmp t4,3
	jle drawloop2
    ret
drawhorizontal endp

revcross proc
    mov dx,t1
    mov bx,t2
    mov cx,t3
    revcross1:
	    mov pixel_row,dx
        mov pixel_col,cx
        mov color,al
        DrawPixel

	inc dx
	dec cx
	cmp dx,bx
	jle revcross1
    ret
revcross endp

