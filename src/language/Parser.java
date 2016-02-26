package language;

import java.util.ArrayList;
import java.util.List;

import statement.CodeBlock;
import statement.ConstantExpression;
import statement.DeclareStatement;
import statement.Expression;
import statement.Function;
import statement.IdentifierExpression;
import statement.InvokeExpression;
import statement.InvokeStatement;
import statement.NameAndType;
import statement.OperatorExpression;
import statement.SetStatement;
import statement.Variable;
import tokens.Token;
import tokens.TokenType;
import tokens.UndeclaredVariableException;
import tokens.UnexpectedTokenException;
import tokens.UnimplementedLanguageFeatureException;

/**
 * Parser for parsing code (Apryx Script) 
 * @author justf
 */
public class Parser {
	
	private TokenProcessor tokens;
	private CodeBlock block;
	
	/**
	 * Creates a new parser with the given token list
	 * @param tokens
	 */
	public Parser(List<Token> tokens){
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
		else if(current.getType() == TokenType.IDENTIFIER)
			parseIdentifier();
		else if(current.getType() == TokenType.LINE_END)
			tokens.next();
		else if(current.getType() == TokenType.CURLY_CLOSE){
			block = block.getParent();
			if(block == null)
				throw new UnexpectedTokenException(tokens.current());
			tokens.next();
		}
		else
			throw new UnexpectedTokenException(current);
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
		else
			throw new UnimplementedLanguageFeatureException();
		
	}
	
	/**
	 * Parses a class declaration
	 */
	private void parseDeclareClass(){
		throw new UnimplementedLanguageFeatureException();
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
			
			Token nextToken = tokens.next();
			if(nextToken.getType() == TokenType.SEPERATOR){
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
		CodeBlock bb = new CodeBlock(block);
		
		block = bb;
		
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
			block = bb.getParent();
		}
		
		//TODO add function
		Function function = new Function(name, type, arguments, bb);
		
		//add it to the original block
		bb.getParent().add(function);
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
			Token seperatorToken2 = tokens.next();
			
			if(seperatorToken2.getType() == TokenType.EQUALS){
				tokens.next();
				
				//parse the expression on right hand side
				Expression e = parseExpression();
				
				//set this
				block.add(new SetStatement(name, e));
			}
			
		}else if(seperatorToken.getType() == TokenType.EQUALS){
			
			//consume the equals
			tokens.next();
			
			Expression e = parseExpression();

			String name = nameToken.getData();
			String type = e.getType();
			
			block.add(new Variable(name, type));
			block.add(new SetStatement(name, e));
			
			
		}else{
			throw new UnexpectedTokenException(nameToken, TokenType.COLON);
		}
		 
	}
	
	/**
	 * Parses an identifier (expression parsing)
	 * Things like:
	 * 
	 * a = 3
	 * b()
	 * 
	 * TODO will be depricated and replaced with an expression wrapped in statement (ExpressionStatement or something)
	 * If we don't replace this, this will result in double the work
	 */
	private void parseIdentifier(){
		//TODO make this into expression parsing
		Token current = tokens.current();
		
		if(current.getType() != TokenType.IDENTIFIER)
			throw new UnexpectedTokenException(current, TokenType.IDENTIFIER);
		
		Token operationToken = tokens.next();
		
		//function call
		if(operationToken.getType() == TokenType.BRACKET_OPEN){
			//consume bracket open :D
			
			Token firstArg = tokens.next();
			List<Expression> e;
			
			if(firstArg.getType() == TokenType.BRACKET_CLOSE){
				//give it an empty list
				e = new ArrayList<Expression>();
				
				//consume the bclose
				tokens.next();
				
			}else{
				e = parseExpressionList();
				
				Token bCloseToken = tokens.current();
				if(bCloseToken.getType() != TokenType.BRACKET_CLOSE)
					throw new UnexpectedTokenException(bCloseToken, TokenType.BRACKET_CLOSE);
				
				//consume bclose
				tokens.next();
				
			}
			
			InvokeStatement statement = new InvokeStatement(current.getData(), e);
			block.add(statement);
		}
		
		//setting variable
		else if(operationToken.getType() == TokenType.EQUALS){
			
			//consume the token
			tokens.next();
						
			Expression e = parseExpression();
			
			//TODO typecheck equals expression
			
			SetStatement statement = new SetStatement(current.getData(), e);
			
			block.add(statement);
		}
		
		//TODO implement . expression
		
		else{
			throw new UnexpectedTokenException(operationToken);
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
			
			if(f == null)
				throw new UndeclaredVariableException(current.getData());
			
			//TODO find type for function!
			exp = new InvokeExpression(current.getData(), f.getType(), arguments);
		}
		
		//VARIABLE
		else{
			Variable variable = block.getVariableByName(current.getData(), false);
			
			if(variable == null)
				throw new UndeclaredVariableException(current.getData());
			
			exp = new IdentifierExpression(current.getData(), variable.getType());
		}
		
		//TODO parse . expression here, not in parse expression
		
		return exp;
	}
	
	
}
