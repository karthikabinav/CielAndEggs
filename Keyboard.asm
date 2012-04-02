.model small
.stack 100h

.data

key db 'b'
pixel_row dw 1
pixel_col dw 2 dup(1)
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
    
    check:
        mov ah,01h
        mov al,00h
        int 16h
        
        
        DrawPixel 0100b 
    
    jnz check

    ;Get keystroke from keyboard
    mov ah,00h
    mov al,0h
    int 16h

    mov key,al
    call printChar

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


end START
