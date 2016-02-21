package language;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import tokens.Token;
import tokens.TokenType;


public class Lexer {
	
	private CharacterProcessor chars;
	
	public Lexer(InputStream stream){
		chars = new CharacterProcessor(stream);
	}

	public List<Token> tokenize() {
		ArrayList<Token> tokens = new ArrayList<Token>();
		
		while(!chars.isDone()){
			char c = chars.current();
						
			//identifier or keyword
			if(Language.isAlphabetic(c)){
				StringBuilder builder = new StringBuilder();
				
				while(Language.isAlphabetic(c) || Language.isDigit(c)){
					builder.append(c);
					c = chars.next();
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
				
				tokens.add(token);
			}
			
			//digit, double, float, long and int // TODO float, double and long
			else if(Language.isDigit(c)){
				StringBuilder builder = new StringBuilder();
				while(Language.isDigit(c)){
					builder.append(c);
					c = chars.next();
				}
				Token token = new Token(TokenType.INTEGER, builder.toString(), chars.getLine());
				tokens.add(token);
			}
			
			//string
			else if(Language.isString(c)){
				StringBuilder builder = new StringBuilder();
				c = chars.next();
				while(!Language.isString(c)){
					builder.append(c);
					c = chars.next();
				}
				Token token = new Token(TokenType.STRING, builder.toString(), chars.getLine());
				tokens.add(token);
				chars.next();
			}
			
			//colons
			else if(Language.isColon(c)){
				Token token = new Token(TokenType.COLON, "" + c, chars.getLine());
				tokens.add(token);
				chars.next();
			}
			
			//equals
			else if(Language.isEquals(c)){
				Token token = new Token(TokenType.EQUALS, "" + c, chars.getLine());
				tokens.add(token);
				chars.next();
			}

			//bracket open
			else if(Language.isBracketOpen(c)){
				Token token = new Token(TokenType.BRACKET_OPEN, "" + c, chars.getLine());
				tokens.add(token);
				chars.next();
			}
			
			//bracket open
			else if(Language.isBracketClose(c)){
				Token token = new Token(TokenType.BRACKET_CLOSE, "" + c, chars.getLine());
				tokens.add(token);
				chars.next();
			}
			
			//curly open
			else if(Language.isCurlyOpen(c)){
				Token token = new Token(TokenType.CURLY_OPEN, "" + c, chars.getLine());
				tokens.add(token);
				chars.next();
			}

			//bracket open
			else if(Language.isCurlyClose(c)){
				Token token = new Token(TokenType.CURLY_CLOSE, "" + c, chars.getLine());
				tokens.add(token);
				chars.next();
			}

			//line ends
			else if(Language.isLineEnd(c)){
				Token token = new Token(TokenType.LINE_END, "" + c, chars.getLine());
				tokens.add(token);
				chars.next();
			}

			//seperators
			else if(Language.isSeperator(c)){
				Token token = new Token(TokenType.SEPERATOR, "" + c, chars.getLine());
				tokens.add(token);
				chars.next();
			}
			
			//multyply and devide
			else if(Language.isMulDiv(c)){
				Token token = new Token(TokenType.MULDIV, "" + c, chars.getLine());
				tokens.add(token);
				chars.next();
			}
			
			//add or subtract
			else if(Language.isPlusMin(c)){
				Token token = new Token(TokenType.PLUSMIN, "" + c, chars.getLine());
				tokens.add(token);
				chars.next();
			}
			
			//whitespace
			else if(Language.isWhitespace(c)){
				//Token token = new Token(TokenType.WHITESPACE, "" + c, chars.getLine());
				//tokens.add(token);
				chars.next();
			}
			
			else{
				System.err.println("Unknown character at " + c + " at line " + chars.getLine());
				chars.next();
			}
			
		}
		
		tokens.add(new Token(TokenType.EOF, "End of file", chars.getLine()));
		
		return tokens;
	}
}
