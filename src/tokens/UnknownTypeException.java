package tokens;

public class UnknownTypeException extends RuntimeException{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public UnknownTypeException(String message){
		super("Unknown type for " + message);
	}
}
