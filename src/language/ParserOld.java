package language;

import java.util.ArrayList;
import java.util.List;

import ast.ApryxClass;
import ast.Function;
import ast.NameAndType;
import ast.Variable;
import statement.CodeBlock;
import statement.ConstantExpression;
import statement.Expression;
import statement.ExpressionStatement;
import statement.IdentifierExpression;
import statement.InvokeExpression;
import statement.OperatorExpression;
import statement.ReturnStatement;
import statement.SetExpression;
import tokens.Token;
import tokens.TokenType;
import tokens.UnexpectedTokenException;
import tokens.UnimplementedLanguageFeatureException;

/**
 * Parser for parsing code (Apryx Script) 
 * @author justf
 */
@Deprecated
public class ParserOld {
	
	private TokenProcessor tokens;
	private CodeBlock block;
	
	/**
	 * Creates a new parser with the given token list
	 * @param tokens
	 */
	public ParserOld(List<Token> tokens){
		this.tokens = new TokenProcessor(tokens);
		block = new CodeBlock();
	}
	
	/**
	 * Starts parsing the code (given in the constructor)
	 * @return
	 */
	public CodeBlock parse(){
		while(!tokens.isDone()){
			parseStatement();			
		}
		if(!block.isRoot())
			throw new UnexpectedTokenException(tokens.current(), TokenType.CURLY_CLOSE);
		
		return block;
	}
	
	/**
	 * Returns the current code block
	 * @return
	 */
	public CodeBlock getBlock() {
		return block;
	}
	
	/**
	 * Parses a statement (this can be any statement)
	 */
	private void parseStatement(){
		Token current = tokens.current();
		if(current.getType() == TokenType.KEYWORD)
			parseKeywords();
		else if(current.getType() == TokenType.LINE_END)
			tokens.next();
		else if(current.getType() == TokenType.CURLY_CLOSE){
			block = block.getParent();
			if(block == null)
				throw new UnexpectedTokenException(tokens.current());
			tokens.next();
		}
		else{
			block.add(new ExpressionStatement(parseExpression()));
		}
	}
	
	/**
	 * Parses a keyword
	 */
	private void parseKeywords(){
		Token current = tokens.current();
		
		if(current.getType() != TokenType.KEYWORD)
			throw new UnexpectedTokenException(current);
		
		
		if(current.getData().equals(Language.VAR))
			parseDeclareVariable();
		else if(current.getData().equals(Language.FUNCTION))
			parseDeclareFunction();
		else if(current.getData().equals(Language.CLASS))
			parseDeclareClass();
		else if(current.getData().equals(Language.RETURN)){
			//consume the return
			tokens.next();
			
			//add it as a return statement
			block.add(new ReturnStatement(parseExpression()));
		}
		else
			throw new UnimplementedLanguageFeatureException();
		
	}
	
	/**
	 * Parses a class declaration
	 */
	private void parseDeclareClass(){
		Token nameToken = tokens.next();
		
		if(nameToken.getType() != TokenType.IDENTIFIER)
			throw new UnexpectedTokenException(nameToken, TokenType.IDENTIFIER);
		
		//TODO implement extends and stuff
		Token curlyToken = tokens.next();

		ApryxClass cls = new ApryxClass(nameToken.getData());
		cls.setParent(block);

		block = cls;
		
		//code block 
		if(curlyToken.getType() == TokenType.CURLY_OPEN){
			//consume the curly open
			tokens.next();
		}
		
		else{
			parseStatement();
			
			block = cls.getParent();
		}
		
		
		cls.getParent().add(cls);
	}
	
	/**
	 * Parses a function declaration
	 */
	private void parseDeclareFunction(){
		Token nameToken = tokens.next();
		
		if(nameToken.getType() != TokenType.IDENTIFIER)
			throw new UnexpectedTokenException(nameToken, TokenType.IDENTIFIER);
		
		Token bracketToken = tokens.next();
		
		if(bracketToken.getType() != TokenType.BRACKET_OPEN)
			throw new UnexpectedTokenException(bracketToken, TokenType.BRACKET_OPEN);
		
		String name = nameToken.getData();
		String type = Language.TYPE_VOID;
		List<NameAndType> arguments = new ArrayList<NameAndType>();
		
		Token argToken = tokens.next();
		
		while(argToken.getType() != TokenType.BRACKET_CLOSE){
			
			if(argToken.getType() != TokenType.IDENTIFIER)
				throw new UnexpectedTokenException(argToken);
			
			Token colonToken = tokens.next();
			
			if(colonToken.getType() != TokenType.COLON)
				throw new UnexpectedTokenException(colonToken, TokenType.COLON);
			
			//consume the colon
			tokens.next();
			
			//get the name
			String nameArg = argToken.getData();
			//parse the type
			String typeArg = parseType();
			
			Token seperator = tokens.current();
			if(seperator.getType() == TokenType.SEPERATOR){
				argToken = tokens.next();
			}else{
				argToken = tokens.current();
			}
			
			arguments.add(new NameAndType(nameArg, typeArg));
		}
		
		Token colonToken = tokens.next();
		
		Token statementBegin;
		
		//find the return type
		if(colonToken.getType() == TokenType.COLON){
			tokens.next();
			
			type = parseType();
			
			statementBegin = tokens.current();
		}else{
			statementBegin = colonToken;
		}
		
		//TODO do stuff with statement begin
		
		//for reference, current block will be the parent for this block
		//so that will kinda fix itself

		//create the given function
		Function function = new Function(name, type, arguments);
		function.setParent(block);
		
		block = function;
		
		//block
		if(statementBegin.getType() == TokenType.CURLY_OPEN){
			//consume curly open
			tokens.next();
			
			//let the parser parse the rest of this function
		}
		
		//single line function
		else{
			parseStatement();
			
			//return to normal
			block = function.getParent();
		}
		
		//add it to the original block
		function.getParent().add(function);
	}
	
