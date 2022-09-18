grammar test;

program
	:	functionDefinition+;

functionDefinition
	:	TYPE IDENTIFIER '(' parameterDeclaration? ')' statement;

parameterDeclaration
	:	declaration (',' declaration)*;
	
declaration
	:	TYPE IDENTIFIER ('=' expression)?;

statement
	:	'{'   '}'
	;

expressionStatement
	:	expression ';';

expression
	:	
	;



unaryExpression
	:	postfixExpression | ('++' | '--') unaryExpression | BINARYOPERATOR;
	
postfixExpression
	:	primaryExpression ('++' | '--')?;

primaryExpression
	:	INT
	|	FLOAT
	|	CHAR
	|	STRING
	|	IDENTIFIER
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

IDENTIFIER
	:	NONDIGIT (NONDIGIT | DIGIT)*;

UNARYOPERATOR
	:	'++' | '--';

BINARYOPERATOR
	:	'+' | '-' | '*' | '/' | '%';

fragment
SIGN:	'+' | '-';

fragment
DIGIT
	:	'0'..'9';

fragment
NONZERO
	:	'1'..'9';

fragment
NONDIGIT
	:	'a'..'z' | 'A'..'Z' | '_';

fragment
EXPONENT
	:	('e'|'E') ('+'|'-')? ('0'..'9')+ ;

WS  :   (' ' | '\t')+ {skip();};

NEWLINE
	:	('\r'? '\n')+ {skip();};

COMMENT
    :   '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    |   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
    ;