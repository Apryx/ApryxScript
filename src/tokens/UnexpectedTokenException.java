package tokens;

public class UnexpectedTokenException extends RuntimeException{
	
	private static final long serialVersionUID = 1L;

	public UnexpectedTokenException(Token got, TokenType expected){
		super("Unexpected " + got.getType() + " at line " + got.getLine() + ". Expected : "+ expected);
	}
	
	public UnexpectedTokenException(Token got){
		super("Unexpected " + got.getType() + " at line " + got.getLine());
	}
}
