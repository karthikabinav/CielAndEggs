.model small
.stack 100h
.data
key db 'b' 

broken_eggs_text db "Number of Broken Eggs : $"
score_text db "Score : $"

pixel_row dw 1
pixel_col dw 1

;Basket details
basket_color db 1010b
basket_file db "..\CIELAN~1\basket.txt$",0
basket_x dw 150
basket_y dw 190

file_handle dw ?
buffer dw ?
broken_eggs dw 0
score dw 0

;Egg details
egg_color dw 1111b,1111b,1111b,1111b
egg_file db "..\CIELAN~1\egg.txt$",0

cycle db 0
frequency dw 129
counter dw 0

egg_x dw 50,100,150,200 
egg_y dw 100,100,100,100
current_eggs dw 0,0,0,0

top_x dw 0
top_y dw 0
color db 1111b

;Variables to store values of where to print
p_x db 0
p_y db 0

comment /*
    Macro to color a pixel
    requires pixel_row,pixel_col variables to be set to the coordinate to be colored
/*
DrawPixel macro 
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

comment/*
    Places the cursor at (row,col)
    @params : row,col
/*
mov_cursor macro row,col 
    mov dh, row ; row number
    mov dl, col ; column numnber
    mov bh, 0 ; page number
    mov ah, 2
    int 10h
    
    
endm

comment/*
    Delays the execution by mh:ml milliseconds
    @params : higher 16 bits of ms , lower 16 bits if ms
/*
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

