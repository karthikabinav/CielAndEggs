.model small
.stack 100h
include ..\CIELAN~1\DATA.INC
.data
.code

comment/*
    Prints single character on the screen
    Requires the character to be present in variable 'key'
/*
printChar proc near
        
    mov dl,key
    mov dh,0
    mov ah,2 
    int 21h 
    
    mov bx,counter
    ret

printChar endp

comment /*
    Prints the number in decimal form on the screen
    Requires cx to have the number to be printed
    Requires p_x,p_y to have the coordinates where it has to be printed
/*
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
        
        mov bx,counter
        ret
printNumber endp

comment/*
    Procedure to move the basket coordinates to the left
/*
move_left proc near
        
    cmp basket_x,0
        jle lret_
    sub basket_x,5
    lret_:
        mov bx,counter
        ret
move_left endp

comment/*
    Procedure to move basket coordinates to the right
/*
move_right proc near
    cmp basket_x,300
        jge rret_

    add basket_x,5
    rret_:
        mov bx,counter
        ret
move_right endp

comment/*
    Detects if the egg has fallen down
/*
detect_broken_egg proc near
    cmp cur_y,190
        jne beret_
    
    cmp egg_color[bx],0100b
        jne not_poison
        dec broken_eggs
        inc score

    not_poison:
    inc broken_eggs
    dec score
    mov current_eggs[bx],0
    mov dx,1
    
    cmp egg_color[bx],1110b
        jne beret_
        dec score
    beret_:
        mov bx,counter
        ret
detect_broken_egg endp

comment/*
    Detects if the egg collided with the basket
/*
detect_collision proc near
        
    mov dx,cur_y
    add dx,8
    
    push bx
    mov al,0
    mov ah,0Dh
    mov cx,cur_x
    add cx,5
    int 10h
    pop bx

    cmp al,1010b
        jne collisionret_
        mov dx,1
        mov current_eggs[bx],0
   cmp egg_color[bx],0100b
        jne collisionret_
        cmp score,0
            je gameover
        dec score
        jmp collisionret_
        gameover:
            mov game_over,1
    collisionret_:
        mov bx,counter
        ret
detect_collision endp
    
comment/*
    Generates a random number from 0 to 3. Uses the system time for generation
    Return : dx has the generated random number
/*
generateRandomNumber proc near
     
    mov al,0
    mov ah,2cH
    int 21h

    add dh,cl
    add dl,dh
    mov dh,0
    mov ax,dx
    mov dx,0
    
    mov cx,4
    div cx
    
    ret
generateRandomNumber endp

comment/*
    Prints the string on the screen
    Requires dx to have the effective adress of the string to be printed
/*
printString proc near

    mov ah , 09h
    int 21h
    
    mov bx,counter
    ret
printString endp

comment/*
    Increments score by 1 and updates the score display on the screen
/*
updateScores proc near
    inc score
    cmp egg_color[bx],1110b
        jne checkPoison
        inc score
    checkPoison:
        cmp egg_color[bx],0100b
            jne normalEgg
            dec score
    normalEgg:
    mov_cursor 0,0
    lea dx,score_text
    call printString    
    
    ;Clearing the next 5 pixels
    mov_cursor 0,8
    lea dx,space
    call printString
   
    mov p_x,0
    mov p_y,8
    mov cx,score
    call printNumber
        
    mov_cursor 1,0
    lea dx,broken_eggs_text
    call printString    

    mov p_x,1
    mov p_y,25
    mov cx,broken_eggs
    call printNumber
    
    cmp broken_eggs,7 ; 7 broken eggs and game over
        jne notGameOver
        mov game_over,1
    notGameOver:
    mov bx,counter
    ret
updateScores endp

comment/*
    Selects a random hen and random egg type
/*
selectRandomHen proc near
    used:
        call generateRandomNumber
        mov ax,dx
        mov dx,0
        mov cx,2
        mul cx
        mov bx,ax
    cmp current_eggs[bx],1
        je used
       
    same:
       call generateRandomNumber
       mov ax,dx
       mov cx,2
       mul cx
       mov dx,ax
       cmp dx,bx
            je same

        cmp dx,0
            jne rand_one
            mov egg_color[bx],1111b
            jmp zero
    rand_one:
        cmp dx,2
            jne rand_two
            mov egg_color[bx],0100b
            jmp zero
    rand_two:
        cmp dx,4
            jne rand_three
            mov egg_color[bx],1110b
            jmp zero
    rand_three:
        mov egg_color[bx],1111b

    zero:
        cmp bx,0
            jne one
            mov egg_x[0],50
            mov egg_y[0],50
            mov current_eggs[0],1
            jmp endSwitch
    one:
        cmp bx,2
            jne two
            mov egg_x[2],170
            mov egg_y[2],50
            mov current_eggs[2],1
            jmp endSwitch
    two:
        cmp bx,4
            jne three
            mov egg_x[4],110
            mov egg_y[4],80
            mov current_eggs[4],1
            jmp endSwitch
    
    three:
        cmp bx,6
            mov egg_x[6],230
            mov egg_y[6],80
            mov current_eggs[6],1
            
    endSwitch:
        mov bx,counter
        ret

selectRandomHen endp

comment/*
    Selects if a new egg has to be dropped based on frequency
/*
newEgg proc near
    inc frequency
    cmp score,50
        jle low_frequency
        mov cx,50
        jmp compare
    low_frequency:
    mov cx,100
    sub cx,score
    compare:
    cmp frequency,cx
        jne doNothing
        mov frequency,0
        
        mov bx,0
        sub bx,2
        checkIfAllDropped:
            add bx,2
            cmp bx,8
                jge doNothing
            cmp current_eggs[bx],0
                jne checkIfAllDropped

        call selectRandomHen
        

    doNothing:
        mov bx,counter
        ret
newEgg endp

comment/*
    moves egg[bx] attributes to cur attributes
/*
eggTocur proc near
    mov dx,egg_x[bx]
    mov cur_x,dx

    mov dx,egg_y[bx]
    mov cur_y,dx

    mov dx,egg_color[bx]
    mov cur_color,dx

    ret
eggTocur endp

comment/*
    moves cur attributes to egg[bx] attributes
/*
curToegg proc near
    mov dx,cur_x
    mov egg_x[bx],dx

    mov dx,cur_y
    mov egg_y[bx],dx

    mov dx,cur_color
    mov egg_color[bx],dx

    ret
curToegg endp
