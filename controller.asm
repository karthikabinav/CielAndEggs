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
    mov bx,0
    dec bx
    checkAllEggs:
        inc bx
        mov counter,bx
        call eggTocur 
        cmp bx,4
            jge no_collide
        cmp current_eggs[bx],1
            jne checkAllEggs
       
        call detect_collision
        call detect_broken_egg
        cmp dx,1
            jne checkAllEggs
        call updateScores
       
        mov cur_color ,0000b
        call drawEgg
        
        call curToegg
        jmp checkAllEggs
        
    no_collide:    
        call drawBasket    
    
        cmp cycle,0
            jne noMoveEgg
        mov bx,0
        dec bx
        moveAllEggs:
            inc bx
            mov counter,bx
            call eggTocur
            cmp bx,4
                jge end_moveAllEggs
            
            cmp current_eggs[bx],1
                jne moveAllEggs
            
            call movEgg
            call curToegg

            jmp moveAllEggs
        end_MoveAllEggs: 
        call newEgg
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