	/**
	 * Parses a variable declaration
	 * 
	 * var IDENTIFIER [: TYPE [= VALUE]] | [ = VALUE]
	 * 
	 * ex:
	 * var a = 3
	 * var b : int
	 * var c : int = 2
	 * 
	 * There must be some way to know the type of the just declared variable.
	 */
	private void parseDeclareVariable(){
		Token nameToken = tokens.next();
		
		if(nameToken.getType() != TokenType.IDENTIFIER)
			throw new UnexpectedTokenException(nameToken, TokenType.IDENTIFIER);
		
		Token seperatorToken = tokens.next();
		
		if(seperatorToken.getType() == TokenType.COLON){
			
			//consume colon
			tokens.next();
			
			String name = nameToken.getData();
			String type = parseType();
			
			Variable variable = new Variable(name, type);
			
			block.add(variable);
			
			//equals token
			Token seperatorToken2 = tokens.current();
			
			if(seperatorToken2.getType() == TokenType.EQUALS){
				tokens.next();
				
				//parse the expression on right hand side
				Expression e = parseExpression();
				
				//give the initial value to the variable
				variable.setInitialValue(e);
				
				//set this
				//block.add(new ExpressionStatement(new SetExpression(name, e)));
			}
			
		}
		
		else if(seperatorToken.getType() == TokenType.EQUALS){
			
			//consume the equals
			tokens.next();
			
			Expression e = parseExpression();

			String name = nameToken.getData();
			String type = e.getType();
			
			Variable v = new Variable(name, type);
			
			v.setInitialValue(e);
			
			block.add(v);
			
		}else{
			throw new UnexpectedTokenException(nameToken, TokenType.COLON);
		}
		 
	}
	
	/**
	 * Parses a list of expressions, for example for function calls or for loops. Expressions are seperated by ,
	 * 
	 * ex:
	 * 
	 * a + b, c
	 * a, b + c
	 * a, b, c
	 * a(), b + c()
	 * 
	 * etc.
	 * 
	 * @return
	 */
	private List<Expression> parseExpressionList(){
		ArrayList<Expression> expressions = new ArrayList<Expression>();
		
		boolean done = false;
		Token current = tokens.current();
		
		while(!done){
			Expression e = parseExpression();
			expressions.add(e);
			current = tokens.current();
			if(current.getType() == TokenType.SEPERATOR){
				current = tokens.next();
			}else{
				done = true;
			}
		}
		
		
		return expressions;
	}
	
	/**
	 * Parses an expression list with brackets around it
	 * 
	 * ex:
	 * 
	 * (a, b, c)
	 * (a + b, c)
	 * (a(), b + c())
	 * 
	 * @return
	 */
	private List<Expression> parseExpressionListBrackets(){
		Token bOpen = tokens.current();
		
		if(bOpen.getType() != TokenType.BRACKET_OPEN)
			throw new UnexpectedTokenException(bOpen, TokenType.BRACKET_OPEN);
		
		Token firstArg = tokens.next();
		List<Expression> e;
		
		if(firstArg.getType() == TokenType.BRACKET_CLOSE){
			//give it an empty list
			e = new ArrayList<Expression>();
			
			tokens.next();
			
		}else{
			e = parseExpressionList();
			
			Token bCloseToken = tokens.current();
			if(bCloseToken.getType() != TokenType.BRACKET_CLOSE)
				throw new UnexpectedTokenException(bCloseToken, TokenType.BRACKET_CLOSE);
			
			//consume bclose
			tokens.next();
			
		}
		
		return e;
	}
	
