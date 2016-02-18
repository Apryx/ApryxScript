package statement;

public class IdentifierExpression extends Expression{

	private String name;
	
	public IdentifierExpression(String name, String type) {
		super(type);
		this.name = name;
	}
	
	public String getName() {
		return name;
	}

}
