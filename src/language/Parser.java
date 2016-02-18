package language;

import java.util.ArrayList;
import java.util.List;

import statement.CodeBlock;
import statement.ConstantExpression;
import statement.DeclareStatement;
import statement.Expression;
import statement.IdentifierExpression;
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
	
	public void parse(){
		while(!tokens.isDone()){
			parseStatement();			
		}
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
				
			}else{
				e = parseExpressionList();
				
			}
			//TODO IMPLEMENT FUNCTION CALLS
		}
		
		else if(operationToken.getType() == TokenType.EQUALS){
			throw new UnimplementedLanguageFeatureException();
		}
		
		else{
			throw new UnexpectedTokenException(operationToken);
		}
	}
	
	private List<Expression> parseExpressionList(){
		return null;
	}
	
	private Expression parseExpression(){
		//TODO everything with add and stuff, will take some time
		Token current = tokens.current();
		
		
		//consume the current
		tokens.next();
		
		if(current.getType() == TokenType.IDENTIFIER)
			return parseExpressionIdentifier();
		else if(current.getType() == TokenType.STRING)
			return new ConstantExpression(Language.TYPE_STRING, current.getData());
		else if(current.getType() == TokenType.INTEGER)
			return new ConstantExpression(Language.TYPE_INT, current.getData());
		else if(current.getType() == TokenType.FLOAT)
			return new ConstantExpression(Language.TYPE_FLOAT, current.getData());
		else 
			throw new UnexpectedTokenException(current);
		
	}
	
	private Expression parseExpressionIdentifier(){
		Token current = tokens.current();
		
		if(current.getType() != TokenType.IDENTIFIER)
			throw new UnexpectedTokenException(current, TokenType.IDENTIFIER);
		
		DeclareStatement initialDeclare = block.getVariableByName(current.getData(), true);
		
		if(initialDeclare == null)
			throw new UndeclaredVariableException(current.getData());
		
		return new IdentifierExpression(current.getData(), initialDeclare.getType());
	}
	
	
}
