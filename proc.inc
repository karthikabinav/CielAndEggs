.model small
.stack 100h
include ..\CIELAN~1\DATA.INC
.data
.code

comment/*
    Procedure to move the egg down by one pixel from (egg_x,egg_y)
/*
movEgg proc near
    
    inc egg_y[bx]
    mov egg_color[bx],1111b
    call drawEgg
    
    dec egg_y[bx]
    mov egg_color[bx] ,0000b
    call drawEgg
    
    inc egg_y[bx]
    mov egg_color[bx],1111b
    call drawEgg

    ret
    
movEgg endp

comment/*
    Prints single character on the screen
    Requires the character to be present in variable 'key'
/*
printChar proc near
        
    mov dl,key
    mov dh,0
    mov ah,2 
    int 21h 
    
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
        ret
move_right endp

comment/*
    Procedure to draw the egg from (egg_x,egg_y)
    Requires egg_x,egg_y to be set to the top left coordinates of the egg
    Requires egg_file to have absolute path of the file having the egg shape
/*
drawEgg proc near
    
    mov dx,egg_x[bx]
    mov top_x,dx

    mov dx,egg_y[bx]
    mov top_y,dx

    mov dl,egg_color[bx]
    mov color,dl
    
    mov dx,offset egg_file
    call singleColorDraw

    ret
drawEgg endp

comment/*
    Procedure to draw the Basket from (basket_x,basket_y)
    Requires basket_x,basket_y to be set to the top left coordinates of the basket
    Requires basket_file to have absolute path of the file having the basket shape
/*
drawBasket proc near
        
      mov dx,basket_x
      mov top_x,dx
      

      mov dx,basket_y
      mov top_y,dx
    
      mov dl,basket_color
      mov color,dl
    
      mov dx,offset basket_file
      call singleColorDraw

      ret
drawBasket endp

comment/*
    Detects if the egg has fallen down
/*
detect_broken_egg proc near
    cmp egg_y[bx],190
        jne beret_
    inc broken_eggs
    dec score
    mov current_eggs[bx],0
    mov dx,1

    beret_:
        ret
detect_broken_egg endp

comment/*
    Detects if the egg collided with the basket
/*
detect_collision proc near
        
    mov dx,egg_y[bx]
    add dx,8

    mov al,0
    mov ah,0Dh
    mov cx,egg_x[bx]
    add cx,5
    int 10h
        
    cmp al,1010b
        jne collisionret_
        mov dx,1
        mov current_eggs[bx],0

    collisionret_:
        ret
detect_collision endp
    
comment/*
    Generates a random number from 0 to 3. Uses the system time for generation
    Return : bx has the generated random number
/*
generateRandomNumber proc near
  
    mov al,0
    mov ah,2Ch
    int 21h

    mov dh,0
    add dx,1
    mov ax,dx
    mov dx,0

    mov cx,4
    div cx
        
    mov bx,dx
        
    ret
generateRandomNumber endp

comment/*
    Prints the string on the screen
    Requires dx to have the effective adress of the string to be printed
/*
printString proc near

    mov ah , 09h
    int 21h
    
    ret
printString endp

comment/*
    Increments score by 1 and updates the score display on the screen
/*
updateScores proc near
    inc score
    mov_cursor 0,0
    lea dx,score_text
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

    ret
updateScores endp

comment/*
    Reads from file dx and draws from (top_x,top_y)
    Requires color to be set to the pixel color to be drawn
/*
singleColorDraw proc near
    mov bx,top_x
    mov pixel_col,bx
    
    inc pixel_col
    mov bx, top_y
    mov pixel_row,bx

        
    mov al,0        
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
            
    DrawPixel
    jmp cont
    newline:
    cmp dx,10
    jne cont
                
    mov dx,top_x
    mov pixel_col,dx
    inc pixel_row

    cont:
    inc pixel_col
    cmp ax,0
    jne read
    
    ret_:
    mov al,0
    mov ah,3Eh
    int 21h

    ret
singleColorDraw endp

selectRandomHen proc near
    call generateRandomNumber
    
    zero:
        cmp bx,0
            jne one
            mov egg_x[0],5
            mov egg_y[0],80
            mov current_eggs[0],1
            jmp endSwitch
    one:
        cmp bx,1
            jne two
            mov egg_x[1],270
            mov egg_y[1],80
            mov current_eggs[1],1
            jmp endSwitch
    two:
        cmp bx,2
            jne three
            mov egg_x[2],50
            mov egg_y[2],130
            mov current_eggs[2],1
            jmp endSwitch
    
    three:
        cmp bx,3
            jne endSwitch
            mov egg_x[3],200
            mov egg_y[3],130
            mov current_eggs[3],1
            
    endSwitch:
        ret

selectRandomHen endp

newEgg proc near
    inc frequency
    cmp frequency,5
        jne doNothing
        mov frequency,0
        
        call selectRandomHen
        

    doNothing:
        ret
newEgg endp
