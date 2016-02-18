package language;

import java.util.List;

import tokens.Token;
import tokens.TokenType;

public class TokenProcessor {
	
	private int index;
	private Token current;
	private List<Token> tokens;
	
	public TokenProcessor(List<Token> tokens){
		this.tokens = tokens;
		index = -1;
		next();
	}
	
	public Token next(){
		index++;
		
		if(index >= tokens.size()){
			current = tokens.get(tokens.size() - 1);
			return current;
		}
		
		current = tokens.get(index);
		return current;
	}
	
	public boolean isDone(){
		return current.getType() == TokenType.EOF;
	}
	
	public Token current(){
		return current;
	}
}
