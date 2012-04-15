.model small
.stack 300h
.data

;The variables used in the home page text
t1 dw 0
t2 dw 0
t3 dw 0
t4 dw 0 ;;; counter
input db 0

high_file db "..\CIELAN~1\high.txt$",0

key db 'b' 

high_text db "High Score: $"
paused_text db "Paused$"

broken_eggs_text db "Broken Eggs : $"
score_text db "Score : $"

pixel_row dw 1
pixel_col dw 1

hen_file db "..\CIELAN~1\DESIGN\hen.txt$",0
hen_x dw 100
hen_y dw 100

;Basket details
basket_color db 1010b
basket_file db "..\CIELAN~1\DESIGN\basket.txt$",0
basket_x dw 150
basket_y dw 190

sprite_file db "..\CIELAN~1\DESIGN\broken.txt$",0

file_handle dw ?
buffer dw ?
broken_eggs dw 0
score dw 10

gameOverText db "Game Over$"

;Egg details
egg_color dw 1111b,1111b,1111b,1111b
egg_file db "..\CIELAN~1\DESIGN\egg.txt$",0

cycle db 0
frequency dw 69
counter dw 0

space db "      $"
game_over db 0

egg_x dw 50,100,150,200 
egg_y dw 100,100,100,100
current_eggs dw 0,0,0,0

cur_x dw ?
cur_y dw ?
cur_color dw ?

top_x dw 0
top_y dw 0
color db 1111b

i dw 0

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
    
    mov ah,86h
    mov dx,ml
    mov cx,mh
    int 15h

endm
comment/*
    Draws a horizontal line on the screen
    @params: (row,col) , length_line
/*
DrawLineHorizontal macro row,col,length_line
   local line
     
    mov dx,row
    mov pixel_row,dx

    mov dx,col
    mov pixel_col,dx
    
    mov cx,length_line
    line:
        DrawPixel 1111b
        inc pixel_col
        loop line
    
endm

