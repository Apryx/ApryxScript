package tokens;

public class UndeclaredVariableException extends RuntimeException{
	
	
	private static final long serialVersionUID = 1L;

	public UndeclaredVariableException(String name){
		super(name);
	}
}