	/**
	 * Parses an expression and returns the found expression
	 * @return
	 */
	private Expression parseExpression(){
		//TODO everything with add and stuff, will take some time
		
		//Hint: this function is recursive as shit, it will call itself a few times.
		
		Token current = tokens.current();
		
		Expression self;
		
		if(current.getType() == TokenType.IDENTIFIER){
			self =  parseExpressionIdentifier();
		}else if(current.getType() == TokenType.STRING){
			tokens.next();
			self = new ConstantExpression(Language.TYPE_STRING, current.getData());
		}else if(current.getType() == TokenType.INTEGER){
			tokens.next();
			self =  new ConstantExpression(Language.TYPE_INT, current.getData());
		}else if(current.getType() == TokenType.FLOAT){
			tokens.next();
			self =  new ConstantExpression(Language.TYPE_FLOAT, current.getData());
		}else 
			throw new UnexpectedTokenException(current);
		
		Token operatorToken = tokens.current();
		
		//TODO parse . expression
		//TODO fix order of operations (hint: operator expression should have an order (integer) value)
		
		//add or subtract!
		if(operatorToken.getType() == TokenType.PLUSMIN){
			tokens.next();
			Expression rightHandSide = parseExpression();
			
			//TODO clean this up
			Expression combined = new OperatorExpression(operatorToken.getData().equals("+") ? OperatorExpression.OPERATION_ADD : OperatorExpression.OPERATION_SUBTRACT, self, rightHandSide);
			
			return combined;
		}
		
		//multiply or devide
		else if(operatorToken.getType() == TokenType.MULDIV){
			tokens.next();
			Expression rightHandSide = parseExpression();
			
			//TODO clean this up
			Expression combined = new OperatorExpression(operatorToken.getData().equals("*") ? OperatorExpression.OPERATION_MULTIPLY : OperatorExpression.OPERATION_DEVIDE, self, rightHandSide);
			
			return combined;
		}
		
		//set expression
		else if(operatorToken.getType() == TokenType.EQUALS){
			tokens.next();
			Expression rightHandSide = parseExpression();
			
			if(!(self instanceof IdentifierExpression))
				throw new UnexpectedTokenException(operatorToken);
			
			IdentifierExpression e = (IdentifierExpression) self;
			
			Expression combined = new SetExpression(e.getName(), rightHandSide);
			
			return combined;
		}
		
		else{
			return self;
		}
		
	}
	
	/**
	 * Parses a type identifyer and returns the type
	 * @return
	 */
	private String parseType(){
		
		//TODO make into Type class
		Token current = tokens.current();
		
		//static type
		if(current.getType() == TokenType.IDENTIFIER){
			
			//consume the identifier
			tokens.next();
			return current.getData();
			
			//TODO parse . expression
		}
		
		//function pointer type
		else if(current.getType() == TokenType.BRACKET_OPEN){
			//TODO parse this type
			throw new UnimplementedLanguageFeatureException("Function pointer variables");
		}
		
		else{
			throw new UnexpectedTokenException(current);
		}
		
	}
	
	/**
	 * Parses an expression starting with an identifier. Call parse expression for recursion and other stuff. This handles the '.' and '()' (funciton calls)
	 * @return
	 */
	private Expression parseExpressionIdentifier(){
		Token current = tokens.current();
		
		if(current.getType() != TokenType.IDENTIFIER)
			throw new UnexpectedTokenException(current, TokenType.IDENTIFIER);
		
		//consume the identifier
		Token operator = tokens.next();
		
		Expression exp;
		
		//FUNCTION
		if(operator.getType() == TokenType.BRACKET_OPEN){
			List<Expression> arguments = parseExpressionListBrackets();
			
			//check for function pointers or something
			//maybe make function a variable type or something
			//TODO make function a variable
			
			Function f = block.getFunctionByName(current.getData(), false);
			
			String type;
			
			if(f == null)
				type = Language.TYPE_UNKNOWN;
			else
				type = f.getType();
			
			//TODO find type for function!
			exp = new InvokeExpression(current.getData(), type, arguments);
			
			//do not consume bracket close, parseExpressionListBrackets does that!
		}
		
		//VARIABLE
		else{
			Variable variable = block.getVariableByName(current.getData(), false);
			
			String type;
			
			//if variable does not exist, it might be a class
			if(variable == null){
				type = Language.TYPE_UNKNOWN;
			}
			else{
				type = variable.getType();
			}
			
			exp = new IdentifierExpression(current.getData(), type);
		}
		
		//TODO parse . expression here, not in parse expression
		
		Token lookupOperator = tokens.current();
		if(lookupOperator.getType() == TokenType.LOOKUP){
			//consume the dot
			tokens.next();
			
			//must be either a function call or sumtin
			Expression e = parseExpressionIdentifier();
		}
		
		return exp;
	}
	
	
}
