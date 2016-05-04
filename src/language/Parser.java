package language;

import statement.Expression;
import statement.ExpressionStatement;
import statement.Statement;
import tokens.Token;
import tokens.TokenType;
import tokens.UnexpectedTokenException;
import context.Context;

public class Parser {
	
	private Lexer lexer;
	
	public Parser(Lexer lexer){
		this.lexer = lexer;
		lexer.next();
	}
	
	public Context parseContext(){
		Context context = new Context();
		
		//TODO parse the context
		parseStatement(context);
		
		return context;
	}
	
	public void parseStatement(Context context){
		Token current = lexer.current();
		if(current.getType() == TokenType.KEYWORD){
			parseKeyword(context);
		}
		else if(current.getType() == TokenType.IDENTIFIER){
			context.addStatement(new ExpressionStatement(parseExpression()));
		}
		else if(current.getType() == TokenType.LINE_END){
			//Consume the line-end
			lexer.next();
		}
		else{
			throw new UnexpectedTokenException(current, TokenType.IDENTIFIER, TokenType.KEYWORD);
		}
	}
	
	public void parseKeyword(Context context){
		
	}
	
	public Expression parseExpression(){
		Token start = lexer.current();
		
		//TODO parse lhs and rhs
		//Have a function that only parses the identifier, int, string, float, etc.
		
		if(start.getType() == TokenType.IDENTIFIER){
			Token operator = lexer.next();
			
			//Function call
			if(operator.getType() == TokenType.BRACKET_OPEN){
				
			}
			
			//Set operator
			else if(operator.getType() == TokenType.EQUALS){
				
			}
			
			else{
				throw new UnexpectedTokenException(operator, TokenType.BRACKET_OPEN, TokenType.IDENTIFIER);
			}
		}
		
		
		return null;
	}
	
}
