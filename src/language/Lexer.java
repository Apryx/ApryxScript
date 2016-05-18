package language;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import tokens.Token;
import tokens.TokenType;


public class Lexer {
	
	private CharacterProcessor chars;
	private Token current;
	
	public Lexer(InputStream stream){
		chars = new CharacterProcessor(stream);
	}
	
	public Token current(){
		return current;
	}
	
	public Token next(){
		current = internalNext();
		return current;
	}
	
	private Token internalNext(){
		
		//identifier or keyword
		if(Language.isAlphabetic(chars.current())){
			StringBuilder builder = new StringBuilder();
			
			while(Language.isAlphabetic(chars.current()) || Language.isDigit(chars.current())){
				builder.append(chars.current());
				chars.next();
			}
			
			String identifier = builder.toString();
			
			Token token;
			
			//keyword
			if(Language.isKeyword(identifier)){
				token = new Token(TokenType.KEYWORD, identifier, chars.getLine());	
			}
			
			//identifier
			else{
				token = new Token(TokenType.IDENTIFIER, identifier, chars.getLine());				
			}
			
			return token;
		}
		
		//digit, double, float, long and int // TODO float, double and long
		else if(Language.isDigit(chars.current())){
			StringBuilder builder = new StringBuilder();
			while(Language.isDigit(chars.current())){
				builder.append(chars.current());
				chars.next();
			}
			Token token = new Token(TokenType.INTEGER, builder.toString(), chars.getLine());
			
			return token;
		}
		
		//string
		else if(Language.isString(chars.current())){
			StringBuilder builder = new StringBuilder();
			chars.next();
			while(!Language.isString(chars.current()) && !chars.isDone()){
				builder.append(chars.current());
				chars.next();
			}
			chars.next();
			Token token = new Token(TokenType.STRING, builder.toString(), chars.getLine());
			
			return token;
		}
		
		//colons
		else if(Language.isColon(chars.current())){
			Token token = new Token(TokenType.COLON, "" + chars.current(), chars.getLine());
			chars.next();
			return token;
		}
		
		//equals
		else if(Language.isEquals(chars.current())){
			Token token;
			if(Language.isEquals(chars.next())){
				token = new Token(TokenType.BOOLEANOPERATOR, "==", chars.getLine());
			}else{
				token = new Token(TokenType.EQUALS, "" + chars.current(), chars.getLine());
			}
			return token;
		}

		//bracket open
		else if(Language.isBracketOpen(chars.current())){
			Token token = new Token(TokenType.BRACKET_OPEN, "" + chars.current(), chars.getLine());
			chars.next();
			return token;
		}
		
		//bracket open
		else if(Language.isBracketClose(chars.current())){
			Token token = new Token(TokenType.BRACKET_CLOSE, "" + chars.current(), chars.getLine());
			chars.next();
			return token;
		}
		
		//curly open
		else if(Language.isCurlyOpen(chars.current())){
			Token token = new Token(TokenType.CURLY_OPEN, "" + chars.current(), chars.getLine());
			chars.next();
			return token;
		}

		//bracket open
		else if(Language.isCurlyClose(chars.current())){
			Token token = new Token(TokenType.CURLY_CLOSE, "" + chars.current(), chars.getLine());
			chars.next();
			return token;
		}

		//line ends
		else if(Language.isLineEnd(chars.current())){
			Token token = new Token(TokenType.LINE_END, "" + chars.current(), chars.getLine());
			chars.next();
			return token;
		}

		//seperators
		else if(Language.isSeperator(chars.current())){
			Token token = new Token(TokenType.SEPERATOR, "" + chars.current(), chars.getLine());
			chars.next();
			return token;
		}
		
		//multyply and devide
		//add or subtract
		else if(Language.isMulDiv(chars.current()) || Language.isPlusMin(chars.current())){
			Token token = new Token(TokenType.BINARYOPERATOR, "" + chars.current(), chars.getLine());
			chars.next();
			return token;
		}
		else if(Language.isLookup(chars.current())){
			Token token = new Token(TokenType.LOOKUP, "" + chars.current(), chars.getLine());
			chars.next();
			return token;
		}

		//boolean operators
		else if(Language.isBooleanOperator(chars.current())){
			Token token = new Token(TokenType.BOOLEANOPERATOR, "" + chars.current(), chars.getLine());
			chars.next();
			return token;
		}

		//whitespace
		else if(Language.isWhitespace(chars.current())){
			while(Language.isWhitespace(chars.current())){
				chars.next();
			}
			
			//call the next next :)
			return next();
		}
		
		else{
			System.err.println("Unknown character at " + chars.current() + " at line " + chars.getLine());
			//What to do with the current here?
			chars.next();
			
			return next();
		}
	}
	
	public boolean isDone(){
		return chars.isDone();
	}

	public List<Token> tokenize() {
		ArrayList<Token> tokens = new ArrayList<Token>();
		
		while(!isDone()){
			tokens.add(next());
		}
		
		tokens.add(new Token(TokenType.EOF, "End of file", chars.getLine()));
		
		return tokens;
	}
}
