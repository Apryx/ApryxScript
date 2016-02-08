package tokens;

public class Token {
	
	private final TokenType type;
	private final String data;
	private final int line;
	
	public Token(TokenType type, String data, int line){
		this.type = type;
		this.data = data;
		this.line = line;
	}
	
	public String getData() {
		return data;
	}
	
	public int getLine() {
		return line;
	}
	
	public TokenType getType() {
		return type;
	}
	
	public String toString(){
		return line + " " + type.toString() + " " + data;
	}
}
