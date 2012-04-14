.model small
.stack 100h
include ..\CIELAN~1\home.inc

.data


.code
START:

    mov ax,@data
    mov ds,ax
    mov es,ax

    mov al,13h
    mov ah,0
    int 10h
    
    call HomePage
    
    mov al,13h
    mov ah,0
    int 10h

    call drawAllHens
    dec score
    call updateScores
  Polling:  
    call initialiseCursor
    ;call hideCursor
    mov bx,0
    sub bx,2
    checkAllEggs:
        add bx,2
        mov counter,bx
        call eggTocur 
        cmp bx,8
            jge no_collide
        cmp current_eggs[bx],1
            jne checkAllEggs
       
        call detect_collision
        call detect_broken_egg
        cmp dx,1
            jne no_collide
        call updateScores
        cmp game_over,1
            jge dummy_endOfGame
        
        mov cur_color ,0000b
        call drawEgg
        
        
    no_collide:    
        call drawBasket    
    
        cmp cycle,0
            jne noMoveEgg
        
        cmp bx,8
            jge end_moveAllEggs
            
        cmp current_eggs[bx],1
            jne checkAllEggs
            
            call movEgg
            call curToegg

            jmp checkAllEggs
        end_MoveAllEggs: 
        call newEgg
    noMoveEgg:
        inc cycle
        cmp cycle,10
            jne mod10
        mov cycle,0
    
        jmp end_dummy_Polling
        dummy_Polling:
            jmp Polling
        end_dummy_Polling:
    mod10:
    cmp is_mouse ,1
        je mouse
    
    mov al,0h
    mov ah,01h
    int 16h

    jz dummy_Polling    
    jnz end_dummy_endOfGame 
    mouse:
        call mouseMove
        jmp Polling 
    dummy_endOfGame:
        jmp endOfGame
    end_dummy_endOfGame:
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
    
    endOfGame:
    call GameOverScreen
    jmp DOS_MODE
    RETURN_CONTROL:
    mov al,13h
    mov ah,0
    int 10h
    
    DOS_MODE:
    mov ax,4c00h
    int 21h
    

    
end START
