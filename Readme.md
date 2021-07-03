# TeaLang_Compiler_CPP20

Presented here is a TeaLang interpreter written in C++ (20). This assignment forms part of the CPS2000 unit which was taken in partial fulfilment of the
requirements for the degree of B.Sc. in Artificial Intelligence.

The interpreter and sub processes were developed and written to follow the specifications in the CPS2000_Assignment_2021 (Part1) pdf.

The TeaLang language follows the following EBNF:


<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CLetter%3E%20%3A%3A%3D%20%5BA-Za-z%5D" alt="<Letter> ::= [A-Za-z]"/> </p>
  


<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CDigit%3E%20%3A%3A%3D%20%5B0-9%5D" alt="<Digit> ::= [0-9]"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CPrintable%3E%20%3A%3A%3D%20%5B%5Ctextbackslash%20x20-%5Ctextbackslash%20x7E%5D" alt="<Printable> ::= [\textbackslash x20-\textbackslash x7E]"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CType%3E%20%3A%3A%3D%20%27float%27%20%7C%20%5C%5C%20%27int%27%20%7C%20%5C%5C%20%27bool%27%20%7C%20%5C%5C%20%27string%27" alt="<Type> ::= 'float' | \\ 'int' | \\ 'bool' | \\ 'string'"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CBooleanLiteral%3E%20%3A%3A%3D%20%27true%27%20%7C%20%5C%5C%20%27false%27" alt="<BooleanLiteral> ::= 'true' | \\ 'false'"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CIntegerLiteral%3E%20%3A%3A%3D%20%3CDigit%3E%20%5C%7B%20%3CDigit%3E%20%5C%7D" alt="<IntegerLiteral> ::= <Digit> \{ <Digit> \}"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CFloatLiteral%3E%20%3A%3A%3D%20%3CDigit%3E%20%5C%7B%20%3CDigit%3E%20%5C%7D%20%27.%27%20%3CDigit%3E%20%5C%7B%20%3CDigit%3E%20%5C%7D" alt="<FloatLiteral> ::= <Digit> \{ <Digit> \} '.' <Digit> \{ <Digit> \}"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CStringLiteral%3E%20%3A%3A%3D%20%27%22%27%20%5C%7B%20%3CPrintable%3E%20%5C%7D%20%27%22%27" alt="<StringLiteral> ::= '"' \{ <Printable> \} '"'"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CLiteral%3E%20%3A%3A%3D%20%3CBooleanLiteral%3E%20%7C%20%5C%5C%20%3CIntegerLiteral%3E%20%7C%20%5C%5C%20%3CFloatLiteral%3E%20%7C%20%5C%5C%20%3CStringLiteral%3E" alt="<Literal> ::= <BooleanLiteral> | \\ <IntegerLiteral> | \\ <FloatLiteral> | \\ <StringLiteral>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CIdentifier%3E%20%3A%3A%3D%20%28%20%27%5C_%27%20%7C%20%5C%5C%20%3CLetter%3E%20%29%20%20%5C%7B%20%27%5C_%27%20%7C%20%5C%5C%20%3CLetter%3E%20%7C%20%5C%5C%20%3CDigit%3E%20%5C%7D" alt="<Identifier> ::= ( '\_' | \\ <Letter> )  \{ '\_' | \\ <Letter> | \\ <Digit> \}"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CMultiplicativeOp%3E%20%3A%3A%3D%20%27%2A%27%20%7C%20%5C%5C%20%27/%27%20%7C%20%5C%5C%20%27and%27" alt="<MultiplicativeOp> ::= '*' | \\ '/' | \\ 'and'"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CAdditiveOp%3E%20%3A%3A%3D%20%27%2B%27%20%7C%20%5C%5C%20%27-%27%20%7C%20%5C%5C%20%27or%27" alt="<AdditiveOp> ::= '+' | \\ '-' | \\ 'or'"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CRelationalOp%3E%20%3A%3A%3D%20%27%3C%27%20%7C%20%5C%5C%20%27%3E%27%20%7C%20%5C%5C%20%27%3D%3D%27%20%7C%20%5C%5C%20%27%21%3D%27%20%7C%20%5C%5C%20%27%3C%3D%27%20%7C%20%5C%5C%20%27%3E%3D%27" alt="<RelationalOp> ::= '<' | \\ '>' | \\ '==' | \\ '!=' | \\ '<=' | \\ '>='"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CActualParams%3E%20%3A%3A%3D%20%3CExpression%3E%20%5C%7B%20%27%2C%27%20%3CExpression%3E%20%5C%7D" alt="<ActualParams> ::= <Expression> \{ ',' <Expression> \}"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CFunctionCall%3E%20%3A%3A%3D%20%3CIdentifier%3E%20%27%28%27%20%5C%5B%20%3CActualParams%3E%20%5C%5D%20%27%29%27" alt="<FunctionCall> ::= <Identifier> '(' \[ <ActualParams> \] ')'"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CSubExpression%3E%20%3A%3A%3D%20%27%28%27%20%3CExpression%3E%20%27%29%27" alt="<SubExpression> ::= '(' <Expression> ')'"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CUnary%3E%20%3A%3A%3D%20%28%20%27-%27%20%7C%20%5C%5C%20%27not%27%20%29%20%3CExpression%3E" alt="<Unary> ::= ( '-' | \\ 'not' ) <Expression>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CFactor%3E%20%3A%3A%3D%20%20%3CLiteral%3E%20%7C%20%5C%5C%20%3CIdentifier%3E%20%7C%20%5C%5C%20%3CFunctionCall%3E%20%7C%20%5C%5C%20%3CSubExpression%3E%20%7C%20%5C%5C%20%3CUnary%3E" alt="<Factor> ::=  <Literal> | \\ <Identifier> | \\ <FunctionCall> | \\ <SubExpression> | \\ <Unary>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CTerm%3E%20%3A%3A%3D%20%3CFactor%3E%20%5C%7B%20%3CMultiplicativeOp%3E%20%3CFactor%3E%20%5C%7D" alt="<Term> ::= <Factor> \{ <MultiplicativeOp> <Factor> \}"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CSimpleExpression%3E%20%3A%3A%3D%20%3CTerm%3E%20%5C%7B%20%3CAdditiveOp%3E%20%3CTerm%3E%20%5C%7D" alt="<SimpleExpression> ::= <Term> \{ <AdditiveOp> <Term> \}"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CExpression%3E%20%3A%3A%3D%20%3CSimpleExpression%3E%20%5C%7B%20%3CRelationalOp%3E%20%3CSimpleExpression%3E%20%5C%7D" alt="<Expression> ::= <SimpleExpression> \{ <RelationalOp> <SimpleExpression> \}"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CAssignment%3E%20%3A%3A%3D%20%3CIdentifier%3E%20%27%3D%27%20%3CExpression%3E" alt="<Assignment> ::= <Identifier> '=' <Expression>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CVariableDecl%3E%20%3A%3A%3D%20%27let%27%20%3CIdentifier%3E%20%27%3A%27%20%3CType%3E%20%27%3D%27%20%3CExpression%3E" alt="<VariableDecl> ::= 'let' <Identifier> ':' <Type> '=' <Expression>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CPrintStatement%3E%20%3A%3A%3D%20%27print%27%20%3CExpression%3E" alt="<PrintStatement> ::= 'print' <Expression>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CRtrnStatement%3E%20%3A%3A%3D%20%27return%27%20%3CExpression%3E" alt="<RtrnStatement> ::= 'return' <Expression>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CIfStatement%3E%20%3A%3A%3D%20%27if%27%20%5C%28%20%3CExpression%3E%20%5C%29%20%3CBlock%3E%20%5C%5B%20%27else%27%20%3CBlock%3E%20%5C%5D" alt="<IfStatement> ::= 'if' \( <Expression> \) <Block> \[ 'else' <Block> \]"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CForStatement%3E%20%3A%3A%3D%20%27for%27%20%5C%28%20%5C%5B%20%3CVariableDecl%3E%20%5C%5D%20%27%3B%27%20%3CExpression%3E%20%27%3B%27%20%5C%5B%20%3CAssignment%3E%20%5C%5D%20%5C%29%20%3CBlock%3E" alt="<ForStatement> ::= 'for' \( \[ <VariableDecl> \] ';' <Expression> ';' \[ <Assignment> \] \) <Block>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CWhileStatement%3E%20%3A%3A%3D%20%27while%27%20%5C%28%20%3CExpression%3E%20%5C%29%20%3CBlock%3E" alt="<WhileStatement> ::= 'while' \( <Expression> \) <Block>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CFormalParam%3E%20%3A%3A%3D%20%3CIdentifier%3E%20%27%3A%27%20%3CType%3E" alt="<FormalParam> ::= <Identifier> ':' <Type>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CFormalParams%3E%20%3A%3A%3D%20%3CFormalParam%3E%20%5C%7B%20%27%2C%27%20%3CFormalParam%3E%20%5C%7D" alt="<FormalParams> ::= <FormalParam> \{ ',' <FormalParam> \}"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CFunctionDecl%3E%20%3A%3A%3D%20%3Ctype%3E%20%3CIdentifier%3E%20%27%28%27%20%5C%5B%20%3CFormalParams%3E%20%5C%5D%20%27%29%27%20%3CBlock%3E" alt="<FunctionDecl> ::= <type> <Identifier> '(' \[ <FormalParams> \] ')' <Block>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CStatement%3E%20%3A%3A%3D%09%3CVariableDecl%3E%20%27%3B%27%20%7C%20%5C%5C%20%3CAssignment%3E%20%27%3B%27%20%7C%20%5C%5C%20%3CPrintStatement%3E%20%27%3B%27%20%7C%20%5C%5C%20%3CIfStatement%3E%20%7C%20%5C%5C%20%3CForStatement%3E%20%7C%20%5C%5C%20%3CWhileStatement%3E%20%7C%20%5C%5C%20%3CRtrnStatement%3E%20%27%3B%27%20%7C%20%5C%5C%20%3CFunctionDecl%3E%20%7C%20%5C%5C%20%3CBlock%3E" alt="<Statement> ::=	<VariableDecl> ';' | \\ <Assignment> ';' | \\ <PrintStatement> ';' | \\ <IfStatement> | \\ <ForStatement> | \\ <WhileStatement> | \\ <RtrnStatement> ';' | \\ <FunctionDecl> | \\ <Block>"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CBlock%3E%20%3A%3A%3D%20%27%7B%27%20%5C%7B%20%3CStatement%3E%20%5C%7D%20%27%7D%27" alt="<Block> ::= '{' \{ <Statement> \} '}'"/> </p>



