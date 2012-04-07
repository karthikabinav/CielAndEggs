.model small
.stack 100h
include d:\CIELAN~1\DATA.INC

.data
.code
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
;Load effective adress of message into dx before the call
printString proc near

    mov ah , 09h
    int 21h
    
    ret
printString endp
