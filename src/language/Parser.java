package language;

import java.util.ArrayList;
import java.util.List;

import tokens.Token;
import tokens.TokenType;
import tokens.UnexpectedTokenException;
import tokens.UnimplementedLanguageFeatureException;

public class Parser {
	
	private List<Token> tokens;
	
	public Parser(List<Token> tokens){
		this.tokens = tokens;
	}
	
	public void parse(){
		ArrayList<Token> line = new ArrayList<Token>();
		for(int i = 0; i < tokens.size(); i++){
			line.add(tokens.get(i));
			if(tokens.get(i).getType() == TokenType.LINE_END){
				parseLine(line);
				line.clear();
			}
		}
	}
	
	private void parseLine(List<Token> line){
		//identifiers :D
		if(line.get(0).getType() == TokenType.IDENTIFIER){
			
			//function calls
			if(line.get(1).getType() == TokenType.BRACKET_OPEN){
				System.out.println("Calling function " + line.get(0).getData());
			}
			
			//
		}
		
		//function class and var
		else if(line.get(0).getType() == TokenType.KEYWORD){
			
			//if is a variable
			if(line.get(0).getData().equals(Language.VAR)){
				String name = null;
				String type = null;
			
				if(line.get(1).getType() != TokenType.IDENTIFIER)
					throw new UnexpectedTokenException(line.get(1), TokenType.IDENTIFIER);
				
				name = line.get(1).getData();
				
				//implicit ~ish object typing
				if(line.get(2).getType() == TokenType.LINE_END)
					type = Language.TYPE_OBJECT;
				
				//explicit typing
				else if(line.get(2).getType() == TokenType.COLON){
					
					//if its not an identifier
					if(line.get(3).getType() != TokenType.IDENTIFIER)
						throw new UnexpectedTokenException(line.get(3), TokenType.IDENTIFIER);
					
					type = line.get(3).getData();
				}
				
				//implicit typing
				else if(line.get(2).getType() == TokenType.EQUALS){
					throw new UnimplementedLanguageFeatureException();
				}
				
				else{
					throw new UnexpectedTokenException(line.get(2));
				}
				
				//here we must have the name and type
				
				System.out.println("Got variable " + name + " " + type);
			}
		}
		
		else{
			System.out.println("Unknown token " + line.get(0) + ";");
		}
	}
	
}
