.model small
.stack 100h
.data
.code 

SoundBreak proc near
        mov     al, 182         
        out     43h, al         
        mov     ax, 2551		
                                
        out     42h, al         
        mov     al, ah          
        out     42h, al 
        in      al, 61h         
                                
        or      al, 00000011b   
        out     61h, al         
        mov     bx, 5      
.pause1:
        mov     cx, 1400
.pause2:
        dec     cx
        jne     .pause2
        dec     bx
        jne     .pause1
       
        mov     ax, 1207		
                                
        out     42h, al         
        mov     al, ah          
        out     42h, al 
        in      al, 61h         
                                
        or      al, 00000011b   
        out     61h, al         
        mov     bx, 5         
.pause11:
        mov     cx, 1300
.pause22:
        dec     cx
        jne     .pause22
        dec     bx
        jne     .pause11
        
        in      al, 61h        
                               
        and     al, 11111100b  
        out     61h, al      
        
        ret
SoundBreak endp   
        
