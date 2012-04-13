.model small
.stack 100h
include ..\CIELAN~1\PROC.INC
.data
.code

comment/*
    Procedure to move the egg down by one pixel from (egg_x,egg_y)
/*
movEgg proc near
    
    inc cur_y
    mov cx,egg_color[bx]
    mov cur_color,cx
    call drawEgg
    
    dec cur_y
    mov cur_color ,0000b
    call drawEgg
    
    inc cur_y
    mov cx,egg_color[bx]
    mov cur_color,cx
    call drawEgg

    mov bx,counter
    ret
    
movEgg endp

comment/*
    Procedure to draw the egg from (egg_x,egg_y)
    Requires egg_x,egg_y to be set to the top left coordinates of the egg
    Requires egg_file to have absolute path of the file having the egg shape
/*
drawEgg proc near
    
    mov dx,cur_x
    mov top_x,dx

    mov dx,cur_y
    mov top_y,dx

    mov dx,cur_color
    mov color,dl
    
    mov dx,offset egg_file
    call singleColorDraw
    
    mov bx,counter
    ret
drawEgg endp

comment/*
    Procedure to draw the Hen from (hen_x,hen_y)
    Requires hen_x,hen_y to be set to the top left coordinates of the egg
    Requires hen_file to have absolute path of the file having the hen shape
/*
drawHen proc near
    
    mov dx,hen_x
    mov top_x,dx

    mov dx,hen_y
    mov top_y,dx

    mov dx,1010b
    mov color,dl
    
    mov dx,offset hen_file
    call singleColorDraw
    
    mov bx,counter
    ret
drawHen endp

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
        
      mov bx,counter
      ret
drawBasket endp

comment/*
    Reads from file dx and draws from (top_x,top_y)
    Requires color to be set to the pixel color to be drawn
/*
singleColorDraw proc near
    mov cx,top_x
    mov pixel_col,cx
    
    inc pixel_col
    mov cx, top_y
    mov pixel_row,cx
            
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

    mov bx,counter
    ret
singleColorDraw endp

comment/*
    Procedure to draw the Hen from (hen_x,hen_y)
    Requires hen_x,hen_y to be set to the top left coordinates of the egg
    Requires hen_file to have absolute path of the file having the hen shape
/*
drawAllHens proc near
    
    mov hen_x,45
    mov hen_y,25
    mov dx,offset hen_file
    
    call drawHen
    
    mov hen_x,145
    mov hen_y,25
    mov dx,offset hen_file
    
    call drawHen

    mov hen_x,95
    mov hen_y,55
    mov dx,offset hen_file
    
    call drawHen

    mov hen_x,195
    mov hen_y,55
    mov dx,offset hen_file
    
    call drawHen

       
    mov bx,counter
    ret
drawAllHens endp

