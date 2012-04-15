.model small
.stack 100h
.data

.code 
SoundCatch proc near
		
        push ax
        push bx
        push cx
        push dx

        mov     al, 182         
        out     43h, al         
        mov     ax, 2482		
                                
        out     42h, al         
        mov     al, ah          
        out     42h, al 
        in      al, 61h         
                                
        or      al, 00000011b   
        out     61h, al         
        mov     bx, 8      
pause1:
        mov     cx, 3000
pause2:
        dec     cx
        jne     pause2
        dec     bx
        jne     pause1
       
        mov     ax, 3151		
                                
        out     42h, al         
        mov     al, ah          
        out     42h, al 
        in      al, 61h         
                                
        or      al, 00000011b   
        out     61h, al         
        mov     bx, 10         
pause11:
        mov     cx, 1500
pause22:
        dec     cx
        jne     pause22
        dec     bx
        jne     pause11
        
        in      al, 61h        
                               
        and     al, 11111100b  
        out     61h, al      
        
        pop dx
        pop cx
        pop bx
        pop ax

        ret
SoundCatch endp        
