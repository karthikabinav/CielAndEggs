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

.code
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
    call detect_broken_egg
    cmp dx,1
        jne no_collide
        inc score
        mov p_x,0
        mov p_y,0
        mov cx,score
        call printNumber

        mov p_x,1
        mov p_y,0
        mov cx,broken_eggs
        call printNumber

        mov egg_color ,0000b
        call drawEgg
        call drawBasket    
        
        call generateRandomNumber
        mov egg_x,dx

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
    
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
   ; Split here into a new file if possible
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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
        
        mov dl,key
        mov dh,0
        mov ah,2 
        int 21h 
        ret

    printChar endp
    
    printNumber proc near
        mov ax,cx
        mov cx,10
        mov bx,0
  
      
        store_into_stack:          
            mov dx, 0
            div cx   
            
            add dx, '0'
            push dx
    
            inc bx
    
            cmp ax, 0                       
                jnz store_into_stack

            
    
            mov_cursor p_x,p_y             
            print_from_stack:
                pop dx
                mov ah,2 
                int 21h  
        
                dec bx
                cmp bx,0
                jnz print_from_stack 
        


        ret
    printNumber endp

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
    detect_broken_egg proc near
        cmp egg_y,190
            jne beret_
            inc broken_eggs
            dec score
            mov dx,1

        beret_:
            
            ret


    detect_broken_egg endp
    detect_collision proc near
        
        mov dx,egg_y
        add dx,8

        mov al,0
        mov ah,0Dh
        mov cx,egg_x
        add cx,5
        int 10h
        
        cmp al,1010b
            jne collisionret_
            mov dx,1
        
        collisionret_:
            ret
    detect_collision endp
    
    ;dx has random number from 1 to 300
    generateRandomNumber proc near
       
    
        mov al,0
        mov ah,2Ch
        int 21h

        mov dh,0
       
        add dx,1
        mov ax,dx
        mov dx,0

        mov cx,300
        div cx
        
        add dx,1
        
        ret
    generateRandomNumber endp

end START
