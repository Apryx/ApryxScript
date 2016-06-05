package language;

import java.util.ArrayList;
import java.util.List;

import statement.ConstantExpression;
import statement.ContextStatement;
import statement.Expression;
import statement.ExpressionStatement;
import statement.IdentifierExpression;
import statement.InvokeExpression;
import statement.LookupExpression;
import statement.OperatorExpression;
import statement.SetExpression;
import tokens.Token;
import tokens.TokenType;
import tokens.UnexpectedTokenException;
import tokens.UnimplementedLanguageFeatureException;
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
		while(!lexer.isDone()){
			parseStatement(context);			
		}
		
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
		else if(current.getType() == TokenType.CURLY_OPEN){
			parseContextStatement(context);
		}
		else{
			throw new UnexpectedTokenException(current, TokenType.IDENTIFIER, TokenType.KEYWORD);
		}
	}
	
	public void parseKeyword(Context context){
		Token currentToken = lexer.current();
		if(currentToken.getType() != TokenType.KEYWORD)
			throw new UnexpectedTokenException(currentToken, TokenType.KEYWORD);
		
		if(currentToken.getData().equals(Language.VAR)){
			Token nameToken = lexer.next();
			if(nameToken.getType() != TokenType.IDENTIFIER)
				throw new UnexpectedTokenException(nameToken, TokenType.IDENTIFIER);
			
			Token operatorToken = lexer.next();
			
			context.addVariable(nameToken.getData());
			
			if(operatorToken.getType() == TokenType.EQUALS){
				//consume equals token
				lexer.next();
				Expression e = parseExpression();
				
				context.addStatement(new ExpressionStatement(new SetExpression(new IdentifierExpression(nameToken.getData()), e)));
			}
			
		}
		
		else if(currentToken.getData().equals(Language.FUNCTION)){
			//TODO implement fully
			
			Token name = lexer.next();
			if(name.getType() != TokenType.IDENTIFIER)
				throw new UnexpectedTokenException(name, TokenType.IDENTIFIER);
			
			//TODO why not change this to no brackets functions, is there somthing against it?
			Token bOpen = lexer.next();
			if(bOpen.getType() != TokenType.BRACKET_OPEN)
				throw new UnexpectedTokenException(name, TokenType.IDENTIFIER);

			if(lexer.next().getType() != TokenType.BRACKET_CLOSE){
				System.out.println("params");
				while(!lexer.isDone()){
					Expression e = parseExpression();
					System.out.println(e);
					if(lexer.current().getType() != TokenType.SEPERATOR)
						break;
					else
						lexer.next();//consume the seperator
				}
			}
			
			if(lexer.current().getType() != TokenType.BRACKET_CLOSE)
				throw new UnexpectedTokenException(lexer.current(), TokenType.BRACKET_CLOSE);
			
			lexer.next();
			
			Context nContext = new Context(context);
			parseStatement(nContext);
			
			System.out.println("body");
			System.out.println(nContext.toJSString());
		}
		
		else{
			throw new UnimplementedLanguageFeatureException();
		}
		
	}
	
	public void parseContextStatement(Context parent){
		if(lexer.current().getType() != TokenType.CURLY_OPEN){
			throw new UnexpectedTokenException(lexer.current(), TokenType.CURLY_OPEN);
		}

		lexer.next();
		Context context = new Context(parent);
		
		while(lexer.current().getType() != TokenType.CURLY_CLOSE){
			parseStatement(context);
		}
		
		//consume
		lexer.next();
		
		parent.addStatement(new ContextStatement(context));
	}
	
	public Expression parseExpression(){
		Expression lhs = parseExpressionSimple();
		
		Token operator = lexer.current();
		
		//operators
		if(operator.getType() == TokenType.BINARYOPERATOR){
			lexer.next();
			Expression rhs = parseExpression();
			
			return new OperatorExpression(lhs,rhs, operator.getData());
		}
		
		//function call
		else if(operator.getType() == TokenType.BRACKET_OPEN){
			//consume the operator
			Token n = lexer.next();
			List<Expression> expressions;
			if(n.getType() != TokenType.BRACKET_CLOSE){
				expressions = parseExpressionList();
				n = lexer.current();
				if(n.getType() != TokenType.BRACKET_CLOSE)
					throw new UnexpectedTokenException(n, TokenType.BRACKET_CLOSE);
				lexer.next();//consume bracket close
			}else{
				expressions = new ArrayList<Expression>();
				lexer.next();//consume bracket close
			}
			
			return new InvokeExpression(lhs, expressions);
		}
		
		return lhs;
	}
	
	public List<Expression> parseExpressionList(){
		ArrayList<Expression> expressions = new ArrayList<Expression>();
		
		Expression exp = parseExpression();
		expressions.add(exp);
		while(lexer.current().getType() == TokenType.SEPERATOR){
			lexer.next();
			exp = parseExpression();
			expressions.add(exp);
		}
		
		return expressions;
	}
	
	/**
	 * Parses a simple expression (ex. a, a.b, etc)
	 * @return
	 */
	public Expression parseExpressionSimple(){
		Token start = lexer.current();
		
		if(start.getType() == TokenType.IDENTIFIER){
			lexer.next();
			Expression lhs = new IdentifierExpression(start.getData());
			if(lexer.current().getType() == TokenType.LOOKUP){
				lexer.next();
				Expression rhs = parseExpressionSimple();
				return new LookupExpression(lhs, rhs);
			}else{
				return lhs;
			}
		}
		else if(start.getType() == TokenType.STRING){
			lexer.next();
			return new ConstantExpression(start.getData(), ConstantExpression.Type.STRING);
		}
		else if(start.getType() == TokenType.INTEGER){
			lexer.next();
			return new ConstantExpression(start.getData(), ConstantExpression.Type.INTEGER);
		}
		
		else{
			throw new UnexpectedTokenException(start, TokenType.IDENTIFIER);
		}
	}
	
}
