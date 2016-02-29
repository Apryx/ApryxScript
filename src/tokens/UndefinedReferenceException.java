package tokens;

public class UndefinedReferenceException extends RuntimeException{
	
	
	private static final long serialVersionUID = 1L;

	public UndefinedReferenceException(String name){
		super(name);
	}
}
