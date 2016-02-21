package language;

import java.util.ArrayList;
import java.util.List;

import statement.CodeBlock;
import statement.ConstantExpression;
import statement.DeclareStatement;
import statement.Expression;
import statement.IdentifierExpression;
import statement.InvokeExpression;
import statement.InvokeStatement;
import statement.OperatorExpression;
import statement.SetStatement;
import tokens.Token;
import tokens.TokenType;
import tokens.UndeclaredVariableException;
import tokens.UnexpectedTokenException;
import tokens.UnimplementedLanguageFeatureException;

public class Parser {
	
	private TokenProcessor tokens;
	
	private CodeBlock block;
	
	public Parser(List<Token> tokens){
		this.tokens = new TokenProcessor(tokens);
		block = new CodeBlock();
	}
	
	public CodeBlock parse(){
		while(!tokens.isDone()){
			parseStatement();			
		}
		return block;
	}
	
	public CodeBlock getBlock() {
		return block;
	}
	
	private void parseStatement(){
		Token current = tokens.current();
		if(current.getType() == TokenType.KEYWORD)
			parseKeywords();
		else if(current.getType() == TokenType.IDENTIFIER)
			parseIdentifier();
		else if(current.getType() == TokenType.LINE_END)
			tokens.next();
		else
			throw new UnexpectedTokenException(current);
	}
	
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
	
	private void parseDeclareClass(){
		throw new UnimplementedLanguageFeatureException();
	}
	
	private void parseDeclareFunction(){
		throw new UnimplementedLanguageFeatureException();
	}
	
	private void parseDeclareVariable(){
		Token nameToken = tokens.next();
		
		if(nameToken.getType() != TokenType.IDENTIFIER)
			throw new UnexpectedTokenException(nameToken, TokenType.IDENTIFIER);
		
		Token seperatorToken = tokens.next();
		
		if(seperatorToken.getType() == TokenType.COLON){
			
			Token typeToken = tokens.next();
			
			if(typeToken.getType() != TokenType.IDENTIFIER)
				throw new UnexpectedTokenException(typeToken, TokenType.IDENTIFIER);
			
			String name = nameToken.getData();
			String type = typeToken.getData();
			
			DeclareStatement statement = new DeclareStatement(name, type);
			
			block.add(statement);
			
			//the = or ;
			Token seperatorToken2 = tokens.next();
			
			if(seperatorToken2.getType() == TokenType.EQUALS){
				//TODO parse expression
				tokens.next();
				
				Expression e = parseExpression();
				
				block.add(new SetStatement(name, e));
				
				System.out.println("TODO parse expression");
			}
				
			else if(seperatorToken2.getType() != TokenType.LINE_END)
				throw new UnexpectedTokenException(seperatorToken2, TokenType.LINE_END);
			
		}else if(seperatorToken.getType() == TokenType.EQUALS){
			
			//consume the equals
			tokens.next();
			
			Expression e = parseExpression();

			String name = nameToken.getData();
			String type = e.getType();
			
			block.add(new DeclareStatement(name, type));
			block.add(new SetStatement(name, e));
			
			
		}else{
			throw new UnexpectedTokenException(nameToken, TokenType.COLON);
		}
		 
	}
	
	private void parseIdentifier(){
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
			//TODO IMPLEMENT FUNCTION CALLS
			
			InvokeStatement statement = new InvokeStatement(current.getData(), e);
			block.add(statement);
		}
		
		else if(operationToken.getType() == TokenType.EQUALS){
			throw new UnimplementedLanguageFeatureException();
		}
		
		else{
			throw new UnexpectedTokenException(operationToken);
		}
	}
	
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
	
	private Expression parseExpression(){
		//TODO everything with add and stuff, will take some time
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
			
			//TODO find type for function!
			exp = new InvokeExpression(current.getData(), Language.TYPE_UNKNOWN, arguments);
		}
		
		//VARIABLE
		else{
			DeclareStatement initialDeclare = block.getVariableByName(current.getData(), true);
			
			if(initialDeclare == null)
				throw new UndeclaredVariableException(current.getData());
			exp = new IdentifierExpression(current.getData(), initialDeclare.getType());
		}
		
		//TODO parse . expression
		
		return exp;
	}
	
	
}
