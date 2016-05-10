; comentário
FLAG: EQU 1
MOD_B: begin
SECTION TExT
A: EXTern
l1: EXTERN
PUBLIC R
PUBLIC MOD_B
LOADD A
LOAD A
MUL B
STORE R
DIV DOIS
lol: store R +     1
JMP L1
COPY Y, R
copy y, R
copy y,    r 
IF FLAG
JMP LOL+2
L3: SPACE 1
		DIV		DOIS

SECTION			 DATA
R: SPACE 2
Y: SPACE 1
DOIS: CONST 2
ADD DOIS
END
