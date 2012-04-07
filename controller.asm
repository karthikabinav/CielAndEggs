.model small
.stack 100h
include ..\CIELAN~1\PROC.inc

.data


.code
START:

    mov ax,@data
    mov ds,ax
    mov es,ax

    mov al,13h
    mov ah,0
    int 10h
   
    dec score
    call updateScores
  Polling:  
    call detect_collision
    call detect_broken_egg
    cmp dx,1
        jne no_collide
    call updateScores

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
            jne mod10
        mov cycle,0
   
    mod10:
    mov al,0h
    mov ah,01h
    int 16h

    jz Polling
    
    mov ah,0h
    mov al,0h
    int 16h
    
    left:
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
    

    
end START
