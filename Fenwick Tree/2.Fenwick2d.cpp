t e m p l a t e   < t y p e n a m e   T >  
 c l a s s   f e n w i c k 2 d  
 {  
 p u b l i c :  
         v e c t o r <   v e c t o r < T >   >   f e n w ;  
         i n t   n ,   m ;  
         f e n w i c k 2 d ( i n t   _ n ,   i n t   _ m )   :   n ( _ n ) ,   m ( _ m )  
         {  
                 f e n w . r e s i z e ( n ) ;  
                 f o r   ( i n t   i   =   0 ;   i   <   n ;   i + + )  
                 {  
                         f e n w [ i ] . r e s i z e ( m ) ;  
                 }  
         }  
         i n l i n e   v o i d   m o d i f y ( i n t   i ,   i n t   j ,   T   v )  
         {  
                 i n t   x   =   i ;  
                 w h i l e   ( x   <   n )  
                 {  
                         i n t   y   =   j ;  
                         w h i l e   ( y   <   m )  
                         {  
                                 f e n w [ x ] [ y ]   + =   v ;  
                                 y   | =   ( y   +   1 ) ;  
                         }  
                         x   | =   ( x   +   1 ) ;  
                 }  
         }  
         i n l i n e   T   g e t ( i n t   i ,   i n t   j )  
         {  
                 T   v { } ;  
                 i n t   x   =   i ;  
                 w h i l e   ( x   > =   0 )  
                 {  
                         i n t   y   =   j ;  
                         w h i l e   ( y   > =   0 )  
                         {  
                                 v   + =   f e n w [ x ] [ y ] ;  
                                 y   =   ( y   &   ( y   +   1 ) )   -   1 ;  
                         }  
                         x   =   ( x   &   ( x   +   1 ) )   -   1 ;  
                 }  
                 r e t u r n   v ;  
         }  
 } ; 