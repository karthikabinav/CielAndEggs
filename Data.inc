.model small
.stack 100h

.data


key db 'b' ;Holds the value of key pressed
pixel_row dw 1
pixel_col dw 1

;Basket details
basket_color db 1010b
basket_file db "d:\basket.txt",0
file_handle dw ?
buffer dw ?

basket_x dw 150
basket_y dw 190

broken_eggs dw 0
score dw 0

;Egg details
egg_color db 1111b
egg_file db "d:\egg.txt",0

cycle db 0,0,0,0,0
egg_x dw 50,100,150,200,250 ; Atmost 5 eggs can fall at a time
egg_y dw 100,100,100,100,100

;Variables to store values of where to print
p_x db 0
p_y db 0

DrawPixel macro color
        push ax
        push cx
        push dx
        mov al,color
        mov dx,pixel_row
        mov cx,pixel_col
        mov ah,0ch
        int 10h
        pop dx
        pop cx
        pop ax
endm

mov_cursor macro row,col 
    mov dh, row ; row number
    mov dl, col ; column numnber
    mov bh, 0 ; page number
    mov ah, 2
    int 10h
    
    
endm

;Params : microseconds as mh:ml
delay macro mh,ml
    push ax
    push cx
    push dx

    mov al,0
    mov ah,86h
    mov dx,ml
    mov cx,mh
    int 15h

    pop dx
    pop cx
    pop ax

endm

