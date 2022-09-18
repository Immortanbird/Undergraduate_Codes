import java.io.*;

%%

%public
%class MyScanner
%function scan
%type void

%char
%line
%column
%unicode

%{
	private int count = 0;

	public void genToken(char[] zzBuffer, int type, int count, int startPos, int endPos) throws IOException{
		FileWriter writer = new FileWriter("out.txt", true);
		String s = String.valueOf(zzBuffer, startPos, endPos - startPos);
		switch(type) {
			// Keyword
			case 0: writer.write("[@" + count + "," + yycolumn + ":" + (yycolumn + endPos - startPos) + "='" + s + "',<'" + s + "'>," + yyline + ":" + yycolumn +"]\n"); break;
			// Identifier
			case 1: writer.write("[@" + count + "," + yycolumn + ":" + (yycolumn + endPos - startPos) + "='" + s + "',<Identifier>," + yyline + ":" + yycolumn +"]\n"); break;
			// Operator
			case 2: writer.write("[@" + count + "," + yycolumn + ":" + (yycolumn + endPos - startPos) + "='" + s + "',<'" + s + "'>," + yyline + ":" + yycolumn +"]\n"); break;
			// Delimiter
			case 3: writer.write("[@" + count + "," + yycolumn + ":" + (yycolumn + endPos - startPos) + "='" + s + "',<'" + s + "'>," + yyline + ":" + yycolumn +"]\n"); break; 
			// IntegerConstant
			case 4: writer.write("[@" + count + "," + yycolumn + ":" + (yycolumn + endPos - startPos) + "='" + s + "',<IntegerConstant>," + yyline + ":" + yycolumn +"]\n"); break;
			// FloatConstant
			case 5: writer.write("[@" + count + "," + yycolumn + ":" + (yycolumn + endPos - startPos) + "='" + s + "',<FloatConstant>," + yyline + ":" + yycolumn +"]\n"); break;
			// CharacterConstant
			case 6: writer.write("[@" + count + "," + yycolumn + ":" + (yycolumn + endPos - startPos) + "='" + s + "',<CharacterConstant>," + yyline + ":" + yycolumn +"]\n"); break;
			// StringLiteral
			case 7: writer.write("[@" + count + "," + yycolumn + ":" + (yycolumn + endPos - startPos) + "='" + s + "',<StringLiteral>," + yyline + ":" + yycolumn +"]\n"); break;
		}
		writer.flush();
		writer.close();
	}
%}

Keyword="auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"inline"|"int"|"long"|"register"|"restrict"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while"

Identifier=[:jletter:] [:jletterdigit:]*

IntegerConstant=0|[1-9][0-9]*

FloatConstant=[0-9]+(\.[0-9]+)

Operator="+"|"-"|"*"|"/"|"%"|"++"|"--"|">"|"<"|"=="|">="|"<="|"!="|"&&"|"||"|"!"|"&"|"|"|"~"|"^"|"<<"|">>"|"="|"+="|"-="|"*="|"/="|"%="|"&="|"|="|"^="|"<<="|">>="|"?"|":"|"."

Delimiter=","|";"|"\""|"'"|"("|")"|"["|"]"|"{"|"}"|"#"

CharacterConstant=\'((\\\S)|[^'])\'

StringLiteral=\"\S*[^\\]\"

Comment = {TraditionalComment} | {EndOfLineComment} | {DocumentationComment}

WhiteSpace=\ |\t|\f|\b

LineTerminator=\r|\n|\r\n

CommentContent       = ( [^*] | \*+ [^/*] )*
TraditionalComment   = "/*" [^*] ~"*/" | "/*" "*"+ "/"
EndOfLineComment     = "//" [^\r\n]* {LineTerminator}?
DocumentationComment = "/**" {CommentContent} "*"+ "/"

%%

<YYINITIAL> {
	{Keyword}     { count++; genToken(zzBuffer, 0, count, zzCurrentPos, zzMarkedPos); }
	{Identifier}  { count++; genToken(zzBuffer, 1, count, zzCurrentPos, zzMarkedPos); }
	{Operator}    { count++; genToken(zzBuffer, 2, count, zzCurrentPos, zzMarkedPos); }
	{Delimiter}   { count++; genToken(zzBuffer, 3, count, zzCurrentPos, zzMarkedPos); }
	{IntegerConstant}   { count++; genToken(zzBuffer, 4, count, zzCurrentPos, zzMarkedPos); }
	{FloatConstant}     { count++; genToken(zzBuffer, 5, count, zzCurrentPos, zzMarkedPos); }
	{CharacterConstant} { count++; genToken(zzBuffer, 6, count, zzCurrentPos, zzMarkedPos); }
	{StringLiteral}     { count++; genToken(zzBuffer, 7, count, zzCurrentPos, zzMarkedPos); }
	{Comment}     {}
}

{LineTerminator}|{WhiteSpace} {}