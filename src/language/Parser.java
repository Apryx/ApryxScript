package language;

import java.util.ArrayList;
import java.util.List;

import statement.Expression;
import statement.ExpressionStatement;
import statement.IdentifierExpression;
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
		Expression lhs = parseExpressionSimple();
		
		Token operator = lexer.current();
		
		//plus or minus
		if(operator.getType() == TokenType.PLUSMIN){
			lexer.next();
			Expression rhs = parseExpression();
		
		}
		
		//multiply or devide
		else if(operator.getType() == TokenType.MULDIV){
			lexer.next();
			Expression rhs = parseExpression();
			
		}
		
		//function call
		else if(operator.getType() == TokenType.BRACKET_OPEN){
			//consume the operator
			Token n = lexer.next();
			List<Expression> expressions;
			if(n.getType() == TokenType.BRACKET_CLOSE){
				expressions = parseExpressionList();
			}else{
				expressions = new ArrayList<Expression>();
			}
		}
		
		return lhs;
	}
	
	public List<Expression> parseExpressionList(){
		ArrayList<Expression> expressions = new ArrayList<Expression>();
		
		return expressions;
	}
	
	public Expression parseExpressionSimple(){
		Token start = lexer.current();
		
		if(start.getType() == TokenType.IDENTIFIER){
			lexer.next();
			return new IdentifierExpression(start.getData(), null);
		}
		else{
			throw new UnexpectedTokenException(start, TokenType.IDENTIFIER);
		}
	}
	
}