<p align="center"> <img src="https://latex.codecogs.com/svg.latex?%3CProgram%3E%20%3A%3A%3D%20%5C%7B%20%3CStatement%3E%20%5C%7D" alt="<Program> ::= \{ <Statement> \}"/> </p>


The following is a syntactically and semantically correct TeaLang program:

'''
float Square (x : float) {
    return x*x;
}
bool XGreaterThanY (x : float , y : float) {
    let ans : bool = true;
    if (y > x) {ans = false ;}
    return ans;
}
bool XGreaterThanYv2 (x : float , y : float) {
    return x > y;
}
float AverageOfThree (x : float , y : float , z : float) {
    let total : float = x + y + z ;
    return total / 3.0;
}

string JoinStr (s1 : string , s2 : string) {
    let s3 : string = s1 + s2 ;
    return s3 ;
}
let x : float = 2.4;
let y : float = Square (2.5);
print y ; //6.25
print XGreaterThanY (x , 2.3 ) ; // t r u e
print XGreaterThanYv2 (Square ( 1.5 ) , y ) ; // f a l s e
print AverageOfThree (x , y , 1.2 ) ; //3.28
print JoinStr(\"Hello\" , \"World\" ) ; // Hello World
for(let ii : int = 0; ii < 10; ii = ii + 1){
   print ii;
}
let ii : int = 0;
while (ii < 10){
   print ii;
   ii = ii + 1;
}
'''

A full detailed report can be found in Report.pdf

The latex for the ebnf was rendered via the https://github.com/bo-ke/latex_render library.