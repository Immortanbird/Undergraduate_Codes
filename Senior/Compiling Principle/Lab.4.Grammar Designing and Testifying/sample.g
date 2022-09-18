grammar sample;

declaration
	:	TYPE Identifier initializer?;

initializer
	:	'=' postfixExpression;

expression//all expressions need following ;
	:	assignmentExpression;

assignmentExpression
	:   unaryExpression ('=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<=' | '>>=' | '&=' | '^=' | '|=') additiveExpression;

additiveExpression
	:	multiplicativeExpression ('+' multiplicativeExpression | '-' multiplicativeExpression)*;

multiplicativeExpression
	:	unaryExpression ('*' unaryExpression | '%' unaryExpression | '/' unaryExpression)* ;

unaryExpression
	:	postfixExpression | prefixExpression;

prefixExpression
	:	('++' | '--')? primaryExpression;

postfixExpression
	:	primaryExpression ('++' | '--')?;

primaryExpression
    : 	Identifier
    | 	INT
    | 	FLOAT
    |	CHAR
    |	STRING
    ;



statement
	:	
	;




loop:	'while' '(' expression ')' statement
    |   'do' statement 'while' '(' expression ')' ';'
    |   'for' '(' expression? ';' expression? ';' expression? ')' statement
    |   'for' '(' declaration ';' expression? ';' expression? ')' statement
    ;

INT :	(SIGN)? NONZERO DIGIT* | '0';

FLOAT
    :   (SIGN)? DIGIT+ '.' DIGIT* EXPONENT?
    |   '.' DIGIT+ EXPONENT?
    |   (SIGN)? DIGIT+ EXPONENT
    ;

CHAR:   '\'' ( ~('\''|'\\') ) '\'';

STRING
	:	'"' ( ~('\"'|'\\') )* '"';

TYPE:	'char' | 'double' | 'float' | 'int' | 'long' | 'short' | 'signed' | 'unsigned' | 'void';

fragment
SIGN:	'+' | '-';

fragment
DIGIT
	:	'0'..'9';

fragment
NONZERO
	:	'1'..'9';

NONDIGIT
	:	'a'..'z' | 'A'..'Z' | '_';

EXPONENT
	:	('e'|'E') ('+'|'-')? ('0'..'9')+ ;

Identifier
	:	NONDIGIT (NONDIGIT | DIGIT)*;

WS  :   (' ' | '\t')+ {skip();};

NEWLINE
	:	('\r'? '\n')+ {skip();};

COMMENT
    :   '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    |   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
    ;