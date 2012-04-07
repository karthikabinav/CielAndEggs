.model small
.stack 100h
include d:\CIELAN~1\PROC.inc

.data


.code
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
    

    
end START
