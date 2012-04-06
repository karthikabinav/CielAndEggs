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

broken_eggs dw,0
score dw ,0

;Egg details
egg_color db 1111b
egg_file db "d:\egg.txt",0

cycle db 0
egg_x dw 100
egg_y dw 100


cur_x dw 50
cur_y dw 300

.code

mov_cursor macro row,col 
    mov dh, row
    mov dl, col
    mov bh, 0
    mov ah, 2
    int 10h
    
    
endm

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
START:

    mov ax,@data
    mov ds,ax
    mov es,ax

    ;Set Graphics mode
    mov al,13h
    mov ah,0
    int 10h
   
  Polling:  
    call detect_collision
    cmp dx,1
        jne no_collide
        mov egg_color ,0000b
        call drawEgg
        call drawBasket    
        
        mov egg_y,100
        jmp Polling
    no_collide:    
    call drawBasket    
    
    cmp cycle,0
        jne noMoveEgg
    call movEgg
    noMoveEgg:
    inc cycle
    cmp cycle,10
        jne mod3
        mov cycle,0
    mod3:
    mov al,0h
    mov ah,01h
    int 16h

    jz polling
    
    ;Get keystroke from keyboard
    mov ah,0h
    mov al,0h
    int 16h
    
    mov key,al
    cmp key,'a'
        jne right


        mov basket_color , 0000b
        call drawBasket
        call move_left
        mov basket_color ,1010b
        
        
        jmp Polling
    right:
        cmp key,'d'
            jne exit
            
            mov basket_color , 0000b
            call drawBasket
            call move_right
            mov basket_color ,1010b
                        
            jmp Polling
    exit:
        cmp key,'x'
            je RETURN_CONTROL
    
            jmp Polling

    RETURN_CONTROL:
    mov ax,4c00h
    int 21h

    movEgg proc near
        egg_draw: 
        inc egg_y
        mov egg_color,1111b
            call drawEgg
    
        dec egg_y
        mov egg_color ,0000b
        call drawEgg
        inc egg_y
        mov egg_color,1111b
        call drawEgg

        ret
    end_egg_draw:


    movEgg endp
    printChar proc near
        
        mov_cursor 10,10

        mov dx,key
        mov ah,2 
        int 21h 
        ret

    printChar endp

    move_left proc near
        
        cmp basket_x,0
            jle lret_
        sub basket_x,5
        lret_:
        ret
    move_left endp

    move_right proc near
        cmp basket_x,300
            jge rret_

        add basket_x,5
        rret_:
        ret
    move_right endp
    
    drawEgg proc near
        
        mov dx,egg_x
        mov pixel_col,dx
        
        mov dx, egg_y
        mov pixel_row,dx
        
        inc pixel_col
        ;Open the file
        mov al,0        
        mov dx,offset egg_file
        mov ah,3dh
        int 21h
        
        jc eggret_
        mov file_handle,ax
        
        

        eggread:
            mov bx,file_handle    
            mov dx,offset buffer
            mov al,0
            mov cx,1
            mov ah,3Fh
            int 21h

            mov dx,buffer 
            cmp dx,'1'
                jne eggnewline
            
            
            
            DrawPixel egg_color

            jmp eggcont
            eggnewline:
                cmp dx,10
                    jne eggcont
                
                mov dx,egg_x
                mov pixel_col,dx
                inc pixel_row

            eggcont:
            inc pixel_col
            cmp ax,0
                jne eggread
        

        eggret_:
        ;Close the file
        mov al,0
        mov ah,3Eh
        int 21h

        ret




    drawEgg endp

    drawBasket proc near
        
        mov dx,basket_x
        mov pixel_col,dx
        
        mov dx, basket_y
        mov pixel_row,dx

        ;Open the file
        mov al,0        
        mov dx,offset basket_file
        mov ah,3dh
        int 21h
        
        jc ret_
        mov file_handle,ax
        
        

        read:
            mov bx,file_handle    
            mov dx,offset buffer
            mov al,0
            mov cx,1
            mov ah,3Fh
            int 21h

            mov dx,buffer 
            cmp dx,'1'
                jne newline
            
            
            
            DrawPixel basket_color

            jmp cont
            newline:
                cmp dx,10
                    jne cont
                
                mov dx,basket_x
                mov pixel_col,dx
                inc pixel_row

            cont:
            inc pixel_col
            cmp ax,0
                jne read
        

        ret_:
        ;Close the file
        mov al,0
        mov ah,3Eh
        int 21h

        ret
    drawBasket endp
    
    detect_collision proc near
        
        mov dx,egg_y
        add dx,1

        mov al,0
        mov ah,0Dh
        mov cx,egg_x
        int 10h
        
        cmp al,1010b
            jne collisionret_
            mov dx,1
        
        collisionret_:
            ret
    detect_collision endp
end START
