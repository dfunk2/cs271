@8192	 
D=A
@MAX  			                
M=D

@0
D=A
@i			
M=D

//LOOP
@KBD					            
D=M
@WHITE		        
D;JEQ   

(BLACK) 
@MAX
D=M
@i
D=D-M
@LOOP
D;JLE


@i
D=M
@SCREEN  
A=D+A 		//i+screen 
M=-1		//set screen to -1

@i			//incrementing i
D=M
D=D+1
@i
M=D

@LOOP
0;JMP

@WHITE     //WHITE
D=M
@i 			
D=M
@SCREEN
A=D+A 
M=0 

@i
D=M
@LOOP
D;JLE  

D=D-1
@i
M=D

@LOOP
0;JMP



