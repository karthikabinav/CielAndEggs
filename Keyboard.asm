.model small
.stack 100h

.data

key db 'b'
pixel_row dw 1
pixel_col dw 1

basket_color db 1111b
basket_file db "d:\basket.txt",0
file_handle dw ?
buffer dw ?

basket_x dw 150
basket_y dw 190

cur_x dw 50
cur_y dw 300

.code

mov_cursor macro row,col 
    mov dh, row ; row number
    mov dl, col ; column numnber
    mov bh, 0 ; page number
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
        int 10h     ; Set the Pixel
        pop dx
        pop cx
        pop ax
endm


START:

    mov ax,@data
    mov ds,ax
    mov es,ax

    ; Set Graphics mode
    mov al,13h
    mov ah,0
    int 10h
    
  Polling:  
    call drawBasket    
    ;check:
        ;mov ah,01h
        ;mov al,00h
        ;int 16h
        
    ;jnz check

    ;Get keystroke from keyboard
    mov ah,00h
    mov al,0h
    int 16h

    mov key,al
    cmp key,'a'
        jne right


        mov basket_color , 0000b
        call drawBasket
        call move_left
        ;call printChar
        mov basket_color ,1111b
        
        
        jmp Polling
    right:
        cmp key,'d'
            jne exit
            
            mov basket_color , 0000b
            call drawBasket
            call move_right
            ;call printChar
            mov basket_color ,1111b
                        
            jmp Polling
    exit:
        cmp key,'x'
            je RETURN_CONTROL
    
            jmp Polling

    RETURN_CONTROL:
    mov ax,4c00h                            ; Return control back to the OS
    int 21h


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
        cmp basket_x,305
            jge rret_

        add basket_x,5
        rret_:
        ret
    move_right endp

    drawBasket proc near
        
        mov dx,basket_x
        mov pixel_col,dx
        
        mov dx, basket_y
        mov pixel_row,dx

        mov al,0        
        mov dx,offset basket_file
        mov ah,3dh
        int 21h
        
        jc ret_
        mov file_handle,ax ; file handle
        
        

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
        mov al,0
        mov ah,3Eh
        int 21h

        ret
    drawBasket endp

end START
